QT       += core
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
    sortalgorithmtype.h



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
    sortalgorithm.cpp



# [CHANGE]
# Add just the cuda source files
CUDA_SOURCES += \



# [CHANGE]
# Remove all cuda source files from SOURCES
# Cuda source files must not be compiled by the C++ compiler.
SOURCES -= \




# [OPTIONAL]
# C++ compiler optimization flags
QMAKE_CXXFLAGS_RELEASE += -O3



# [OPENMP]
# C++ Openmp compiler optimization flags
QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp



# [OPTIONAL]
# Cuda installation path
CUDA_DIR                = /usr/local/cuda

# [CHANGE]
# Bits of operation system (32 or 64)
SYSTEM_TYPE             = 64                            # '32' or '64', depending on your system

# [CHANGE]
# Type of CUDA architecture (Compute Capability)
CUDA_ARCH               = sm_50

# [OPTIONAL]
# nvcc compiler options
NVCC_COMPILER_OPTIONS   = -Xptxas -O3 -use_fast_math

# [DON'T CHANGE]
# Cuda libraries
CUDA_INC = $$join($$CUDA_DIR/include,'" -I"','-I"','"')
CUDA_LIB_NAMES = cudart cuda
for(lib, CUDA_LIB_NAMES) {
    CUDA_LIBS += -l$$lib
}
LIBS += $$CUDA_LIBS
QMAKE_LIBDIR += $$CUDA_DIR/lib64

# [DON'T CHANGE]
# Include path
INCLUDEPATH += $$CUDA_DIR/include             # include paths



# [DON'T CHANGE]
# Config cuda debug compilation
CONFIG(debug, debug|release) {
    DESTDIR = debug
    OBJECTS_DIR = debug/obj

    cuda_compiler_debug.input = CUDA_SOURCES
    cuda_compiler_debug.output = $${OBJECTS_DIR}/${QMAKE_FILE_BASE}.o
    cuda_compiler_debug.commands = $$CUDA_DIR/bin/nvcc $$CUDA_INC $$CUDA_LIBS \
                    --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH \
                    --device-c -G ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
    cuda_compiler_debug.variable_out = CUDA_OBJECTS OBJECTS
    QMAKE_EXTRA_COMPILERS += cuda_compiler_debug

    cuda_linker_debug.input = CUDA_OBJECTS
    cuda_linker_debug.CONFIG = combine
    cuda_linker_debug.output = $${OBJECTS_DIR}/device-link.o
    cuda_linker_debug.commands = $$CUDA_DIR/bin/nvcc \
                    --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH \
                    --device-link -G ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
    cuda_linker_debug.dependency_type = TYPE_C
    cuda_linker_debug.variable_out = OBJECTS
    QMAKE_EXTRA_COMPILERS += cuda_linker_debug
}


# [DON'T CHANGE]
# Config cuda release compilation
else{
    DESTDIR = release
    OBJECTS_DIR = release/obj

    cuda_compiler.input = CUDA_SOURCES
    cuda_compiler.output = $${OBJECTS_DIR}/${QMAKE_FILE_BASE}.o
    cuda_compiler.commands = $$CUDA_DIR/bin/nvcc $$NVCC_COMPILER_OPTIONS $$CUDA_INC $$CUDA_LIBS \
                    --machine $$SYSTEM_TYPE --gpu-architecture=$$CUDA_ARCH \
                    --device-c ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
    cuda_compiler.variable_out = CUDA_OBJECTS OBJECTS
    QMAKE_EXTRA_COMPILERS += cuda_compiler

    cuda_linker.input = CUDA_OBJECTS
    cuda_linker.CONFIG = combine
    cuda_linker.output = $${OBJECTS_DIR}/device-link.o
    cuda_linker.commands = $$CUDA_DIR/bin/nvcc \
                    --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH \
                    --device-link ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
    cuda_linker.dependency_type = TYPE_C
    cuda_linker.variable_out = OBJECTS
    QMAKE_EXTRA_COMPILERS += cuda_linker
}
