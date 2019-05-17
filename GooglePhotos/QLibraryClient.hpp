#ifndef GOOGLEPHOTOSLIBRARYCLIENT_HPP
#define GOOGLEPHOTOSLIBRARYCLIENT_HPP

#include <QObject>
#include <QAbstractOAuth>
#include <QVector>

#include <GooglePhotos/LibrarySettings.hpp>
#include <GooglePhotos/QAlbum.hpp>

class QOAuth2AuthorizationCodeFlow;
class QOAuthHttpServerReplyHandler;

namespace GooglePhotos
{

class QLibraryClient : public QObject
{
    Q_OBJECT
public:
    QLibraryClient(const LibrarySettings& settings, QObject* parent = nullptr);

    bool isSettingsValid() const;
    bool isAccessGranted() const;

    const QVector<QAlbum*>& getAlbums();

    QOAuth2AuthorizationCodeFlow* getAuthorizationCodeFlow() const;

public slots:
    void tryConnect();
    void retrieveAlbumsInformation();

private:
    void initialize(const LibrarySettings& settings);
    void onAlbumsInformationReceived();

    LibrarySettings m_librarySettings;
    QOAuth2AuthorizationCodeFlow* m_authorizationCodeFlow = nullptr;
    QOAuthHttpServerReplyHandler* m_serverReplyHandler = nullptr;

    QVector<QAlbum*> m_albums;

signals:
    void authentificationSuccessed();
    void authentificationFailed(QAbstractOAuth::Error error);
    void albumsInformationAvailable();
};

} //namespace GooglePhotos

#endif // GOOGLEPHOTOSLIBRARYCLIENT_HPP
