#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QStringList>


class global
{
public:

    static QString usuario;
    static int currentYear;
    static QString filterBD;
    static QString dir_bd;
    static double porcentajeAPF; //porcentaje Aporte fondo pensiones
    static double porcentajeEPS; //porcentaje Aporte Salud
    static double porcentajeAFSP;//porcentaje Aporte fondo solidario pensiones
    static double porcentajeIVA; //porcentaje inpuesto IVA
    static double porcentajeConsumo; //porcentaje inpuesto al consumo
    static QStringList metodosPago;
    static QStringList categoriaCompra;

   static void setMetodoPago(QStringList x);
    static void setCategoriaCompra(QStringList x);



};


#endif // GLOBAL_H
