#include "basedatos.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QSqlTableModel>
const int BaseDatos::TABLA_COMPRAS=0;
const int BaseDatos::TABLA_INGRESOS=1;
const int BaseDatos::TABLA_METODOSPAGOS=3;


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

bool BaseDatos::insert(QStringList registro,int tabla)
{

   QString query;

    switch(tabla){
    case TABLA_COMPRAS:
        query="INSERT INTO COMPRAS(FECHA,DESCRIPCION,SUBTOTAL, IVA,IMP_CONSUMO,TOTAL,Metodo_De_Pago,N_Cuotas) VALUES( ?,?, ?, ?, ?,?,?,?)";
        break;
    case TABLA_INGRESOS:
        query="INSERT INTO INGRESOS(FECHA,DESCRIPCION,VALOR_DEVENGADO, BONIFICACION,APORTE_APF,APORTE_EPS,APORTE_AFSP,VALOR_NETO) VALUES( ?, ?, ?, ?,?,?,?,?)";
        break;
    case TABLA_METODOSPAGOS:
        break;
    }
    QSqlQuery sql(database);
    sql.prepare(query);
    foreach (QString aux, registro) {
        sql.addBindValue(aux);

    }
    return sql.exec();
}

bool BaseDatos::createTable(int tabla)
{
    QSqlQuery sql(database);
    QString query;

    switch(tabla){
    case TABLA_COMPRAS:
        query="CREATE  TABLE IF NOT EXISTS \
                COMPRAS (ID  integer PRIMARY KEY NOT NULL,\
                         FECHA TEXT,\
                         DESCRIPCION TEXT,\
                         SUBTOTAL DOUBLE,\
                         IVA DOUBLE,\
                         IMP_CONSUMO DOUBLE,\
                         TOTAL DOUBLE,\
                         Metodo_De_Pago TEXT,\
                         N_Cuotas integer DEFAULT 1)";   // Crea la tabla";
        break;
    case TABLA_INGRESOS:
        query="CREATE  TABLE IF NOT EXISTS \
                INGRESOS (ID  integer PRIMARY KEY NOT NULL,\
                          FECHA TEXT,\
                          DESCRIPCION TEXT,\
                          VALOR_DEVENGADO DOUBLE,\
                          BONIFICACION DOUBLE,\
                          APORTE_APF DOUBLE,\
                          APORTE_EPS DOUBLE,\
                          APORTE_AFSP DOUBLE,\
                          VALOR_NETO DOUBLE)";

                break;
    case TABLA_METODOSPAGOS:
        query="CREATE  TABLE IF NOT EXISTS METODOS_PAGO(METODO  TEXT PRIMARY KEY NOT NULL)";   // Crea la tabla

        break;
    }
    return sql.exec(query);
}


