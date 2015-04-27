#include "qtzxing_plugin.h"
#include "qrquickitem.h"

#include <qqml.h>

void QtZXingPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<QRQuickItem>(uri, 1, 0, "QtZXing");
}


