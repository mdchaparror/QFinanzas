#include "basedatos.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QSqlTableModel>
const int BaseDatos::TABLA_COMPRAS=0;
const int BaseDatos::TABLA_INGRESOS=1;
const int BaseDatos::TABLA_METODOSPAGOS=2;
const int BaseDatos::TABLA_PRESUPUESTO=3;
const int BaseDatos::TABLA_CATEGORIA_COMPRA=4;

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
        query="INSERT INTO COMPRAS(FECHA,DESCRIPCION,SUBTOTAL, IVA,IMP_CONSUMO,TOTAL,Metodo_De_Pago,N_Cuotas,CATEGORIA) VALUES( ?,?, ?, ?, ?,?,?,?,?)";
        break;
    case TABLA_INGRESOS:
        query="INSERT INTO INGRESOS(FECHA,DESCRIPCION,VALOR_DEVENGADO, BONIFICACION,APORTE_APF,APORTE_EPS,APORTE_AFSP,VALOR_NETO) VALUES( ?, ?, ?, ?,?,?,?,?)";
        break;
    case TABLA_PRESUPUESTO:
        query="INSERT INTO PRESUPUESTO(MES,DETALLE,GASTOS,INGRESOS) VALUES(?,?,?,?)";
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
                         N_Cuotas integer DEFAULT 1,\
                         CATEGORIA TEXT DEFAULT '')";   // Crea la tabla";
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

    case TABLA_CATEGORIA_COMPRA:
        query="CREATE  TABLE IF NOT EXISTS CATEGORIA_COMPRA(CATEGORIA  TEXT PRIMARY KEY NOT NULL)";   // Crea la tabla

        break;

    case TABLA_PRESUPUESTO:
        query="CREATE  TABLE IF NOT EXISTS PRESUPUESTO(ID  integer PRIMARY KEY NOT NULL,MES TEXT,DETALLE  TEXT,GASTOS DOUBLE DEFAULT 0.0,INGRESOS DOUBLE DEFAULT 0.0)";   // Crea la tabla

        break;
    }
    return sql.exec(query);
}

QSqlTableModel* BaseDatos::TablasModel(QString tmp)
{
     QSqlTableModel *X;
     X=new 	QSqlTableModel (0,database);
     X->setTable(tmp);

     X->setSort(1,Qt::AscendingOrder);
     X->select();

        return X;
}

QStringList BaseDatos::getColumn(QString table, QString columna)
{
    QSqlQuery sql(database);
    QStringList temp;
    QString consulta =QString("SELECT %2 FROM %1").arg(table).arg(columna);
    if(sql.exec(consulta)){
        while(sql.next()){
            temp.append(sql.value(0).toString());
        }

    }
    else{
        qDebug()<<"No se pudo ejecutar la consulta";
    }
    return temp;
}

double BaseDatos::getSumCoulmna(int tabla, QString col, QString filter)
{

    QString query;
    switch(tabla){
    case TABLA_COMPRAS:
         query=QString("SELECT SUM(%1) FROM COMPRAS WHERE %3;").arg(col).arg(filter);
        break;
    case TABLA_INGRESOS:
        query=QString("SELECT SUM(%1) FROM INGRESO WHERE %3;").arg(col).arg(filter);
        break;
    case TABLA_PRESUPUESTO:
        query=QString("SELECT SUM(%1) FROM PRESUPUESTO WHERE %3;").arg(col).arg(filter);
        break;


    }
     QSqlQuery sql(query,database);
    // qDebug()<<query;
     while(sql.next()){
         return sql.value(0).toDouble();
     }
    return 0.0;


}
