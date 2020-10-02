### This Makefile can be used as a template for writing MessageAPI compatible C/C++ conditions that extend the 
# NativeCondition.
# Note that the goal of native condition production is to create a shared library,
# as shared libraries are used by the Java code. Once produced, the fully-qualified shared library should just be referenced in the
# config map for the condition itself. If you are reading this, you most likely understand what is necessary, but if not, see the example
# 'native condition' in the MessageAPI source code 'test' namespace with associated parameter map.

# The majority of this Makefile is standard, with only six user specified variables. These are denoted by the comment USER SPECIFIED.
# All user specified variables are at the top of this makefile. The build process is standardized to automatically include MessageAPI resources,
# So if there is an issue at first, make sure you have installed the library correctly (need $MESSAGEAPI_SRC and $MESSAGEAPI_HEADERS env vars).

# There are a few other system-specific requirements and other notable things to keep in mind when using this Makefile:
## 1. You must have a JDK installed (not JRE). This library requires the jni.h and jnimd.h headers included in your jdk.
## 2. JAVA_HOME must be set to your JDK home directory (one level above the java binary). This Makefile references JAVA_HOME in looking for jni.h and jnimd.h

#The following is used to bootstrap the PROJECT_ROOT 
CURRENT_DIR=$(PWD)

#The following represents the root project path. In this tailored example, we use a relative path to the project root.
#In your own Makefile, this variable can be set directly.
PROJECT_ROOT=$(firstword $(subst /scripts/build/c/test, ,$(CURRENT_DIR)))


#Set target directories - this is where the library will build from/to.
BUILD_DIR=$(PROJECT_ROOT)/build/c/test/condition
COMPILE_DIR=$(BUILD_DIR)/compile#.o files produced here
HEADER_DIR=$(BUILD_DIR)/headers#.h files copied here before build (for central include path)
LIB_DIR=$(PROJECT_ROOT)/libs/test/c/condition#.so moved here before test

#USER SPECIFIED - Specify the base name of the lib (e.g., if lib to be built as libMyCondition.so, put MyCondition here)
LIBRARY_NAME=ConditionDemo
SO_NAME=lib$(LIBRARY_NAME).so

#The following represent directories for JNI Libraries that must be included during C and CPP compilation.
#The following represent a standard RHEL 7/8 system with OpenJDK.
JNIDIR=$(JAVA_HOME)/include
JNIMDDIR=$(JAVA_HOME)/include/linux

#compilers
CXX=g++
CC=gcc

C_DIR=$(PROJECT_ROOT)/src/c/

C_SRC_FILES=test/conditions/condition_lib/ConditionWrapper.c
C_FQ_SRC_FILES=$(addprefix $(C_DIR), $(C_SRC_FILES))

C_H_FILES=main/structs/messageapi_structs.h main/wrappers/condition/gov_noaa_messageapi_conditions_NativeCondition.h
C_FQ_H_FILES=$(addprefix $(C_DIR), $(C_H_FILES))

CPP_DIR=$(PROJECT_ROOT)/src/cpp/main/

CPP_SRC_FILES=utils/general/jni/JniUtils.cpp utils/general/type/TypeUtils.cpp utils/general/map/MapUtils.cpp \
utils/general/list/ListUtils.cpp utils/api/condition/ConditionUtils.cpp utils/api/condition/NativeConditionUtils.cpp \
utils/api/field/FieldUtils.cpp api/condition/MessageApiCondition.cpp libs/condition/MessageApiConditionLib.cpp

CPP_FQ_SRC_FILES=$(addprefix $(CPP_DIR), $(CPP_SRC_FILES))

CPP_H_FILES=utils/general/jni/JniUtils.h utils/general/type/TypeUtils.h utils/general/map/MapUtils.h \
utils/general/list/ListUtils.h utils/api/condition/ConditionUtils.h utils/api/condition/NativeConditionUtils.h \
utils/api/field/FieldUtils.h api/condition/MessageApiCondition.h libs/condition/MessageApiConditionLib.h

CPP_FQ_H_FILES=$(addprefix $(CPP_DIR), $(CPP_H_FILES))


all: check_sys prep build

.PHONY : check_sys prep build

check_sys:
	@echo "Checking OS type"
ifneq ($(shell uname),Linux)
	@echo "This makefile is for building shared libraries on linux, OS is $(shell uname). Terminating."
	@exit 1
endif
	@echo "System OS is Linux, continuing build."

prep:
	@echo "Preparing system for build."
	@rm -rf $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(COMPILE_DIR)
	@mkdir -p $(HEADER_DIR)
	@mkdir -p $(LIB_DIR)

build:
	@echo "Building $(LIBRARY_NAME) as $(SO_NAME) in $(LIB_DIR)"
	@echo "Copying all headers to include path."
	@cp $(C_FQ_H_FILES) $(HEADER_DIR)
	@cp $(CPP_FQ_H_FILES) $(HEADER_DIR)

	@echo "Compiling C++ object files with position independent code."
	@echo ""
	@-cd $(COMPILE_DIR) && $(CXX) -I$(HEADER_DIR) -I$(JNIDIR) -I$(JNIMDDIR) -fPIC -c $(CPP_FQ_SRC_FILES)
	@echo ""
	@echo "Compiling C object files with position independent code."
	@echo ""
	@-cd $(COMPILE_DIR) && $(CC) -I$(HEADER_DIR) -I$(JNIDIR) -I$(JNIMDDIR) -fPIC -std=c99 -c $(C_FQ_SRC_FILES)
	@echo ""
	@echo "Creating shared library."
	@echo ""
	@-cd $(COMPILE_DIR) && $(CXX) -shared -fPIC -std=c99 *.o -o $(SO_NAME)
	@-cd $(COMPILE_DIR) && mv $(SO_NAME) $(LIB_DIR)
	@echo "Build success for $(LIBRARY_NAME) as $(LIB_DIR)/$(SO_NAME)"
