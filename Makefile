#Primary Makefile for the MessageAPI package.
#
#This Makefile currently controls the build for:
#
#1. Java-core build, test, and subsequent artifact (versioned uberjar + install script) tar packaging
#2. C/C++ API shared library build, test, and subsequent artifact (versioned .so + current full source/header set + install script)
#tar packaging
#3. Java API documentation artifact (html documents as tar) packaging
#
#Note that the package itself has an install.sh bash script ($PKG/scripts/install/package/install.sh)
#that controls installation of specific libraries for any logged in user on the NCEI mission network.

#Library Name and Version
LIBRARY_NAME=messageapi
MAJOR_VERSION=1
MINOR_VERSION=0
PATCH_VERSION=0

#Root Path Computation
PROJECT_ROOT:=$(PWD)

#Java Related Paths
JAR_SRC_DIR=$(PROJECT_ROOT)/build/libs
SRC_JAR=$(LIBRARY_NAME).jar
JAVA_ARTIFACT_DIR=$(PROJECT_ROOT)/dist/artifacts/java/$(LIBRARY_NAME)_$(MAJOR_VERSION)_$(MINOR_VERSION)_$(PATCH_VERSION)
TARGET_JAR=messageapi-core-$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION).jar
JAR_INSTALL_SCRIPT=$(PROJECT_ROOT)/scripts/install/java/main/install.sh

DOCS_SRC_DIR=$(PROJECT_ROOT)/build/docs/groovydoc
API_DOCS_DIR=$(PROJECT_ROOT)/dist/docs/api

TEMPLATE_SRC_DIR=$(PROJECT_ROOT)/resources/main/templates
SESSION_TEMPLATE_SRC_DIR=$(TEMPLATE_SRC_DIR)/sessions
METADATA_TEMPLATE_SRC_DIR=$(TEMPLATE_SRC_DIR)/metadata

#C/C++ Related Paths
C_MAIN_BUILD_DIR=$(PROJECT_ROOT)/scripts/build/c/main
C_TEST_BUILD_DIR=$(PROJECT_ROOT)/scripts/build/c/test

TEST_RESOURCE_DIR=$(PROJECT_ROOT)/libs

run-native-tests: export LD_LIBRARY_PATH = $(JAVA_HOME)/lib/jli:$(JAVA_HOME)/lib/server
run-native-tests: export CLASSPATH = $(TEST_RESOURCE_DIR)/test/java/jars/$(SRC_JAR)

.PHONY: build-c_cpp prep-java build-java dist-java run-native-tests copy-docs cleanup

all: build-c_cpp prep-java build-java dist-java copy-docs run-native-tests cleanup

build-c_cpp:
	@echo "Building the shared library for C/C++ native sessions and the distributable native C artifacts."
	@make -C $(C_MAIN_BUILD_DIR)
	@echo "Building C/C++ binary for native transformation tests."
	@make -C $(C_TEST_BUILD_DIR)/transformation
	@echo "Building C/C++ binary for native endpoint tests."
	@make -C $(C_TEST_BUILD_DIR)/endpoint
	@echo "Building C/C++ binary for native session tests."
	@make -C $(C_TEST_BUILD_DIR)/session
	@echo "Finished all C/C++ related build tasks."

cleanup:
	@echo "Cleaning up test resources."
	@rm -rf $(TEST_RESOURCE_DIR)

prep-java:
	@echo "Cleaning any residual Java artifacts."
	@rm -rf $(JAVA_ARTIFACT_DIR)
	@rm -rf $(API_DOCS_DIR)
	@echo "Java ready for build."

build-java:
	@echo "Running java gradle build and tests for MessageAPI."
	@gradle
	@mkdir -p $(TEST_RESOURCE_DIR)/test/java/jars
	@cp $(PROJECT_ROOT)/build/libs/$(SRC_JAR) $(TEST_RESOURCE_DIR)/test/java/jars
	@echo "Finished java gradle build and tests for MessageAPI."

dist-java:
	@echo "Creating distributable Java artifacts."
	@cp $(JAR_SRC_DIR)/$(SRC_JAR) $(JAR_SRC_DIR)/$(TARGET_JAR)
	@cp $(JAR_INSTALL_SCRIPT) $(JAR_SRC_DIR)
	@cp $(SESSION_TEMPLATE_SRC_DIR)/*.json $(JAR_SRC_DIR)
	@cp $(METADATA_TEMPLATE_SRC_DIR)/*.json $(JAR_SRC_DIR)
	@mkdir -p $(JAVA_ARTIFACT_DIR)
	@-cd $(JAR_SRC_DIR) && tar -cf $(LIBRARY_NAME).tar $(TARGET_JAR) install.sh *.json
	@-cd $(JAR_SRC_DIR) && mv $(LIBRARY_NAME).tar $(JAVA_ARTIFACT_DIR)

copy-docs:
	@echo "Copying API docs for distribution."
	@mkdir -p $(API_DOCS_DIR)
	@-cd $(DOCS_SRC_DIR) && tar -cf $(API_DOCS_DIR)/messageapi_docs.tar *
	@echo "Finished copying API docs for distribution."

run-native-tests:
	@echo "Running native C/C++ session test."
	@-cd $(TEST_RESOURCE_DIR)/test/c/session && ./SessionDemo.bin
	@echo "Finished running native C/C++ session test."

install-k3:
	@echo "Installing package to system for current user."
	@wget https://k3.cicsnc.org/rberkheimer/messageapi/-/raw/mac-develop/scripts/install/package/install_k3.sh?inline=false --no-check-certificate -O install_k3.sh
	@chmod +x install_k3.sh
	@./install_k3.sh "C_CPP"
	@rm install_k3.sh
	@echo "Finished installing package, validate ~./bashrc and env vars for success."

install:
	@echo "Installing package to system for current user."
	@wget https://git.ncei.noaa.gov/sesb/sscs/messageapi/-/raw/master/scripts/install/package/install.sh?inline=false --no-check-certificate -O install.sh
	@chmod +x install.sh
	@./install.sh "C_CPP"
	@rm install.sh
	@echo "Finished installing package, validate ~/.bashrc and env vars for success."