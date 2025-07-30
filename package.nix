{
  lib,
  stdenv,
  cmake,
  boost,
  python3,
  pkg-config,
  swig,
  doCheck ? true,
}:

stdenv.mkDerivation rec {
  pname = "nscsearch";
  version = "1.0.1";

  # Good source filtering is important for caching of builds
  # Using the same approach as the original
  src = ./.;
  # Alternative with source filtering (uncomment if needed):
  # src = lib.sourceByRegex ./. [
  #   "^src.*"
  #   "^include.*" 
  #   "^example.*"
  #   "CMakeLists.txt"
  #   "^flake.*"
  #   "package.nix"
  # ];

  # Distinguishing between native build inputs (runnable on the host
  # at compile time) and normal build inputs (runnable on target  
  # platform at run time) is important for cross compilation.
  nativeBuildInputs = [
    cmake
    pkg-config
    swig
    python3
  ];

  buildInputs = [
    python3
    boost
  ];

  # CMake configuration with Python support
  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    # Ensure Python paths are correctly detected
    "-DPython3_EXECUTABLE=${python3}/bin/python3"
    "-DPython3_INCLUDE_DIR=${python3}/include/python${python3.pythonVersion}"
    "-DPython3_LIBRARY=${python3}/lib/libpython${python3.pythonVersion}.so"
  ] ++ lib.optional (!doCheck) "-DBUILD_TESTING=OFF";

  # Configure environment for Python module compilation
  preConfigure = ''
    export CPPFLAGS="$(${python3}/bin/python3-config --includes)"
    export LDFLAGS="$(${python3}/bin/python3-config --ldflags)"
  '';

  # Enable tests by default, but allow disabling for cross-compilation
  inherit doCheck;

  checkPhase = lib.optionalString doCheck ''
    runHook preCheck
    make check
    runHook postCheck
  '';

  # Install Python module to the correct location (matching original makeFlags approach)
  postInstall = ''
    # Make sure the Python module is installed to the correct site-packages location
    # This matches the original: pythondir=\''${out}/${python3.sitePackages}
    if [ -d $out/lib/python*/site-packages ]; then
      mkdir -p $out/${python3.sitePackages}
      cp -r $out/lib/python*/site-packages/* $out/${python3.sitePackages}/ || true
      rm -rf $out/lib/python*/site-packages
    fi
    
    # Ensure the Python module was installed correctly
    if [ -f $out/${python3.sitePackages}/nscsearch.py ]; then
      echo "Python module installed successfully at $out/${python3.sitePackages}"
    else
      echo "Warning: Python module not found in expected location"
      find $out -name "nscsearch.py" -o -name "_nscsearch.so" || true
    fi
  '';

  meta = with lib; {
    description = "A method for searching for similar motifs with non-standard compositions in protein sequences";
    homepage = "https://github.com/patryk-jarnot/nsc-search"; 
    license = licenses.gpl3Plus;
    maintainers = [ ];
    platforms = platforms.linux ++ platforms.darwin;
    mainProgram = "nscsearch";
  };
}
