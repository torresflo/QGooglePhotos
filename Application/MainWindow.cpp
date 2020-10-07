#include <QMessageBox>
#include <QAction>
#include <QScrollArea>

#include <Application/MainWindow.hpp>

#include <GooglePhotos/QLibraryClient.hpp>
#include <GooglePhotos/LibrarySettings.hpp>

#include <Widgets/QFlowLayout.h>
#include <Widgets/QAlbumsWidget.hpp>
#include <Widgets/QMediaItemListWidget.hpp>

MainWindow::MainWindow(QWidget *parent) : MainWindowUI(parent)
{
    GooglePhotos::LibrarySettings settings("clientid.json");
    m_libraryClient = new GooglePhotos::QLibraryClient(settings, this);

    connect(m_libraryClient, &GooglePhotos::QLibraryClient::authentificationSuccessed, this, &MainWindow::handleAuthorizationSuccessful);
    connect(m_libraryClient, &GooglePhotos::QLibraryClient::authentificationFailed, this, &MainWindow::handleAuthorizationFailure);

    connect(m_connectionAction, &QAction::triggered, this, &MainWindow::tryConnect);
}

void MainWindow::tryConnect()
{
    if(QSslSocket::sslLibraryBuildVersionNumber() > QSslSocket::sslLibraryVersionNumber())
    {
        QMessageBox::critical(this, tr("Invalid OpenSSL library"), tr("It seems you do not have the required SSL Library binaries installed on your computer.\n"
                                                                       "The required version is at least: %0.").arg(QSslSocket::sslLibraryBuildVersionNumber()));
        return;
    }

    if(m_libraryClient->isSettingsValid())
    {
        if(!m_libraryClient->isAccessGranted())
        {
            m_libraryClient->tryConnect();
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Invalid library settings"), tr("The connection settings are invalid.\n"
                                                                       "Please verify that clientid.json is correctly configured."));
    }
}

void MainWindow::initAlbumsWidget()
{
    const QVector<GooglePhotos::QAlbum*>& albums = m_libraryClient->getAlbums();
    QAlbumsWidget* albumsWidget = new QAlbumsWidget(albums, this);
    connect(albumsWidget, &QAlbumsWidget::albumSelected, this, &MainWindow::onAlbumSelected);
    setCentralWidget(albumsWidget);
}

void MainWindow::handleAuthorizationSuccessful()
{
    connect(m_libraryClient, &GooglePhotos::QLibraryClient::albumsInformationAvailable, this, &MainWindow::initAlbumsWidget);

    m_connectionAction->setText(tr("Connected"));
    m_connectionAction->setEnabled(false);

    m_libraryClient->retrieveAlbumsInformation();
}

void MainWindow::handleAuthorizationFailure()
{
    QMessageBox::critical(this, "Failed!", "Authorization failed!");
}

void MainWindow::handleError()
{
    QMessageBox::critical(this, "Error!", "There is an error!");
}

void MainWindow::onAlbumSelected(GooglePhotos::QAlbum* album)
{
    QMediaItemListWidget* mediaItemListWidget = new QMediaItemListWidget(album, m_libraryClient, this);
    setCentralWidget(mediaItemListWidget);
}
