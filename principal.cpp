#include "principal.h"
#include "ui_principal.h"

principal::principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);
}

principal::~principal()
{
    delete ui;
}
