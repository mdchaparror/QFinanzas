#include "categoriacompra.h"
#include "ui_categoriacompra.h"


CategoriaCompra::CategoriaCompra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CategoriaCompra)
{
    ui->setupUi(this);
}

CategoriaCompra::~CategoriaCompra()
{
    delete ui;
}

void CategoriaCompra::on_add_clicked()
{
    ui->categoriaCompra->model()->insertRow(0);


}

void CategoriaCompra::on_remove_clicked()
{
    QModelIndex index=ui->categoriaCompra->currentIndex();
    ui->categoriaCompra->model()->removeRow(index.row());
    ui->categoriaCompra->model()->sort(1);

}
void CategoriaCompra::setModel(QSqlTableModel *m)
{
    model=m;
    ui->categoriaCompra->setModel(model);


}


