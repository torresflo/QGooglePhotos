#ifndef QGOOGLEPHOTOSMEDIAITEM_HPP
#define QGOOGLEPHOTOSMEDIAITEM_HPP

#include <QDateTime>
#include <QString>
#include <QImage>
#include <QObject>

#include <GooglePhotos/QLibraryItemDownloader.hpp>

class QJsonObject;
class QOAuth2AuthorizationCodeFlow;

namespace GooglePhotos
{

class QLibraryClient;

class QMediaItem : public QLibraryItemDownloader
{
    Q_OBJECT
public:
    virtual ~QMediaItem() override = 0;

    const QImage& getPreview() const;
    const QString& getIdentifier() const;
    const QString& getDescription() const;
    const QString& getProductUrl() const;
    const QString& getBaseUrl() const;
    const QString& getMimeType() const;
    const QString& getFileName() const;
    const QDateTime& getCreationDateTime() const;
    int getWidth() const;
    int getHeight() const;

    void downloadPreview();
    bool isPreviewAvailable() const;

protected:
    QMediaItem(const QJsonObject& jsonObject, QLibraryClient* parent);

    void onImageAvailable(const QImage& image) override;

    QImage m_preview;
    QString m_identifier;
    QString m_description;
    QString m_productUrl;
    QString m_baseUrl;
    QString m_mimeType;
    QString m_fileName;
    QDateTime m_creationDateTime;
    int m_width;
    int m_height;

signals:
    void previewAvailable();
};

} //namespace GooglePhotos

#endif // QGOOGLEPHOTOSMEDIAITEM_HPP
