#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

#include <Utils/ImageCreator.hpp>

#include <GooglePhotos/QMediaItem.hpp>

#include <Widgets/QMediaItemPreviewWidget.hpp>

QMediaItemPreviewWidget::QMediaItemPreviewWidget(GooglePhotos::QMediaItem* mediaItem, QWidget *parent) : QWidget(parent)
{
    QImage photoPreview;
    if(mediaItem->isPreviewAvailable())
    {
        photoPreview = mediaItem->getPreview();
    }
    else
    {
        connect(mediaItem, &GooglePhotos::QMediaItem::previewAvailable, this, &QMediaItemPreviewWidget::onPreviewAvailable);

        int maxHeight = qMin(mediaItem->getHeight(), 300); //TODO Retrieve the height from UrlPhotoSettings
        int maxWidth = (maxHeight * mediaItem->getWidth()) / mediaItem->getHeight();
        photoPreview = Utils::ImageCreator::createPreviewImage(maxWidth, maxHeight);
    }

    m_preview = new QLabel(this);
    m_preview->setContentsMargins(0, 0, 0, 0);
    m_preview->setPixmap(QPixmap::fromImage(photoPreview));
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_preview);

    setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

void QMediaItemPreviewWidget::onPreviewAvailable()
{
    GooglePhotos::QMediaItem* mediaItem = static_cast<GooglePhotos::QMediaItem*>(sender());
    m_preview->setPixmap(QPixmap::fromImage(mediaItem->getPreview()));
}
