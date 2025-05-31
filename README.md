# NSC-Search: Method for similarity analyses of motifs with non-standard amino acid compositions.

This method is designed for searching for similar motifs with non-standard compositions which include homopolymers, short tandem repeats, low complexity regions and compositionally biased regions.

## Dependencies

NSC-Search has the following build dependencies:
* g++ 12.2.0 or later
* swig 4.0 or later
* python library and header files python3-dev 3.11.2 or later

## Installation

Release version can be downloaded from:
* [Release version v1.0.0](https://github.com/patryk-jarnot/nsc-search/releases/download/v1.0.0/nscsearch-1.0.0.tar.gz)

Then you can install NSC-Search using the following commands:

```[bash]
./configure
make
make install
```

## Development version compilation

To download NSC-Search source code use:

```[bash]
git clone https://github.com/patryk-jarnot/nsc-search.git
```

To build sources use:

```[bash]
cd nsc-search
autoreconf -fi
autoreconf -i
mkdir build
cd build
INSTALLROOT=$PWD/../install-root
../configure --prefix=$INSTALLROOT
make
make install
export PATH="$INSTALLROOT/bin:$PATH"
```

To use python module execute:

```[bash]
export PYTHONPATH=$(dirname $(find $INSTALLROOT -name nscsearch.py -print))
python3 -c 'import nscsearch; nscsearch.example_hello()'
```

## Usage

To search for similar sequences using global-to-local alignment use:

```[bash]
nscsearch -q [query_file_fasta] -d [database_fasta]
```

To use SimiComp to identify fragments of similar compositions and align them globally to the query use:

```[bash]
nscsearch -a 0 --simi-comp -q [query_file_fasta] -d [database_fasta]
```

For local alignment use:

```[bash]
nscsearch -a 1 -q [query_file_fasta] -d [database_fasta]
```

## Help

To find more options use:

```[bash]
nscsearch --help
```

## Links
* [Patryk Jarnot Web Page](https://www.pjarnot.com)


