#!/bin/bash

#------------------------------------------------------------------------------
# Installs gcc / g++ in Linux Mint / Ubuntu
# 	More: http://www.techerina.com/2015/04/installing-upgrading-gcc-in-ubuntu-linuxmint-machine.html
#
# DEPRECIATED - only here as a reminder!
#------------------------------------------------------------------------------

VERSION="5"
#VERSION="4.9"

add-apt-repository ppa:ubuntu-toolchain-r/test
apt-get update

apt-get install gcc-${VERSION} g++-${VERSION}
apt-get remove  gcc-${VERSION}-locales
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-${VERSION} 60 --slave /usr/bin/g++ g++ /usr/bin/g++-${VERSION}

#apt-get install gcc-${VERSION}-base libgcc-${VERSION}-dev gcc-${VERSION}-multilib gcc-${VERSION}-doc gcc-${VERSION}-locales 

update-alternatives --remove-all gcc 

update-alternatives --remove-all g++

update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-${VERSION} 20

update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-${VERSION} 20

update-alternatives --config gcc

update-alternatives --config g++

echo 
echo "Your compiler is set to:"
gcc --version

