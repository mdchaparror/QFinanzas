#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T10:01:48
#
#-------------------------------------------------

QT       += core gui sql

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
    delegatepresupuesto.cpp

HEADERS  += principal.h \
    ingresos.h \
    global.h \
    basedatos.h \
    compra.h \
    delegatecompras.h \
    delegateingreso.h \
    metodopago.h \
    presupuesto.h \
    delegatepresupuesto.h

FORMS    += principal.ui \
    metodopago.ui

OTHER_FILES += \
    .gitignore \
    sql.txt

RESOURCES += \
    imagenes.qrc
