#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QStringList>


class global
{
public:

    static QString usuario;
    static QString currentYear;
    static QString filterBD;
    static QString dir_bd;
    static int porcentajeAPF; //porcentaje Aporte fondo pensiones
    static int porcentajeEPS; //porcentaje Aporte Salud
    static int porcentajeAFSP;//porcentaje Aporte fondo solidario pensiones
    static int porcentajeIVA; //porcentaje inpuesto IVA
    static int porcentajeConsumo; //porcentaje inpuesto al consumo
    static QStringList metodosPago;
    static QStringList categoriaCompra;

   static void setMetodoPago(QStringList x);
    static void setCategoriaCompra(QStringList x);



};


#endif // GLOBAL_H
