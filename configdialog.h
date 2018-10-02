#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include "global.h"
namespace Ui {
class configDialog;
}

class configDialog : public QDialog
{
    Q_OBJECT

public:
    explicit configDialog(QWidget *parent = nullptr);
    ~configDialog();
public slots:
    void loadConfig();
private slots:
    void on_save_clicked();

private:
    Ui::configDialog *ui;
};

#endif // CONFIGDIALOG_H
