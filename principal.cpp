#include "principal.h"
#include "ui_principal.h"
#include <QResizeEvent>

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
    delegateP = new delegatePresupuesto(this);

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
    ui->tablePresupuesto->setItemDelegate(delegateP);

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
    ui->tableIngresos->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableCompras->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tablePresupuesto->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(MetodosPagoModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateMetodoPago()));
    connect(PresupuestoModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(dataPresupuestoChange()));

    connect(ui->tableIngresos, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestIngreso(QPoint)));
    connect(ui->tableCompras, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestCompras(QPoint)));
    connect(ui->tablePresupuesto, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestPresupuesto(QPoint)));

    ui->AmortizacionTable->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");
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

    if(QMessageBox::question(this,"Borrar registro","¿Desea borrar el registro?",QMessageBox::Yes| QMessageBox::No)==QMessageBox::Yes){
        QModelIndex index=ui->tableCompras->currentIndex();
        ui->tableCompras->model()->removeRow(index.row());
        ui->tableCompras->model()->sort(1);
    }
    else{
        return;
    }



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
    if(QMessageBox::question(this,"Borrar registro","¿Desea borrar el registro?",QMessageBox::Yes| QMessageBox::No)==QMessageBox::Yes){
        QModelIndex index=ui->tableIngresos->currentIndex();
        ui->tableIngresos->model()->removeRow(index.row());
        ui->tableIngresos->model()->sort(1);

    }
    else{
        return;
    }




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


    if(QMessageBox::question(this,"Borrar registro","¿Desea borrar el registro?",QMessageBox::Yes| QMessageBox::No)==QMessageBox::Yes){
        QModelIndex index=ui->tablePresupuesto->currentIndex();
        ui->tablePresupuesto->model()->removeRow(index.row());
        ui->tablePresupuesto->model()->sort(1);
        on_mes_currentTextChanged(ui->mes->currentText());

    }
    else{
        return;
    }




}

void principal::on_mes_currentTextChanged(const QString &arg1)
{
    QString filter=QString("MES='%1_%2'").arg(arg1).arg(ui->year->value());
    PresupuestoModel->setFilter(filter);
    ui->tablePresupuesto->model()->sort(1);
    dataPresupuestoChange();


}

void principal::dataPresupuestoChange()
{

    QString mes=ui->mes->currentText();
    QString filter=QString("MES='%1_%2'").arg(mes).arg(ui->year->value());
    double totalIngresos=finanzasBD.getSumCoulmna(BaseDatos::TABLA_PRESUPUESTO,"INGRESOS",filter);
    double totalGastos=finanzasBD.getSumCoulmna(BaseDatos::TABLA_PRESUPUESTO,"GASTOS",filter);
    ui->totalGastos->setValue(totalGastos);
    ui->totalIngresos->setValue(totalIngresos);

    ui->Totales->setValue(totalIngresos-totalGastos);
    if(ui->Totales->value()<0){
        ui->Totales->setStyleSheet("background-color: rgb(255, 0, 0)");
    }
    else{
        ui->Totales->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void principal::contextMenuRequestIngreso(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    menu->addAction(QIcon(":/imagenes/Imagenes/add.png"),"Añadir Ingreso", this, SLOT(on_addIngreso_clicked()));
    if(ui->tableIngresos->currentIndex().isValid())
        menu->addAction(QIcon(":/imagenes/Imagenes/quit.png"),"Remover Ingreso", this, SLOT(on_removeIngreso_clicked()));


    menu->popup(ui->tableIngresos->mapToGlobal(pos));
}

void principal::contextMenuRequestCompras(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction(QIcon(":/imagenes/Imagenes/add.png"),"Añadir Compra", this, SLOT(on_addCompra_clicked()));
    if(ui->tableCompras->currentIndex().isValid())
        menu->addAction(QIcon(":/imagenes/Imagenes/quit.png"),"Remover Compra", this, SLOT(on_removeCompra_clicked()));
    menu->popup(ui->tableCompras->mapToGlobal(pos));
}
void principal::contextMenuRequestPresupuesto(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction(QIcon(":/imagenes/Imagenes/add.png"),"Añadir registro", this, SLOT(on_addRegPresupuesto_clicked()));
    if(ui->tablePresupuesto->currentIndex().isValid())
        menu->addAction(QIcon(":/imagenes/Imagenes/quit.png"),"Remover registro", this, SLOT(on_removeRegPresupuesto_clicked()));
    menu->popup(ui->tablePresupuesto->mapToGlobal(pos));
}

void principal::resizeEvent(QResizeEvent *re){



    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
    QWidget::resizeEvent(re);
}





void principal::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 1:
        for(int i=1;i<ui->tableCompras->model()->columnCount();i++){
            ui->tableCompras->setColumnWidth(i,ui->tableCompras->rect().width()/(ui->tableCompras->model()->columnCount()-1)-2);

        }
        break;
    case 2:
        for(int i=1;i<ui->tableIngresos->model()->columnCount();i++){
            ui->tableIngresos->setColumnWidth(i,ui->tableIngresos->rect().width()/(ui->tableIngresos->model()->columnCount()-1)-2);
        }
        break;

    case 3:
        int size =ui->tablePresupuesto->rect().width()-18;
        for(int i = 2;i<5;i++){
            ui->tablePresupuesto->setColumnWidth(i,size/(ui->tablePresupuesto->model()->columnCount()-2));
            ui->totalGastos->setMinimumWidth(size/3);
            ui->totalIngresos->setMinimumWidth(size/3);
            ui->Totales->setMinimumWidth(size*2/3);
            ui->labelSubTotal->setMaximumWidth(size/3);
            ui->labelTotal->setMaximumWidth(size/3);
        }
        break;

    }
}

void principal::on_Calcular_Amortizacion_clicked()
{
    double saldo= ui->Valor->value();
    double interesMensual = ui->interesAnual->value()/12.0/100;
    int nCuotas= ui->nCuotas->value();
    double cuotaMensual = (double)saldo/nCuotas;
    AmortizacionModel = new QStandardItemModel(nCuotas+1,5,this);
    QModelIndex index;
    index = AmortizacionModel->index(0,0,QModelIndex());
    AmortizacionModel->setData(index,0);
    index = AmortizacionModel->index(0,1,QModelIndex());
    AmortizacionModel->setData(index,saldo);

    for(int i= 1;i<nCuotas+1;i++){
        index = AmortizacionModel->index(i,0,QModelIndex());
        AmortizacionModel->setData(index,i);
        double interes=saldo*interesMensual;
        saldo -= cuotaMensual;
        double pago = interes+cuotaMensual;
        index = AmortizacionModel->index(i,1,QModelIndex());
        AmortizacionModel->setData(index,qRound(saldo));
        index = AmortizacionModel->index(i,2,QModelIndex());
        AmortizacionModel->setData(index,cuotaMensual);
        index = AmortizacionModel->index(i,3,QModelIndex());
        AmortizacionModel->setData(index,interes);
        index = AmortizacionModel->index(i,4,QModelIndex());
        AmortizacionModel->setData(index,pago);



    }
    QStringList headers;
    headers<<"Mes"<<"Saldo"<<"Amortización"<<"Interés"<<"Cuota";
    AmortizacionModel->setHorizontalHeaderLabels(headers);
    ui->AmortizacionTable->setModel(AmortizacionModel);
}
