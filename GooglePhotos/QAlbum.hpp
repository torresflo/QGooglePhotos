#ifndef GOOGLEPHOTOSALBUM_HPP
#define GOOGLEPHOTOSALBUM_HPP

#include <QObject>

#include <QImage>
#include <QString>
#include <QUrl>

#include <QVector>

#include <GooglePhotos/QLibraryItemDownloader.hpp>

class QJsonObject;
class QOAuth2AuthorizationCodeFlow;

namespace GooglePhotos
{

class QLibraryClient;
class QMediaItem;

class QAlbum : public QLibraryItemDownloader
{
    Q_OBJECT
public:
    QAlbum(const QJsonObject& jsonObject, QLibraryClient* parent);

    const QImage& getCoverImage() const;
    const QString& getIdentifier() const;
    const QString& getTitle() const;
    const QUrl& getProductUrl() const;
    const QUrl& getCoverPhotoBaseUrl() const;
    const QString& getCoverPhotoMediaItemIdentifier() const;
    bool getIsWriteable() const;
    int getTotalMediaItemsCount() const;

    bool isCoverImageAvailable() const;
    void downloadCoverImage();

    void downloadMediaItemsData();
    const QVector<QMediaItem*>& getMediaItems() const; //TODO Add iterators?

protected:
    void onImageAvailable(const QImage& image) override;
    void onJsonAvailable(const QJsonDocument& json) override;

private:
    QImage m_coverImage;
    QString m_identifier;
    QString m_title;
    QUrl m_productUrl;
    QUrl m_coverPhotoBaseUrl;
    QString m_coverPhotoMediaItemIdentifier;
    bool m_isWriteable = false;
    int m_totalMediaItemsCount = -1;

    QVector<QMediaItem*> m_mediaItems;

signals:
    void coverImageAvailable();
    void mediaItemsDataAvailable(int minRange);
};

} //namespace GooglePhotos

#endif // GOOGLEPHOTOSALBUM_HPP
