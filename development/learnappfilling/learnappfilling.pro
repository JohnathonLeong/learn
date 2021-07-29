QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
#TEMPLATE = lib
#DEFINES += LEARNAPPFILLING_LIBRARY

win32:CONFIG(release, debug|release): TARGET = learnappfilling
else:win32:CONFIG(debug, debug|release): TARGET = learnappfilling_debug
else:unix: TARGET = learnappfilling

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
    learnappfilling.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    learnappfilling.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS += -L$$PWD/../../libs/
win32:CONFIG(release, debug|release): LIBS += -lgenericlibrarymaths -llearnlibrarycustomwidgets -llearnlibraryfunctions
else:win32:CONFIG(debug, debug|release): LIBS += -lgenericlibrarymaths_debug -llearnlibrarycustomwidgets_debug -llearnlibraryfunctions_debug
else:unix: LIBS += -lgenericlibrarymaths -llearnlibrarycustomwidgets -llearnlibraryfunctions

INCLUDEPATH += $$PWD/../../libs/
DEPENDPATH += $$PWD/../../libs/
INCLUDEPATH += $$PWD/../../includes/
DEPENDPATH += $$PWD/../../includes/
