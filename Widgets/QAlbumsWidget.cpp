#include <GooglePhotos/QAlbum.hpp>

#include <Widgets/QFlowLayout.h>
#include <Widgets/QAlbumCoverWidget.hpp>
#include <Widgets/QAlbumsWidget.hpp>

QAlbumsWidget::QAlbumsWidget(const QVector<GooglePhotos::QAlbum*>& albums, QWidget *parent)
    : QScrollArea(parent)
{
    QWidget* centralWidget = new QWidget();
    m_mainFlowLayout = new QFlowLayout(centralWidget);
    centralWidget->setLayout(m_mainFlowLayout);

    for(int i = 0; i < albums.count(); ++i)
    {
        GooglePhotos::QAlbum* album = albums.at(i);
        QAlbumCoverWidget* albumItem = new QAlbumCoverWidget(album);
        connect(albumItem, &QAlbumCoverWidget::released, this, &QAlbumsWidget::onAlbumClicked);
        m_mainFlowLayout->addWidget(albumItem);
    }

    setWidget(centralWidget);
    setWidgetResizable(true);
}

void QAlbumsWidget::onAlbumClicked()
{
    QAlbumCoverWidget* albumCoverWidget = static_cast<QAlbumCoverWidget*>(sender());
    GooglePhotos::QAlbum* album = albumCoverWidget->getAlbum();
    emit albumSelected(album);
}
