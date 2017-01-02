#include "principal.h"
#include "ui_principal.h"
#include <QResizeEvent>

principal::principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);



    MetodosPagoModel= new QSqlTableModel(this);
    report = new ReportExcel();
    finanzasBD = new BaseDatos(this);
    finanzasBD->open(global::dir_bd+global::usuario+".db");
    ui->comprasWidget->setBaseDatos(finanzasBD);
    ui->ingresosWidget->setBaseDatos(finanzasBD);

    ui->presupuestoWidget->setBaseDatos(finanzasBD);
    ui->presupuestoWidget->setReportes(report);



    finanzasBD->createTable(BaseDatos::TABLA_METODOSPAGOS);
    finanzasBD->createTable(BaseDatos::TABLA_CATEGORIA_COMPRA);

    MetodosPagoModel=finanzasBD->TablasModel("METODOS_PAGO");

    CategoriaComprasModel=finanzasBD->TablasModel("CATEGORIA_COMPRA");


    global::setMetodoPago(finanzasBD->getColumn("METODOS_PAGO","METODO"));
    global::setCategoriaCompra(finanzasBD->getColumn("CATEGORIA_COMPRA","CATEGORIA"));

    connect(MetodosPagoModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateMetodoPago()));
    connect(CategoriaComprasModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateCategoriaCompra()));



}

principal::~principal()
{
    delete ui;
    finanzasBD->close();
    delete report;
}


void principal::on_actionAdd_Categoria_Compra_triggered()
{
    categoriaCompra = new CategoriaCompra(this);
    categoriaCompra->setModel(CategoriaComprasModel);
    categoriaCompra->show();
}





void principal::on_actionAdd_Metodo_de_Pago_triggered()
{
    metodoPago = new MetodoPago(this);
    metodoPago->setModel(MetodosPagoModel);
    metodoPago->show();

}
void principal::updateMetodoPago(){
    global::setMetodoPago(finanzasBD->getColumn("METODOS_PAGO","METODO"));
}
void principal::updateCategoriaCompra(){
   global::setCategoriaCompra(finanzasBD->getColumn("CATEGORIA_COMPRA","CATEGORIA"));
}

void principal::resizeEvent(QResizeEvent *event)
{

    qDebug()<<event->size();
}

