#ifndef METODOPAGO_H
#define METODOPAGO_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class MetodoPago;
}

class MetodoPago : public QDialog
{
    Q_OBJECT

public:
    explicit MetodoPago(QWidget *parent = 0);
    ~MetodoPago();

private slots:
    void on_add_clicked();

    void on_remove_clicked();



public slots:

    void setModel(QSqlTableModel *m);

private:
    Ui::MetodoPago *ui;
    QSqlTableModel *model;
};

#endif // METODOPAGO_H
