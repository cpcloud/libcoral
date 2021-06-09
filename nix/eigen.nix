self: super: {
  eigen = super.eigen.overrideAttrs (old: {
    patches = [ ./include-dir.patch ];
    src = self.fetchFromGitLab {
      owner = "libeigen";
      repo = "eigen";
      rev = "3d9051ea84a5089b277c88dac456b3b1576bfa7f";
      sha256 = "1y3f2jvimb5i904f4n37h23cv2pkdlbz8656s0kga1y7c0p50wif";
    };
  });
}
