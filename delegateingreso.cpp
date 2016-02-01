#include "delegateingreso.h"

delegateIngreso::delegateIngreso(QObject *parent) :
    QItemDelegate(parent)
{
}
QWidget * delegateIngreso::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{

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
    case 6:
    case 7:
    case 8:{
        QDoubleSpinBox *editorDouble=new QDoubleSpinBox(parent);
        editorDouble->setMinimum(0.0);
        editorDouble->setMaximum(10000000.0);
        return editorDouble;
    }

    }






}
void delegateIngreso::setEditorData(QWidget *editor, const QModelIndex &index) const{

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
    case 3:
    case 4:{
        double Value=index.model()->data(index,Qt::EditRole).toDouble();
        QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setValue(Value);
        break;
    }
    case 5:{
        QModelIndex indexValor= index.model()->index(index.row(),3);
        double Value = index.model()->data(indexValor,Qt::EditRole).toDouble();
        Value *= (double)global::porcentajeAPF/100;
        QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setValue(Value);
        break;
    }
    case 6:{
        QModelIndex indexValor= index.model()->index(index.row(),3);
        double Value = index.model()->data(indexValor,Qt::EditRole).toDouble();
        Value *= (double)global::porcentajeEPS/100;
        QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setValue(Value);
        break;
    }
    case 7:{
        QModelIndex indexValor= index.model()->index(index.row(),3);
        double Value = index.model()->data(indexValor,Qt::EditRole).toDouble();
        Value *= (double)global::porcentajeAFSP/100;
        QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setValue(Value);
        break;


    }
    case 8:{

        QModelIndex indexValor= index.model()->index(index.row(),3);
        QModelIndex indexBONO= index.model()->index(index.row(),4);
        QModelIndex indexAPF= index.model()->index(index.row(),5);
        QModelIndex indexEPS= index.model()->index(index.row(),6);
        QModelIndex indexAFSP= index.model()->index(index.row(),7);
        double Value = index.model()->data(indexValor,Qt::EditRole).toDouble();
        double bono = index.model()->data(indexBONO,Qt::EditRole).toDouble();
        double APF = index.model()->data(indexAPF,Qt::EditRole).toDouble();
        double EPS = index.model()->data(indexEPS,Qt::EditRole).toDouble();
        double AFSP = index.model()->data(indexAFSP,Qt::EditRole).toDouble();
        Value = Value+bono-APF-EPS-AFSP;
        QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setValue(Value);
        break;


    }


    }


}
void delegateIngreso::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{

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
    case 6:
    case 7:
    case 8:{

        QDoubleSpinBox *Valor=static_cast<QDoubleSpinBox *>(editor);
        Valor->interpretText();
        double value=Valor->value();
        model->setData(index,value,Qt::EditRole);
        break;

    }

    }


}

void delegateIngreso::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{


    editor->setGeometry(option.rect);

}
