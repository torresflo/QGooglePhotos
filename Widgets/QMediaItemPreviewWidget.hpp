#ifndef QPHOTOPREVIEWWIDGET_HPP
#define QPHOTOPREVIEWWIDGET_HPP

#include <QWidget>

class QLabel;

namespace GooglePhotos
{
class QMediaItem;
}

class QMediaItemPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    QMediaItemPreviewWidget(GooglePhotos::QMediaItem* mediaItem, QWidget *parent = nullptr);

    GooglePhotos::QMediaItem* getMediaItem() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    GooglePhotos::QMediaItem* m_mediaItem = nullptr;
    QLabel* m_preview = nullptr;
    bool m_pressed = false;

    void onPreviewAvailable();

signals:
    void pressed();
    void released();
};

#endif // QPHOTOPREVIEWWIDGET_HPP
