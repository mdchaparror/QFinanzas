#include "reportexcel.h"
#include "presupuesto.h"
ReportExcel::ReportExcel()
{

    headerColor=QColor(Qt::darkBlue);
    headerColor2=QColor(Qt::darkRed);
    fontColor=QColor(Qt::white);
    headerFormat.setPatternBackgroundColor(headerColor);
    headerFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    headerFormat.setFontBold(true);
    headerFormat.setFontSize(12);
    headerFormat.setFontColor(fontColor);
    headerFormat.setBorderStyle(QXlsx::Format::BorderMedium);
    headerFormat2.setPatternBackgroundColor(headerColor2);
    headerFormat2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    headerFormat2.setFontBold(true);
    headerFormat2.setFontSize(12);
    headerFormat2.setFontColor(fontColor);
    headerFormat2.setBorderStyle(QXlsx::Format::BorderMedium);
    cellFormat.setFontColor(QColor(Qt::black));
    cellFormat.setFontSize(10);
    cellFormat.setHorizontalAlignment(QXlsx::Format::AlignLeft);
    cellFormat.setBorderStyle(QXlsx::Format::BorderThin);


    cellFormatNumember.setFontColor(QColor(Qt::black));
    cellFormatNumember.setFontSize(11);
    cellFormatNumember.setHorizontalAlignment(QXlsx::Format::AlignRight);
    cellFormatNumember.setBorderStyle(QXlsx::Format::BorderThin);
    cellFormatNumember.setNumberFormat(0);

    cellFormatMoneda.setFontColor(QColor(Qt::black));
    cellFormatMoneda.setFontSize(11);
    cellFormatMoneda.setHorizontalAlignment(QXlsx::Format::AlignRight);
    cellFormatMoneda.setBorderStyle(QXlsx::Format::BorderThin);
    cellFormatMoneda.setNumberFormat("$ #,##0");

}

QString ReportExcel::ReportPresupuesto(QString _mes, QString NameFileIN, QList<Presupuesto> &registros)
{
    BaseDatos TablaConsolidadop;

    QString sheetName="PRESUPUESTO_"+_mes;
    int colDetalle=1;
    int colGasto=2;
    int colIngreso=3;

    QXlsx::Document excelFile(NameFileIN);

    qDebug()<<excelFile.sheetNames().indexOf(sheetName);

    if(excelFile.sheetNames().indexOf(sheetName)>-1){


        excelFile.addSheet("Hoja1");
        qDebug()<<"Borrado: sheht"<<excelFile.deleteSheet(sheetName);


    }


    /*
     * ENCABEZADOS
     *
     * */



    excelFile.insertSheet(excelFile.sheetNames().length(),sheetName);
    excelFile.moveSheet("Hoja1",excelFile.sheetNames().length());
    excelFile.deleteSheet("Hoja1");
    excelFile.selectSheet(sheetName);



    excelFile.mergeCells("A1:C1",headerFormat);

    excelFile.write("A1",_mes,headerFormat);
    excelFile.write(2,colDetalle,"DETALLE",headerFormat2);
    excelFile.write(2,colGasto,"GASTOS",headerFormat2);
    excelFile.write(2,colIngreso,"INGRESOS",headerFormat2);
    excelFile.setColumnWidth(colDetalle,20);
    excelFile.setColumnWidth(colGasto,14);
    excelFile.setColumnWidth(colIngreso,14);
    int row=3;

    foreach (Presupuesto p, registros) {
        excelFile.write(row,colDetalle,p.getDetalle(),cellFormat);
        excelFile.write(row,colGasto,p.getDebito(),cellFormatMoneda);
        excelFile.write(row,colIngreso,p.getCredito(),cellFormatMoneda);
        row++;
    }
    QString merge=QString("A%1:B%1").arg(row);
    QString rango1=QString("B3:B%1").arg(row-1);
    QString rango2=QString("C3:C%1").arg(row-1);
    QString formula=QString("=SUM(%1)-SUM(%2)").arg(rango2).arg(rango1);
    excelFile.mergeCells(merge,headerFormat);
    excelFile.write(row,colDetalle,"TOTAL NETO",headerFormat);
    excelFile.write(row,colIngreso,formula,cellFormatMoneda);

    excelFile.setDocumentProperty("creator","Martin Chaparro");
    excelFile.setDocumentProperty("company","MDCHAPARROR, MDCHAPARROR");
    excelFile.setDocumentProperty("title","PRESUPUESTO");
    excelFile.saveAs(NameFileIN);

    TablaConsolidadop.close();
    qDebug()<<"Guardado archivo: "+NameFileIN;
    return "Guardado archivo: "+NameFileIN;

}


