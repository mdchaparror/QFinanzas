#include "amortizacion_widget.h"
#include "ui_amortizacion_widget.h"

Amortizacion_Widget::Amortizacion_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Amortizacion_Widget)
{
    ui->setupUi(this);
    ui->AmortizacionTable2->setStyleSheet("alternate-background-color: rgb(170, 255, 255)");
}

Amortizacion_Widget::~Amortizacion_Widget()
{
    delete ui;
}

void Amortizacion_Widget::on_Calcular_Amortizacion_clicked()
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
    ui->AmortizacionTable2->setModel(AmortizacionModel);
}
