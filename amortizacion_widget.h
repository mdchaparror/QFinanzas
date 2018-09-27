#ifndef AMORTIZACION_WIDGET_H
#define AMORTIZACION_WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
namespace Ui {
class Amortizacion_Widget;
}

class Amortizacion_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Amortizacion_Widget(QWidget *parent = 0);
    ~Amortizacion_Widget();

private slots:
    void on_Calcular_Amortizacion_clicked();

private:
    Ui::Amortizacion_Widget *ui;
    QStandardItemModel *AmortizacionModel;

};

#endif // AMORTIZACION_WIDGET_H
