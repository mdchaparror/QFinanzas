#include "ingresos.h"

Ingreso::Ingreso()
{
     id=0;
     fecha="0000-00-00";
     descripcion="SUELDO";
     valorDevengado=0.0;
     bono=0.0;
     aporteAFP=0.0;
     aporteEPS=0.0;
     aporteAFSP=0.0;
     valorNeto=0.0;
}

void Ingreso::setID(int x)
{
    id=x;
}
void Ingreso::setFecha(QString x){
    fecha=x;
}
void Ingreso::setDetalle(QString x){
    descripcion=x;
}
void Ingreso::setVdevengado(double x){
    valorDevengado=x;
}
void Ingreso::setBono(double x){
    bono=x;
}
void Ingreso::setAPF(double x){
    aporteAFP=x;
}
void Ingreso::setEPS(double x){
    aporteEPS=x;
}
void Ingreso::setAFSP(double x){
    aporteAFSP=x;
}
void Ingreso::setVneto(double x){
    valorNeto=x;
}

QStringList Ingreso::toStringList()
{
    QStringList reg;
  //  reg.append(QString::number(id));
    reg.append(fecha);
    reg.append(descripcion);
    reg.append(QString::number(valorDevengado));
    reg.append(QString::number(bono));
    reg.append(QString::number(aporteAFP));
    reg.append(QString::number(aporteEPS));
    reg.append(QString::number(aporteAFSP));
    reg.append(QString::number(valorNeto));
    return reg;

}
