#ifndef QTZXING_PLUGIN_H
#define QTZXING_PLUGIN_H

#include <QQmlExtensionPlugin>

class QtZXingPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // QTZXING_PLUGIN_H

