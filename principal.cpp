#include "principal.h"
#include "ui_principal.h"
#include <QResizeEvent>
#include <QSettings>
#include <QDebug>

principal::principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::principal)
{

    ui->setupUi(this);

    config = new configDialog(this);
    connect(config,SIGNAL(save()),this,SLOT(saveConfiguracion()));
    loadConfiguracion();



    MetodosPagoModel= new QSqlTableModel(this);
    report = new ReportExcel();
    finanzasBD = new BaseDatos(this);
    finanzasBD->open(global::dir_bd+global::usuario+".db");
    ui->comprasWidget->setBaseDatos(finanzasBD);
    ui->ingresosWidget->setBaseDatos(finanzasBD);

    ui->presupuestoWidget->setBaseDatos(finanzasBD);
    ui->presupuestoWidget->setReportes(report);



    finanzasBD->createTable(BaseDatos::TABLA_METODOSPAGOS);
    finanzasBD->createTable(BaseDatos::TABLA_CATEGORIA_COMPRA);

    MetodosPagoModel=finanzasBD->TablasModel("METODOS_PAGO");

    CategoriaComprasModel=finanzasBD->TablasModel("CATEGORIA_COMPRA");


    global::setMetodoPago(finanzasBD->getColumn("METODOS_PAGO","METODO"));
    global::setCategoriaCompra(finanzasBD->getColumn("CATEGORIA_COMPRA","CATEGORIA"));

    connect(MetodosPagoModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateMetodoPago()));
    connect(CategoriaComprasModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(updateCategoriaCompra()));



}

principal::~principal()
{
    saveConfiguracion();
    delete ui;
    finanzasBD->close();
    delete report;
}


void principal::on_actionAdd_Categoria_Compra_triggered()
{
    categoriaCompra = new CategoriaCompra(this);
    categoriaCompra->setModel(CategoriaComprasModel);
    categoriaCompra->show();
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
void principal::updateCategoriaCompra(){
   global::setCategoriaCompra(finanzasBD->getColumn("CATEGORIA_COMPRA","CATEGORIA"));
}

void principal::resizeEvent(QResizeEvent *event)
{

    qDebug()<<event->size();
}


void principal::on_actionShowAmortizacion_toggled(bool arg1)
{
    ui->amortizacionWidget->setVisible(arg1);
    verAmortizacion=arg1;
     ui->actionShowAmortizacion->setChecked(arg1);

}

void principal::on_actionCompras_toggled(bool arg1)
{
    ui->comprasWidget->setVisible(arg1);
    verCompras=arg1;
    ui->actionCompras->setChecked(arg1);
}

void principal::on_actionIngresos_toggled(bool arg1)
{
    ui->ingresosWidget->setVisible(arg1);
    verIngresos=arg1;
    ui->actionIngresos->setChecked(arg1);
}

void principal::on_actionPresupuesto_toggled(bool arg1)
{
    ui->presupuestoWidget->setVisible(arg1);
    verPresupuesto=arg1;
    ui->actionPresupuesto->setChecked(arg1);
}

void principal::on_actionConfiguracion_triggered()
{
    config->show();
}

void principal::saveConfiguracion()
{
    QSettings settings("mdchaparror","finanza");
    settings.beginGroup("Mainwindow");
    settings.setValue("usuario", global::usuario);
    settings.setValue("year", global::currentYear);
    settings.setValue("APF", global::porcentajeAPF);
    settings.setValue("EPS", global::porcentajeEPS);
    settings.setValue("AFSP", global::porcentajeAFSP);
    settings.setValue("IVA", global::porcentajeIVA);
    settings.setValue("CONSUMO", global::porcentajeConsumo);
    settings.setValue("VER_PRESUPUESTO",verPresupuesto);
    settings.setValue("VER_COMPRAS",verCompras);
    settings.setValue("VER_AMORTIZACION",verAmortizacion);
    settings.setValue("VER_INGRESOS",verIngresos);
    settings.setValue("TEMA",global::tema);
    settings.endGroup();
     setStyleSheet(global::stringFromResource(global::tema));
    qDebug()<<"Configuracion Guardada ";

}

void principal::loadConfiguracion()
{
    QSettings settings("mdchaparror","finanza");
    settings.beginGroup("Mainwindow");
    global::usuario=settings.value("usuario").toString();
    global::currentYear=settings.value("year").toInt();
    global::porcentajeAPF = settings.value("APF").toDouble();
    global::porcentajeEPS=settings.value("EPS").toDouble();
    global::porcentajeAFSP =settings.value("AFSP").toDouble();
    global::porcentajeIVA =settings.value("IVA").toDouble();
    global::porcentajeConsumo =settings.value("CONSUMO").toDouble();
    global::tema=settings.value("TEMA").toString();
    verPresupuesto=settings.value("VER_PRESUPUESTO").toBool();
    verAmortizacion=settings.value("VER_AMORTIZACION").toBool();
    verCompras=settings.value("VER_COMPRAS").toBool();
    verIngresos=settings.value("VER_INGRESOS").toBool();

    settings.endGroup();
    on_actionCompras_toggled(verCompras);
    on_actionIngresos_toggled(verIngresos);
    on_actionPresupuesto_toggled(verPresupuesto);
    on_actionShowAmortizacion_toggled(verAmortizacion);


    global::filterBD=QString("fecha like '%1%'").arg(global::currentYear);
    setStyleSheet(global::stringFromResource(global::tema));
    qDebug()<<"Configuracion Cargada";
}
