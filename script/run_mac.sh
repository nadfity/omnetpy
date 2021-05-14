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

DISPLAY=host.docker.internal:0 workspace=$workspace omnetpydir=$(realpath $rootdir/omnetpy) docker-compose -f $rootdir/docker-compose.yml up -d
docker-compose -f $rootdir/docker-compose.yml exec omnetpyenv bash
