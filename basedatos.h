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
    static const int TABLA_COMPRAS;
    static const int TABLA_INGRESOS;
    static const int TABLA_METODOSPAGOS;
    static const int TABLA_PRESUPUESTO;
      static const int TABLA_CATEGORIA_COMPRA;

signals:
    void table_changed(QString table);

public slots:

    void open(QString x);
    void close();
    bool insert(QStringList registro, int tabla);
    bool createTable(int tabla);
    QSqlTableModel* TablasModel(QString tmp);
    QStringList getColumn(QString table, QString columna);
    double getSumCoulmna(int tabla,QString col,QString filter);
private:

    QSqlDatabase database;

QSqlQueryModel *model;

};

#endif // BASEDATOS_H
#include <QObject>

