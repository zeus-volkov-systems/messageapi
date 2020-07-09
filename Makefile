#Primary Makefile for the MessageAPI package.
#
#This Makefile currently controls the Gradle build for:
#
#1. Java-core build,test, and subsequent artifact (uberjar + install script) tar packaging
#2. C/C++ API shared library build, test, and subsequent artifact (.so + full source/header set + install script)
#tar packaging
#3. Java API documentation artifact (html documents as tar) packaging
#
#Note that the package itself has an install.sh bash script ($PKG/scripts/install/package/install.sh)
#that controls installation of specific libraries for any logged in user on the NCEI mission network.

#Library Name and Version
LIBRARY_NAME=messageapi
MAJOR_VERSION=0
MINOR_VERSION=0
PATCH_VERSION=10

#Root Path Computation
PROJECT_ROOT:=$(PWD)

#Java Related Paths
JAR_SRC_DIR=$(PROJECT_ROOT)/build/libs
SRC_JAR=messageapi-$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION)-all.jar
JAVA_ARTIFACT_DIR=$(PROJECT_ROOT)/dist/artifacts/java/$(LIBRARY_NAME)_$(MAJOR_VERSION)_$(MINOR_VERSION)_$(PATCH_VERSION)
TARGET_JAR=messageapi-core-$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION).jar
JAR_INSTALL_SCRIPT=$(PROJECT_ROOT)/scripts/install/java/main/install.sh

DOCS_SRC_DIR=$(PROJECT_ROOT)/build/docs/groovydoc
API_DOCS_DIR=$(PROJECT_ROOT)/dist/docs/api

#C/C++ Related Paths
C_MAIN_BUILD_DIR=$(PROJECT_ROOT)/scripts/build/c/main

.PHONY: build-c_cpp prep-java build-java dist-java copy-docs

all: build-c_cpp prep-java build-java dist-java copy-docs

build-c_cpp:
	@echo "Building the shared library for C/C++ native sessions and the distributable native C artifacts."
	@make -C $(C_MAIN_BUILD_DIR)
	#@echo "Building C/C++ binary for native transformation tests."
	#make -C $(PWD)/scripts/build/c/test/transformation
	#@echo "building C/C++ binary for native endpoint tests."
	#make -C $(PWD)/scripts/build/c/test/endpoint
	@echo "Finished all C/C++ related build tasks."

prep-java:
	@echo "Cleaning any residual Java artifacts."
	@rm -rf $(JAVA_ARTIFACT_DIR)
	@rm -rf $(API_DOCS_DIR)
	@echo "Java ready for build."

build-java:
	@echo "Running java gradle build and tests for MessageAPI."
	@gradle
	@echo "Finished java gradle build and tests for MessageAPI."

dist-java:
	@echo "Creating distributable Java artifacts."
	@cp $(JAR_SRC_DIR)/$(SRC_JAR) $(JAR_SRC_DIR)/$(TARGET_JAR)
	@cp $(JAR_INSTALL_SCRIPT) $(JAR_SRC_DIR)
	@mkdir -p $(JAVA_ARTIFACT_DIR)
	@-cd $(JAR_SRC_DIR) && tar -cf $(LIBRARY_NAME).tar $(TARGET_JAR) install.sh
	@-cd $(JAR_SRC_DIR) && mv $(LIBRARY_NAME).tar $(JAVA_ARTIFACT_DIR)

copy-docs:
	@echo "Copying API docs for distribution."
	@mkdir -p $(API_DOCS_DIR)
	@-cd $(DOCS_SRC_DIR) && tar -cf $(API_DOCS_DIR)/messageapi_docs.tar *
	@echo "Finished copying API docs for distribution."