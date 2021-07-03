#!/bin/bash

RED='\033[0;31m'

if [[ "$1" = "" ]]; then
	echo -e "${RED}Choose type of execution: run/test"
	echo -e "${RED}Example: ./run_cmake.sh test"
	exit 0
fi

if [ ! -d "build" ]; then
	mkdir build
fi
cd build

if [[ "$2" = "" ]]
then
	echo "We added a default Path for Qt5"
	echo "Pass the Correct Path if this is not Correct: "
	current_username=$(echo `whoami`)
	QT_PATH=/Users/$current_username/Qt5.14.0/5.14.0/clang_64
	echo $QT_PATH
else
	QT_PATH=$2
fi

echo ""

if [[ "$1" = "run" ]]
then
	echo "EXECUTING CMAKE FOR RUNNING APPLICATION"
	echo ""
	cmake -DAPP_ENABLE=ON  -DTEST_ENABLE=OFF -DCMAKE_PREFIX_PATH=$QT_PATH ..

elif [[ "$1" = "test" ]]
then
	echo "EXECUTING CMAKE FOR TESTING APPLICATION"
	echo ""
	cmake -DAPP_ENABLE=OFF -DTEST_ENABLE=ON  -DCMAKE_PREFIX_PATH=$QT_PATH ..
fi


