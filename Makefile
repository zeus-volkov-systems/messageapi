.PHONY : install

all: install

install:
	echo "Running gradle build for MessageAPI."
	${GRADLE}
	echo "Finished gradle build for MessageAPI."
