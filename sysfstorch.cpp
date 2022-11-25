#include "sysfstorch.h"

#define SYSFS_ENABLE 255

SysfsTorch::SysfsTorch(QObject *parent) : QObject(parent)
{
}


SysfsTorch::~SysfsTorch()
{

}


void SysfsTorch::start()
{

    if (QDBusConnection::sessionBus().connect("org.droidian.Flashlightd", "/org/droidian/Flashlightd",
                "org.freedesktop.DBus.Properties", "PropertiesChanged", this,
                SLOT(propertyChanged(QString, QVariantMap, QStringList)))) {
        qDebug() << "PropertiesChanged signal connected successfully to slot";
        } else {
            qDebug() << "PropertiesChanged signal connection was not successful";
     }

}


void SysfsTorch::propertyChanged(QString interface, QVariantMap changed_properties, QStringList invalidated_properties)
{
    int brightness  = changed_properties["Brightness"].toInt();
    for (int i = 0; i < m_sysfsPathSize; i++)
        sysfsWrite(m_sysfsPath[i], SYSFS_ENABLE * brightness);
    for (int i =0; i < m_sysfsSwitchSize; i++)
        sysfsWrite(m_sysfsSwitch[i], brightness);
}

void SysfsTorch::sysfsWrite(QString path, int value) {
    QFile sysfsFile(path);
    if (!sysfsFile.open(QFile::ReadWrite))
    {
        qDebug() << "Failed to open " << path;
    }
    else
    {

        QTextStream in(&sysfsFile);
        in << QString("%1\n").arg(value);
        sysfsFile.close();
    }
}

QByteArray SysfsTorch::sysfsRead(QString path)
{
    QByteArray content = nullptr;
    QFile sysfsFile(path);
    if (!sysfsFile.open(QFile::WriteOnly))
    {
        qDebug() << "Failed to open " << path;
    }
    else
    {
        content = sysfsFile.readAll();
        sysfsFile.close();
    }
    return content;
}
