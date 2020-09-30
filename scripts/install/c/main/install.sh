#!/bin/bash

#Updates the LD_LIBRARY_PATH for libjli and libjvm. Exits install if no java on path.
update_ld_library_paths () {
    echo ""
    if java -version 2>&1 >/dev/null | grep -E "\S+\s+version"; then
        echo "The java binary was found on the path; using to determine path of libjli.so and libjvm.so"
        local java_bin
        local java_home
        local java_lib
        local java_jli
        local java_jvm
        java_bin=$(dirname "$(readlink -f "$(which java)")")
        java_home=$(cd "${java_bin}" && cd .. && echo "${PWD}")
        java_lib=$(cd "${java_home}" && cd lib && echo "${PWD}")
        java_jli=$(cd "${java_lib}" && cd jli && echo "${PWD}")
        java_jvm=$(cd "${java_lib}" && cd server && echo "${PWD}")
        if [[ -n $java_jli &&  -n $java_jvm ]]; then
            echo "Updating LD_LIBRARY_PATH with locations for libjli and libjvm in bashrc."
            sed '/#messageapi_jvm_ld_library_path/d' "${BASHRC}" > "${BASHRC_TMP}"
            mv "${BASHRC_TMP}" "${BASHRC}"
            echo "export LD_LIBRARY_PATH=${java_jli}:${java_jvm}:\$LD_LIBRARY_PATH #messageapi_jvm_ld_library_path" >> "${BASHRC}"
            echo "Successfully updated LD_LIBRARY_PATH in ${BASHRC}"
        else
            echo "Could not find the libjli or libjvm folders. C/C++ lib will not work correctly."
            echo "Please contact messageapi maintainers for help, it appears you have a non-supported java setup."
            echo "Quitting installation."
            exit 1
        fi
    else
        echo "java binary not found on path, C/C++ lib will not work correctly."
        echo "Please update your PATH to include the location of the java binary, or contact messageapi maintainers for help."
        echo "Quitting installation."
        exit 1
    fi
    echo ""
}

update_headers_var () {
    echo ""
    echo "Updating the MESSAGEAPI_HEADERS environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_c_cpp_set_headers/d' "${BASHRC}" > "${BASHRC_TMP}"
    mv "${BASHRC_TMP}" "${BASHRC}"
    echo "export MESSAGEAPI_HEADERS=${HEADERS_INSTALL_DIR} #messageapi_c_cpp_set_headers" >> "${BASHRC}"
    echo "Added a 'MESSAGEAPI_HEADERS' environment variable to ${BASHRC} for convenient inclusion of library headers."
    echo "When creating a C/C++ session, endpoint, condition, or transformation, you can use the MESSAGEAPI_HEADERS as the include location."
    echo "Build file templates for each of these is provided in the templates directory, accessible via the MESSAGEAPI_C_TEMPLATES environment variable."
    echo ""
}

update_libs_var () {
    echo ""
    echo "Updating the MESSAGEAPI_LIBS environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_c_cpp_set_libs/d' "${BASHRC}" > "${BASHRC_TMP}"
    mv "${BASHRC_TMP}" "${BASHRC}"
    echo "export MESSAGEAPI_LIBS=${LIBS_INSTALL_DIR} #messageapi_c_cpp_set_libs" >> "${BASHRC}"
    sed '/#messageapi_c_cpp_ld_library_path/d' "${BASHRC}" > "${BASHRC_TMP}"
    mv "${BASHRC_TMP}" "${BASHRC}"
    echo "export LD_LIBRARY_PATH=${LIBS_INSTALL_DIR}:\$LD_LIBRARY_PATH #messageapi_c_cpp_ld_library_path" >> "${BASHRC}"
    echo "Added a 'MESSAGEAPI_LIBS' environment variable to ${BASHRC} for convenient inclusion of the C/C++ shared library."
    echo "Updated the LD_LIBRARY_PATH environment variable to include the MESSAGEAPI_LIBS path."
    echo "When creating a C/C++ program that uses the MessageAPI session library, you can use the MESSAGEAPI_LIBS as the linking location."
    echo ""
}

update_src_var () {
    echo ""
    echo "Updating the MESSAGEAPI_SRC environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_c_cpp_set_src/d' "${BASHRC}" > "${BASHRC_TMP}"
    mv "${BASHRC_TMP}" "${BASHRC}"
    echo "export MESSAGEAPI_SRC=${SRC_INSTALL_DIR} #messageapi_c_cpp_set_src" >> "${BASHRC}"
    echo "Added a 'MESSAGEAPI_SRC' environment variable to ${BASHRC} for convenient inclusion of the C/C++ source files."
    echo "When creating a C/C++ session, endpoint, condition, or transformation, you can use the MESSAGEAPI_SRC for base source paths during build."
    echo "Build file templates for each of these is provided in the templates directory, accessible via the MESSAGEAPI_C_TEMPLATES environment variable."
    echo ""
}

update_template_var () {
    echo ""
    echo "Updating the MESSAGEAPI_C_TEMPLATES environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_c_cpp_build_templates/d' "${BASHRC}" > "${BASHRC_TMP}"
    mv "${BASHRC_TMP}" "${BASHRC}"
    echo "export MESSAGEAPI_C_TEMPLATES=${TEMPLATE_INSTALL_DIR} #messageapi_c_cpp_build_templates" >> "${BASHRC}"
    echo "Added a 'MESSAGEAPI_C_TEMPLATES' environment variable to ${BASHRC} for convenient access to the C/C++ build templates."
    echo "These templates are set up to use the installation paths for messageapi source code, libraries, and headers."
    echo "To use them, copy the template to your desired build location, fill out the fields with USER FIELD comments, and run 'make'."
    echo ""
}

install_headers () {
    echo ""
    echo "Installing messageapi C/C++ headers to ${HEADERS_INSTALL_DIR}."
    rm -rf "${HEADERS_INSTALL_DIR}"
    mkdir -p "${HEADERS_INSTALL_DIR}"
    cp headers/* "${HEADERS_INSTALL_DIR}"
    echo "Finished installing messageapi C/C++ headers to ${HEADERS_INSTALL_DIR}."
    echo ""
}

install_libs () {
    echo ""
    echo "Installing messageapi C/C++ shared libs to ${LIBS_INSTALL_DIR}."
    rm -rf "${LIBS_INSTALL_DIR}"
    mkdir -p "${LIBS_INSTALL_DIR}"
    cp libs/* "${LIBS_INSTALL_DIR}"
    echo "Finished installing messageapi C/C++ shared libs to ${LIBS_INSTALL_DIR}."
    echo ""
}

install_src () {
    echo ""
    echo "Installing messageapi C/C++ src files to ${SRC_INSTALL_DIR}."
    rm -rf "${SRC_INSTALL_DIR}"
    mkdir -p "${SRC_INSTALL_DIR}"
    cp src/* "${SRC_INSTALL_DIR}"
    echo "Finished installing messageapi C/C++ src files to ${SRC_INSTALL_DIR}."
    echo ""
}

install_templates () {
    echo ""
    echo "Installing messageapi C/C++ build templates to ${TEMPLATE_INSTALL_DIR}."
    rm -rf "${TEMPLATE_INSTALL_DIR}"
    mkdir -p "${TEMPLATE_INSTALL_DIR}"
    cp templates/* "${TEMPLATE_INSTALL_DIR}"
    echo "Finished installing messageapi C/C++ build templates to ${TEMPLATE_INSTALL_DIR}."
    echo ""
}

refresh_shell () {
    unset LD_LIBRARY_PATH
}

BASHRC=${HOME}/.bashrc
BASHRC_TMP=${HOME}/.bashrc_tmp

INSTALL_DIR=${HOME}/.messageapi/c
LIBS_INSTALL_DIR=${INSTALL_DIR}/libs
HEADERS_INSTALL_DIR=${INSTALL_DIR}/headers
SRC_INSTALL_DIR=${INSTALL_DIR}/src
TEMPLATE_INSTALL_DIR=${INSTALL_DIR}/templates

#Main Body
echo ""
echo "Installing the MessageAPI C/C++ libs, headers, src, and build templates for the current user $(whoami)"
update_ld_library_paths
install_libs
update_libs_var
install_headers
update_headers_var
install_src
update_src_var
install_templates
update_template_var
refresh_shell
echo "Finished installing the MessageAPI C/C++ libs, headers, src, and build templates for user $(whoami)."
echo ""