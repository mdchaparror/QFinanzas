#ifndef INGRESO_H
#define INGRESO_H
#include <QString>
#include <QStringList>

class Ingreso
{
public:
    Ingreso();
    int getID(){return id;}
    QString getFecha(){return fecha;}
    QString getDet(){return descripcion;}
    double  getVdevengado(){return valorDevengado;}
    double getBono(){return bono;}
    double getAPF(){ return aporteAFP;}
    double getEPS(){ return aporteEPS;}
    double getAFSP(){return aporteAFSP;}
    double getVneto(){return  valorNeto;}
    void setID (int x);
    void setFecha(QString x);
    void setDetalle(QString x);
    void setVdevengado(double x);
    void setBono(double x);
    void setAPF(double x);
    void setEPS(double x);
    void setAFSP(double x);
    void setVneto(double x);
    QStringList toStringList();
private:
    int id;
    QString fecha;
    QString descripcion;
    double  valorDevengado;
    double  bono;
    double  aporteAFP; //Aporte fondo pensiones
    double  aporteEPS;   //Aporte EPS
    double  aporteAFSP;  //Aporte fondo solidario de pensiones
    double  valorNeto;


};

#endif // INGRESOS_H
