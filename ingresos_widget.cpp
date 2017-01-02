#include "ingresos_widget.h"
#include "ui_ingresos_widget.h"
#include <QMenu>
#include <QMessageBox>
Ingresos_Widget::Ingresos_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ingresos_Widget)
{
    ui->setupUi(this);
    IngresosModel = new  QSqlTableModel(this);
    delegateI = new delegateIngreso(this);
    ui->tableIngresos->setItemDelegate(delegateI);

    ui->tableIngresos->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");

    ui->tableIngresos->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableIngresos, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestIngreso(QPoint)));

}

Ingresos_Widget::~Ingresos_Widget()
{
    delete ui;
}

void Ingresos_Widget::setBaseDatos(BaseDatos *bd)
{
    finanzasBD = bd;
    finanzasBD->createTable(BaseDatos::TABLA_INGRESOS);
    IngresosModel=finanzasBD->TablasModel("INGRESOS");
    IngresosModel->setFilter(global::filterBD);
    ui->tableIngresos->setModel(IngresosModel);
    ui->tableIngresos->resizeColumnsToContents();
    ui->tableIngresos->hideColumn(0);
    ui->tableIngresos->sortByColumn(1);

}

void Ingresos_Widget::on_addIngreso_clicked()
{
    Ingreso  newIngreso;
    newIngreso.setFecha(QDate::currentDate().toString(Qt::ISODate));
    finanzasBD->insert(newIngreso.toStringList(),BaseDatos::TABLA_INGRESOS);
    ui->tableIngresos->model()->sort(1);
}

void Ingresos_Widget::on_removeIngreso_clicked()
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

void Ingresos_Widget::contextMenuRequestIngreso(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    menu->addAction(QIcon(":/imagenes/Imagenes/add.png"),"Añadir Ingreso", this, SLOT(on_addIngreso_clicked()));
    if(ui->tableIngresos->currentIndex().isValid())
        menu->addAction(QIcon(":/imagenes/Imagenes/quit.png"),"Remover Ingreso", this, SLOT(on_removeIngreso_clicked()));


    menu->popup(ui->tableIngresos->mapToGlobal(pos));
}

void Ingresos_Widget::on_saveIngresos_clicked()
{

}
