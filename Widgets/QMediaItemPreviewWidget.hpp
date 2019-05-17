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

private:
    QLabel* m_preview = nullptr;

    void onPreviewAvailable();
};

#endif // QPHOTOPREVIEWWIDGET_HPP
