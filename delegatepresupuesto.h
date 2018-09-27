#ifndef DELEGATEPRESUPUESTO_H
#define DELEGATEPRESUPUESTO_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QComboBox>
#include "global.h"

class delegatePresupuesto : public QItemDelegate
{
    Q_OBJECT
public:
    explicit delegatePresupuesto(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

public slots:

};

#endif // DELEGATEPRESUPUESTO_H
