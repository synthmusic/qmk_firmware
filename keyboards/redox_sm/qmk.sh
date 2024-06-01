#!/bin/bash
if [ $# -eq 0 ]; then
  echo "Running compile and flash in sequence"
  qmk compile -kb redox_sm -km default && qmk flash -kb redox_sm -km default
  exit 1
fi

# Access the first argument
argument=$1

# Check the value of the argument and run different commands
if [ $argument == "compile" ]; then
    echo "Running compile"
    qmk compile -kb redox_sm -km default
elif [ $argument == "help" ]; then
    echo "compile: Compiles only"
elif [ $argument == "command2" ]; then
    echo "Running command 2..."
else
    echo "Invalid argument. Please provide a valid argument."
fi