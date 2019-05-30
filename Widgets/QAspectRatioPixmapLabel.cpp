#include <Widgets/QAspectRatioPixmapLabel.hpp>

QAspectRatioPixmapLabel::QAspectRatioPixmapLabel(QWidget* parent)
    :QLabel(parent)
{
    setMinimumSize(1, 1);
    setScaledContents(false);
    setAlignment(Qt::AlignCenter);
}

QAspectRatioPixmapLabel::QAspectRatioPixmapLabel(Qt::TransformationMode transformationMode, QWidget* parent)
    :QAspectRatioPixmapLabel(parent)
{
    m_transformationMode = transformationMode;
}

int QAspectRatioPixmapLabel::heightForWidth(int width) const
{
    if(m_originalPixmap.isNull())
    {
        return height();
    }
    return static_cast<int>((static_cast<double>(m_originalPixmap.height()) * width) / m_originalPixmap.width());
}

QSize QAspectRatioPixmapLabel::sizeHint() const
{
    int width = this->width();
    return QSize(width, heightForWidth(width));
}

QPixmap QAspectRatioPixmapLabel::getScaledPixmap() const
{
    return m_originalPixmap.scaled(size(), Qt::KeepAspectRatio, m_transformationMode);
}

void QAspectRatioPixmapLabel::setPixmap(const QPixmap& pixmap)
{
    m_originalPixmap = pixmap;
    QLabel::setPixmap(getScaledPixmap());
}

void QAspectRatioPixmapLabel::resizeEvent(QResizeEvent* event)
{
    QLabel::resizeEvent(event);

    if(!m_originalPixmap.isNull())
    {
        QLabel::setPixmap(getScaledPixmap());
    }
}
