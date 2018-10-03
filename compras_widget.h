#ifndef COMPRAS_WIDGET_H
#define COMPRAS_WIDGET_H

#include <QWidget>
#include <QDebug>
#include "compra.h"
#include "global.h"
#include "basedatos.h"
#include "delegatecompras.h"
namespace Ui {
class Compras_Widget;
}

class Compras_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Compras_Widget(QWidget *parent = 0);
    ~Compras_Widget();
public slots:
     void setBaseDatos(BaseDatos *bd);
private slots:
    void on_addCompra_clicked();

    void on_removeCompra_clicked();
    void addSoporte();

    void on_saveCompras_clicked();

   void contextMenuRequestCompras(QPoint pos);
private:
    Ui::Compras_Widget *ui;
     BaseDatos *finanzasBD;
     QSqlTableModel*  ComprasModel;
     DelegateCompras *delegateC;
};

#endif // COMPRAS_WIDGET_H
