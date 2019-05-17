#ifndef GOOGLEPHOTOSALBUMITEM_HPP
#define GOOGLEPHOTOSALBUMITEM_HPP

#include <Widgets/QHoverableWidget.hpp>

class QLabel;

namespace GooglePhotos
{
class QAlbum;
}

class QAlbumCoverWidget : public QHoverableWidget
{
    Q_OBJECT
public:
    QAlbumCoverWidget(GooglePhotos::QAlbum* album, QWidget* parent = nullptr);

    GooglePhotos::QAlbum* getAlbum() const;

signals:
    void pressed();
    void released();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseHoverEnter(QHoverEvent* event) override;
    void mouseHoverLeave(QHoverEvent* event) override;

private:
    void setAlbumCoverPixmap(const QImage coverImage);

    GooglePhotos::QAlbum* m_album;

    QPalette m_previousPalette;
    QLabel* m_albumCoverLabel;

    bool m_pressed = false;

private slots:
    void onAlbumCoverReceived();
};

#endif // GOOGLEPHOTOSALBUMITEM_HPP
