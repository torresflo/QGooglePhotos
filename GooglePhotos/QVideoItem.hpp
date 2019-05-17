#ifndef QGOOGLEPHOTOSVIDEOITEM_HPP
#define QGOOGLEPHOTOSVIDEOITEM_HPP

#include <QString>

#include <GooglePhotos/QMediaItem.hpp>

namespace GooglePhotos
{

class QLibraryClient;

class QVideoItem : public QMediaItem
{
public:
    QVideoItem(const QJsonObject& jsonObject, QLibraryClient* parent);

    const QString& getCameraMake() const;
    const QString& getCameraModel() const;
    double getFps() const;
    const QString& getStatus() const;

private:
    QString m_cameraMake;
    QString m_cameraModel;
    double m_fps;
    QString m_status;
};

} //namespace GooglePhotos

#endif // QGOOGLEPHOTOSVIDEOITEM_HPP
