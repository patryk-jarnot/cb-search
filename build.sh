#!/usr/bin/env bash

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Default values
BUILD_TYPE="Release"
BUILD_DIR="build"
INSTALL_DIR="$PWD/install-root"
CLEAN=false
RUN_TESTS=false
PYTHON_TEST=false

# Function to print colored output
print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Help function
show_help() {
    cat << EOF
Usage: $0 [OPTIONS]

Build nsc-search with CMake

OPTIONS:
    -h, --help          Show this help message
    -c, --clean         Clean build directory before building
    -d, --debug         Build in debug mode (default: Release)
    -b, --build-dir     Set build directory (default: build)
    -i, --install-dir   Set install directory (default: ./install-root)
    -t, --test          Run C++ tests after build
    -p, --python-test   Run Python tests after build
    --all-tests         Run both C++ and Python tests

Examples:
    $0                          # Basic build
    $0 --clean --debug          # Clean debug build
    $0 --test --python-test     # Build and run all tests
EOF
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -d|--debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        -b|--build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        -i|--install-dir)
            INSTALL_DIR="$2"
            shift 2
            ;;
        -t|--test)
            RUN_TESTS=true
            shift
            ;;
        -p|--python-test)
            PYTHON_TEST=true
            shift
            ;;
        --all-tests)
            RUN_TESTS=true
            PYTHON_TEST=true
            shift
            ;;
        *)
            print_error "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Check if CMakeLists.txt exists
if [[ ! -f "CMakeLists.txt" ]]; then
    print_error "CMakeLists.txt not found in current directory"
    exit 1
fi

# Check if config header template exists
if [[ ! -f "config-nscsearch.h.in" ]]; then
    print_error "config-nscsearch.h.in not found. This file is required to replace autotools config header."
    exit 1
fi

# Clean build directory if requested
if [[ "$CLEAN" == true ]]; then
    print_status "Cleaning build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
fi

# Create build directory
print_status "Creating build directory: $BUILD_DIR"
mkdir -p "$BUILD_DIR"

# Configure with CMake
print_status "Configuring with CMake (Build type: $BUILD_TYPE)"
cmake -B "$BUILD_DIR" -S . \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR"

# Build
print_status "Building project"
cmake --build "$BUILD_DIR" --parallel "$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)"

# Install
print_status "Installing to: $INSTALL_DIR"
cmake --install "$BUILD_DIR"

# Run tests if requested
if [[ "$RUN_TESTS" == true ]]; then
    print_status "Running C++ tests"
    cd "$BUILD_DIR"
    ctest --output-on-failure
    cd ..
fi

if [[ "$PYTHON_TEST" == true ]]; then
    print_status "Running Python tests"
    export PYTHONPATH="$BUILD_DIR"
    cd "$BUILD_DIR"
    if command -v python3 &> /dev/null; then
        python3 -m unittest discover ../src/tests/python
    else
        print_warning "python3 not found, skipping Python tests"
    fi
    cd ..
fi

# Print success message and usage instructions
print_status "Build completed successfully!"
echo
print_status "Configuration header generated at: $BUILD_DIR/include/config-nscsearch.h"
print_status "To use the installed binary:"
echo "  export PATH=\"$INSTALL_DIR/bin:\$PATH\""
echo "  nscsearch --help"
echo
print_status "To use the Python module:"
echo "  export PYTHONPATH=\"$BUILD_DIR:\$PYTHONPATH\""
echo "  python3 -c 'import nscsearch; nscsearch.example_hello()'"
echo
print_status "Or with installed Python module:"
PYTHON_SITE_PACKAGES=$(python3 -c "import site; print(site.getsitepackages()[0])" 2>/dev/null || echo "$INSTALL_DIR/lib/python*/site-packages")
echo "  export PYTHONPATH=\"$INSTALL_DIR/$PYTHON_SITE_PACKAGES:\$PYTHONPATH\""
echo "  python3 -c 'import nscsearch; nscsearch.example_hello()'"
