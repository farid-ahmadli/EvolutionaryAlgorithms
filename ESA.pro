#-------------------------------------------------
#
# Project created by QtCreator 2011-11-06T21:19:15
#
#-------------------------------------------------

QT       -= gui

TARGET = ESA
TEMPLATE = lib

DEFINES += ESA_LIBRARY

SOURCES += \
    Program.cpp \
    Population.cpp \
    Individual.cpp \
    HeapSort.cpp \
    ESASolver.cpp \
    Debug.cpp \
    DataWriter.cpp \
    DataUnit.cpp \
    DataReader.cpp

HEADERS += \
    Population.h \
    Individual.h \
    HeapSort.h \
    ESASolver.h \
    Debug.h \
    DataWriter.h \
    DataUnit.h \
    DataReader.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE42A6CA8
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ESA.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}





