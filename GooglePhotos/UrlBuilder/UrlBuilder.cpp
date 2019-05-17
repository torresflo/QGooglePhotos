#include <GooglePhotos/UrlBuilder/UrlBuilder.hpp>

namespace GooglePhotos
{

QUrl UrlBuilder::buildGetAlbumsUrl()
{
    static QUrl getAlbumsUrl(QString("https://photoslibrary.googleapis.com/v1/albums"));
    return getAlbumsUrl;
}

QUrl UrlBuilder::buildGetAlbumPhotosUrl()
{
    static QUrl getAlbumPhotosUrl(QString("https://photoslibrary.googleapis.com/v1/mediaItems:search"));
    return getAlbumPhotosUrl;
}

QUrl UrlBuilder::buildGetPhotoUrl(const GooglePhotos::UrlPhotoSettings& settings)
{
    QString stringUrl("%0=w%1-h%2");
    stringUrl = stringUrl.arg(settings.m_baseUrl.toString(), QString("%0").arg(settings.m_maxWidth), QString("%0").arg(settings.m_maxHeight));

    if(settings.m_cropImage)
    {
        stringUrl += "-c";
    }

    if(settings.m_downloadMetadata)
    {
        stringUrl += "-d";
    }

    return QUrl(stringUrl);
}

UrlBuilder::UrlBuilder()
{}

}
