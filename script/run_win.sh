#!/usr/bin/env bash
#
# # Usage
# Call this script with the project workspace you want to mount.
#
#     bash run.sh ~/workspace/omnetproject
#

rootdir=$(git -C "$(dirname $0)" rev-parse --show-toplevel)

workspace=$(realpath ${1:-.})
workspace=${workspace:-$(pwd)}

echo "DISPLAY=$DISPLAY"
echo "workspace=$workspace"
echo "omnetpydir=$(realpath $rootdir/omnetpy)"

DISPLAY=$DISPLAY workspace=$workspace omnetpydir=$(realpath $rootdir/omnetpy) docker-compose -f $rootdir/docker-compose.yml up --build -d
docker-compose -f $rootdir/docker-compose.yml exec omnetpyenv bash
