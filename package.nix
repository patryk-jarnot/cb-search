{ lib, stdenv, cmake, boost, python3, autoconf, automake, libtool, pkg-config
, swig }:

stdenv.mkDerivation {
  name = "nscsearch";
  version = "1.0.0";

  # good source filtering is important for caching of builds.
  # It's easier when subprojects have their own distinct subfolders.
  src = ./.;
  # src = lib.sourceByRegex ./. [
  #   "^src.*"
  #   "^include.*"
  #   "CMakeLists.txt"
  # ];

  # Distinguishing between native build inputs (runnable on the host
  # at compile time) and normal build inputs (runnable on target
  # platform at run time) is important for cross compilation.

  ## Dependencies that should only exist in the build environment.

  nativeBuildInputs = [ autoconf automake libtool pkg-config swig ];

  buildInputs = [ python3 ];

  preConfigure = ''
    export CPPFLAGS="$(${python3}/bin/python3-config --includes)"
    export LDFLAGS="$(${python3}/bin/python3-config --ldflags)"
    # Create m4 directory for autotools macros
    mkdir -p m4
    mkdir -p build
    autoreconf -fiv
  '';

  # Override Python installation directory to our output
  makeFlags = [ "pythondir=\${out}/${python3.sitePackages}" ];
  # checkInputs = [ catch2 ];

  # doCheck = enableTests;
  # cmakeFlags = lib.optional (!enableTests) "-DTESTING=off";
}
