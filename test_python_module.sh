#!/bin/bash

set -e

autoreconf -fi
autoreconf -i

rm -rf build

mkdir build
cd build

INSTALLROOT=$PWD/../install-root

rm -rf $INSTALLROOT

../configure --prefix=$INSTALLROOT
make
make install

export PYTHONPATH=$(dirname $(find $INSTALLROOT -name cbsearch.py -print))
python3 -c 'import cbsearch; cbsearch.example_hello()'
