### This Makefile can be used as a template for writing MessageAPI compatible C/C++ Transformations that extend the 
# NativeTransformation. This Makefile itself is setup for the test endpoint, but with a few modifications, it can be
# updated for user endpoint content. Note that the goal of native endpoint production is to create a shared library,
# as shared libraries are used by the Java code. Once produced, the shared library should just be referenced in the
# config map for the endpoint itself (fully qualified of course).

# The majority of this Makefile is standard, with very few user specified things.

# There are a few specific requirements and other notable things to keep in mind when using this Makefile:
## 1. You must have a JDK installed (not JRE). This library requires the jni.h and jnimd.h headers included in your jdk.
## 2. JAVA_HOME must be set to your JDK home directory. This Makefile references JAVA_HOME in looking for jni.h and jnimd.h

#Messageapi C/C++ Artifact Versioning
SO_NAME=messageapi
MAJOR_VERSION=1
MINOR_VERSION=0
PATCH_VERSION=0

#The following is used to bootstrap the PROJECT_ROOT 
CURRENT_DIR=$(PWD)

#The following represents the root project path. In this tailored example, we use a relative path to the project root.
#In your own Makefile, this variable can be set directly.
PROJECT_ROOT=$(firstword $(subst /scripts/build/c/test, ,$(CURRENT_DIR)))

#Set target directories - this is where the library will build from/to.
ARTIFACT_DIR=$(PROJECT_ROOT)/dist/artifacts/c
BUILD_DIR=$(PROJECT_ROOT)/build/c/test/session
SO_DIR=$(BUILD_DIR)/resources
COMPILE_DIR=$(BUILD_DIR)/compile#.o files produced here
HEADER_DIR=$(BUILD_DIR)/headers#.h files copied here before build (for central include path)
BIN_DIR=$(PROJECT_ROOT)/libs/test/c/session#.so moved here before test
DEPS_DIR=$(BIN_DIR)/so


#The following var represents the 
BIN_NAME=SessionDemo.bin

#The following represent directories for JNI Libraries that must be included during C and CPP compilation.
#The following represent a standard RHEL 7/8 system with OpenJDK.
JNIDIR=$(JAVA_HOME)/include
JNIMDDIR=$(JAVA_HOME)/include/linux
JVM_SO_DIR=$(JAVA_HOME)/lib/server
JLI_SO_DIR=$(JAVA_HOME)/lib/jli

export LD_LIBRARY_PATH=$(JLI_SO_DIR):$(JVM_SO_DIR)

#compilers
CC=gcc

C_DIR=$(PROJECT_ROOT)/src/c/

C_SRC_FILES=test/sessions/session_demo/SessionDemo.c
C_FQ_SRC_FILES=$(addprefix $(C_DIR), $(C_SRC_FILES))


all: check_sys prep copy-shared build clean

.PHONY : check_sys prep copy-shared build clean

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
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(SO_DIR)
	@mkdir -p $(COMPILE_DIR)
	@mkdir -p $(HEADER_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(DEPS_DIR)
	@echo "Finished preparing system for build."

copy-shared:
	@echo "Extracting and copying production artifacts as shared resources for build."
	@cp $(ARTIFACT_DIR)/$(SO_NAME)_$(MAJOR_VERSION)_$(MINOR_VERSION)_$(PATCH_VERSION)/$(SO_NAME).tar $(SO_DIR)
	@-cd $(SO_DIR) && tar -xf $(SO_NAME).tar
	@cp $(SO_DIR)/libs/* $(DEPS_DIR)
	@cp $(SO_DIR)/headers/* $(HEADER_DIR)
	@echo "Finished copying resources."


build:
	@echo "Building $(BIN_NAME) in $(BIN_DIR)"
	@echo "Compiling C object files with position independent code."
	@-cd $(COMPILE_DIR) && $(CC) -fPIC -std=c99 -I$(HEADER_DIR) -I$(JNIDIR) -I$(JNIMDDIR) -L$(DEPS_DIR) -Wl,-rpath,$(DEPS_DIR) -l$(SO_NAME) $(C_FQ_SRC_FILES) -o $(BIN_NAME)
	@cp $(COMPILE_DIR)/$(BIN_NAME) $(BIN_DIR)
	@echo "Completed build of $(BIN_DIR)/$(BIN_NAME)."

clean:
	@echo "Cleaning up build refuse."
	@rm -rf $(BUILD_DIR)
	@echo "Finished cleaning up build refuse."