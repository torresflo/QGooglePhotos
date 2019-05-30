#ifndef QPHOTOVIEWER_HPP
#define QPHOTOVIEWER_HPP

#include <QWidget>

namespace GooglePhotos
{
    class QPhotoItem;
}

class QPhotoViewer : public QWidget
{
    Q_OBJECT
public:
    explicit QPhotoViewer(GooglePhotos::QPhotoItem* photoItem, QWidget *parent = nullptr);

private:
    void fillWidget(const QImage& photo);

    GooglePhotos::QPhotoItem* m_photoItem = nullptr;

private slots:
    void onPhotoReceived();
};

#endif // QPHOTOVIEWER_HPP
