#!/bin/bash

update_classpath_var () {
    echo ""
    echo "Updating the CLASSPATH environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_core_set_classpath/d' "${BASHRC}" > "${BASHRC_TMP}"
    mv "${BASHRC_TMP}" "${BASHRC}"
    echo "export CLASSPATH=${CORE_INSTALL_DIR}/${JAR_NAME}:\$CLASSPATH #messageapi_core_set_classpath" >> "${BASHRC}"
    echo ""
}

update_template_var () {
    echo ""
    echo "Updating the MESSAGEAPI_SESSION_TEMPLATE_DIR environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_core_set_template_dir/d' "${BASHRC}" > "${BASHRC_TMP}"
    mv "${BASHRC_TMP}" "${BASHRC}"
    echo "export MESSAGEAPI_SESSION_TEMPLATE_DIR=${SESSION_TEMPLATE_INSTALL_DIR} #messageapi_core_set_template_dir" >> "${BASHRC}"
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

install_standard_session_template_resources () {
    echo ""
    echo "Installing messageapi standard session template resources to ${SESSION_TEMPLATE_INSTALL_DIR}."
    rm -rf "${SESSION_TEMPLATE_INSTALL_DIR}"
    mkdir -p "${SESSION_TEMPLATE_INSTALL_DIR}"
    cp *.json "${SESSION_TEMPLATE_INSTALL_DIR}"
    echo "Finished installing messageapi standard session template resources to ${SESSION_TEMPLATE_INSTALL_DIR}."
    echo ""
}

refresh_shell () {
    unset CLASSPATH
    unset MESSAGEAPI_SESSION_TEMPLATE_DIR
}


BASHRC=${HOME}/.bashrc
BASHRC_TMP=${HOME}/.bashrc_tmp

CORE_INSTALL_DIR=${HOME}/.messageapi/java/jars
SESSION_TEMPLATE_INSTALL_DIR=${HOME}/.messageapi/java/templates

MAJOR_VERSION=1
MINOR_VERSION=0
PATCH_VERSION=0
JAR_NAME=messageapi-core-${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}.jar

#Main Body
echo ""
echo "Installing the MessageAPI-Core Jar for the current user $(whoami)"
install_core_jar
install_standard_session_template_resources
update_classpath_var
update_template_var
refresh_shell
echo "Finished installing the MessageAPI-Core Jar for user $(whoami)."
echo ""