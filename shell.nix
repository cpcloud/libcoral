let
  pkgs = import ./nix;
  bintools_lld = pkgs.wrapBintoolsWith {
    bintools = pkgs.llvmPackages_12.bintools;
  };
in
pkgs.llvmPackages_12.stdenv.mkDerivation {
  name = "libcoral";
  buildInputs = (with pkgs; [
    stdenv
    bintools_lld
    abseil-cpp
    clang-tools
    cmake
    eigen
    fd
    flatbuffers
    gbenchmark
    glog
    gmock
    gtest
    libusb
    libedgetpu
    meson
    ninja
    niv
    pkg-config
    tensorflow-lite
    xxd
  ]) ++ (with pkgs.gst_all_1; [
    gst-libav
    gst-plugins-bad
    gst-plugins-base
    gst-plugins-good
    gst-plugins-ugly
    gstreamer
  ]) ++ (with pkgs.llvmPackages_12; [
    clang
    lld
  ]);
  NIX_CFLAGS_LINK = "-fuse-ld=lld";
}
