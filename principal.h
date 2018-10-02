#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "global.h"
#include "basedatos.h"
#include "metodopago.h"
#include "reportexcel.h"
#include "categoriacompra.h"
#include "configdialog.h"

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

    void on_actionAdd_Metodo_de_Pago_triggered();
    void updateMetodoPago();


    void on_actionAdd_Categoria_Compra_triggered();

    void updateCategoriaCompra();
    void on_actionShowAmortizacion_toggled(bool arg1);

    void on_actionCompras_toggled(bool arg1);

    void on_actionIngresos_toggled(bool arg1);

    void on_actionPresupuesto_toggled(bool arg1);

    void on_actionConfiguracion_triggered();

protected:
  virtual void	resizeEvent(QResizeEvent * event);

private:
    Ui::principal *ui;
    BaseDatos *finanzasBD;
    QSqlTableModel*  MetodosPagoModel;
    MetodoPago *metodoPago;
    QSqlTableModel*  CategoriaComprasModel;
    CategoriaCompra *categoriaCompra;
    configDialog * config;
    ReportExcel *report;


};

#endif // PRINCIPAL_H
