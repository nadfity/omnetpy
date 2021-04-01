#!/usr/bin/env bash
#
# # Usage
# Call this script with the project workspace you want to mount.
#
#     bash run.sh ~/workspace/omnetproject
#

workspace=$(realpath $1)

docker run --rm \
     -ti -e DISPLAY=$DISPLAY \
     -v $workspace:/home/userpp/workspace \
     -v $(realpath ./omnetpy/omnetpy):/home/userpp/omnetpy \
     -e OMNETPY_ROOT=/home/userpp/workspace/omnetpy/omnetpy \
     --privileged \
     -v /tmp/.X11-unix:/tmp/.X11-unix \
     nadfity/omnetpy bash
