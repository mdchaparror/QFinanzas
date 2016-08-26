#include "compras_widget.h"
#include "ui_compras_widget.h"
#include "compra.h"
#include "delegatecompras.h"
#include <QMessageBox>
#include <QMenu>
Compras_Widget::Compras_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Compras_Widget)
{
    ui->setupUi(this);
    ComprasModel = new  QSqlTableModel(this);
    delegateC = new DelegateCompras(this);


    ui->tableCompras->setItemDelegate(delegateC);
    ui->tableCompras->setModel(ComprasModel);
    ui->tableCompras->hideColumn(0);
    ui->tableCompras->resizeColumnsToContents();
    ui->tableCompras->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableCompras, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestCompras(QPoint)));
    ui->tableCompras->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");
}

Compras_Widget::~Compras_Widget()
{
    delete ui;
}

void Compras_Widget::on_addCompra_clicked()
{
    compra newCompra;
    newCompra.setFecha(QDate::currentDate().toString(Qt::ISODate));
    finanzasBD->insert(newCompra.toStringList(),BaseDatos::TABLA_COMPRAS);
    ui->tableCompras->model()->sort(1);
}

void Compras_Widget::on_removeCompra_clicked()
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

void Compras_Widget::on_saveCompras_clicked()
{

}

void Compras_Widget::setBaseDatos(BaseDatos *bd)
{
    finanzasBD = bd;
    ComprasModel=finanzasBD->TablasModel("COMPRAS");
    finanzasBD->createTable(BaseDatos::TABLA_COMPRAS);
    ui->tableCompras->setModel(ComprasModel);
}
void Compras_Widget::contextMenuRequestCompras(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction(QIcon(":/imagenes/Imagenes/add.png"),"Añadir Compra", this, SLOT(on_addCompra_clicked()));
    if(ui->tableCompras->currentIndex().isValid())
        menu->addAction(QIcon(":/imagenes/Imagenes/quit.png"),"Remover Compra", this, SLOT(on_removeCompra_clicked()));
    menu->popup(ui->tableCompras->mapToGlobal(pos));
}
