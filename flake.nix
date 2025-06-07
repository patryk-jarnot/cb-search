{
  description = "nsc-search - A method for searching for similar motifs with non-standard compositions in protein sequences. ";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        # Our C++ library with Python bindings
        nsc-search = pkgs.stdenv.mkDerivation rec {
          pname = "nsc-search";
          version = "1.0.0";

          src = ./.;

          nativeBuildInputs = with pkgs; [
            autoconf
            automake
            libtool
            pkg-config
            swig
            python3
            python3Packages.setuptools
          ];

          buildInputs = with pkgs; [
            python3
            python3Packages.python
          ];

          preConfigure = ''
            export CPPFLAGS="$(${pkgs.python3}/bin/python3-config --includes)"
            export LDFLAGS="$(${pkgs.python3}/bin/python3-config --ldflags)"
            # Create m4 directory for autotools macros
            mkdir -p m4
            mkdir -p build
            autoreconf -fiv
          '';

          # Override Python installation directory to our output
          makeFlags = [ "pythondir=\${out}/${pkgs.python3.sitePackages}" ];
        };

        # Python environment with our library
        pythonEnv = pkgs.python3.withPackages (ps: [ ]);

      in {
        packages = {
          default = nsc-search;
          nsc-search = nsc-search;
        };

        apps = {
          default = {
            type = "app";
            program = "${nsc-search}/bin/nscsearch";
          };
        };

        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            # Build tools
            autoconf
            automake
            libtool
            pkg-config

            # C++ development
            gcc
            gdb

            # SWIG and Python
            swig
            python3
            python3Packages.setuptools

            # Development utilities
            gnumake
            which
          ];

          shellHook = ''
            echo "🔧 C++ SWIG Python Development Environment"
            echo "Available commands:"
            echo "  autoreconf -fiv       # Generate configure script"
            echo "  ./configure --enable-tests --enable-python-bindings"
            echo "  make                  # Build everything"
            echo "  make check           # Run C++ tests"
            echo "  pytest tests/        # Run Python tests"
            echo ""
            echo "For nix users:"
            echo "  nix build            # Build the package"
            echo "  nix run              # Run the CLI tool"
            echo "  nix run .#python-demo # Run Python demo"
            echo "  nix run .#test       # Run all tests"
          '';
        };
      });
}
