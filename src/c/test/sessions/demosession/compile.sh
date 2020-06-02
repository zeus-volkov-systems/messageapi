#!/bin/bash

gcc NativeSessionDemo.c -I$(/usr/libexec/java_home)/include/ -I$(/usr/libexec/java_home)/include/darwin -L$(/usr/libexec/java_home)/jre/lib/jli -L$(/usr/libexec/java_home)/jre/lib/server/ -ljli -ljvm
