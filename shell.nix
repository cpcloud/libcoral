let
  pkgs = import ./nix;
in
(pkgs.stdenvAdapters.useGoldLinker pkgs.stdenv).mkDerivation {
  name = "libcoral";
  buildInputs = (with pkgs; [
    abseil-cpp
    cmake
    eigen
    fd
    flatbuffers
    gbenchmark
    glog
    gmock
    gtest
    libedgetpu
    meson
    ninja
    niv
    pkg-config
    tensorflow-lite
  ]) ++ (with pkgs.gst_all_1; [
    gst-libav
    gst-plugins-bad
    gst-plugins-base
    gst-plugins-good
    gst-plugins-ugly
    gstreamer
  ]);
}
