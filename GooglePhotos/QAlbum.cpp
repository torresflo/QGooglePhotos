#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTransform>

#include <QString>
#include <QObject>

#include <QNetworkReply>
#include <QOAuth2AuthorizationCodeFlow>

#include <GooglePhotos/UrlBuilder/UrlBuilder.hpp>
#include <GooglePhotos/QLibraryClient.hpp>
#include <GooglePhotos/QPhotoItem.hpp>
#include <GooglePhotos/QVideoItem.hpp>
#include <GooglePhotos/QAlbum.hpp>

namespace GooglePhotos
{

QAlbum::QAlbum(const QJsonObject& jsonObject, QLibraryClient* parent)
    :QLibraryItemDownloader (parent)
{
    m_identifier = jsonObject["id"].toString();
    m_title = jsonObject["title"].toString();
    m_productUrl = jsonObject["productUrl"].toString();
    m_coverPhotoBaseUrl = jsonObject["coverPhotoBaseUrl"].toString();
    m_coverPhotoMediaItemIdentifier = jsonObject["coverPhotoMediaItemId"].toString();
    m_isWriteable = jsonObject["isWriteable"].toBool();
    m_totalMediaItemsCount = jsonObject["mediaItemsCount"].toString().toInt();
}

const QImage& QAlbum::getCoverImage() const
{
    return m_coverImage;
}

const QString& QAlbum::getIdentifier() const
{
    return m_identifier;
}

const QString& QAlbum::getTitle() const
{
    return m_title;
}

const QUrl& QAlbum::getProductUrl() const
{
    return m_productUrl;
}

const QUrl& QAlbum::getCoverPhotoBaseUrl() const
{
    return m_coverPhotoBaseUrl;
}

const QString& QAlbum::getCoverPhotoMediaItemIdentifier() const
{
    return m_coverPhotoMediaItemIdentifier;
}

bool QAlbum::getIsWriteable() const
{
    return m_isWriteable;
}

int QAlbum::getTotalMediaItemsCount() const
{
    return m_totalMediaItemsCount;
}

bool QAlbum::isCoverImageAvailable() const
{
    return !m_coverImage.isNull();
}

void QAlbum::downloadCoverImage()
{
    const UrlPhotoSettings& settings = UrlPhotoSettings::buildAlbumCoverSettings(m_coverPhotoBaseUrl);
    downloadImage(settings);
}

void QAlbum::downloadMediaItemsData()
{
    m_mediaItems.clear();
    m_mediaItems.reserve(m_totalMediaItemsCount);

    QUrl url = UrlBuilder::buildGetAlbumPhotosUrl();
    QJsonObject data;
    data.insert("albumId", m_identifier);

    downloadJson(url, data);
}

const QVector<QMediaItem*>& QAlbum::getMediaItems() const
{
    return m_mediaItems;
}

void QAlbum::onImageAvailable(const QImage& image)
{
    m_coverImage = image;
    emit coverImageAvailable();
}

void QAlbum::onJsonAvailable(const QJsonDocument& json)
{
    const QJsonArray& mediaItems = json["mediaItems"].toArray();
    int currentCountItems = m_mediaItems.count();

    for(int i = 0; i < mediaItems.count(); ++i)
    {
        const QJsonObject& mediaItem = mediaItems[i].toObject();
        const QJsonObject& mediaMetadata = mediaItem["mediaMetadata"].toObject();
        if(mediaMetadata.find("photo") != mediaMetadata.end())
        {
            m_mediaItems.push_back(new QPhotoItem(mediaItem, getLibraryClient()));
        }
        else if(mediaMetadata.find("video") != mediaMetadata.end())
        {
            m_mediaItems.push_back(new QVideoItem(mediaItem, getLibraryClient()));
        }
    }

    emit mediaItemsDataAvailable(currentCountItems);
}

} //namespace GooglePhotos
