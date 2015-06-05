#ifndef QRDECODER_H
#define QRDECODER_H

#include <QObject>
#include <QFuture>

class QRDecoder
{
public:
    static QByteArray decodeImage(QImage &);
    static QFuture<QByteArray> decodeImageAsync(QImage&);
};

#endif // QRDECODER_H
