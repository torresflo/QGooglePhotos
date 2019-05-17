#include <QOAuth2AuthorizationCodeFlow>

#include <QImage>
#include <QJsonDocument>

#include <GooglePhotos/UrlBuilder/UrlBuilder.hpp>
#include <GooglePhotos/UrlBuilder/UrlPhotoSettings.hpp>
#include <GooglePhotos/QLibraryItemDownloader.hpp>

#include <GooglePhotos/QLibraryClient.hpp>

namespace GooglePhotos
{

QLibraryItemDownloader::QLibraryItemDownloader(QLibraryClient* parent) : QObject(parent)
{}

QLibraryClient* QLibraryItemDownloader::getLibraryClient() const
{
    return static_cast<QLibraryClient*>(parent());
}

void QLibraryItemDownloader::downloadImage(const UrlPhotoSettings& settings)
{
    QUrl url = UrlBuilder::buildGetPhotoUrl(settings);
    QOAuth2AuthorizationCodeFlow* authorizationCodeFlow = getLibraryClient()->getAuthorizationCodeFlow();
    QNetworkReply* reply = authorizationCodeFlow->get(url);

    m_networkReplyList.append(reply);
    connect(reply, &QNetworkReply::finished, this, &QLibraryItemDownloader::onImageRequestFinished);
}

void QLibraryItemDownloader::downloadJson(const QUrl url, const QJsonObject& dataToPost)
{
    m_lastJsonUrl = url;
    m_lastDataToPost = dataToPost;
    m_nextPageToken.clear();

    QOAuth2AuthorizationCodeFlow* authorizationCodeFlow = getLibraryClient()->getAuthorizationCodeFlow();
    QJsonDocument jsonDocument(dataToPost);
    QNetworkReply* reply = authorizationCodeFlow->post(url, jsonDocument.toJson());

    m_networkReplyList.append(reply);
    connect(reply, &QNetworkReply::finished, this, &QLibraryItemDownloader::onJsonRequestFinished);
}

bool QLibraryItemDownloader::hasNextPageToDownload() const
{
    return !m_nextPageToken.isEmpty();
}

void QLibraryItemDownloader::downloadNextJsonPage()
{
    if(hasNextPageToDownload())
    {
        QJsonObject dataToPost = m_lastDataToPost;
        dataToPost.insert("pageToken", m_nextPageToken);
        downloadJson(m_lastJsonUrl, dataToPost);
    }
}

void QLibraryItemDownloader::onImageAvailable(const QImage& image)
{
    Q_UNUSED(image);
}

void QLibraryItemDownloader::onJsonAvailable(const QJsonDocument& jsonDocument)
{
    Q_UNUSED(jsonDocument);
}

PaginationMode QLibraryItemDownloader::getPaginationMode() const
{
    return m_paginationMode;
}

void QLibraryItemDownloader::setPaginationMode(const PaginationMode& paginationMode)
{
    m_paginationMode = paginationMode;
}

void QLibraryItemDownloader::abortAllRequests()
{
    for(QNetworkReply* reply : m_networkReplyList)
    {
        reply->abort();
    }
    m_networkReplyList.clear();
}

void QLibraryItemDownloader::onRequestFinished(QNetworkReply* networkReply, QByteArray& result)
{
    if(networkReply->error() == QNetworkReply::NoError)
    {
        result = networkReply->readAll();
        emit requestSucceded(result);
    }
    else
    {
        emit requestFailed(networkReply->error());
    }
}

void QLibraryItemDownloader::onImageRequestFinished()
{
    QByteArray data;
    QNetworkReply* networkReply = static_cast<QNetworkReply*>(sender());
    onRequestFinished(networkReply, data);

    if(!data.isNull())
    {
        const QImage& image = QImage::fromData(data);
        onImageAvailable(image);
    }

    bool isRemoved = m_networkReplyList.removeOne(networkReply);
    Q_ASSERT_X(isRemoved, "QLibraryItemDownloader::onImageRequestFinished", "Network reply not found. This must not happen.");
}

void QLibraryItemDownloader::onJsonRequestFinished()
{
    QByteArray data;
    QNetworkReply* networkReply = static_cast<QNetworkReply*>(sender());
    onRequestFinished(networkReply, data);

    if(!data.isNull())
    {
        const QJsonDocument& jsonDocument = QJsonDocument::fromJson(data);
        onJsonAvailable(jsonDocument);

        m_nextPageToken = jsonDocument["nextPageToken"].toString();
        if(m_paginationMode == PaginationMode::Automatic)
        {
            downloadNextJsonPage();
        }
        else if(m_paginationMode == PaginationMode::Manual
                && !m_nextPageToken.isEmpty())
        {
            emit nextPageTokenAvailable(m_nextPageToken);
        }
    }

    bool isRemoved = m_networkReplyList.removeOne(networkReply);
    Q_ASSERT_X(isRemoved, "QLibraryItemDownloader::onJsonRequestFinished", "Network reply not found. This must not happen.");
}

}
