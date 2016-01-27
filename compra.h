#ifndef COMPRA_H
#define COMPRA_H
#include <QString>
#include <QStringList>
class compra
{
public:
    compra();
    compra(int id, QString fecha, QString det, double sub, double iva, double consumo, double total, QString pago, int cuotas);
    int getId(){return id;}
    QString getFecha(){return fecha;}
    QString getDet(){return descripcion;}
    QString getMetodoPago(){return metodoPago;}
    int getNumeroCuotas(){return numeroCuotas;}

    double getSubValor(){return subValor;}
    double getIva(){return impIVA;}
    double getConsumo(){return impConsumo;}
    double getTotal(){return valorTotal;}
    void setId(int  tmp){id=tmp;}
    void setFecha(QString  tmp){fecha=tmp;}
    void setDet(QString tmp){descripcion=tmp;}
    void setSubValor(double tmp){subValor=tmp;}
    void setIva(double tmp){impIVA=tmp;}
    void setConsumo(double tmp){impConsumo=tmp;}
    void setTotal(double tmp){valorTotal=tmp;}
    void setTotal(QString tmp){metodoPago=tmp;}
    void setTotal(int tmp){numeroCuotas=tmp;}
    QStringList toStringList();
private:
    int id;
    QString fecha;
    QString descripcion;
    QString metodoPago;
    double subValor;
    double impIVA;  //impuesto iva
    double impConsumo; //impuesto al consumo
    double valorTotal;
    int numeroCuotas;


};

#endif // COMPRA_H
