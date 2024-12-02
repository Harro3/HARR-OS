{
  description = "HARR-OS cross compiler env";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in {
    devShells.${system}.default = pkgs.mkShell {
      name = "harr-os";

      nativeBuildInputs = with pkgs; [
        nasm
        pkgsCross.i686-embedded.buildPackages.gcc
        pkgsCross.i686-embedded.buildPackages.gdb
        qemu
      ];
    };
  };
}
