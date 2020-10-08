#include <QHBoxLayout>

#include <GooglePhotos/QPhotoItem.hpp>

#include <Widgets/QAspectRatioPixmapLabel.hpp>
#include <Widgets/QPhotoViewer.hpp>

QPhotoViewer::QPhotoViewer(GooglePhotos::QPhotoItem* photoItem, QWidget* parent)
    :QWidget(parent), m_photoItem(photoItem)
{
    if(m_photoItem->isPhotoAvailable())
    {
        fillWidget(m_photoItem->getPhoto());
    }
    else
    {
        connect(m_photoItem, &GooglePhotos::QPhotoItem::photoAvailable, this, &QPhotoViewer::onPhotoReceived);
        m_photoItem->downloadPhoto();
    }

    setMinimumSize(300, 300);
}

void QPhotoViewer::fillWidget(const QImage& photo)
{
    QAspectRatioPixmapLabel* photoLabel = new QAspectRatioPixmapLabel(this);
    photoLabel->setPixmap(QPixmap::fromImage(photo));

    QHBoxLayout* mainlayout = new QHBoxLayout(this);
    mainlayout->addWidget(photoLabel);

    setLayout(mainlayout);
}

void QPhotoViewer::onPhotoReceived()
{
    fillWidget(m_photoItem->getPhoto());
}
