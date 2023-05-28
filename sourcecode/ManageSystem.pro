QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    administrator.cpp \
    dlg_addproduct.cpp \
    dlg_addsales.cpp \
    dlg_addsalesman.cpp \
    main.cpp \
    page_login.cpp \
    productsql.cpp \
    salesman.cpp \
    salesmansql.cpp \
    salessql.cpp

HEADERS += \
    administrator.h \
    dlg_addproduct.h \
    dlg_addsales.h \
    dlg_addsalesman.h \
    page_login.h \
    productsql.h \
    salesman.h \
    salesmansql.h \
    salessql.h

FORMS += \
    administrator.ui \
    dlg_addproduct.ui \
    dlg_addsales.ui \
    dlg_addsalesman.ui \
    page_login.ui \
    salesman.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
