#include <QJsonObject>

#include <GooglePhotos/UrlBuilder/UrlPhotoSettings.hpp>

#include <GooglePhotos/QPhotoItem.hpp>

namespace GooglePhotos
{

QPhotoItem::QPhotoItem(const QJsonObject& jsonObject, QLibraryClient* parent)
    :QMediaItem (jsonObject, parent)
{
    const QJsonObject& mediaMetadataObject = jsonObject["mediaMetada"].toObject();
    const QJsonObject& photoObject = mediaMetadataObject["photo"].toObject();
    m_cameraMake = photoObject["cameraMake"].toString();
    m_cameraModel = photoObject["cameraModel"].toString();
    m_focalLenght = photoObject["focalLength"].toDouble();
    m_apertureNumber = photoObject["apertureNumber"].toDouble();
    m_isoEquivalent = photoObject["isoEquivalent"].toDouble();
    m_exposureTime = photoObject["exposureTime"].toString();
}

const QImage& QPhotoItem::getPhoto() const
{
    return m_photo;
}

const QString& QPhotoItem::getCameraMake() const
{
    return m_cameraMake;
}

const QString& QPhotoItem::getCameraModel() const
{
    return m_cameraModel;
}

double QPhotoItem::getFocalLenght() const
{
    return m_focalLenght;
}

double QPhotoItem::getApertureNumber() const
{
    return m_apertureNumber;
}

double QPhotoItem::getIsoEquivalent() const
{
    return m_isoEquivalent;
}

const QString& QPhotoItem::getExposureTime() const
{
    return m_exposureTime;
}

void QPhotoItem::downloadPhoto()
{
    UrlPhotoSettings settings = UrlPhotoSettings::buildPhotoItemFullImageSettings(m_baseUrl);
    downloadImage(settings);
}

bool QPhotoItem::isPhotoAvailable() const
{
    return !m_photo.isNull();
}

void QPhotoItem::onImageAvailable(const QImage& image)
{
    if(image.width() == getWidth() //TODO Find a better way to identify who started the download
       && image.height() == getHeight())
    {
        m_photo = image;
        emit photoAvailable();
    }
    else
    {
        QMediaItem::onImageAvailable(image);
    }
}

} //namespace GooglePhotos
