#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QStringList>


class global
{
public:

    static QString usuario;
    static QString dir_bd;
    static int porcentajeAPF; //porcentaje Aporte fondo pensiones
    static int porcentajeEPS; //porcentaje Aporte Salud
    static int porcentajeAFSP;//porcentaje Aporte fondo solidario pensiones
    static int porcentajeIVA; //porcentaje inpuesto IVA
    static int porcentajeConsumo; //porcentaje inpuesto al consumo
    static QStringList metodosPago;

   static void setMetodoPago(QStringList x);




};


#endif // GLOBAL_H
