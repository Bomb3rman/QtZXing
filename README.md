# QtZXing
A Qt wrapper for the ZXing library for decoding QR Code
The project includes a forked version of the abandoned c++ port of the ZXing library (https://github.com/glassechidna/zxing-cpp.git).

Some of the code was "inspired" by QZXing (http://sourceforge.net/projects/qzxing/).

This project offers a lightweight wrapper around ZXing for decoding bar-code. It does only offer a subset of the
ZXing functionality but is very straight forward to use.

For QWidget applications there is a QRVideoWidget. It acts as a viewfinder and QR decoder at the same time.

For QtQuick 2 applications there is a QRQuickItem which just like the widget acts as viewfinder and decoder.

This software is a published under the Apache 2.0 license (http://www.apache.org/licenses/LICENSE-2.0).


# Build

Make sure the zxing submodule is cloned and up to date. Afterwards invoke cmake and make.

A shared library qtzxing should be created and a QML plugin.


# Usage

## QML

import QtQuick 2.0
import QtZXing 1.0

Item {
    QtZXing {
        anchors.centerIn: parent
        width: 400
        height: 300
        onQrCodeFound: print("QR Code found")
        Component.onCompleted: startQR();
    }


## Widget

Just use the widget as any other QWidget. "startQRSearch()" will start camera and viewfinder. Once a QR code is detected the
"qrDecoded(QByteArray data)" signal will be emitted.


