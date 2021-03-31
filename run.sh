#!/usr/bin/env bash
docker run --rm \
     -ti -e DISPLAY=$DISPLAY \
     -v $(realpath ./omnetws):/home/userpp/workspace \
     -e OMNETPY_ROOT=/home/userpp/workspace/omnetpy/omnetpy \
     --privileged \
     -v /tmp/.X11-unix:/tmp/.X11-unix \
     nadfity/omnetpy bash
