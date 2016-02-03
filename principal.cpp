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
    PresupuestoModel= new QSqlTableModel(this);


    delegateC = new DelegateCompras(this);
    delegateI = new delegateIngreso(this);

    finanzasBD.open(global::dir_bd+global::usuario+".db");
    finanzasBD.createTable(BaseDatos::TABLA_COMPRAS);
    finanzasBD.createTable(BaseDatos::TABLA_INGRESOS);
    finanzasBD.createTable(BaseDatos::TABLA_METODOSPAGOS);
    finanzasBD.createTable(BaseDatos::TABLA_PRESUPUESTO);

    ComprasModel=finanzasBD.TablasModel("COMPRAS");
    IngresosModel=finanzasBD.TablasModel("INGRESOS");
    MetodosPagoModel=finanzasBD.TablasModel("METODOS_PAGO");
    PresupuestoModel=finanzasBD.TablasModel("PRESUPUESTO");

    global::setMetodoPago(finanzasBD.getColumn("METODOS_PAGO","METODO"));

    ui->tableCompras->setItemDelegate(delegateC);
    ui->tableIngresos->setItemDelegate(delegateI);
    ui->tableCompras->setModel(ComprasModel);
    ui->tableCompras->hideColumn(0);
    ui->tableCompras->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");

    ui->tableIngresos->setModel(IngresosModel);
    ui->tableIngresos->hideColumn(0);
    ui->tableIngresos->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");

    ui->tablePresupuesto->setModel(PresupuestoModel);
    ui->tablePresupuesto->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");
    ui->tablePresupuesto->hideColumn(0);
    ui->tablePresupuesto->hideColumn(1);
    ui->year->setValue(QDate::currentDate().year());
    ui->mes->setCurrentIndex(QDate::currentDate().month()-1);



    ui->tableIngresos->resizeColumnsToContents();
    ui->tableCompras->resizeColumnsToContents();

    connect(MetodosPagoModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateMetodoPago()));




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
    finanzasBD.insert(newCompra.toStringList(),BaseDatos::TABLA_COMPRAS);
    ui->tableCompras->model()->sort(1);



}

void principal::on_removeCompra_clicked()
{
    QModelIndex index=ui->tableCompras->currentIndex();
    ui->tableCompras->model()->removeRow(index.row());
    ui->tableCompras->model()->sort(1);

}

void principal::on_saveCompras_clicked()
{

}

void principal::on_addIngreso_clicked()
{
    Ingreso  newIngreso;
    newIngreso.setFecha(QDate::currentDate().toString(Qt::ISODate));
    finanzasBD.insert(newIngreso.toStringList(),BaseDatos::TABLA_INGRESOS);
    ui->tableIngresos->model()->sort(1);

}

void principal::on_removeIngreso_clicked()
{
    QModelIndex index=ui->tableIngresos->currentIndex();
    ui->tableIngresos->model()->removeRow(index.row());
    ui->tableIngresos->model()->sort(1);



}

void principal::on_saveIngresos_clicked()
{

}


void principal::on_actionAdd_Metodo_de_Pago_triggered()
{
    metodoPago = new MetodoPago(this);
    metodoPago->setModel(MetodosPagoModel);
    metodoPago->show();

}
void principal::updateMetodoPago(){
    global::setMetodoPago(finanzasBD.getColumn("METODOS_PAGO","METODO"));
}





void principal::on_addRegPresupuesto_clicked()
{
    Presupuesto newReg;
    newReg.setMes(ui->mes->currentText()+"_"+QString::number(ui->year->value()));
    finanzasBD.insert(newReg.toStringList(),BaseDatos::TABLA_PRESUPUESTO);

    ui->tablePresupuesto->model()->sort(1);
    on_mes_currentTextChanged(ui->mes->currentText());

}

void principal::on_removeRegPresupuesto_clicked()
{

    QModelIndex index=ui->tablePresupuesto->currentIndex();
    ui->tablePresupuesto->model()->removeRow(index.row());
    ui->tablePresupuesto->model()->sort(1);
    on_mes_currentTextChanged(ui->mes->currentText());

}

void principal::on_mes_currentTextChanged(const QString &arg1)
{
    QString filter=QString("MES='%1_%2'").arg(arg1).arg(ui->year->value());
    PresupuestoModel->setFilter(filter);
    ui->tablePresupuesto->model()->sort(1);
    double totalDebito=finanzasBD.getSumCoulmna(BaseDatos::TABLA_PRESUPUESTO,"DEBITO",filter);
    double totalCredito=finanzasBD.getSumCoulmna(BaseDatos::TABLA_PRESUPUESTO,"CREDITO",filter);
    ui->totalCredito->setValue(totalCredito);
    ui->totalDebito->setValue(totalDebito);

}

void principal::on_totalDebito_valueChanged(double arg1)
{
    ui->Totales->setValue(arg1-ui->totalCredito->value());
    if(ui->Totales->value()<0){
       ui->Totales->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    else{
        ui->Totales->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}
