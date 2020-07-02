.PHONY : install



all: build-c build-java

build-c:
	@echo "Building C/C++ binary for native transformation tests."
	make -C $(PWD)/scripts/test/jni/demotransformationlibrary
	@echo "building C/C++ binary for native endpoint tests."
	make -C $(PWD)/scripts/test/jni/demoendpointlibrary
	@echo "Finished building C/C++ binaries."

build-java:
	@echo "Running java gradle build and tests for MessageAPI."
	@gradle
	@echo "Finished java gradle build and tests for MessageAPI."
