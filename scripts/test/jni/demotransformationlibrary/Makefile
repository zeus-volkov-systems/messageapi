### This is a Makefile for MessageAPI Native Transformations.
# The majority of this Makefile is standard, with very few user specified things.
# There are a few specific requirements and other notable things to keep in mind when using this Makefile:
## 1. You must have a JDK installed (not JRE). This library requires the jni.h header included in your jdk.
## 2. JAVA_HOME must be set to your JDK home directory. This Makefile references JAVA_HOME in looking for jni.h
## 3. This Makefile assumes a specific project layout when setting the PROJECTPATH. If the Makefile is not working,
##    you should look at how it uses PROJECTPATH, TRANSFORMATION_NAME, and TRANSFORMATION_TYPE to find required files.
##    if your project is set up differently, i.e. custom project layout, then path dependent vars will need to be
##    looked at and possibly changed.

#The following represents the root project path. DO NOT EDIT
SCRIPTDIR=$(PWD)
PROJECTPATH=$(firstword $(subst /scripts/$(TRANSFORMATION_TYPE)/, ,$(SCRIPTDIR)))

#The following is used to determine how native resources are compiled. DO NOT EDIT.
UNAME := $(shell uname)

###################################################### USER SPECIFIED SECTION - PLEASE EDIT ###########################
#USER SPECIFIED
#The following vars are used to route source code and scripts (from the scripts and src dirs)
#to the library dir as compiled files (the job name should match the name of the directory/job map.)
#the job type is simply a test job or a main job and should either be test or main.
TRANSFORMATION_NAME=demotransformationlibrary
TRANSFORMATION_TYPE=test

#USER SPECIFIED
#The following var represents the output name of the JniLib that will be created and referenced in the job map.
#Do not specify the extension (.so/.dll/.jnilib) - these are determined automatically on build.
#The full path to the created library must be referenced in the transformation config.
LIBNAME=DemoTransformationLibrary

#USER SPECIFIED
#The following vars should contain strings representing the C, Fortran, and CPP libraries that glue the fortran code to java code.
#These strings should contain the user libraries in the order they need to be compiled (ex, "First.c Second.c Third.c")
#These vars do not need to specify libraries they depend on that are found in the common variables (those are automatically compiled first).
USERC=TransformationWrapper.c
USERCPP=
USERFORTRAN=

###################################################### END USER SPECIFIED SECTION ###########################

#The following represent directories for JNI Libraries that must be included during C and CPP compilation.
#These are platform dependent. If you have a default setup, these probably will not have to be modified.
#However, if you have nonstandard include paths, or you are getting errors, this may need to be altered.
ifeq ($(UNAME), Linux)
#The following represent a standard RHEL 7 system.
JNIDIR="$(JAVA_HOME)/include"
JNIMDDIR="$(JAVA_HOME)/include/linux"
JVMHEADERS="$(JAVA_HOME)/include/linux"
endif
ifeq ($(UNAME), Darwin)
#The following represent a standard OSX system.
JNIDIR="$(JAVA_HOME)/include"
JNIMDDIR="$(JAVA_HOME)/include/darwin"
JVMHEADERS="$(JAVA_HOME)/include"
endif

#compilers
CXX=g++
CC=gcc
FF=gfortran

#The following vars contain strings representing common libraries used by all code
#at a project level. These should generally not be touched by users.
COMMONC=
COMMONCPP=JniUtils.cpp TypeUtils.cpp ListUtils.cpp MapUtils.cpp ConditionUtils.cpp FieldUtils.cpp \
TransformationUtils.cpp RecordUtils.cpp RejectionUtils.cpp PacketUtils.cpp \
MessageApiTransformation.cpp MessageApiTransformationLib.cpp
COMMONFORTRAN=
JAVACLASSES:=$(PROJECTPATH)/src/java/main/gov/noaa/messageapi/transformations/NativeTransformation.java
JAVAPATH=$(PROJECTPATH)/src/java/main:$(PROJECTPATH)/src/java/main/gov/noaa/messageapi/transformations


#The following contains source code paths derived from the TRANSFORMATION_NAME and TRANSFORMATION_TYPE supplied by the user.
COMMONCPATH=$(PROJECTPATH)/src/c/main/common/structs/
USERCPATH=$(PROJECTPATH)/src/c/$(TRANSFORMATION_TYPE)/transformations/$(TRANSFORMATION_NAME)/
COMMONCPPPATH=$(PROJECTPATH)/src/cpp/main/common/
USERCPPPATH=$(PROJECTPATH)/src/cpp/$(TRANSFORMATION_TYPE)/$(TRANSFORMATION_NAME)/
COMMONFORTRANPATH=$(PROJECTPATH)/src/fortran/main/common/
USERFORTRANPATH=$(PROJECTPATH)/src/fortran/$(TRANSFORMATION_TYPE)/$(TRANSFORMATION_NAME)/

#The following var contains the target path for the project code.
TARGETPATH="$(PROJECTPATH)/lib/$(TRANSFORMATION_TYPE)/native/$(TRANSFORMATION_NAME)/"

#The following is the target library for the native jni library.
ifeq ($(UNAME), Linux)
#The following represents a standard RHEL 7 system.
LNFLAGS=-dynamiclib -shared -lgfortran -I$(JVMHEADERS)
endif
ifeq ($(UNAME), Darwin)
#The following represents a standard OSX system.
LNFLAGS=-dynamiclib -shared -lgfortran -I$(JVMHEADERS) -framework JavaVM
endif

CFLAGS=-I$(JVMHEADERS) -I$(COMMONCPPPATH) -I$(COMMONCPATH) -I$(USERCPPPATH) -I$(USERCPATH) -I$(JNIDIR) -I$(JNIMDDIR) -fpic -std=c99
FFLAGS=-I$(COMMONFORTRANPATH) -I$(USERFORTRANPATH) -fPIC -fopenmp

#The following is the target library for the native jni library.
ifeq ($(UNAME), Linux)
#The following represents a standard RHEL 7 system.
DYLIB=lib$(LIBNAME).so
endif
ifeq ($(UNAME), Darwin)
#The following represents a standard OSX system.
DYLIB=lib$(LIBNAME).jnilib
endif

#COMMONFORTRAN1=$(addprefix $(COMMONFORTRANPATH), $(COMMONFORTRAN))
#USERFORTRAN1=$(addprefix $(USERFORTRANPATH), $(USERFORTRAN))
COMMONC1=$(addprefix $(COMMONCPATH), $(COMMONC))
USERC1=$(addprefix $(USERCPATH), $(USERC))
COMMONCPP1=$(addprefix $(COMMONCPPPATH), $(COMMONCPP))
USERCPP1=$(addprefix $(USERCPPPATH), $(USERCPP))

all: clean gen-headers build

.PHONY : clean gen-headers build

gen-headers:
	echo "Generating headers. "
	echo ""
	$(foreach header,$(JAVACLASSES),javac -h $(USERCPATH) -classpath $(JAVAPATH) $(header);)
	echo ""

build:
	echo "Building " $(TRANSFORMATION_NAME) " in " $(PROJECTPATH)
	#echo "Compiling Fortran"
	#echo ""
	#cd $(TARGETPATH) && $(FF) $(FFLAGS) -c $(COMMONFORTRAN1) $(USERFORTRAN1)
	#echo ""
	echo "Compiling CPP"
	echo ""
	cd $(TARGETPATH) && $(CXX) $(CFLAGS) -c $(COMMONCPP1) $(USERCPP1)
	echo ""
	echo "Compiling C"
	echo ""
	cd $(TARGETPATH) && $(CC) $(CFLAGS) -c $(COMMONC1) $(USERC1)
	echo ""
	echo "Creating JNI Library"
	echo ""
	cd $(TARGETPATH) && $(CXX) $(LNFLAGS) *.o -o $(DYLIB)
	echo "Build success for " $(TRANSFORMATION_NAME)

clean:
	echo "Cleaning up."
	echo ""
	-cd $(TARGETPATH) && rm *.h
	-cd $(TARGETPATH) && rm *.o
	-cd $(TARGETPATH) && rm *.mod
	-cd $(TARGETPATH) && rm *.jnilib
	-cd $(TARGETPATH) && rm *.so
	echo ""
