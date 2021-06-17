let
  pkgs = import ./nix;
in
pkgs.mkShell {
  name = "libcoral";
  buildInputs = (with pkgs; [
    niv
    meson
    pkg-config
    fd
    ninja
    cmake
    abseil-cpp
    eigen
    flatbuffers
    tensorflow-lite
    libedgetpu
    gtest
    glog
    gmock
    gbenchmark
  ]) ++ (with pkgs.gst_all_1; [
    gst-libav
    gst-plugins-bad
    gst-plugins-base
    gst-plugins-good
    gst-plugins-ugly
    gstreamer
  ]);
}
