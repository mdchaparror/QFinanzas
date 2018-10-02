#include "configdialog.h"
#include "ui_configdialog.h"

configDialog::configDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configDialog)
{
    ui->setupUi(this);
}

configDialog::~configDialog()
{
    delete ui;
}

void configDialog::loadConfig()
{
    ui->usuario->setText(global::usuario);
    ui->year->setValue(global::currentYear);
    ui->AFP->setValue(global::porcentajeAPF);
    ui->EPS->setValue(global::porcentajeEPS);
    ui->AFSP->setValue(global::porcentajeAFSP);
    ui->IVA->setValue(global::porcentajeIVA);
    ui->CONSUMO->setValue(global::porcentajeConsumo);

}

void configDialog::on_save_clicked()
{


    global::usuario=ui->usuario->text();
    global::currentYear=ui->year->value();
    global::porcentajeAPF=ui->AFP->value();
    global::porcentajeEPS=ui->EPS->value();
    global::porcentajeAFSP=ui->AFSP->value();
    global::porcentajeIVA=ui->IVA->value();
    global::porcentajeConsumo=ui->CONSUMO->value();
    global::filterBD=QString("fecha like '%1%'").arg(global::currentYear);

}
