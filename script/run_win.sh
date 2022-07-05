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

docker run --rm -ti -e DISPLAY=$DISPLAY -v ${workspace}:/home/userpp/workspace -v ${omnetpydir}:/home/userpp/omnetpy -e OMNETPY_ROOT=/home/userpp/workspace/omnetpy/omnetpy --privileged -v /tmp/.X11-unix:/tmp/.X11-unix nadfity/omnetpy bash
DISPLAY=$DISPLAY workspace=$workspace omnetpydir=$(realpath $rootdir/omnetpy) docker-compose -f $rootdir/docker-compose.yml exec nadfity/omnetpy bash
