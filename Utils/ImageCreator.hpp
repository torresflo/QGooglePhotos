#ifndef IMAGECREATOR_HPP
#define IMAGECREATOR_HPP

#include <QImage>

namespace Utils
{

class ImageCreator
{
public:
    static QImage createRoundedImage(const QImage& baseImage, int xRadius, int yRadius);
    static QImage createRoundedImage(const QBrush& brush, int width, int height, int xRadius, int yRadius);
    static QImage createRoundedImage(const QColor& color, int width, int height, int xRadius, int yRadius);

    static QImage createColorImage(const QColor& color, int width, int height);

    static QImage createPreviewImage(int width, int height);

private:
    ImageCreator();
};

}

#endif // IMAGECREATOR_HPP
