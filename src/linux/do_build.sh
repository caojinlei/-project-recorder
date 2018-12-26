#!/usr/bin/env bash

case "$1" in
    1)
        OS=embedded_linux
        ARCH='x86_64'
        CROSS_TOOLCHAIN=/usr
        CXX_COMPILER=${CROSS_TOOLCHAIN}/bin/g++
        C_COMPILER=${CROSS_TOOLCHAIN}/bin/gcc
        STRIP=${CROSS_TOOLCHAIN}/bin/strip
        ;;
    2)
        OS=mib3
        ARCH='aarch64'
        CROSS_TOOLCHAIN=/opt/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu
        CXX_COMPILER=${CROSS_TOOLCHAIN}/bin/aarch64-linux-gnu-g++
        C_COMPILER=${CROSS_TOOLCHAIN}/bin/aarch64-linux-gnu-gcc
        STRIP=${CROSS_TOOLCHAIN}/bin/aarch64-linux-gnu-strip
        ;;
    *)
        echo "unknown arch: $1"
        exit 1
        ;;
esac

BUILD_DIR="build"
rm -rf ${BUILD_DIR} && mkdir -p ${BUILD_DIR}

INSTALL_DIR="install"
rm -rf ${INSTALL_DIR} && mkdir -p ${INSTALL_DIR}

cd ${BUILD_DIR}
cmake \
    -DARCH=$ARCH \
    -DOS=$OS \
    -DCMAKE_INSTALL_PREFIX=../install \
    -DCMAKE_C_COMPILER=$C_COMPILER \
    -DCMAKE_CXX_COMPILER=$CXX_COMPILER \
    -DCMAKE_BUILD_TYPE=Debug ..

make -j4
make install

cd ..
