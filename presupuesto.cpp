#include "presupuesto.h"

Presupuesto::Presupuesto()
{
    id=0;
    mes="ENERO";
    detalle="";
    debito=0.0;
    credito=0.0;
}

QStringList Presupuesto::toStringList()
{
    QStringList reg;
    reg.append(mes);
    reg.append(detalle);
    reg.append(QString::number(debito));
    reg.append(QString::number(credito));
    return reg;

}
