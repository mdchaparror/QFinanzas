#ifndef INGRESOS_WIDGET_H
#define INGRESOS_WIDGET_H

#include <QWidget>
#include "basedatos.h"
#include "ingresos.h"
#include "delegateingreso.h"

namespace Ui {
class Ingresos_Widget;
}

class Ingresos_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Ingresos_Widget(QWidget *parent = 0);
    ~Ingresos_Widget();

public slots:
    void setBaseDatos(BaseDatos *bd);
private slots:
    void on_addIngreso_clicked();

    void on_removeIngreso_clicked();
    void contextMenuRequestIngreso(QPoint pos);

    void on_saveIngresos_clicked();

private:
    Ui::Ingresos_Widget *ui;
     BaseDatos *finanzasBD;
     QSqlTableModel*  IngresosModel;
     delegateIngreso *delegateI;
};

#endif // INGRESOS_WIDGET_H
