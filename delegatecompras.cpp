#include "delegatecompras.h"
#include <QDebug>

DelegateCompras::DelegateCompras(QObject *parent) :
    QItemDelegate(parent)
{
}
QWidget * DelegateCompras::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{

    switch(index.column()){
    case 1:{

        QDateEdit *editorFecha=new QDateEdit(parent);
        editorFecha->setCalendarPopup(true);
        editorFecha->setDisplayFormat("yyyy-MM-dd");
        return editorFecha;
    }
    case 2:{

        QTextEdit *editorTexto=new QTextEdit(parent);
        return editorTexto;
    }
    case 3:
    case 4:
    case 5:
    case 6:{
        QDoubleSpinBox *editorDouble=new QDoubleSpinBox(parent);
        editorDouble->setMinimum(0.0);
        editorDouble->setMaximum(10000000.0);
        editorDouble->setPrefix("$ ");
        return editorDouble;
    }
    case 7:{
           QComboBox *editorCombox= new QComboBox(parent);
           editorCombox->addItems(global::metodosPago);
           return editorCombox;
    }
    case 8:{
        QSpinBox *editorInt=new QSpinBox(parent);
        editorInt->setMinimum(1);
        editorInt->setMaximum(72);
        return editorInt;
    }

    }






}
void DelegateCompras::setEditorData(QWidget *editor, const QModelIndex &index) const{

    switch(index.column()){
    case 1:{
        QString fecha = index.model()->data(index,Qt::EditRole).toString();
        QDateEdit *Fecha= static_cast<QDateEdit*>(editor);
        Fecha->setDate(QDate::fromString(fecha,Qt::ISODate));

        break;
      }

    case 2:{
        QString descripcion = index.model()->data(index,Qt::EditRole).toString();
        QTextEdit *editorTexto= static_cast<QTextEdit *>(editor);
        editorTexto->append(descripcion);
        break;

    }
    case 3:{
        double Value=index.model()->data(index,Qt::EditRole).toDouble();
        QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setPrefix("$ ");
        editorDouble->setValue(Value);
        break;
    }
    case 4:{
        QModelIndex indexValor= index.model()->index(index.row(),3);
        double Value = index.model()->data(indexValor,Qt::EditRole).toDouble();
        Value *= (double)global::porcentajeIVA/100;
        QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setValue(Value);
        break;
    }
    case 5:{
        QModelIndex indexValor= index.model()->index(index.row(),3);
        double Value = index.model()->data(indexValor,Qt::EditRole).toDouble();
        Value *= (double)global::porcentajeConsumo/100;
         QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setValue(Value);
        break;
    }
    case 6:{
       QModelIndex indexValor= index.model()->index(index.row(),3);;
       QModelIndex indexIVa= index.model()->index(index.row(),4);
       QModelIndex indexConsumo=index.model()->index(index.row(),5);

        double Value = index.model()->data(indexValor,Qt::EditRole).toDouble();
        Value += index.model()->data(indexIVa,Qt::EditRole).toDouble();
        Value += index.model()->data(indexConsumo,Qt::EditRole).toDouble();
         QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setValue(Value);
        break;


    }
    case 7:{
        QString metodoPago = index.model()->data(index,Qt::EditRole).toString();
        QComboBox *editorMetodo=static_cast<QComboBox *>(editor);
        editorMetodo->setCurrentText(metodoPago);
        break;

    }
    case 8:{
        int value=index.model()->data(index,Qt::EditRole).toInt();
        QSpinBox *editorInt=static_cast<QSpinBox *>(editor);
        editorInt->setValue(value);
        break;

    }

    }


}
void DelegateCompras::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{

    switch(index.column()){
    case 1:{

        QDateEdit *Fecha= static_cast<QDateEdit*>(editor);
        Fecha->interpretText();
        QString fecha= Fecha->text();
        model->setData(index,fecha,Qt::EditRole);
        break;
      }

    case 2:{
        QTextEdit *texto= static_cast<QTextEdit*>(editor);
        QString descripcion= texto->toPlainText();
        model->setData(index,descripcion,Qt::EditRole);
        break;

    }
    case 3:
    case 4:
    case 5:
    case 6:{

        QDoubleSpinBox *Valor=static_cast<QDoubleSpinBox *>(editor);
        Valor->interpretText();
        double value=Valor->value();
        model->setData(index,value,Qt::EditRole);
        break;

    }
    case 7:{

      QComboBox *metodo=static_cast<QComboBox *>(editor);
      QString metodoPago=metodo->currentText();
      model->setData(index,metodoPago,Qt::EditRole);
      break;

    }
    case 8:{
        QSpinBox *Valor=static_cast<QSpinBox *>(editor);
        Valor->interpretText();
        int value=Valor->value();
        model->setData(index,value,Qt::EditRole);
        break;

    }

    }


}

void DelegateCompras::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{


    editor->setGeometry(option.rect);

}
