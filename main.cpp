
#include "principal.h"
#include <QApplication>
#include <QStyleFactory>
#include<QFile>

QString stringFromResource(const QString &resName)
{
    QFile file(resName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ts(&file);
    return ts.readAll();
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    principal w;

    w.setStyleSheet(stringFromResource("Imagenes/style.qss"));
    w.showMaximized();
    //w.showMaximized();
    w.show();

    return a.exec();
}
