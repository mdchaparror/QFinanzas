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

    finanzasBD.open(global::dir_bd+global::usuario+".db");
    finanzasBD.createTable(BaseDatos::TABLA_COMPRAS);
    finanzasBD.createTable(BaseDatos::TABLA_INGRESOS);
    finanzasBD.createTable(BaseDatos::TABLA_METODOSPAGOS);

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

principal::~principal()
{
    delete ui;
    finanzasBD.close();
}

void principal::on_addCompra_clicked()
{

}

void principal::on_removeCompra_clicked()
{

}

void principal::on_saveCompras_clicked()
{

}

void principal::on_addIngreso_clicked()
{

}

void principal::on_removeIngreso_clicked()
{

}

void principal::on_saveIngresos_clicked()
{

}
