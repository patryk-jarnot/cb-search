# CB-Search: Method for similarity analyses of motifs with biased compositions.

This method is designed for searching for similar motifs with non-standard compositions which include homopolymers, short tandem repeats, low complexity regions and compositionally biased regions.

## Dependencies

CB-Search has the following build dependencies:
* g++ 12.2.0 or later
* make 4.4.1 or later
* swig 4.0 or later
* python library and header files python3-dev 3.11.2 or later

Install dependencies on Ubuntu:

```[bash]
apt install g++ make swig python3-dev
```

## Installation

Release version can be downloaded from:
[Release version v1.0.2](https://github.com/patryk-jarnot/cb-search/releases/download/v1.0.2/cbsearch-1.0.2.tar.gz)

Then you can install CB-Search using the following commands:

```[bash]
./configure
make
make install
```

## Development version compilation

To download CB-Search source code use:

```[bash]
git clone https://github.com/patryk-jarnot/cb-search.git
```

To build sources use:

```[bash]
cd cb-search
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
export PYTHONPATH=$(dirname $(find $INSTALLROOT -name cbsearch.py -print))
python3 -c 'import cbsearch; cbsearch.example_hello()'
```

## Usage

To search for similar sequences using global-to-local alignment use:

```[bash]
cbsearch -q [query_file_fasta] -d [database_fasta]
```

To use SimiComp to identify fragments of similar compositions and align them globally to the query use:

```[bash]
cbsearch -a 0 --simi-comp -q [query_file_fasta] -d [database_fasta]
```

For local alignment use:

```[bash]
cbsearch -a 1 -q [query_file_fasta] -d [database_fasta]
```

## Example

To search for RGG/RG boxes using global-to-local algorithm in an example set execute the following:

```[bash]
./cbsearch -t 0.25 --gap-open=6 --gap-extend=2 -q example/Q01560.fasta -d example/database.fasta
```

## Help

To find more options use:

```[bash]
cbsearch --help
```

## Links
* [Patryk Jarnot Web Page](https://pjarnot.com)


