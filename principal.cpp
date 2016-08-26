#include "principal.h"
#include "ui_principal.h"
#include <QResizeEvent>

principal::principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);



    MetodosPagoModel= new QSqlTableModel(this);






    finanzasBD = new BaseDatos(this);

     finanzasBD->open(global::dir_bd+global::usuario+".db");
    ui->comprasWidget->setBaseDatos(finanzasBD);
    ui->ingresosWidget->setBaseDatos(finanzasBD);
    ui->presupuestoWidget->setBaseDatos(finanzasBD);



    finanzasBD->createTable(BaseDatos::TABLA_METODOSPAGOS);


 MetodosPagoModel=finanzasBD->TablasModel("METODOS_PAGO");



    global::setMetodoPago(finanzasBD->getColumn("METODOS_PAGO","METODO"));

connect(MetodosPagoModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateMetodoPago()));




}

principal::~principal()
{
    delete ui;
    finanzasBD->close();
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











void principal::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    //ui->ComprasdockWidget->setSizeIncrement(size.width()/2,size.height()/2);
    qDebug()<<event->size();
}
