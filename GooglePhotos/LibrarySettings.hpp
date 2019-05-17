#ifndef AUTHENTIFICATIONSETTINGS_HPP
#define AUTHENTIFICATIONSETTINGS_HPP

#include <QUrl>

class QString;
class QOAuth2AuthorizationCodeFlow;

namespace GooglePhotos
{

class LibrarySettings
{
public:
    LibrarySettings();
    LibrarySettings(const QString& fileName);

    bool initFromJsonFile(const QString& fileName);
    void fillAuthorizationCodeFlow(QOAuth2AuthorizationCodeFlow* authorizationCodeFlow);

    const QUrl& getAuthorizationUrl() const;
    void setAuthorizationUrl(const QUrl& authorizationUrl);

    const QString& getClientIdentifier() const;
    void setClientIdentifier(const QString& clientIdentifier);

    const QUrl& getAccessTokenUrl() const;
    void setAccessTokenUrl(const QUrl& accessTokenUrl);

    const QString& getClientIdentifierSharedKey() const;
    void setClientIdentifierSharedKey(const QString& clientIdentifierSharedKey);

    const QUrl& getFirstRedirectUrl() const;
    void setFirstRedirectUrl(const QUrl& firstRedirectUrl);

    quint16 getRedirectUrlPort() const;
    void setRedirectUrlPort(const quint16& redirectUrlPort);

    bool isValid() const;

private:
    QUrl m_authorizationUrl;
    QString m_clientIdentifier;
    QUrl m_accessTokenUrl;
    QString m_clientIdentifierSharedKey;
    QUrl m_firstRedirectUrl;
    quint16 m_redirectUrlPort = 0;
};

} //namespace GooglePhotos

#endif // AUTHENTIFICATIONSETTINGS_HPP
