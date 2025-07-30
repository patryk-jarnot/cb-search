{
  description = "nsc-search - A method for searching for similar motifs with non-standard compositions in protein sequences.";
  
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  
  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        packages = {
          default = pkgs.callPackage ./package.nix { };
          clang = pkgs.callPackage ./package.nix { stdenv = pkgs.clangStdenv; };
        } // pkgs.lib.optionalAttrs (system != "x86_64-linux") {
          crossIntel = pkgs.pkgsCross.gnu64.callPackage ./package.nix {
            doCheck = false;
          };
        } // pkgs.lib.optionalAttrs (system != "aarch64-linux") {
          crossAarch64 = pkgs.pkgsCross.aarch64-multiplatform.callPackage ./package.nix {
            doCheck = false;
          };
        };
        
        checks = self.packages.${system} // {
          clang = self.packages.${system}.default.override {
            stdenv = pkgs.clangStdenv;
          };
        };
        
        formatter = pkgs.alejandra;
      });
}