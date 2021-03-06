#!/bin/bash

set -o errexit

die () {
    echo >&2 "$@"
    exit 1
}

install_core () {
    echo "Installing MessageAPI Core version ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}"
    #Set target specific vars
    local lib_path=dist/artifacts/java/messageapi_${MAJOR_VERSION}_${MINOR_VERSION}_${PATCH_VERSION}
    local file_path=${BASE_URL}/${BRANCH}/${lib_path}/${FILE_NAME}${FILE_SUFFIX}
    #Set tmp dir location
    local tmp_dir=${HOME}/.messageapi/tmp
    #Retrieve file
    rm -rf "${tmp_dir}"
    mkdir -p "${tmp_dir}/java"
    cd "${tmp_dir}/java"
    wget "${file_path}" --no-check-certificate
    mv "${FILE_NAME}${FILE_SUFFIX}" "${FILE_NAME}"
    tar -xf "${FILE_NAME}"
    ./install.sh
    rm -rf "${tmp_dir}"
    echo "Finished installing MessageAPI Core version ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}"
}

install_c_cpp () {
    echo "Installing MessageAPI for C/C++ version ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}"
    #Set target specific vars
    local lib_path=dist/artifacts/c/messageapi_${MAJOR_VERSION}_${MINOR_VERSION}_${PATCH_VERSION}
    local file_path=${BASE_URL}/${BRANCH}/${lib_path}/${FILE_NAME}${FILE_SUFFIX}
    #Set tmp dir location
    local tmp_dir=${HOME}/.messageapi/tmp
    #Retrieve file
    rm -rf "${tmp_dir}"
    mkdir -p "${tmp_dir}/c"
    cd "${tmp_dir}/c"
    wget "${file_path}" --no-check-certificate
    mv "${FILE_NAME}${FILE_SUFFIX}" "${FILE_NAME}"
    tar -xf "${FILE_NAME}"
    ./install.sh
    rm -rf "${tmp_dir}"
    echo "Finished installing MessageAPI for C/C++ version ${MAJOR_VERSION}_${MINOR_VERSION}_${PATCH_VERSION}."
}

#Main Body

echo "This is the main install script to install various MessageAPI packages as precompiled artifacts (not source) built for use on RHEL7."
echo "To use, pass in an argument - current options are CORE or C_CPP"
echo "If choosing an option with dependencies, those dependencies will first be installed automatically (e.g., C_CPP depends on CORE)."
echo "To change the version of download, open this file and update the BRANCH, MAJOR_VERSION, MINOR_VERSION, or PATCH_VERSION vars as desired."
echo "The version that is configured to be automatically downloaded is the most recently approved release."

[ "$#" -eq 1 ] || die "target argument required (CORE or C_CPP), $# provided"

BASE_URL=https://k3.cicsnc.org/rberkheimer/messageapi/-/raw
BRANCH=mac-develop
FILE_NAME=messageapi.tar
FILE_SUFFIX="?inline=false"
MAJOR_VERSION=1
MINOR_VERSION=0
PATCH_VERSION=0

TARGET=$1

case ${TARGET} in
     CORE)
          install_core
          ;;
     C_CPP)
          install_core
          install_c_cpp
          ;;
     *)
          echo "Not a valid option."
          ;;
esac