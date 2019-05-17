#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <Application/MainWindowUI.hpp>

namespace GooglePhotos
{
class QLibraryClient;
class QAlbum;
}

class MainWindow : public MainWindowUI
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    GooglePhotos::QLibraryClient* m_libraryClient = nullptr;

private slots:
    void tryConnect();
    void handleAuthorizationSuccessful();
    void handleAuthorizationFailure();
    void initAlbumsWidget();

    void onAlbumSelected(GooglePhotos::QAlbum* album);
};

#endif // MAINWINDOW_HPP
