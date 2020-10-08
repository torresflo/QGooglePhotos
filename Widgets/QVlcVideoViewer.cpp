#include <Widgets/QVlcVideoViewer.hpp>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCloseEvent>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include <VLCQtWidgets/WidgetSeek.h>
#include <VLCQtWidgets/WidgetVideo.h>
#include <VLCQtWidgets/WidgetVolumeSlider.h>

#include <GooglePhotos/QVideoItem.hpp>

QVlcVideoViewer::QVlcVideoViewer(GooglePhotos::QVideoItem* videoItem, QWidget* parent)
    :QMainWindow(parent)
{
    m_videoItem = videoItem;

    m_vlcInstance = new VlcInstance(VlcCommon::args(), this);
    m_vlcMedia = new VlcMedia(m_videoItem->getVideoDataUrl(), false, m_vlcInstance);

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainlayout = new QVBoxLayout(centralWidget);

    VlcWidgetVideo* vlcWidgetVideo = new VlcWidgetVideo(centralWidget);
    m_vlcMediaPlayer = new VlcMediaPlayer(m_vlcInstance);
    m_vlcMediaPlayer->setVideoWidget(vlcWidgetVideo);
    vlcWidgetVideo->setMediaPlayer(m_vlcMediaPlayer);
    vlcWidgetVideo->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
    vlcWidgetVideo->setMinimumSize(300, 300);

    VlcWidgetVolumeSlider* vlcWidgetVolumeSlider = new VlcWidgetVolumeSlider(centralWidget);
    vlcWidgetVolumeSlider->setMediaPlayer(m_vlcMediaPlayer);
    vlcWidgetVolumeSlider->setOrientation(Qt::Orientation::Horizontal);
    vlcWidgetVolumeSlider->setVolume(50);

    VlcWidgetSeek* vlcWidgetSeek = new VlcWidgetSeek(centralWidget);
    vlcWidgetSeek->setMediaPlayer(m_vlcMediaPlayer);

    QPushButton* pauseButton = new QPushButton(tr("Pause"), centralWidget);
    pauseButton->setCheckable(true);
    QPushButton* stopButton = new QPushButton(tr("Stop"), centralWidget);

    QHBoxLayout* videoControlsLayout = new QHBoxLayout(centralWidget);
    videoControlsLayout->addWidget(pauseButton);
    videoControlsLayout->addWidget(stopButton);
    videoControlsLayout->addWidget(vlcWidgetVolumeSlider);

    QVBoxLayout* controlsLayout = new QVBoxLayout(centralWidget);
    controlsLayout->addLayout(videoControlsLayout);
    controlsLayout->addWidget(vlcWidgetSeek);

    mainlayout->addWidget(vlcWidgetVideo);
    mainlayout->addLayout(controlsLayout);

    this->setCentralWidget(centralWidget);
    m_vlcMediaPlayer->open(m_vlcMedia);

    connect(pauseButton, &QPushButton::clicked, m_vlcMediaPlayer, &VlcMediaPlayer::togglePause);
    connect(stopButton, &QPushButton::clicked, m_vlcMediaPlayer, &VlcMediaPlayer::stop);
}

QVlcVideoViewer::~QVlcVideoViewer()
{
    m_vlcMediaPlayer->stop();

    delete m_vlcMediaPlayer;
    delete m_vlcMedia;
}

void QVlcVideoViewer::closeEvent(QCloseEvent* event)
{
    m_vlcMediaPlayer->stop();
    event->accept();
}
