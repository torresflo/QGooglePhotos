#ifndef QGOOGLEPHOTOSALBUMSWIDGET_HPP
#define QGOOGLEPHOTOSALBUMSWIDGET_HPP

#include <QScrollArea>
#include <QVector>

class QFlowLayout;

namespace GooglePhotos
{
class QAlbum;
}

class QAlbumsWidget : public QScrollArea
{
    Q_OBJECT
public:
    QAlbumsWidget(const QVector<GooglePhotos::QAlbum*>& albums, QWidget *parent = nullptr);

signals:
    void albumSelected(GooglePhotos::QAlbum* album);

private:
    QFlowLayout* m_mainFlowLayout = nullptr;

    void onAlbumClicked();
};

#endif // QGOOGLEPHOTOSALBUMSWIDGET_HPP
