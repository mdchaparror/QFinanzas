#include "global.h"
#include <QDebug>
#include <QThread>
#define pruebas true

QString global::dir_bd="sqliteBD/";
QString global::usuario="mdchaparror";
QStringList global::metodosPago;
QStringList global::categoriaCompra;
int global::porcentajeAPF=4;
int global::porcentajeEPS=4;
int global::porcentajeAFSP=1;
int global::porcentajeIVA=16;
int global::porcentajeConsumo=4;
QString global::currentYear="2017";
QString global::filterBD=QString("fecha like '%1%'").arg(global::currentYear);



void global::setMetodoPago(QStringList x)
{
    global::metodosPago.clear();
    global::metodosPago = x;
}

void global::setCategoriaCompra(QStringList x)
{
    global::categoriaCompra.clear();
    global::categoriaCompra = x;
}
