#include <QVBoxLayout>
#include <QLabel>
#include <QImage>

#include <QHoverEvent>

#include <QPalette>

#include <GooglePhotos/QAlbum.hpp>

#include <Utils/ImageCreator.hpp>
#include <Widgets/QAlbumCoverWidget.hpp>

QAlbumCoverWidget::QAlbumCoverWidget(GooglePhotos::QAlbum* album, QWidget* parent)
    :QHoverableWidget (parent)
{
    m_album = album;

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel* titleLabel = new QLabel(QString("<b>%0</b>").arg(album->getTitle()), this);
    QLabel* itemCountLabel = new QLabel(QString("%0 items").arg(album->getTotalMediaItemsCount()));

    m_albumCoverLabel = new QLabel(this);
    mainLayout->addWidget(m_albumCoverLabel);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(itemCountLabel);
    setLayout(mainLayout);

    if(album->isCoverImageAvailable())
    {
        setAlbumCoverPixmap(album->getCoverImage());
    }
    else
    {
        connect(album, &GooglePhotos::QAlbum::coverImageAvailable, this, &QAlbumCoverWidget::onAlbumCoverReceived);
        QImage temporaryCoverImage(200, 200, QImage::Format_RGB32);
        temporaryCoverImage.fill(Qt::lightGray);
        setAlbumCoverPixmap(temporaryCoverImage);
    }

    m_previousPalette = palette();
    setAutoFillBackground(true);
}

GooglePhotos::QAlbum* QAlbumCoverWidget::getAlbum() const
{
    return m_album;
}

void QAlbumCoverWidget::mousePressEvent(QMouseEvent* event)
{
    if(!m_pressed)
    {
        m_pressed = true;
        emit pressed();
    }
    event->accept();
}

void QAlbumCoverWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(m_pressed)
    {
        m_pressed = false;
        emit released();
    }
    event->accept();
}

void QAlbumCoverWidget::mouseHoverEnter(QHoverEvent* event)
{
    QPalette currentPalette = palette();
    currentPalette.setColor(QPalette::Background, Qt::gray);
    setPalette(currentPalette);
    event->accept();
}

void QAlbumCoverWidget::mouseHoverLeave(QHoverEvent* event)
{
    setPalette(m_previousPalette);
    event->accept();
}

void QAlbumCoverWidget::setAlbumCoverPixmap(const QImage coverImage)
{
    QImage roundedCoverImage = Utils::ImageCreator::createRoundedImage(coverImage, 20, 20);
    m_albumCoverLabel->setPixmap(QPixmap::fromImage(roundedCoverImage));
}

void QAlbumCoverWidget::onAlbumCoverReceived()
{
    setAlbumCoverPixmap(m_album->getCoverImage());
    disconnect(m_album, &GooglePhotos::QAlbum::coverImageAvailable, this, &QAlbumCoverWidget::onAlbumCoverReceived);
}
