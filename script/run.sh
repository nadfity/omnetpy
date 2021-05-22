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

DISPLAY=$DISPLAY workspace=$workspace omnetpydir=$(realpath $rootdir/omnetpy) docker-compose -f $rootdir/docker-compose.yml up -d
docker-compose -f $rootdir/docker-compose.yml exec omnetpyenv bash
