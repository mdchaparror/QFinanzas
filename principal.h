#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QDebug>
#include "ingresos.h"
#include "global.h"
#include "basedatos.h"
namespace Ui {
class principal;
}

class principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit principal(QWidget *parent = 0);
    ~principal();

private slots:
    void on_addCompra_clicked();

    void on_removeCompra_clicked();

    void on_saveCompras_clicked();

    void on_addIngreso_clicked();

    void on_removeIngreso_clicked();

    void on_saveIngresos_clicked();

private:
    Ui::principal *ui;
    BaseDatos finanzasBD;
    QSqlTableModel*  ComprasModel;
    QSqlTableModel*  IngresosModel;
    QSqlTableModel*  MetodosPagoModel;

};

#endif // PRINCIPAL_H
