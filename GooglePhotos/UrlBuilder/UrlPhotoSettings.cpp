#include <GooglePhotos/UrlBuilder/UrlPhotoSettings.hpp>

namespace GooglePhotos
{

UrlPhotoSettings::UrlPhotoSettings()
{}

UrlPhotoSettings UrlPhotoSettings::buildAlbumCoverSettings(const QUrl& baseUrl)
{
    UrlPhotoSettings newSettings;
    newSettings.m_baseUrl = baseUrl;
    newSettings.m_maxWidth = 200;
    newSettings.m_maxHeight = 200;
    newSettings.m_cropImage = true;

    return newSettings;
}

UrlPhotoSettings UrlPhotoSettings::buildMediaItemPreviewSettings(const QUrl& baseUrl)
{
    UrlPhotoSettings newSettings;
    newSettings.m_baseUrl = baseUrl;
    newSettings.m_maxHeight = 300;

    return newSettings;
}

UrlPhotoSettings UrlPhotoSettings::buildPhotoItemFullImageSettings(const QUrl& baseUrl)
{
    UrlPhotoSettings newSettings;
    newSettings.m_baseUrl = baseUrl;
    newSettings.m_downloadFullImage = true;

    return newSettings;
}

}
