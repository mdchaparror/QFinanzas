#ifndef CATEGORIACOMPRA_H
#define CATEGORIACOMPRA_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class CategoriaCompra;
}

class CategoriaCompra : public QDialog
{
    Q_OBJECT

public:
    explicit CategoriaCompra(QWidget *parent = 0);
    ~CategoriaCompra();

public slots:
    void setModel(QSqlTableModel *m);
private slots:
    void on_add_clicked();

    void on_remove_clicked();

private:
    Ui::CategoriaCompra *ui;
    QSqlTableModel *model;

};

#endif // CATEGORIACOMPRA_H
