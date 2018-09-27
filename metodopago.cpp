#include "metodopago.h"
#include "ui_metodopago.h"

MetodoPago::MetodoPago(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetodoPago)
{
    ui->setupUi(this);
}

MetodoPago::~MetodoPago()
{
    delete ui;


}

void MetodoPago::on_add_clicked()
{

  ui->metodoPago->model()->insertRow(0);

}

void MetodoPago::on_remove_clicked()
{
    QModelIndex index=ui->metodoPago->currentIndex();
    ui->metodoPago->model()->removeRow(index.row());
    ui->metodoPago->model()->sort(1);


}

void MetodoPago::setModel(QSqlTableModel *m)
{
    model=m;
    ui->metodoPago->setModel(model);


}


