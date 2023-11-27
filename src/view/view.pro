QT       += core gui printsupport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

qmake
TARGET = ../SmartCalc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/smart_calc/controller.cc \
    ../controller/credit/credit_controller.cc \
    ../controller/deposit/deposit_controller.cc \
    ../model/credit/credit_model.cc \
    ../model/deposit/deposit_model.cc \
    ../model/smart_calc/model.cc \
    credit/credit.cc \
    deposit/deposit.cc \
    graph/graph.cc \
    ../main.cc \
    graph/qcustomplot.cc \
    smart_calc/smartcalc.cc

HEADERS += \
    ../controller/smart_calc/controller.h \
    ../controller/credit/credit_controller.h \
    ../controller/deposit/deposit_controller.h \
    ../model/credit/credit_model.h \
    ../model/deposit/deposit_model.h \
    ../model/smart_calc/model.h \
    credit/credit.h \
    deposit/deposit.h \
    graph/graph.h \
    graph/qcustomplot.h \
    smart_calc/smartcalc.h

FORMS += \
    credit/credit.ui \
    deposit/deposit.ui \
    graph/graph.ui \
    smart_calc/smartcalc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
