#ifndef PRESUPUESTO_H
#define PRESUPUESTO_H
#include<QString>
#include <QStringList>

class Presupuesto
{
public:
    Presupuesto();
    QStringList toStringList();
    void setId(int x){id=x;}
    void setMes(QString x){mes=x;}
    void setDetalle(QString x){detalle=x;}
    void setDebito(double x){debito=x;}
    void setCredito(double x){credito=x;}
    int getId(){return id;}
    QString getMes(){return mes;}
    QString getDetalle(){return detalle;}
    double getDebito(){return debito;}
    double getCredito(){return credito;}


 private:
    int id;
    QString mes;
    QString detalle;
    double debito;
    double credito;

};

#endif // PRESUPUESTO_H
