
#include "principal.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    principal w;
    //w.showMaximized();
    w.show();

    return a.exec();
}
