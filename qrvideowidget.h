#include <QWidget>

class QRVideoSurface;

class QRVideoWidget : public QWidget
{
    Q_OBJECT
public:
    QRVideoWidget(QWidget *parent);
    ~QRVideoWidget();

    QSize sizeHint() const;
    QSizePolicy sizePolicy() const;

public Q_SLOTS:
    void startQRSearch();
    void stopQRSearch();

signals:
    void qrCodeFound(QByteArray code);

protected:
    void paintEvent(QPaintEvent *evt);

private:
    QRVideoSurface *m_surface;
};
