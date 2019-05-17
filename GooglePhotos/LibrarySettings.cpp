#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QString>

#include <GooglePhotos/LibrarySettings.hpp>

namespace GooglePhotos
{

LibrarySettings::LibrarySettings()
{}

LibrarySettings::LibrarySettings(const QString& fileName)
{
    initFromJsonFile(fileName);
}

bool LibrarySettings::initFromJsonFile(const QString& fileName)
{
    QFile fileToLoad(fileName);
    if(!fileToLoad.open(QIODevice::ReadOnly))
    {
        qCritical("Cannot open the authentification settings file provided.");
        return false;
    }

    QByteArray jsonData = fileToLoad.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);

    const QJsonObject& jsonObject = jsonDocument.object();
    const QJsonObject& settingsObject = jsonObject["web"].toObject();
    setAuthorizationUrl(settingsObject["auth_uri"].toString());
    setClientIdentifier(settingsObject["client_id"].toString());
    setAccessTokenUrl(settingsObject["token_uri"].toString());
    setClientIdentifierSharedKey(settingsObject["client_secret"].toString());
    const QJsonArray& redirectUrls = settingsObject["redirect_uris"].toArray();
    setFirstRedirectUrl(redirectUrls[0].toString());
    setRedirectUrlPort(static_cast<quint16>(getFirstRedirectUrl().port()));

    return true;
}

void LibrarySettings::fillAuthorizationCodeFlow(QOAuth2AuthorizationCodeFlow* authorizationCodeFlow)
{
    authorizationCodeFlow->setAuthorizationUrl(getAuthorizationUrl());
    authorizationCodeFlow->setClientIdentifier(getClientIdentifier());
    authorizationCodeFlow->setAccessTokenUrl(getAccessTokenUrl());
    authorizationCodeFlow->setClientIdentifierSharedKey(getClientIdentifierSharedKey());
}

const QUrl& LibrarySettings::getAuthorizationUrl() const
{
    return m_authorizationUrl;
}

void LibrarySettings::setAuthorizationUrl(const QUrl& authorizationUrl)
{
    m_authorizationUrl = authorizationUrl;
}

const QString& LibrarySettings::getClientIdentifier() const
{
    return m_clientIdentifier;
}

void LibrarySettings::setClientIdentifier(const QString& clientIdentifier)
{
    m_clientIdentifier = clientIdentifier;
}

const QUrl& LibrarySettings::getAccessTokenUrl() const
{
    return m_accessTokenUrl;
}

void LibrarySettings::setAccessTokenUrl(const QUrl& accessTokenUrl)
{
    m_accessTokenUrl = accessTokenUrl;
}

const QString& LibrarySettings::getClientIdentifierSharedKey() const
{
    return m_clientIdentifierSharedKey;
}

void LibrarySettings::setClientIdentifierSharedKey(const QString& clientIdentifierSharedKey)
{
    m_clientIdentifierSharedKey = clientIdentifierSharedKey;
}

const QUrl& LibrarySettings::getFirstRedirectUrl() const
{
    return m_firstRedirectUrl;
}

void LibrarySettings::setFirstRedirectUrl(const QUrl& firstRedirectUrl)
{
    m_firstRedirectUrl = firstRedirectUrl;
}

quint16 LibrarySettings::getRedirectUrlPort() const
{
    return m_redirectUrlPort;
}

void LibrarySettings::setRedirectUrlPort(const quint16& redirectUrlPort)
{
    m_redirectUrlPort = redirectUrlPort;
}

bool LibrarySettings::isValid() const
{
    return getAuthorizationUrl().isValid()
            && !getClientIdentifier().isEmpty()
            && getAccessTokenUrl().isValid()
            && !getClientIdentifierSharedKey().isEmpty()
            && getFirstRedirectUrl().isValid()
            && getRedirectUrlPort() != 0;
}

} //namespace GooglePhotos
