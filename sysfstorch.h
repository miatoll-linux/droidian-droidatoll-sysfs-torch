#ifndef SYSFSTORCH_H
#define SYSFSTORCH_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QVariantMap>
#include <QStringList>
#include <QtDBus/QDBusConnection>

class SysfsTorch : public QObject
{
    Q_OBJECT
public:
    SysfsTorch(QObject *parent = nullptr);
    ~SysfsTorch();
    void start();

private:
    void sysfsWrite(QString path, int value);
    QByteArray sysfsRead(QString path);

    const static int m_sysfsSwitchSize = 1;
    char* m_sysfsSwitch[m_sysfsSwitchSize] = {"/sys/class/leds/led:switch_0/brightness"};

    const static int m_sysfsPathSize = 2;
    char* m_sysfsPath[m_sysfsPathSize] = {"/sys/class/leds/led:torch_0/brightness", "/sys/class/leds/flashlight/brightness"};

protected slots:
    void propertyChanged(QString interface, QVariantMap changed_properties, QStringList invalidated_properties);

};

#endif // SYSFSTORCH_H
