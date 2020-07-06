#!/usr/bin/bash

SHARED_LIB_DIR=/workspaces/messageapi/artifacts/c/libs
HEADER_DIR=/workspaces/messageapi/artifacts/c/headers

JNI_DIR=${JAVA_HOME}/include
JNIMD_DIR=${JAVA_HOME}/include/linux

gcc -I${JNI_DIR} -I${JNIMD_DIR} -I${HEADER_DIR} -L${SHARED_LIB_DIR} -Wl,-rpath,${SHARED_LIB_DIR} -lmessageapisession -Wall -o nativesessiondemo.bin NativeSessionDemo.c

./nativesessiondemo.bin
