#!/bin/bash

update_classpath_var () {
    echo ""
    echo "Updating the CLASSPATH environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_core_set_classpath/d' "${HOME}/.bashrc" > "${HOME}/.bashrc_tmp"
    mv "${HOME}/.bashrc_tmp" "${HOME}/.bashrc"
    echo "CLASSPATH=${CORE_INSTALL_DIR}/${JAR_NAME}:$CLASSPATH #messageapi_core_set_classpath" >> "${HOME}/.bashrc"
    echo ""
}

install_core_jar () {
    echo ""
    echo "Installing messageapi core jar to ${CORE_INSTALL_DIR}."
    rm -rf "${CORE_INSTALL_DIR}"
    mkdir -p "${CORE_INSTALL_DIR}"
    cp "${JAR_NAME}" "${CORE_INSTALL_DIR}"
    echo "Finished installing messageapi core jar to ${CORE_INSTALL_DIR}."
    echo ""
}

source_bashrc () {
    echo ""
    echo "Sourcing bashrc"
    source "${HOME}/.bashrc"
    echo ""
}

CORE_INSTALL_DIR=${HOME}/.messageapi/java/jars
MAJOR_VERSION=1
MINOR_VERSION=0
PATCH_VERSION=0
JAR_NAME=messageapi-core-${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}.jar

#Main Body
echo ""
echo "Installing the MessageAPI-Core Jar for the current user $(whoami)"
install_core_jar
update_classpath_var
source_bashrc
echo "Finished installing the MessageAPI-Core Jar for user $(whoami)."
echo ""