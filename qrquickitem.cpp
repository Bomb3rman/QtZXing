#include "qrquickitem.h"

#include "zxingimagesource.h"
#include "qrvideosurface.h"
#include "qrdecoder.h"

#include <QPainter>

QRQuickItem::QRQuickItem(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_surface(new QRVideoSurface(this))
{
    connect(&m_futureWatcher, &QFutureWatcher<QByteArray>::finished, [&]() {
        QByteArray data = m_futureWatcher.result();
        if (!data.isEmpty()) {
            m_lastQRCode = data;
            qrCodeFound(m_lastQRCode);
        }
    });
}

QRQuickItem::~QRQuickItem()
{
}

QByteArray QRQuickItem::qrCode()
{
    return m_lastQRCode;
}

void QRQuickItem::startQR()
{
    m_surface->startCamera();
}

void QRQuickItem::stopQR()
{
    m_surface->stopCamera();
}

void QRQuickItem::paint(QPainter * painter)
{
    QRectF paintArea = contentsBoundingRect();
    QVideoFrame currentFrame = m_surface->currentFrame();
    setImplicitWidth(currentFrame.width());
    setImplicitHeight(currentFrame.height());
    if (currentFrame.isValid() &&
            currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
        QImage image(
                    currentFrame.bits(),
                    currentFrame.width(),
                    currentFrame.height(),
                    currentFrame.bytesPerLine(),
                    m_surface->imageFormat());

        if (!m_futureWatcher.isRunning()) {
            QFuture<QByteArray> computeFuture = QRDecoder::decodeImageAsync(image);
            m_futureWatcher.setFuture(computeFuture);
        }

        QRectF targetRect;
        if (((float)image.width()/(float)image.height()) > (float)paintArea.width()/(float)paintArea.height()) {
            float targetHeight = (float)paintArea.width() / (float)image.width() * (float)image.height();
            targetRect.setY(((paintArea.height() - targetHeight))/2.0); // It is important to set y first. Setting y will change hight of the rect
            targetRect.setWidth(paintArea.width());
            targetRect.setHeight(targetHeight);
        } else {
            float targetWidth = (float)paintArea.height() / (float)image.height() * (float)image.width(); // See above
            targetRect.setX((paintArea.width() - targetWidth)/2.0);
            targetRect.setHeight(paintArea.height());
            targetRect.setWidth(targetWidth);
        }
        //qDebug() << targetRect << " " << (float)targetRect.height() / (float)targetRect.width();
        if (!image.isNull()) {
            painter->drawImage(targetRect, image);
        }

        currentFrame.unmap();
    }
}

