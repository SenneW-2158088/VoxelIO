{
  description = "C/C++ environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils, ... }@inputs:
    utils.lib.eachDefaultSystem (
      system:
let
        p = import nixpkgs { 
				inherit system;
				config = { 
					allowUnfree = true; 
				}; 
			};
        llvm = p.llvmPackages_latest;
      in{
        devShell = p.mkShell.override { stdenv = p.clangStdenv; } rec {
          packages = with p; [
			# builder
			gnumake
			cmake
			cmake-format
			cmake-language-server
			ninja
			pkg-config

			# debugger
			llvm.lldb

			# fix headers not found
			clang-tools

			# LSP and compiler
			llvm.libstdcxxClang

			# other tools
			llvm.libllvm

			# stdlib for cpp
			llvm.libcxx
				
			# libs
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

          ];
          name = "C";
        };
      }
    );
}
