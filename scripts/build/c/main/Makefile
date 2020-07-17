### This is a Makefile for creating the native session shared library.
# The majority of this Makefile is standard.
# There are a few specific requirements and other notable things to keep in mind when using this Makefile:
# 1. You must have a JDK installed as well as the JRE. This library requires the jni.h header and the shared libraries for jli and jvm.
# 2. JAVA_HOME must be set to your JDK home directory. This Makefile references JAVA_HOME in looking for jni.h, libjli.so, and libjvm.so.

#Library info
LIBRARY_NAME=messageapi
MAJOR_VERSION=1
MINOR_VERSION=0
PATCH_VERSION=0

LINKER_NAME=lib$(LIBRARY_NAME).so
SO_NAME=$(LINKER_NAME).$(MAJOR_VERSION)
REAL_NAME=$(LINKER_NAME).$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION)

#Compute Root Project Path from Makefile path
CURRENT_DIR=$(PWD)
PROJECT_ROOT=$(firstword $(subst /scripts/build/c/main, ,$(CURRENT_DIR)))

#Set target directoies
BUILD_DIR=$(PROJECT_ROOT)/build/c/main
SRC_DIR=$(BUILD_DIR)/src
COMPILE_DIR=$(BUILD_DIR)/compile
HEADER_DIR=$(BUILD_DIR)/headers
LIB_DIR=$(BUILD_DIR)/libs

ARTIFACT_DIR=$(PROJECT_ROOT)/dist/artifacts/c/$(LIBRARY_NAME)_$(MAJOR_VERSION)_$(MINOR_VERSION)_$(PATCH_VERSION)

#Include Paths for JNI (dependent on Java Home being set)
JNI_H_DIR=$(JAVA_HOME)/include
JNIMD_H_DIR=$(JAVA_HOME)/include/linux
JVM_SO_DIR=$(JAVA_HOME)/lib/server
JLI_SO_DIR=$(JAVA_HOME)/lib/jli

export LD_LIBRARY_PATH=$(JLI_SO_DIR):$(JVM_SO_DIR)

#Compilers
CXX=g++
CC=gcc

#Source Code and Header Sets
SCRIPT_SRC_DIR=$(PROJECT_ROOT)/scripts/install/c/main

C_DIR=$(PROJECT_ROOT)/src/c/main/

C_SRC_FILES=

C_FQ_SRC_FILES=$(addprefix $(C_DIR), $(C_SRC_FILES))

C_H_FILES=structs/messageapi_structs.h

C_FULL_H_FILES=wrappers/endpoint/gov_noaa_messageapi_endpoints_NativeEndpoint.h \
wrappers/transformation/gov_noaa_messageapi_transformations_NativeTransformation.h

C_FQ_H_FILES=$(addprefix $(C_DIR), $(C_H_FILES))

C_FQ_FULL_H_FILES=$(addprefix $(C_DIR), $(C_FULL_H_FILES))

CPP_DIR=$(PROJECT_ROOT)/src/cpp/main/

CPP_SRC_FILES=utils/general/jni/JniUtils.cpp utils/general/type/TypeUtils.cpp utils/general/list/ListUtils.cpp \
utils/general/map/MapUtils.cpp utils/api/condition/ConditionUtils.cpp utils/api/field/FieldUtils.cpp \
utils/api/records/schema/RecordUtils.cpp utils/api/rejection/RejectionUtils.cpp utils/api/packet/PacketUtils.cpp \
utils/api/session/SessionUtils.cpp utils/api/request/RequestUtils.cpp utils/api/response/ResponseUtils.cpp \
api/session/MessageApiSession.cpp libs/session/MessageApiSessionLib.cpp

CPP_FULL_SRC_FILES=utils/api/endpoint/EndpointUtils.cpp utils/api/records/protocol/ProtocolRecordUtils.cpp \
utils/api/transformation/TransformationUtils.cpp api/endpoint/MessageApiEndpoint.cpp \
api/transformation/MessageApiTransformation.cpp libs/endpoint/MessageApiEndpointLib.cpp \
libs/transformation/MessageApiTransformationLib.cpp

CPP_FQ_SRC_FILES=$(addprefix $(CPP_DIR), $(CPP_SRC_FILES))

CPP_FQ_FULL_SRC_FILES=$(addprefix $(CPP_DIR), $(CPP_FULL_SRC_FILES))

CPP_H_FILES=utils/general/jni/JniUtils.h utils/general/type/TypeUtils.h utils/general/list/ListUtils.h \
utils/general/map/MapUtils.h utils/api/condition/ConditionUtils.h utils/api/field/FieldUtils.h \
utils/api/records/schema/RecordUtils.h utils/api/rejection/RejectionUtils.h utils/api/packet/PacketUtils.h \
utils/api/session/SessionUtils.h utils/api/request/RequestUtils.h utils/api/response/ResponseUtils.h \
api/session/MessageApiSession.h libs/session/MessageApiSessionLib.h

CPP_FULL_H_FILES=utils/api/endpoint/EndpointUtils.h utils/api/records/protocol/ProtocolRecordUtils.h \
utils/api/transformation/TransformationUtils.h api/endpoint/MessageApiEndpoint.h \
api/transformation/MessageApiTransformation.h libs/endpoint/MessageApiEndpointLib.h \
libs/transformation/MessageApiTransformationLib.h

CPP_FQ_H_FILES=$(addprefix $(CPP_DIR), $(CPP_H_FILES))

CPP_FQ_FULL_H_FILES=$(addprefix $(CPP_DIR), $(CPP_FULL_H_FILES))

all: check_sys prep build link dist clean

.PHONY : check_sys prep build link dist clean

check_sys:
	@echo "Checking OS type"
ifneq ($(shell uname),Linux)
	@echo "This makefile is for building shared libraries on linux, OS not linux. Terminating."
	@exit 1
endif
	@echo "System OS is Linux, continuing build."

prep:
	@echo "Preparing system for build."
	@rm -rf $(BUILD_DIR)
	@rm -rf $(ARTIFACT_DIR)

	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(COMPILE_DIR)
	@mkdir -p $(HEADER_DIR)
	@mkdir -p $(LIB_DIR)

	@mkdir -p $(ARTIFACT_DIR)

build:
	@echo "Copying source and header resources for build."
	@cp $(C_FQ_H_FILES) $(HEADER_DIR)
	@cp $(CPP_FQ_H_FILES) $(HEADER_DIR)
	@echo "Copying installation script to build dir."
	@-cd $(SCRIPT_SRC_DIR) && cp install.sh $(BUILD_DIR)
	@echo "Finished copying resources."
	@echo "Building $(LIBRARY_NAME) in $(PROJECT_ROOT)."
	@echo "Compiling object files with position independent code."
	@-cd $(COMPILE_DIR) && $(CXX) -c -Wall -fPIC -I$(JNI_H_DIR) -I$(JNIMD_H_DIR) \
	-I$(HEADER_DIR) $(CPP_FQ_SRC_FILES)
	@echo ""
	@echo "Creating shared library from object files."
	@echo ""
	@cp $(JVM_SO_DIR)/libjvm.so $(COMPILE_DIR)
	@cp $(JLI_SO_DIR)/libjli.so $(COMPILE_DIR)
	@-cd $(COMPILE_DIR) && $(CXX) -shared -fPIC -std=c99 \
	-L$(COMPILE_DIR) -Wl,-rpath,$(COMPILE_DIR) \
	-Wl,-soname,$(SO_NAME) -ljli -ljvm -o $(REAL_NAME) *.o
	@echo "Build success for the C/C++ session shared library."

link:
	@echo "Linking shared library."
	@-cd $(COMPILE_DIR) && ln -s $(REAL_NAME) $(SO_NAME)
	@-cd $(COMPILE_DIR) && ln -s $(SO_NAME) $(LINKER_NAME)
	@cp $(COMPILE_DIR)/libmessageapi.so $(LIB_DIR)
	@cp $(COMPILE_DIR)/libmessageapi.so.* $(LIB_DIR)
	@echo "Finished linking shared library."

dist:
	@echo "Copying all headers and source files for full library distribution."
	@cp $(C_FQ_FULL_H_FILES) $(HEADER_DIR)
	@cp $(CPP_FQ_FULL_H_FILES) $(HEADER_DIR)
	@cp $(CPP_FQ_SRC_FILES) $(SRC_DIR)
	@cp $(CPP_FQ_FULL_SRC_FILES) $(SRC_DIR)
	@echo "Building tarfile for distribution."
	@-cd $(BUILD_DIR) && tar -cf $(LIBRARY_NAME).tar src libs headers install.sh
	@echo "Moving tarfile to $(ARTIFACT_DIR)."
	@-cd $(BUILD_DIR) && mv $(LIBRARY_NAME).tar $(ARTIFACT_DIR)
	@echo "Finished build, artifacts are now tarred and available in $(ARTIFACT_DIR)."

clean:
	@echo "Cleaning up build data."
	@rm -rf $(BUILD_DIR)
	@echo ""
