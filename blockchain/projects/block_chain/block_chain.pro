###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.opennn.net                                                                                #
#                                                                                                 #
#   B L O C K   C H A I N   P R O J E C T                                                         #
#                                                                                                 #
#   Alberto Quesada    albertoquesada@artelnics.com                                               #
#                                                                                                 #
###################################################################################################


QT += core \
      widgets \
      gui \
      charts \
      printsupport

TEMPLATE = app
CONFIG += console
CONFIG += c++11

TARGET = blockchain

DESTDIR = "$$PWD/bin"

HEADERS += Block.h \
           BlockChain.h \
           TransactionData.h \

SOURCES += main.cpp \
           Block.cpp \
           BlockChain.cpp \
		   
		   
win32-g++{
QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++
QMAKE_LFLAGS += -static
}

# OpenNN library


# Tiny XML 2 library

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../tinyxml2/release/ -ltinyxml2
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../tinyxml2/debug/ -ltinyxml2

#INCLUDEPATH += $$PWD/../../tinyxml2
#DEPENDPATH += $$PWD/../../tinyxml2

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../tinyxml2/release/libtinyxml2.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../tinyxml2/debug/libtinyxml2.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../tinyxml2/release/tinyxml2.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../tinyxml2/debug/tinyxml2.lib

# OpenMP library

win32:!win32-g++{
QMAKE_CXXFLAGS += -openmp
QMAKE_LFLAGS   += -openmp
}

!win32{
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS   += -fopenmp
}

# MPI libraries
#include(../mpi.pri)

# CUDA libraries
#include(../cuda.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../opennn/opennn/release/ -lopennn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../opennn/opennn/debug/ -lopennn
else:unix: LIBS += -L$$OUT_PWD/../../opennn/opennn/ -lopennn

INCLUDEPATH += $$PWD/../../opennn/opennn
DEPENDPATH += $$PWD/../../opennn/opennn

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../opennn/opennn/release/libopennn.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../opennn/opennn/debug/libopennn.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../opennn/opennn/release/opennn.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../opennn/opennn/debug/opennn.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../opennn/opennn/libopennn.a
