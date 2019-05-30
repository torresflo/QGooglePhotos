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
    QString stringUrl = settings.m_baseUrl.toString();
    if(settings.m_downloadFullImage)
    {
        stringUrl += "=d";
    }
    else
    {
        QString sizeParameters("=w%0-h%1");
        stringUrl += sizeParameters.arg(QString("%0").arg(settings.m_maxWidth), QString("%0").arg(settings.m_maxHeight));

        if(settings.m_cropImage)
        {
            stringUrl += "-c";
        }
    }
    return QUrl(stringUrl);
}

UrlBuilder::UrlBuilder()
{}

}
