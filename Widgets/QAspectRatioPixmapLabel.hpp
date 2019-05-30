#ifndef QASPECTRATIOPIXMAPLABEL_HPP
#define QASPECTRATIOPIXMAPLABEL_HPP

#include <QLabel>

class QAspectRatioPixmapLabel : public QLabel
{
    Q_OBJECT
public:
    QAspectRatioPixmapLabel(QWidget* parent = nullptr);
    QAspectRatioPixmapLabel(Qt::TransformationMode transformationMode, QWidget* parent = nullptr);

    virtual int heightForWidth(int width) const override;
    virtual QSize sizeHint() const override;
    QPixmap getScaledPixmap() const;

public slots:
    void setPixmap(const QPixmap& pixmap);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Qt::TransformationMode m_transformationMode = Qt::SmoothTransformation;
    QPixmap m_originalPixmap;
};

#endif // QASPECTRATIOPIXMAPLABEL_HPP
