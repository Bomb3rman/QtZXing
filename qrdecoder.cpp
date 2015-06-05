#include "qrdecoder.h"
#include "zxingimagesource.h"

#include "zxing/core/src/zxing/ZXing.h"
#include "zxing/core/src/zxing/BinaryBitmap.h"
#include "zxing/core/src/zxing/Result.h"
#include "zxing/core/src/zxing/common/HybridBinarizer.h"
#include "zxing/core/src/zxing/DecodeHints.h"
#include "zxing/core/src/zxing/Reader.h"
#include "zxing/core/src/zxing/MultiFormatReader.h"

#include <QDebug>
#include <QtConcurrent/QtConcurrent>


QByteArray QRDecoder::decodeImage(QImage &image)
{
    std::vector<zxing::Ref<zxing::Result> > results;
    zxing::Ref<zxing::LuminanceSource> source(new ZXingImageSource(image));

    try {
        zxing::Ref<zxing::HybridBinarizer> binarizer(new zxing::HybridBinarizer(source));
        zxing::DecodeHints hints(zxing::DecodeHints::DEFAULT_HINT);
        hints.setTryHarder(false);
        zxing::Ref<zxing::BinaryBitmap> binary(new zxing::BinaryBitmap(binarizer));

        zxing::Ref<zxing::Reader> reader(new zxing::MultiFormatReader);
        results.push_back(reader->decode(binary, hints));
    } catch (...){
    }
    if (results.size() == 1) {
        qDebug() << QString::fromStdString(results[0]->getText()->getText());
        return QByteArray::fromStdString(results[0]->getText()->getText());
    }
    return QByteArray();
}

QFuture<QByteArray> QRDecoder::decodeImageAsync(QImage &image)
{
    return QtConcurrent::run(&QRDecoder::decodeImage, image);
}
