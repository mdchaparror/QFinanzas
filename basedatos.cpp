#include "basedatos.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QSqlTableModel>
int BaseDatos::TABLA_COMPRAS=0;
int BaseDatos::TABLA_INGRESOS=1;
int BaseDatos::TABLA_METODOSPAGOS=3;


BaseDatos::BaseDatos(QObject *parent): QObject(parent)
{
    model = new QSqlQueryModel();

}


void BaseDatos::open(QString x){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(x);
    if(database.open()==false)
    {
        qDebug() << "Can not open database";
    }
    else
    {

        qDebug()<<"Base datos abierta";

    }


}

void BaseDatos::close()
{
    database.close();
    qDebug()<<"Base datos cerrada";
}


