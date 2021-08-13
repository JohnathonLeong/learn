QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
#TEMPLATE = lib
#DEFINES += LEARNAPPSSELECTION_LIBRARY

win32:CONFIG(release, debug|release): TARGET = learnappsselection
else:win32:CONFIG(debug, debug|release): TARGET = learnappsselection_debug
else:unix: TARGET = learnappsselection

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    learnappsselection.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    learnappsselection.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/../libs/
win32:CONFIG(release, debug|release): LIBS += -llearnappfilling \
    -llearnapprecognizing \
    -llearnappspelling \
    -llearnappjumbling \
    -lgenericlibrarymaths \
    -llearnlibrarycustomwidgets \
    -llearnlibraryfunctions
else:win32:CONFIG(debug, debug|release): LIBS += -llearnappfilling_debug \
    -llearnapprecognizing_debug \
    -llearnappspelling_debug \
    -llearnappjumbling_debug \
    -lgenericlibrarymaths_debug \
    -llearnlibrarycustomwidgets_debug \
    -llearnlibraryfunctions_debug
else:unix: LIBS += -llearnappfilling \
    -llearnapprecognizing \
    -llearnappspelling \
    -llearnappjumbling \
    -lgenericlibrarymaths \
    -llearnlibrarycustomwidgets \
    -llearnlibraryfunctions
INCLUDEPATH += $$PWD/../libs/
DEPENDPATH += $$PWD/../libs/
INCLUDEPATH += $$PWD/../includes/
DEPENDPATH += $$PWD/../includes/
