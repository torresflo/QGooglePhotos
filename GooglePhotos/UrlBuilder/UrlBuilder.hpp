#ifndef GOOGLEPHOTOSURLBUILDER_HPP
#define GOOGLEPHOTOSURLBUILDER_HPP

#include <QUrl>

#include <GooglePhotos/UrlBuilder/UrlPhotoSettings.hpp>

namespace GooglePhotos
{

class UrlBuilder
{
public:
    static QUrl buildGetAlbumsUrl();
    static QUrl buildGetAlbumPhotosUrl();
    static QUrl buildGetPhotoUrl(const GooglePhotos::UrlPhotoSettings& settings);

private:
    UrlBuilder();
};


}

#endif // GOOGLEPHOTOSURLBUILDER_HPP
