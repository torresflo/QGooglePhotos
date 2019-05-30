#include <QJsonObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QNetworkReply>

#include <GooglePhotos/UrlBuilder/UrlBuilder.hpp>
#include <GooglePhotos/QLibraryClient.hpp>
#include <GooglePhotos/QMediaItem.hpp>

namespace GooglePhotos
{

QMediaItem::~QMediaItem()
{}

const QImage& QMediaItem::getPreview() const
{
    return m_preview;
}

const QString& QMediaItem::getIdentifier() const
{
    return m_identifier;
}

const QString& QMediaItem::getDescription() const
{
    return m_description;
}

const QString& QMediaItem::getProductUrl() const
{
    return m_productUrl;
}

const QString& QMediaItem::getBaseUrl() const
{
    return m_baseUrl;
}

const QString& QMediaItem::getMimeType() const
{
    return m_mimeType;
}

const QString& QMediaItem::getFileName() const
{
    return m_fileName;
}

const QDateTime& QMediaItem::getCreationDateTime() const
{
    return m_creationDateTime;
}

int QMediaItem::getWidth() const
{
    return m_width;
}

int QMediaItem::getHeight() const
{
    return m_height;
}

void QMediaItem::downloadPreview()
{
    UrlPhotoSettings settings = UrlPhotoSettings::buildMediaItemPreviewSettings(m_baseUrl);
    downloadImage(settings);
}

bool QMediaItem::isPreviewAvailable() const
{
    return !m_preview.isNull();
}

QMediaItem::QMediaItem(const QJsonObject& jsonObject, QLibraryClient* parent)
    :QLibraryItemDownloader (parent)
{
    m_identifier = jsonObject["id"].toString();
    m_description = jsonObject["description"].toString();
    m_productUrl = jsonObject["productUrl"].toString();
    m_baseUrl = jsonObject["baseUrl"].toString();
    m_mimeType = jsonObject["mimeType"].toString();
    m_fileName = jsonObject["filename"].toString();

    const QJsonObject& mediaMetadataObject = jsonObject["mediaMetadata"].toObject();
    const QString& dataTimeString = mediaMetadataObject["creationTime"].toString();
    m_creationDateTime = QDateTime::fromString(dataTimeString, Qt::DateFormat::ISODate);
    m_width = mediaMetadataObject["width"].toString().toInt();
    m_height = mediaMetadataObject["height"].toString().toInt();
}

void QMediaItem::onImageAvailable(const QImage& image)
{
    m_preview = image;
    emit previewAvailable();
}

} //namespace GooglePhotos
