#ifndef QGOOGLEPHOTOSPHOTOITEM_HPP
#define QGOOGLEPHOTOSPHOTOITEM_HPP

#include <QImage>

#include <GooglePhotos/QMediaItem.hpp>

namespace GooglePhotos
{

class QLibraryClient;

class QPhotoItem : public QMediaItem
{
public:
    QPhotoItem(const QJsonObject& jsonObject, QLibraryClient* parent);

    const QString& getCameraMake() const;
    const QString& getCameraModel() const;
    double getFocalLenght() const;
    double getApertureNumber() const;
    double getIsoEquivalent() const;
    const QString& getExposureTime() const;

private:
    QString m_cameraMake;
    QString m_cameraModel;
    double m_focalLenght;
    double m_apertureNumber;
    double m_isoEquivalent;
    QString m_exposureTime; //TODO need to be transformed in a timed value
};

} //namespace GooglePhotos

#endif // QGOOGLEPHOTOSPHOTOITEM_HPP
