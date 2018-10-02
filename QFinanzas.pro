#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T10:01:48
# CREADO POR MARTIN CHAPARRO
#-------------------------------------------------

QT       += core gui sql printsupport
#QT += axcontainer
include(xlsx/qtxlsx.pri)
XLSX_NO_LIB

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QFinanzas
TEMPLATE = app


SOURCES += main.cpp\
        principal.cpp \
    ingresos.cpp \
    global.cpp \
    basedatos.cpp \
    compra.cpp \
    delegatecompras.cpp \
    delegateingreso.cpp \
    metodopago.cpp \
    presupuesto.cpp \
    delegatepresupuesto.cpp \
    amortizacion_widget.cpp \
    compras_widget.cpp \
    ingresos_widget.cpp \
    presupuesto_widget.cpp \
    reportexcel.cpp \
    categoriacompra.cpp \
    configdialog.cpp


HEADERS  += principal.h \
    ingresos.h \
    global.h \
    basedatos.h \
    compra.h \
    delegatecompras.h \
    delegateingreso.h \
    metodopago.h \
    presupuesto.h \
    delegatepresupuesto.h \
    amortizacion_widget.h \
    compras_widget.h \
    ingresos_widget.h \
    presupuesto_widget.h \
    reportexcel.h \
    categoriacompra.h \
    configdialog.h


FORMS    += principal.ui \
    metodopago.ui \
    amortizacion_widget.ui \
    compras_widget.ui \
    ingresos_widget.ui \
    presupuesto_widget.ui \
    categoriacompra.ui \
    configdialog.ui

OTHER_FILES += \
    .gitignore \
    sql.txt

RESOURCES += \
    imagenes.qrc
