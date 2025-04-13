#-------------------------------------------------
#
# Project created by QtCreator 2023-07-06T14:39:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorMap
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    vtkPVColorTransferControlPointsItem.cxx \
    igwTransferFunctionWidget.cxx \
    igwCoreUtilities.cxx \
    colormap.cpp \
    igwTimer.cxx \
    igwTransferFunctionPresets.cpp \
    igwPresetGroupsManager.cxx

HEADERS += \
        colormap.h \
    vtkPVColorTransferControlPointsItem.h \
    igwTransferFunctionWidget.h \
    igwCoreUtilities.h \
    igwTimer.h \
    igwTransferFunctionPresets.h \
    igwTransferFunctionPresetsBuiltin.h \
    igwPresetGroupsManager.h

FORMS += \
        colormap.ui

INCLUDEPATH += /usr/local/include/vtk-9.2/
LIBS += /usr/local/lib/libvtk*-9.2.so

DISTFILES +=

RESOURCES += \
    res.qrc
