#include "presupuesto_widget.h"
#include "ui_presupuesto_widget.h"
#include <QMenu>
Presupuesto_Widget::Presupuesto_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Presupuesto_Widget)
{
    ui->setupUi(this);
    PresupuestoModel= new QSqlTableModel(this);
    delegateP = new delegatePresupuesto(this);
    ui->tablePresupuesto->setItemDelegate(delegateP);
     ui->tablePresupuesto->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");
     ui->tablePresupuesto->hideColumn(0);
     ui->tablePresupuesto->hideColumn(1);
     ui->year->setValue(QDate::currentDate().year());

      ui->tablePresupuesto->setContextMenuPolicy(Qt::CustomContextMenu);

      connect(PresupuestoModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(dataPresupuestoChange()));
       connect(ui->tablePresupuesto, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestPresupuesto(QPoint)));


}

Presupuesto_Widget::~Presupuesto_Widget()
{
    delete ui;
}

void Presupuesto_Widget::setBaseDatos(BaseDatos *bd)
{
    finanzasBD = bd;
    finanzasBD->createTable(BaseDatos::TABLA_PRESUPUESTO);
    PresupuestoModel=finanzasBD->TablasModel("PRESUPUESTO");
    ui->tablePresupuesto->setModel(PresupuestoModel);
    ui->mes->setCurrentIndex(QDate::currentDate().month()-1);


}

void Presupuesto_Widget::on_addRegPresupuesto_clicked()
{
    Presupuesto newReg;
    newReg.setMes(ui->mes->currentText()+"_"+QString::number(ui->year->value()));
    finanzasBD->insert(newReg.toStringList(),BaseDatos::TABLA_PRESUPUESTO);

    ui->tablePresupuesto->model()->sort(1);
    on_mes_currentTextChanged(ui->mes->currentText());
}

void Presupuesto_Widget::on_removeRegPresupuesto_clicked()
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
void Presupuesto_Widget::dataPresupuestoChange()
{

    QString mes=ui->mes->currentText();
    QString filter=QString("MES='%1_%2'").arg(mes).arg(ui->year->value());
    double totalIngresos=finanzasBD->getSumCoulmna(BaseDatos::TABLA_PRESUPUESTO,"INGRESOS",filter);
    double totalGastos=finanzasBD->getSumCoulmna(BaseDatos::TABLA_PRESUPUESTO,"GASTOS",filter);
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

void Presupuesto_Widget::contextMenuRequestPresupuesto(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction(QIcon(":/imagenes/Imagenes/add.png"),"Añadir registro", this, SLOT(on_addRegPresupuesto_clicked()));
    if(ui->tablePresupuesto->currentIndex().isValid())
        menu->addAction(QIcon(":/imagenes/Imagenes/quit.png"),"Remover registro", this, SLOT(on_removeRegPresupuesto_clicked()));
    menu->popup(ui->tablePresupuesto->mapToGlobal(pos));
}


void Presupuesto_Widget::on_mes_currentTextChanged(const QString &arg1)
{
    QString filter=QString("MES='%1_%2'").arg(arg1).arg(ui->year->value());
    PresupuestoModel->setFilter(filter);
    ui->tablePresupuesto->model()->sort(1);
    dataPresupuestoChange();
}
