TEMPLATE = app

QT += \
    core \
    widgets \
    network \
    networkauth

SOURCES += \
    GooglePhotos/LibrarySettings.cpp \
    GooglePhotos/QAlbum.cpp \
    GooglePhotos/QLibraryClient.cpp \
    GooglePhotos/QLibraryItemDownloader.cpp \
    GooglePhotos/QMediaItem.cpp \
    GooglePhotos/QPhotoItem.cpp \
    GooglePhotos/QVideoItem.cpp \
    GooglePhotos/UrlBuilder/UrlBuilder.cpp \
    GooglePhotos/UrlBuilder/UrlPhotoSettings.cpp \
    Utils/ImageCreator.cpp \
    Application/MainWindow.cpp \
    Application/MainWindowUI.cpp \
    Widgets/QAlbumCoverWidget.cpp \
    Widgets/QAlbumsWidget.cpp \
    Widgets/QAspectRatioPixmapLabel.cpp \
    Widgets/QFlowLayout.cpp \
    Widgets/QHoverableWidget.cpp \
    Widgets/QMediaItemListWidget.cpp \
    Widgets/QMediaItemPreviewWidget.cpp \
    Widgets/QPhotoViewer.cpp \
    Widgets/QVlcVideoViewer.cpp \
    main.cpp \

HEADERS += \
    GooglePhotos/LibrarySettings.hpp \
    GooglePhotos/QAlbum.hpp \
    GooglePhotos/QLibraryClient.hpp \
    GooglePhotos/QLibraryItemDownloader.hpp \
    GooglePhotos/QMediaItem.hpp \
    GooglePhotos/QPhotoItem.hpp \
    GooglePhotos/QVideoItem.hpp \
    GooglePhotos/UrlBuilder/UrlBuilder.hpp \
    GooglePhotos/UrlBuilder/UrlPhotoSettings.hpp \
    Utils/ImageCreator.hpp \
    Application/MainWindow.hpp \
    Application/MainWindowUI.hpp \ \
    Utils/NonCopyable.hpp \
    Utils/Singleton.hpp \
    Utils/Singleton.inl \
    Widgets/QAlbumCoverWidget.hpp \
    Widgets/QAlbumsWidget.hpp \
    Widgets/QAspectRatioPixmapLabel.hpp \
    Widgets/QFlowLayout.h \
    Widgets/QHoverableWidget.hpp \
    Widgets/QMediaItemListWidget.hpp \
    Widgets/QMediaItemPreviewWidget.hpp \
    Widgets/QPhotoViewer.hpp \
    Widgets/QVlcVideoViewer.hpp

LIBS += \
    -L$$PWD/VLC-Qt/lib -lVLCQtCore -lVLCQtWidgets

INCLUDEPATH += \
    $$PWD/VLC-Qt/include

DEPENDPATH += \
    $$PWD/VLC-Qt/include
