#!/bin/bash
if [ $# -ne 2 ]
then
	echo "usage: writer.sh <file> <text>"
	exit 1
fi
DIR="$(dirname ${1})"
if [ ! -d ${DIR} ]
then
	mkdir -p ${DIR}
fi
echo "${2}" > ${1}
exit 0
