#ifndef MYVIDEOSURFACE_H
#define MYVIDEOSURFACE_H

#include <QWidget>
#include <QVideoFrame>
#include <QImage>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>

class QCamera;

class QRVideoSurface: public QAbstractVideoSurface
{
    Q_OBJECT
public:
    QRVideoSurface(QObject* parent = 0);
    ~QRVideoSurface();

    bool start(const QVideoSurfaceFormat &format);

    bool present(const QVideoFrame &frame);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
                QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

    QVideoFrame &currentFrame();

    QImage::Format imageFormat();

    void startCamera();
    void stopCamera();

private:
    QVideoFrame m_frame;
    QImage::Format m_imageFormat;
    QVideoSurfaceFormat m_videoFormat;
    QCamera *m_camera;
};

#endif // MYVIDEOSURFACE_H
