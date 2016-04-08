#!/bin/bash

gcc -o simulator simulator.c

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

if [ -e simulator ]; then
	printf "${GREEN}compilation success the simulator start now${NC}\n"
	./simulator
	exit 0
else
	printf "${RED}compilation FAILED${NC}\n"
	exit 1
fi

if [ -e simulator ]; then
	rm simulator
fi
