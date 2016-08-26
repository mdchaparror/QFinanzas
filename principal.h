#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "global.h"
#include "basedatos.h"
#include "metodopago.h"

namespace Ui {
class principal;
}

class principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit principal(QWidget *parent = 0);
    ~principal();

private slots:











    void on_actionAdd_Metodo_de_Pago_triggered();
    void updateMetodoPago();


protected:
  virtual void	resizeEvent(QResizeEvent * event);

private:
    Ui::principal *ui;
    BaseDatos *finanzasBD;
    QSqlTableModel*  MetodosPagoModel;
    MetodoPago *metodoPago;


};

#endif // PRINCIPAL_H
