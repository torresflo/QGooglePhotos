#include <QJsonObject>

#include <GooglePhotos/QVideoItem.hpp>

namespace GooglePhotos
{

QVideoItem::QVideoItem(const QJsonObject& jsonObject, QLibraryClient* parent)
    :QMediaItem (jsonObject, parent)
{
    const QJsonObject& mediaMetadataObject = jsonObject["mediaMetada"].toObject();
    const QJsonObject& videoObject = mediaMetadataObject["video"].toObject();
    m_cameraMake = videoObject["cameraMake"].toString();
    m_cameraModel = videoObject["cameraModel"].toString();
    m_fps = videoObject["fps"].toDouble();
    m_status = videoObject["status"].toString();
}

const QString& QVideoItem::getCameraMake() const
{
    return m_cameraMake;
}

const QString& QVideoItem::getCameraModel() const
{
    return m_cameraModel;
}

double QVideoItem::getFps() const
{
    return m_fps;
}

const QString& QVideoItem::getStatus() const
{
    return m_status;
}

} //namespace GooglePhotos
