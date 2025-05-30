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


# exact destination depends on python version
# this is a hack; the idea is to get wherever "example.py" and "_example.so" are
# onto PYTHONPATH
export PYTHONPATH=$(dirname $(find $INSTALLROOT -name nscsearch.py -print))
#python -c 'import example; example.example_hello()'
python3 -c 'import nscsearch; nscsearch.example_hello()'
