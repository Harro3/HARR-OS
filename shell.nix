{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    nasm
    pkgsCross.i686-embedded.buildPackages.gcc
    pkgsCross.i686-embedded.buildPackages.gdb
    qemu
  ];
}
