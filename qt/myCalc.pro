QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/calcController.cc \
    ../main.cc \
    ../model/calculate/calcCalculate.cc \
    ../model/credit/calcCredit.cc \
    ../model/deposit/calcDeposit.cc \
    ../model/parser/calcParser.cc \
    ../model/validator/calcValidator.cc \
    ../plot/qcustomplot.cc \
    ../view/calcView.cc

HEADERS += \
    ../controller/calcController.h \
    ../model/calculate/calcCalculate.h \
    ../model/calcModel.h \
    ../model/common/calcCommon.h \
    ../model/credit/calcCredit.h \
    ../model/deposit/calcDeposit.h \
    ../model/parser/calcParser.h \
    ../model/validator/calcValidator.h \
    ../plot/qcustomplot.h \
    ../view/calcView.h

FORMS += \
    calcView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
