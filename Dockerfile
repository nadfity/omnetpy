FROM ubuntu:20.04 as base
MAINTAINER Marcos Modenesi <marcosmodenesi@gmail.com>

# install basic packages
RUN apt-get update && apt-get dist-upgrade -y \
    && DEBIAN_FRONTEND=noninteractive apt-get -y install \
        locales sudo wget git \
        build-essential gcc g++ bison flex perl \
        qt5-default tcl-dev tk-dev libxml2-dev zlib1g-dev \
        default-jre doxygen graphviz \
        libopenscenegraph-dev openscenegraph-plugin-osgearth \
        openmpi-bin libopenmpi-dev \
        python3 python3-pip libqt5opengl5-dev \
        openscenegraph-plugin-osgearth libosgearth-dev \
        libpcap-dev nemiver \
        && rm -rf /var/lib/apt/lists/*

# setup locale
RUN locale-gen en_US.UTF-8
ENV LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8

ENV USERNAME userpp
ENV UID 1000
ENV GID 1000
ENV HOME /home/${USERNAME}

# inspired by http://fabiorehm.com/blog/2014/09/11/running-gui-apps-with-docker/
RUN groupadd --gid $GID $USERNAME
RUN useradd -m -d $HOME -s /bin/bash --uid $UID --gid $GID -G sudo $USERNAME
RUN echo "${USERNAME} ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
RUN mkdir -p $HOME/workspace && chown -R $USERNAME:$USERNAME $HOME

# =================================================================================================
# End base stage
# =================================================================================================

FROM base as omnetpp

USER $USERNAME
ADD dockerfiles/bashrc $HOME/.bashrc
RUN sudo chown $USERNAME:$USERNAME $HOME/.bashrc
RUN echo '. ~/.bashrc' >> ~/.bash_profile

RUN pip3 install numpy scipy pandas matplotlib posix_ipc

ARG OMNETPP_VERSION="6.0pre10"
ENV OMNETPP_ROOT $HOME/omnetpp-${OMNETPP_VERSION}
ENV OMNETPY_ROOT $HOME/omnetpy
ENV PYTHONPATH ${OMNETPY_ROOT}/bindings:$OMNETPP_ROOT/python

# get source code
RUN wget -P $HOME --progress=dot:giga \
    https://github.com/omnetpp/omnetpp/archive/refs/tags/omnetpp-${OMNETPP_VERSION}.tar.gz \
    && tar xzf $HOME/omnetpp-${OMNETPP_VERSION}.tar.gz --directory $HOME \
    && rm $HOME/omnetpp-${OMNETPP_VERSION}.tar.gz
RUN wget -P $HOME --progress=dot:giga \
    https://github.com/omnetpp/omnetpp/releases/download/omnetpp-6.0pre11/omnetpp-6.0pre11-src-linux.tgz \
    && tar xzf $HOME/omnetpp-6.0pre11-src-linux.tgz --directory $HOME \
    && rm $HOME/omnetpp-6.0pre11-src-linux.tgz

RUN mv $HOME/omnetpp-omnetpp-${OMNETPP_VERSION}/ $HOME/omnetpp-${OMNETPP_VERSION}/
RUN cp -r $HOME/omnetpp-6.0pre11/ide $HOME/omnetpp-${OMNETPP_VERSION}/
RUN cp $HOME/omnetpp-6.0pre11/configure.user $HOME/omnetpp-${OMNETPP_VERSION}/
RUN rm -rf $HOME/omnetpp-6.0pre11

# configure and compile
ENV PYTHONPATH ${PYTHONPATH}:$OMNETPP_ROOT/python
RUN export PATH=$OMNETPP_ROOT/bin:$PATH; cd $OMNETPP_ROOT \
    && ./configure && make MODE=release -j4

# =================================================================================================
# End omnetpp stage
# =================================================================================================

FROM omnetpp as omnetpy

USER root
RUN apt-get update && apt-get dist-upgrade -y \
        python3-pip python3-dev \
        && rm -rf /var/lib/apt/lists/*

RUN pip3 install pybind11==2.4.3

# copy pyopp
ADD --chown=1000:1000 omnetpy ${OMNETPY_ROOT}
ADD --chown=1000:1000 pysamples ${HOME}/pysamples

VOLUME "${HOME}/workspace"
VOLUME "${HOME}/omnetpy"
WORKDIR $HOME/workspace

# compile bindings
USER $USERNAME
RUN cd ${OMNETPY_ROOT} && make

# =================================================================================================
# End omnetpy stage
# =================================================================================================
