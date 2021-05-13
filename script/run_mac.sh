#!/usr/bin/env bash
#
# # Usage
# Call this script with the project workspace you want to mount.
#
#     bash run.sh ~/workspace/omnetproject
#
realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}
rootdir=$(git -C "$(dirname $0)" rev-parse --show-toplevel)

workspace=$(realpath $1)
workspace=${workspace:-$(pwd)}

docker run --rm \
     -ti \
     -e DISPLAY=host.docker.internal:0 \
     -v $workspace:/home/userpp/workspace \
     -v $(realpath $rootdir/omnetpy):/home/userpp/omnetpy \
     -e OMNETPY_ROOT=/home/userpp/workspace/omnetpy/omnetpy \
     --privileged \
     -v /tmp/.X11-unix:/tmp/.X11-unix \
     nadfity/omnetpy bash
