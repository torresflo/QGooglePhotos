#include <QBrush>
#include <QPainter>

#include <Utils/ImageCreator.hpp>

namespace Utils
{

QImage ImageCreator::createRoundedImage(const QImage& baseImage, int xRadius, int yRadius)
{
    QBrush brush(baseImage);
    return ImageCreator::createRoundedImage(brush, baseImage.width(), baseImage.height(), xRadius, yRadius);
}

QImage ImageCreator::createRoundedImage(const QBrush& brush, int width, int height, int xRadius, int yRadius)
{
    QImage roundedImage(width, height, QImage::Format_ARGB32);
    roundedImage.fill(Qt::transparent);

    QPainter painter(&roundedImage);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(0, 0, width, height, xRadius, yRadius);

    return roundedImage;
}

QImage ImageCreator::createRoundedImage(const QColor& color, int width, int height, int xRadius, int yRadius)
{
    QBrush brush(color);
    return ImageCreator::createRoundedImage(brush, width, height, xRadius, yRadius);
}

QImage ImageCreator::createColorImage(const QColor& color, int width, int height)
{
    QImage image(width, height, QImage::Format_RGB32);
    image.fill(color);

    return image;
}

QImage ImageCreator::createPreviewImage(int width, int height)
{
    return ImageCreator::createColorImage(Qt::lightGray, width, height);
}

ImageCreator::ImageCreator()
{

}

}
