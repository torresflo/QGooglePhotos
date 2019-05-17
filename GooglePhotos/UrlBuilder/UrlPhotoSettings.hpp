#ifndef URLBUILDERPHOTOSETTINGS_HPP
#define URLBUILDERPHOTOSETTINGS_HPP

#include <QUrl>

namespace GooglePhotos
{

class UrlPhotoSettings
{
public:
    UrlPhotoSettings();

    static UrlPhotoSettings buildAlbumCoverSettings(const QUrl& baseUrl);
    static UrlPhotoSettings buildMediaItemPreviewSettings(const QUrl& baseUrl);

    QUrl m_baseUrl;
    unsigned int m_maxWidth = 1280;
    unsigned int m_maxHeight = 720;
    bool m_cropImage = false;
    bool m_downloadMetadata = false;
};

}

#endif // URLBUILDERPHOTOSETTINGS_HPP
