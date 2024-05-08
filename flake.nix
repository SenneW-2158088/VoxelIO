{
  description = "C/C++ environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils, ... }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config = {
            allowUnfree = true;
          };
        };
        llvm = pkgs.llvmPackages_latest;
      in {
        devShell = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } rec {
          packages = with pkgs; [
            gnumake
            cmake
            cmake-format
            cmake-language-server
            ninja
            pkg-config
            llvm.lldb
            clang-tools
            llvm.libstdcxxClang
            llvm.libllvm
            llvm.libcxx
            libGL
            libGLU
            libglvnd
            libvdpau-va-gl
            faac
            faad2
            freeglut
            glew
            glfw
            glm
            assimp
            alsaLib
            alsa-lib
          ];
          name = "C";

          shellHook = ''
            export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [ pkgs.alsaLib ]}:$LD_LIBRARY_PATH
          '';
        };
      }
    );
}
