#include <QOAuthHttpServerReplyHandler>
#include <QOAuth2AuthorizationCodeFlow>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QDesktopServices>
#include <QEventLoop>
#include <QTimer>

#include <GooglePhotos/UrlBuilder/UrlBuilder.hpp>
#include <GooglePhotos/QMediaItem.hpp>
#include <GooglePhotos/QLibraryClient.hpp>

namespace GooglePhotos
{

QLibraryClient::QLibraryClient(const LibrarySettings& settings, QObject* parent)
    :QObject (parent)
{
    initialize(settings);
}

bool QLibraryClient::isSettingsValid() const
{
    return m_librarySettings.isValid();
}

bool QLibraryClient::isAccessGranted() const
{
    return m_authorizationCodeFlow->status() == QAbstractOAuth::Status::Granted;
}

const QVector<QAlbum*>& QLibraryClient::getAlbums()
{
    return m_albums;
}

QOAuth2AuthorizationCodeFlow* QLibraryClient::getAuthorizationCodeFlow() const
{
    return m_authorizationCodeFlow;
}

void QLibraryClient::tryConnect()
{
    m_authorizationCodeFlow->grant();
}

void QLibraryClient::retrieveAlbumsInformation()
{
    QNetworkReply* reply = m_authorizationCodeFlow->get(UrlBuilder::buildGetAlbumsUrl());
    QObject::connect(reply, &QNetworkReply::finished, this, &QLibraryClient::onAlbumsInformationReceived);
}

void QLibraryClient::initialize(const LibrarySettings& settings)
{
    m_librarySettings = settings;
    m_serverReplyHandler = new QOAuthHttpServerReplyHandler(m_librarySettings.getRedirectUrlPort(), this);

    m_authorizationCodeFlow = new QOAuth2AuthorizationCodeFlow(this);
    m_authorizationCodeFlow->setScope("https://www.googleapis.com/auth/photoslibrary.readonly");
    m_authorizationCodeFlow->setReplyHandler(m_serverReplyHandler);
    m_authorizationCodeFlow->setContentType(QAbstractOAuth::ContentType::Json);
    m_librarySettings.fillAuthorizationCodeFlow(m_authorizationCodeFlow);


    connect(m_authorizationCodeFlow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, [=](QUrl url)
    {
        QUrlQuery query(url);
        query.addQueryItem("prompt", "consent");      // Param required to get data everytime
        query.addQueryItem("access_type", "offline"); // Needed for Refresh Token (as AccessToken expires shortly)
        url.setQuery(query);

        QDesktopServices::openUrl(url);
    });
    connect(m_authorizationCodeFlow, &QOAuth2AuthorizationCodeFlow::granted, this, &QLibraryClient::authentificationSuccessed);
    connect(m_authorizationCodeFlow, &QOAuth2AuthorizationCodeFlow::requestFailed, this, &QLibraryClient::authentificationFailed);
    connect(m_authorizationCodeFlow, &QOAuth2AuthorizationCodeFlow::error, this, &QLibraryClient::error);
}

void QLibraryClient::onAlbumsInformationReceived()
{
    QNetworkReply* networkReply = static_cast<QNetworkReply*>(sender());
    if (networkReply->error() == QNetworkReply::NoError)
    {
        //TODO Need to flush albums and delete elements here
        QJsonDocument document = QJsonDocument::fromJson(networkReply->readAll());
        const QJsonArray& albumsData = document["albums"].toArray();

        for(int i = 0; i < albumsData.count(); i++)
        {
            const QJsonObject& albumData = albumsData.at(i).toObject();
            m_albums.push_back(new QAlbum(albumData, this));
            m_albums.at(i)->downloadCoverImage();
        }

        emit albumsInformationAvailable();
    }
}

} //namespace GooglePhotos
