#include "qrvideosurface.h"
#include <QCamera>
#include <QQuickPaintedItem>

#include "zxingimagesource.h"

QRVideoSurface::QRVideoSurface(QObject* parent)
    : QAbstractVideoSurface(parent), m_camera(0)
{
    m_imageFormat = QImage::Format_Invalid;
}

QRVideoSurface::~QRVideoSurface()
{
}

bool QRVideoSurface::start(const QVideoSurfaceFormat &format)
{
    m_videoFormat = format;
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    if (imageFormat != QImage::Format_Invalid && !size.isEmpty()) {
        m_imageFormat = imageFormat;
        QAbstractVideoSurface::start(format);
        return true;
    } else {
        qDebug() << "Could not start video surface";
        return false;
    }
}

bool QRVideoSurface::present(const QVideoFrame &frame)
{
    m_frame = frame;
    if (qobject_cast<QWidget*>(parent()) != 0) {
        qobject_cast<QWidget*>(parent())->update();
    } else if (qobject_cast<QQuickPaintedItem*>(parent())) {
        qobject_cast<QQuickPaintedItem*>(parent())->update();
    }

    return true;
}


QList<QVideoFrame::PixelFormat> QRVideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB555;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }
}

QVideoFrame &QRVideoSurface::currentFrame()
{
    return m_frame;
}

QImage::Format QRVideoSurface::imageFormat()
{
    return m_imageFormat;
}

void QRVideoSurface::startCamera()
{
    m_camera = new QCamera(this);
    m_camera->load();
    m_camera->setViewfinder(this);
    m_camera->start();
}

void QRVideoSurface::stopCamera()
{
    m_camera->stop();
    delete m_camera;
    m_camera = 0;
}
