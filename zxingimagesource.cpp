#include "zxingimagesource.h"
#include <QColor>
#include "zxing/core/src/zxing/ZXing.h"
#include "zxing/core/src/zxing/LuminanceSource.h"
#include "zxing/core/src/zxing/common/Array.h"

ZXingImageSource::ZXingImageSource(const QImage &sourceImage) : zxing::LuminanceSource(sourceImage.width(), sourceImage.height())
{
    m_image = sourceImage.copy();
}

int ZXingImageSource::getWidth() const
{
    return m_image.width();
}

int ZXingImageSource::getHeight() const
{
    return m_image.height();
}

unsigned char ZXingImageSource::getPixel(int x, int y) const
{
    QRgb pixel = m_image.pixel(x,y);

    return qGray(pixel);
}

unsigned char* ZXingImageSource::copyMatrix() const
{
    unsigned char* newMatrix = (unsigned char*)malloc(m_image.width()*m_image.height()*sizeof(char));

    int cnt = 0;
    for(int i=0; i<m_image.width(); i++)
    {
        for(int j=0; j<m_image.height(); j++)
        {
            newMatrix[cnt++] = getPixel(i,j);
        }
    }

    return newMatrix;
}

QImage ZXingImageSource::grayScaleImage(QImage::Format f)
{
    QImage tmp(m_image.width(), m_image.height(), f);
    for(int i=0; i<m_image.width(); i++)
    {
        for(int j=0; j<m_image.height(); j++)
        {
            int pix = (int)getPixel(i,j);
            tmp.setPixel(i,j, qRgb(pix ,pix,pix));
        }
    }

    return tmp;
}

QImage ZXingImageSource::getOriginalImage()
{
    return m_image;
}

zxing::ArrayRef<char> ZXingImageSource::getRow(int y, zxing::ArrayRef<char> row) const
{
    int width = getWidth();

    if (row->size() != width)
        row.reset(zxing::ArrayRef<char>(width));

    for (int x = 0; x < width; x++)
        row[x] = getPixel(x,y);

    return row;
}

zxing::ArrayRef<char> ZXingImageSource::getMatrix() const
{
    int width = getWidth();
    int height =  getHeight();
    char* matrix = new char[width * height];
    char* m = matrix;

    for(int y=0; y<height; ++y) {
        zxing::ArrayRef<char> tmpRow;
        tmpRow = getRow(y, zxing::ArrayRef<char>(width));
        memcpy(m, &tmpRow->values()[0], width);
        m += width * sizeof(unsigned char);
    }

    zxing::ArrayRef<char> arr = zxing::ArrayRef<char>(matrix, width * height);

    if(matrix)
        delete matrix;

    return arr;
}

