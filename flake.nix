{
  description = "Basic C++ Template Project with libgcc, CMake, Google Benchmark, and Catch2";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc
            cmake
            gbenchmark
            catch2_3
            libgcc
            git
            ninja
          ];

          nativeBuildInputs = with pkgs; [ 
            gdb 
            valgrind 
          ];

          shellHook = ''
            echo "Development environment for C++ template project with Catch2 and Google Benchmark is ready."
          '';
        };

      }
    );
}