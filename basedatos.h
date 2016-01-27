#ifndef BASEDATOS_H
#define BASEDATOS_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

#include <QStandardItemModel>
#include <QSqlTableModel>

class BaseDatos : public QObject
{
     Q_OBJECT
public:
  explicit BaseDatos(QObject *parent = 0);
    static int TABLA_COMPRAS;
    static int TABLA_INGRESOS;
    static int TABLA_METODOSPAGOS;

signals:
    void table_changed(QString table);
public slots:

    void open(QString x);
    void close();

private:

    QSqlDatabase database;

QSqlQueryModel *model;

};

#endif // BASEDATOS_H
#include <QObject>

