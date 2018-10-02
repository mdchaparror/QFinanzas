#include "global.h"
#include <QDebug>
#include <QThread>
#define pruebas true

QString global::dir_bd="sqliteBD/";
QString global::usuario="mdchaparror";
QStringList global::metodosPago;
QStringList global::categoriaCompra;
double global::porcentajeAPF=4;
double global::porcentajeEPS=4;
double global::porcentajeAFSP=1;
double global::porcentajeIVA=19;
double global::porcentajeConsumo=4;
int global::currentYear=2018;
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
