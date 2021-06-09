let
  sources = import ./sources.nix;
in
import sources.nixpkgs {
  overlays = [
    (import ../libedgetpu/nix/abseil-cpp.nix)
    (import ./eigen.nix)
    (self: super: {
      libedgetpu = import ../libedgetpu;
    })
  ];
}
