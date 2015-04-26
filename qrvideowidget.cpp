#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

#include "qrvideowidget.h"
#include "qrvideosurface.h"
#include "zxingimagesource.h"
#include "qrdecoder.h"

QRVideoWidget::QRVideoWidget(QWidget *parent)
    : QWidget(parent), m_surface(new QRVideoSurface(this))
{
}

QRVideoWidget::~QRVideoWidget()
{
    delete m_surface;
}

QSize QRVideoWidget::sizeHint() const
{
    return QSize(400,400);
}

QSizePolicy QRVideoWidget::sizePolicy() const
{
    return QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void QRVideoWidget::startQRSearch()
{
    m_surface->startCamera();
}

void QRVideoWidget::stopQRSearch()
{
    m_surface->stopCamera();
}

void QRVideoWidget::paintEvent(QPaintEvent *evt)
{
    QVideoFrame currentFrame = m_surface->currentFrame();
    if (currentFrame.isValid() &&
            currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
        QPainter painter(this);
        QImage image(
                    currentFrame.bits(),
                    currentFrame.width(),
                    currentFrame.height(),
                    currentFrame.bytesPerLine(),
                    m_surface->imageFormat());

        QByteArray data = QRDecoder::decodeImage(image);
        if (!data.isEmpty())
            Q_EMIT qrCodeFound(data);

        //Paint the image with the correct aspect ratio
        QRectF targetRect = rect();
        if (((float)image.width()/(float)image.height()) > (float)width()/(float)height()) {
            float targetHeight = (float)width() / (float)image.width() * (float)image.height();
            targetRect.setY(((height() - targetHeight))/2.0); // It is important to set y first. Setting y will change hight of the rect
            targetRect.setWidth(width());
            targetRect.setHeight(targetHeight);
        } else {
            float targetWidth = (float)height() / (float)image.height() * (float)image.width(); // See above
            targetRect.setX((width() - targetWidth)/2.0);
            targetRect.setHeight(height());
            targetRect.setWidth(targetWidth);
        }
        if (!image.isNull()) {
            painter.drawImage(targetRect, image);
        }

        currentFrame.unmap();
    }
}
