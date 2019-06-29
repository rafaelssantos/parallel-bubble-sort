TARGET = parallel-hybrid-sort
TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


# [CHANGE]
# Add all source files, even cuda source files
HEADERS += \
    bubblesort.h \
    valuesmanager.h \
    sortmanager.h \
    mergesort.h \
    hybridsort.h \
    sortalgorithm.h \
    sortalgorithmtype.h \
    logger.h



# [CHANGE]
# Add all source files, even cuda source files
# Here, there is a trick in Qt Creator.
# CUDA files are after removed from SOURCES.
SOURCES += \
    main.cpp \
    bubblesort.cpp \
    valuesmanager.cpp \
    mergesort.cpp \
    sortmanager.cpp \
    hybridsort.cpp \
    sortalgorithm.cpp \
    logger.cpp


# [OPTIONAL]
# C++ compiler optimization flags
QMAKE_CXXFLAGS_RELEASE += -O3



# [MPI]
# C++ MPI compiler optimization flags
QMAKE_CXX = mpicxx
QMAKE_CXX_RELEASE = $$QMAKE_CXX
QMAKE_CXX_DEBUG = $$QMAKE_CXX
QMAKE_LINK = $$QMAKE_CXX
QMAKE_CC = mpicc

QMAKE_CFLAGS += $$system(mpicc --showme:compile)
QMAKE_LFLAGS += $$system(mpicxx --showme:link)
QMAKE_CXXFLAGS += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK
QMAKE_CXXFLAGS_RELEASE += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK
