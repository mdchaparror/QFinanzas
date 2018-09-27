#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <QWidget>

namespace Ui {
class Configuracion;
}

class Configuracion : public QWidget
{
    Q_OBJECT

public:
    explicit Configuracion(QWidget *parent = 0);
    ~Configuracion();

private:
    Ui::Configuracion *ui;
};

#endif // CONFIGURACION_H
