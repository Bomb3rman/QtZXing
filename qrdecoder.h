#ifndef QRDECODER_H
#define QRDECODER_H

#include <QObject>

class QRDecoder
{
public:
    static QByteArray decodeImage(QImage &);
};

#endif // QRDECODER_H
