#ifndef QMEDIAITEMDOWNLOADER_HPP
#define QMEDIAITEMDOWNLOADER_HPP

#include <QObject>
#include <QNetworkReply>
#include <QJsonObject>

namespace GooglePhotos
{

class QLibraryClient;
class UrlPhotoSettings;

enum class PaginationMode
{
    None = -1,
    Automatic,
    Manual
};

class QLibraryItemDownloader : public QObject
{
    Q_OBJECT
public:
    QLibraryItemDownloader(QLibraryClient* parent = nullptr);

    PaginationMode getPaginationMode() const;
    void setPaginationMode(const PaginationMode& paginationMode);

    void abortAllRequests();

protected:
    QLibraryClient* getLibraryClient() const;

    void downloadImage(const UrlPhotoSettings& settings);
    void downloadJson(const QUrl url, const QJsonObject& dataToPost);

    void downloadNextJsonPage();
    bool hasNextPageToDownload() const;

    virtual void onImageAvailable(const QImage& image);
    virtual void onJsonAvailable(const QJsonDocument& jsonDocument);

private:
    PaginationMode m_paginationMode = PaginationMode::None;
    QUrl m_lastJsonUrl;
    QJsonObject m_lastDataToPost;
    QString m_nextPageToken;

    QList<QNetworkReply*> m_networkReplyList;

    void onRequestFinished(QNetworkReply* networkReply, QByteArray& result);
    void onImageRequestFinished();
    void onJsonRequestFinished();

signals:
    void requestSucceded(const QByteArray& data);
    void requestFailed(QNetworkReply::NetworkError error);
    void nextPageTokenAvailable(const QString& nextPageToken);
};

}

#endif // QMEDIAITEMDOWNLOADER_HPP
