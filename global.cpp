#include "global.h"
#include <QDebug>
#include <QThread>
#define pruebas true

QString global::dir_bd="sqliteBD/";
QString global::usuario="mdchaparror";
QStringList global::metodosPago;
int global::porcentajeAPF=4;
int global::porcentajeEPS=4;
int global::porcentajeAFSP=1;
int global::porcentajeIVA=16;
int global::porcentajeConsumo=4;




void global::setMetodoPago(QStringList x)
{
    global::metodosPago.clear();
    global::metodosPago = x;
}
