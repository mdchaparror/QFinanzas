#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "ingresos.h"
#include "compra.h"
#include "global.h"
#include "basedatos.h"
#include "delegatecompras.h"
#include "delegateingreso.h"
#include "delegatepresupuesto.h"
#include "metodopago.h"
#include "presupuesto.h"
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


    void on_actionAdd_Metodo_de_Pago_triggered();
    void updateMetodoPago();



    void on_addRegPresupuesto_clicked();

    void on_removeRegPresupuesto_clicked();

    void on_mes_currentTextChanged(const QString &arg1);

    void dataPresupuestoChange();
    void contextMenuRequestIngreso(QPoint pos);
    void contextMenuRequestCompras(QPoint pos);
    void contextMenuRequestPresupuesto(QPoint pos);
    void resizeEvent ( QResizeEvent *re );
   void on_tabWidget_currentChanged(int index);

   void on_Calcular_Amortizacion_clicked();

private:
    Ui::principal *ui;
    BaseDatos finanzasBD;
    QSqlTableModel*  ComprasModel;
    QSqlTableModel*  IngresosModel;
    QSqlTableModel*  MetodosPagoModel;
    QSqlTableModel*  PresupuestoModel;
    DelegateCompras *delegateC;
    delegateIngreso *delegateI;
    delegatePresupuesto *delegateP;
    MetodoPago *metodoPago;
    QStandardItemModel *AmortizacionModel;


};

#endif // PRINCIPAL_H
