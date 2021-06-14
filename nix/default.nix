let
  sources = import ./sources.nix;
in
import sources.nixpkgs {
  overlays = [
    (import ./eigen.nix)
  ];
}
