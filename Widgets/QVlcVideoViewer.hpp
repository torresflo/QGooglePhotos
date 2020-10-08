#ifndef QVLCVIDEOVIEWER_HPP
#define QVLCVIDEOVIEWER_HPP

#include <QMainWindow>

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class VlcWidgetVideo;

namespace GooglePhotos
{
    class QVideoItem;
}

class QVlcVideoViewer : public QMainWindow
{
    Q_OBJECT

public:
    QVlcVideoViewer(GooglePhotos::QVideoItem* videoItem, QWidget *parent = nullptr);
    virtual ~QVlcVideoViewer();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    GooglePhotos::QVideoItem* m_videoItem = nullptr;

    VlcInstance* m_vlcInstance = nullptr;
    VlcMedia *m_vlcMedia = nullptr;
    VlcMediaPlayer *m_vlcMediaPlayer = nullptr;

    VlcWidgetVideo* m_vlcWidgetVideo = nullptr;
};

#endif // QVLCVIDEOVIEWER_HPP
