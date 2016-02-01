#include "principal.h"
#include "ui_principal.h"

principal::principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);

    ComprasModel = new  QSqlTableModel(this);
    IngresosModel = new  QSqlTableModel(this);
    MetodosPagoModel= new QSqlTableModel(this);
    delegateC = new DelegateCompras(this);
     delegateI = new delegateIngreso(this);

    finanzasBD.open(global::dir_bd+global::usuario+".db");
    finanzasBD.createTable(BaseDatos::TABLA_COMPRAS);
    finanzasBD.createTable(BaseDatos::TABLA_INGRESOS);
    finanzasBD.createTable(BaseDatos::TABLA_METODOSPAGOS);

    ComprasModel=finanzasBD.TablasModel("COMPRAS");
    IngresosModel=finanzasBD.TablasModel("INGRESOS");
    MetodosPagoModel=finanzasBD.TablasModel("METODOS_PAGO");

    global::setMetodoPago(finanzasBD.getColumn("METODOS_PAGO","METODO"));

   ui->tableCompras->setItemDelegate(delegateC);
   ui->tableIngresos->setItemDelegate(delegateI);
    ui->tableCompras->setModel(ComprasModel);
    ui->tableCompras->hideColumn(0);
    ui->tableCompras->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");
    ui->tableIngresos->setModel(IngresosModel);
    ui->tableIngresos->hideColumn(0);
    ui->tableIngresos->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");



}

principal::~principal()
{
    delete ui;
    finanzasBD.close();
}

void principal::on_addCompra_clicked()
{
      compra newCompra;
      newCompra.setFecha(QDate::currentDate().toString(Qt::ISODate));
      qDebug()<<finanzasBD.insert(newCompra.toStringList(),BaseDatos::TABLA_COMPRAS);
      updateModels();




}

void principal::on_removeCompra_clicked()
{
   QModelIndex index=ui->tableCompras->currentIndex();
   ui->tableCompras->model()->removeRow(index.row());
   updateModels();

}

void principal::on_saveCompras_clicked()
{

}

void principal::on_addIngreso_clicked()
{
    Ingreso  newIngreso;
    newIngreso.setFecha(QDate::currentDate().toString(Qt::ISODate));
    finanzasBD.insert(newIngreso.toStringList(),BaseDatos::TABLA_INGRESOS);
    updateModels();
}

void principal::on_removeIngreso_clicked()
{
    QModelIndex index=ui->tableIngresos->currentIndex();
    ui->tableIngresos->model()->removeRow(index.row());
    updateModels();

}

void principal::on_saveIngresos_clicked()
{

}
void principal::updateModels(){
    ComprasModel=finanzasBD.TablasModel("COMPRAS");
    IngresosModel=finanzasBD.TablasModel("INGRESOS");
    MetodosPagoModel=finanzasBD.TablasModel("METODOS_PAGO");
    ui->tableCompras->setModel(ComprasModel);
    ui->tableCompras->hideColumn(0);
    ui->tableCompras->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");
    ui->tableIngresos->setModel(IngresosModel);
    ui->tableIngresos->hideColumn(0);
    ui->tableIngresos->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");
}
