#ifndef PRESUPUESTO_WIDGET_H
#define PRESUPUESTO_WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "basedatos.h"
#include "delegatepresupuesto.h"
#include "presupuesto.h"

namespace Ui {
class Presupuesto_Widget;
}

class Presupuesto_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Presupuesto_Widget(QWidget *parent = 0);
    ~Presupuesto_Widget();
public slots:
    void setBaseDatos(BaseDatos *bd);

private slots:
    void on_addRegPresupuesto_clicked();

    void on_removeRegPresupuesto_clicked();
    void dataPresupuestoChange();
    void contextMenuRequestPresupuesto(QPoint pos);



    void on_mes_currentTextChanged(const QString &arg1);

private:
    Ui::Presupuesto_Widget *ui;
     BaseDatos *finanzasBD;
     QSqlTableModel*  PresupuestoModel;
     delegatePresupuesto *delegateP;

};

#endif // PRESUPUESTO_WIDGET_H
