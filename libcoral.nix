{ abseil-cpp
, cmake
, flatbuffers
, meson
, ninja
, pkg-config
, stdenv
, tensorflow-lite
, libedgetpu
, eigen
, fd
, glog
, gtest
, gbenchmark
, gmock
, gst_all_1
}:
stdenv.mkDerivation {
  pname = "libcoral";
  version = "1.0.0";

  nativeBuildInputs = [
    meson
    pkg-config
    cmake
    ninja
    fd
  ];

  buildInputs = [
    abseil-cpp
    flatbuffers
    eigen
    tensorflow-lite
    libedgetpu
    gbenchmark
    gmock
    gtest
    glog
  ] ++ (with gst_all_1; [
    gst-libav
    gst-plugins-bad
    gst-plugins-base
    gst-plugins-good
    gst-plugins-ugly
    gstreamer
  ]);

  mesonFlags = [
    "--buildtype=release"
    "-Dtests=enabled"
    "-Dexamples=disabled"
    "-Dbenchmarks=disabled"
    "-Dcpp_std=c++17"
  ];

  doCheck = true;

  checkPhase = ''
    meson test --suite=cpu
  '';

  src = ./.;
}
