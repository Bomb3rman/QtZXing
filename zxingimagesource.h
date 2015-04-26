#ifndef ZXINGIMAGESOURCE_H
#define ZXINGIMAGESOURCE_H


#include <QImage>
#include <QString>
#include "zxing/core/src/zxing/LuminanceSource.h"


class ZXingImageSource : public zxing::LuminanceSource
{
public:
    ZXingImageSource(const QImage& sourceImage);

    int getWidth() const;
    int getHeight() const;

    unsigned char getPixel(int x, int y) const;
    unsigned char* copyMatrix() const;

    QImage grayScaleImage(QImage::Format f);
    QImage getOriginalImage();

    // Callers take ownership of the returned memory and must call delete [] on it themselves.
    zxing::ArrayRef<char> getRow(int y, zxing::ArrayRef<char> row) const;
    zxing::ArrayRef<char> getMatrix() const;

private:
    QImage m_image;
};
#endif // ZXINGIMAGESOURCE_H
