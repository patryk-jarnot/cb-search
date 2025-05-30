# NSC-Search: Method for similarity analyses of motifs with non-standard amino acid compositions.

This method is designed for searching for similar motifs with non-standard compositions which include homopolymers, short tandem repeats, low complexity regions and compositionally biased regions.

## Compilation

NSC-Search has the following build dependencies:
* autotools 20220109.1 or later
* GCC 13.3.0 or later
* python library 13.12.3 or later (to build python module)

To download NSC-Search source code use:

```[bash]
git clone [url]
```

To build sources use:

```[bash]
cd nsc_search
mkdir build
cd build
INSTALLROOT=$PWD/../install-root
../configure --prefix=$INSTALLROOT
make
make install
export PATH="$INSTALLROOT/bin:$PATH"
```

To build python module use:

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


