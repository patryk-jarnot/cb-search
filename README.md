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

[![How to install the software](https://img.youtube.com/vi/oiigt9AD45g/maxresdefault.jpg)](https://www.youtube.com/watch?v=oiigt9AD45g)

Release version can be downloaded from:
[Release version v1.0.8](https://github.com/patryk-jarnot/cb-search/releases/download/v1.0.8/cbsearch-1.0.8.tar.gz)

Then you can install CB-Search using the following commands:

```[bash]
./configure
make
make install
```

## Development version compilation

Development version of CB-Search has the following additional dependencies:
* autoconf 2.72 or later
* libtool 2.5.4 or later
* autoconf-archive 20220903-3 or later

Install dependencies on Ubuntu:

```[bash]
apt install autoconf libtool autoconf-archive
```

To download CB-Search source code use:

```[bash]
git clone https://github.com/patryk-jarnot/cb-search.git
```

To build sources use:

```[bash]
cd cb-search
autoreconf -fi
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

## Cite

Jarnot, P. CB-Search: a method for searching for similar protein motifs with biased compositions. BMC Bioinformatics 27, 173 (2026). https://doi.org/10.1186/s12859-026-06509-w

## Poster video

[![How CB-Search works](https://img.youtube.com/vi/hsnGZjhpGUY/maxresdefault.jpg)](https://www.youtube.com/watch?v=hsnGZjhpGUY)

## Links
* [Patryk Jarnot Web Page](https://pjarnot.com)


