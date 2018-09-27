#ifndef REPORTEXCEL_H
#define REPORTEXCEL_H
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
#include "xlsxcellformula.h"
#include <QColor>
#include <QString>
#include <Qt>
#include <QDebug>
#include <QImage>
#include "basedatos.h"
#include "global.h"
#include "presupuesto.h"
class ReportExcel
{
public:
    ReportExcel();
    QString ReportPresupuesto(QString _mes, QString NameFileIN, QList<Presupuesto> &registros);


private:

    //QColor headerColor(0,0,128);
    QColor headerColor;
    QColor headerColor2;
    QColor fontColor;
    QXlsx::Format headerFormat;
    QXlsx::Format headerFormat2;
    QXlsx::Format cellFormat;
    QXlsx::Format cellFormatNumember;
    QXlsx::Format cellFormatMoneda;


};

#endif // REPORTEXCEL_H
