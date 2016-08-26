#include "delegatepresupuesto.h"

delegatePresupuesto::delegatePresupuesto(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *delegatePresupuesto::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch(index.column()){
    case 2:{
        QTextEdit *editorTexto=new QTextEdit(parent);
        return editorTexto;}

    case 3:
    case 4:
        QDoubleSpinBox *editorDouble=new QDoubleSpinBox(parent);
        editorDouble->setMinimum(0.0);
        editorDouble->setMaximum(10000000.0);
        editorDouble->setPrefix("$ ");
        return editorDouble;

    }
}

void delegatePresupuesto::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch(index.column()){
    case 2:{
        QString descripcion = index.model()->data(index,Qt::EditRole).toString();
        QTextEdit *editorTexto= static_cast<QTextEdit *>(editor);
        editorTexto->append(descripcion);
        break;
    }
    case 3:
    case 4:
        double Value=index.model()->data(index,Qt::EditRole).toDouble();
        QDoubleSpinBox *editorDouble=static_cast<QDoubleSpinBox *>(editor);
        editorDouble->setPrefix("$ ");
        editorDouble->setValue(Value);
        break;
    }

}

void delegatePresupuesto::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch(index.column()){
    case 2:{
        QTextEdit *texto= static_cast<QTextEdit*>(editor);
        QString descripcion= texto->toPlainText();
        model->setData(index,descripcion,Qt::EditRole);
        break;
    }
    case 3:
    case 4:
        QDoubleSpinBox *Valor=static_cast<QDoubleSpinBox *>(editor);
        Valor->interpretText();
        double value=Valor->value();
        model->setData(index,value,Qt::EditRole);
        break;
    }

}

void delegatePresupuesto::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
