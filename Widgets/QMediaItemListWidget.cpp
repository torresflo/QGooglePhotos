#include <QOAuth2AuthorizationCodeFlow>

#include <GooglePhotos/QLibraryClient.hpp>
#include <GooglePhotos/QAlbum.hpp>
#include <GooglePhotos/QMediaItem.hpp>

#include <Widgets/QFlowLayout.h>
#include <Widgets/QMediaItemPreviewWidget.hpp>
#include <Widgets/QMediaItemListWidget.hpp>

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
        m_mainLayout->addWidget(previewWidget);
    }
}
