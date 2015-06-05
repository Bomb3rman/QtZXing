#ifndef QRQUICKITEM_H
#define QRQUICKITEM_H

#include <QQuickPaintedItem>
#include <QFutureWatcher>

class QPainter;
class QRVideoSurface;

class QRQuickItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QByteArray qrCode READ qrCode NOTIFY qrCodeFound)
public:
    QRQuickItem(QQuickItem *parent = 0);
    ~QRQuickItem();

    /** Returns the last found QR Code as byte array
     *
     */
    QByteArray qrCode();

    /** Starts the viewfinder and enables QR detection
     *
     */
    Q_INVOKABLE void startQR();

    Q_INVOKABLE void stopQR();

Q_SIGNALS:
    void qrCodeChanged();

protected:
    void paint(QPainter * painter);

Q_SIGNALS:
    void qrCodeFound(QByteArray code);

private:
    QRVideoSurface *m_surface;
    QByteArray m_lastQRCode;
    QFutureWatcher<QByteArray> m_futureWatcher;
};

#endif // QRQUICKITEM_H
