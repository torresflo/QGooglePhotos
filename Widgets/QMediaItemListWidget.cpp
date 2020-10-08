#include <QOAuth2AuthorizationCodeFlow>

#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Common.h>

#include <GooglePhotos/QLibraryClient.hpp>
#include <GooglePhotos/QAlbum.hpp>
#include <GooglePhotos/QMediaItem.hpp>
#include <GooglePhotos/QPhotoItem.hpp>
#include <GooglePhotos/QVideoItem.hpp>

#include <Widgets/QFlowLayout.h>
#include <Widgets/QMediaItemPreviewWidget.hpp>
#include <Widgets/QMediaItemListWidget.hpp>
#include <Widgets/QPhotoViewer.hpp>
#include <Widgets/QVlcVideoViewer.hpp>

QMediaItemListWidget::QMediaItemListWidget(GooglePhotos::QAlbum* album, GooglePhotos::QLibraryClient* libraryClient, QWidget* parent)
    :QScrollArea (parent)
{
    m_libraryClient = libraryClient;

    connect(album, &GooglePhotos::QAlbum::mediaItemsDataAvailable, this, &QMediaItemListWidget::onMediaItemsDataAvailable);
    album->setPaginationMode(GooglePhotos::PaginationMode::Automatic);
    album->downloadMediaItemsData();

    m_mainLayout = new QFlowLayout(this);
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(m_mainLayout);

    setWidget(centralWidget);
    setWidgetResizable(true);
}

void QMediaItemListWidget::onMediaItemsDataAvailable(int minRange)
{
    GooglePhotos::QAlbum* album = static_cast<GooglePhotos::QAlbum*>(sender());
    const QVector<GooglePhotos::QMediaItem*>& mediaItems = album->getMediaItems();

    for(int i = minRange; i < mediaItems.count(); ++i)
    {
        GooglePhotos::QMediaItem* mediaItem = mediaItems[i];
        QMediaItemPreviewWidget* previewWidget = new QMediaItemPreviewWidget(mediaItem, this);
        mediaItem->downloadPreview();

        connect(previewWidget, &QMediaItemPreviewWidget::released, this, &QMediaItemListWidget::onMediaItemClicked);
        m_mainLayout->addWidget(previewWidget);
    }
}

void QMediaItemListWidget::onMediaItemClicked()
{
    QMediaItemPreviewWidget* mediaItemPreviewWidget = static_cast<QMediaItemPreviewWidget*>(sender());
    GooglePhotos::QMediaItem* mediaItem = mediaItemPreviewWidget->getMediaItem();
    if(GooglePhotos::QPhotoItem* photoItem = dynamic_cast<GooglePhotos::QPhotoItem*>(mediaItem))
    {
        QPhotoViewer* photoViewer = new QPhotoViewer(photoItem);
        photoViewer->show();
    }
    else if(GooglePhotos::QVideoItem* videoItem = dynamic_cast<GooglePhotos::QVideoItem*>(mediaItem))
    {
        QVlcVideoViewer* videoViewer = new QVlcVideoViewer(videoItem);
        videoViewer->show();
    }
}
