#!/bin/bash

#Updates the LD_LIBRARY_PATH for libjli and libjvm. Exits install if no java on path.
update_ld_library_paths () {
    if java -version 2>&1 >/dev/null | egrep "\S+\s+version"; then
        echo "java binary was found on the path; using to determine path of libjli.so and libjvm.so"
        local java_bin=$(dirname $(readlink -f $(which java)))
        local java_home=$(cd $java_bin && cd .. && echo $PWD)
        local java_lib=$(cd $java_home && cd lib && echo $PWD)
        local java_jli=$(cd $java_lib && cd jli && echo $PWD)
        local java_jvm=$(cd $java_lib && cd server && echo $PWD)
        if [[ -n $java_jli &&  -n $java_jvm ]]; then
            echo "Updating LD_LIBRARY_PATH with locations for libjli and libjvm in bashrc."
            sed '/#messageapi_jvm_ld_library_path/d' $HOME/.bashrc >> $HOME/.bashrc
            echo "LD_LIBRARY_PATH=${java_jli}:${java_jvm}:$LD_LIBRARY_PATH #messageapi_jvm_ld_library_path" >> ${HOME}/.bashrc
            echo "Successfully updated LD_LIBRARY_PATH in ${HOME}/.bashrc"
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
}

update_headers_var () {
    echo "Updating the MESSAGEAPI_HEADERS environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_c_cpp_set_headers/d' $HOME/.bashrc >> $HOME/.bashrc
    echo "MESSAGEAPI_HEADERS=${HEADERS_INSTALL_DIR} #messageapi_c_cpp_set_headers" >> $HOME/.bashrc
    echo "Added a 'MESSAGEAPI_HEADERS' environment variable to ${HOME}/.bashrc for convenient inclusion of library headers."
    echo "When creating a C/C++ session, endpoint, condition, or transformation, you can use the MESSAGEAPI_HEADERS as the include location."
    echo "Build file templates for each of these is provided in the templates directory, accessible via the MESSAGEAPI_TEMPLATES environment variable."
}

update_libs_var () {
    echo "Updating the MESSAGEAPI_LIBS environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_c_cpp_set_libs/d' $HOME/.bashrc >> $HOME/.bashrc
    echo "MESSAGEAPI_LIBS=${LIBS_INSTALL_DIR} #messageapi_c_cpp_set_libs" >> $HOME/.bashrc
    sed '/#messageapi_libs_ld_library_path/d' $HOME/.bashrc >> $HOME/.bashrc
    echo "LD_LIBRARY_PATH=${MESSAGEAPI_LIBS}:$LD_LIBRARY_PATH #messageapi_libs_ld_library_path" >> ${HOME}/.bashrc
    echo "Added a 'MESSAGEAPI_LIBS' environment variable to ${HOME}/.bashrc for convenient inclusion of the C/C++ shared library."
    echo "Updated the LD_LIBRARY_PATH environment variable to include the MESSAGEAPI_LIBS path."
    echo "When creating a C/C++ program that uses the MessageAPI session library, you can use the MESSAGEAPI_LIBS as the linking location."
}

update_src_var () {
    echo "Updating the MESSAGEAPI_SRC environment variable in $(whoami)'s ~/.bashrc."
    sed '/#messageapi_c_cpp_set_src/d' $HOME/.bashrc >> $HOME/.bashrc
    echo "MESSAGEAPI_SRC=${SRC_INSTALL_DIR} #messageapi_c_cpp_set_src" >> $HOME/.bashrc
    echo "Added a 'MESSAGEAPI_SRC' environment variable to ${HOME}/.bashrc for convenient inclusion of the C/C++ source files."
    echo "When creating a C/C++ session, endpoint, condition, or transformation, you can use the MESSAGEAPI_SRC for base source paths during build."
    echo "Build file templates for each of these is provided in the templates directory, accessible via the MESSAGEAPI_TEMPLATES environment variable."
}

install_headers () {
    echo "Installing messageapi C/C++ headers to ${HEADERS_INSTALL_DIR}."
    mkdir -p ${HEADERS_INSTALL_DIR}
    cp ../headers/* ${HEADERS_INSTALL_DIR}
    echo "Finished installing messageapi C/C++ headers to ${HEADERS_INSTALL_DIR}."
}

install_libs () {
    echo "Installing messageapi C/C++ shared libs to ${LIBS_INSTALL_DIR}."
    mkdir -p ${LIBS_INSTALL_DIR}
    cp ../libs/* ${LIBS_INSTALL_DIR}
    echo "Finished installing messageapi C/C++ shared libs to ${LIBS_INSTALL_DIR}."
}

install_src () {
    echo "Installing messageapi C/C++ src files to ${SRC_INSTALL_DIR}."
    mkdir -p ${SRC_INSTALL_DIR}
    cp ../src/* ${SRC_INSTALL_DIR}
    echo "Finished installing messageapi C/C++ src files to ${SRC_INSTALL_DIR}."
}


source_bashrc () {
    source ${HOME}/.bashrc
}

LIBS_INSTALL_DIR=${HOME}/.messageapi/c/libs
HEADERS_INSTALL_DIR=${HOME}/.messageapi/c/headers
SRC_INSTALL_DIR=${HOME}/.messageapi/c/src

#Main Body
echo "Installing the MessageAPI C/C++ libs, headers, and src for the current user $(whoami)"
update_ld_library_paths
install_libs
update_libs_var
install_headers
update_headers_var
install_src
update_src_var
source_bashrc
echo "Finished installing the MessageAPI C/C++ libs, headers, and src for user $(whoami)."