#include <QCoreApplication>
#include <sysfstorch.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SysfsTorch *sysfsTorch = new SysfsTorch();
    sysfsTorch->start();

    return a.exec();
}
