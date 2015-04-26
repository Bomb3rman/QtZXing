#ifndef QRQUICKITEM_H
#define QRQUICKITEM_H

#include <QQuickPaintedItem>

class QPainter;
class QRVideoSurface;

class QRQuickItem : public QQuickPaintedItem
{
public:
    QRQuickItem(QQuickItem *parent);
    ~QRQuickItem();

protected:
    void paint(QPainter * painter);

Q_SIGNALS:
    void qrCodeFound(QByteArray code);

private:
    QRVideoSurface *m_surface;
};

#endif // QRQUICKITEM_H
