QT       += core

QT       -= gui

TARGET = cudaQTS
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    cudacu/kernel.h

SOURCES += main.cpp

# This makes the .cu files appear in your project
#OTHER_FILES +=  ./kernel.cu

# CUDA settings <-- may change depending on your system
CUDA_SOURCES += ./cudacu/kernel.cu

win32 {
    CUDA_SDK = "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.2"   # Path to cuda SDK install
    CUDA_DIR = "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.2"            # Path to cuda toolkit install
    # library directories
    QMAKE_LIBDIR += $$CUDA_DIR/lib/x64/
    SYSTEM_NAME = Win64         # Depending on your system either 'Win32', 'x64', or 'Win64'
    SYSTEM_TYPE = 64            # '32' or '64', depending on your system
    CUDA_ARCH = sm_61          # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'GTX1050ti 61
    NVCC_OPTIONS = --use_fast_math
    message("win")
}
unix {
    CUDA_SDK = "/usr/local/cuda-10.0"   # Path to cuda SDK install
    CUDA_DIR = "/usr/local/cuda-10.0"            # Path to cuda toolkit install
    # library directories
    QMAKE_LIBDIR += $$CUDA_DIR/lib64/
    SYSTEM_NAME = ubuntu         # Depending on your system either 'Win32', 'x64', or 'Win64'
    SYSTEM_TYPE = 64            # '32' or '64', depending on your system
    CUDA_ARCH = sm_72          # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'XAVIER72
    NVCC_OPTIONS = --use_fast_math
    message("unix")
}

# include paths
INCLUDEPATH += $$CUDA_DIR/include
INCLUDEPATH += $$PWD
#message($$PWD)

CUDA_OBJECTS_DIR = ./

# Add the necessary libraries
CUDA_LIBS = -lcuda -lcudart

# The following makes sure all path names (which often include spaces) are put between quotation marks
CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')
#LIBS += $$join(CUDA_LIBS,'.so ', '', '.so')
LIBS += $$CUDA_LIBS

# Configuration of the Cuda compiler
CONFIG(debug, debug|release) {
    # Debug mode
    cuda_d.input = CUDA_SOURCES
    cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda_d.o
    cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda_d.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda_d
}
else {
    # Release mode
    cuda.input = CUDA_SOURCES
    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda
}
