#!/bin/bash

OPTIONS="$@"

echo "`date` + `whoami` + gdb test" >> gdb-output.log
exec /usr/bin/gdb "$@" 
