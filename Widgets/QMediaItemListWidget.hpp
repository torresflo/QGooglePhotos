#ifndef QMEDIAITEMLISTWIDGET_HPP
#define QMEDIAITEMLISTWIDGET_HPP

#include <QScrollArea>

namespace GooglePhotos
{
class QLibraryClient;
class QAlbum;
}

class QFlowLayout;

class QMediaItemListWidget : public QScrollArea
{
    Q_OBJECT
public:
    QMediaItemListWidget(GooglePhotos::QAlbum* album, GooglePhotos::QLibraryClient* libraryClient, QWidget *parent = nullptr);

private slots:
    void onMediaItemsDataAvailable(int minRange);
    void onMediaItemClicked();

private:
    QFlowLayout* m_mainLayout;
    GooglePhotos::QLibraryClient* m_libraryClient = nullptr;
};

#endif // QMEDIAITEMLISTWIDGET_HPP
