#include "compra.h"

compra::compra()
{
    id=0;
    fecha="0000-00-00";
    descripcion="";
    metodoPago="EFECTIVO";
    subValor=0.0;
    impIVA=0.0;
    impConsumo=0.0;
    valorTotal=0.0;
    numeroCuotas=1;
    categoria="";
}
compra::compra(int id,QString fecha, QString det,double sub, double iva,double consumo,double total,QString pago,int cuotas,QString categ){
  id=id;
  fecha=fecha;
  descripcion=det;
  subValor=sub;
  impIVA=iva;
  impConsumo=consumo;
  valorTotal=total;
  metodoPago=pago;
  numeroCuotas=cuotas;
  categoria=categ;
}

QStringList compra::toStringList()
{
    QStringList reg;
    //reg.append(QString::number(id));
    reg.append(fecha);
    reg.append(descripcion);
    reg.append(QString::number(subValor));
    reg.append(QString::number(impIVA));
    reg.append(QString::number(impConsumo));
    reg.append(QString::number(valorTotal));
    reg.append(metodoPago);
    reg.append(QString::number(numeroCuotas));
    reg.append(categoria);

    return reg;
}

QString compra::getCategoria() const
{
    return categoria;
}

void compra::setCategoria(const QString &value)
{
    categoria = value;
}

