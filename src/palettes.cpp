#include <Rcpp.h>
#include "colourvalues/palettes.hpp"
#include "colourvalues/palette_utils/palette_utils.hpp"
using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::NumericMatrix rcpp_get_palette( std::string palette ) {

  Rcpp::NumericVector red;
  Rcpp::NumericVector green;
  Rcpp::NumericVector blue;
  colourvalues::palette_utils::resolve_palette( palette, red, green, blue );

  R_xlen_t n = red.length();

  Rcpp::NumericMatrix nm( n, 3 );
  nm( Rcpp::_, 0 ) = red * 255;
  nm( Rcpp::_, 1 ) = green * 255;
  nm( Rcpp::_, 2 ) = blue * 255;

  return nm;
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_viridis() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::viridis_red,
    _["green"] = colourvalues::palette::viridis_green,
    _["blue"] = colourvalues::palette::viridis_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_inferno() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::inferno_red,
    _["green"] = colourvalues::palette::inferno_green,
    _["blue"] = colourvalues::palette::inferno_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_magma() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::magma_red,
    _["green"] = colourvalues::palette::magma_green,
    _["blue"] = colourvalues::palette::magma_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_plasma() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::plasma_red,
    _["green"] = colourvalues::palette::plasma_green,
    _["blue"] = colourvalues::palette::plasma_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_cividis() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::cividis_red,
    _["green"] = colourvalues::palette::cividis_green,
    _["blue"] = colourvalues::palette::cividis_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_terrain() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::terrain_red,
    _["green"] = colourvalues::palette::terrain_green,
    _["blue"] = colourvalues::palette::terrain_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_topo() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::topo_red,
    _["green"] = colourvalues::palette::topo_green,
    _["blue"] = colourvalues::palette::topo_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_heat() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::heat_red,
    _["green"] = colourvalues::palette::heat_green,
    _["blue"] = colourvalues::palette::heat_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_ylorrd() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::ylorrd_red,
    _["green"] = colourvalues::palette::ylorrd_green,
    _["blue"] = colourvalues::palette::ylorrd_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_ylorbr() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::ylorbr_red,
    _["green"] = colourvalues::palette::ylorbr_green,
    _["blue"] = colourvalues::palette::ylorbr_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_ylgnbu() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::ylgnbu_red,
    _["green"] = colourvalues::palette::ylgnbu_green,
    _["blue"] = colourvalues::palette::ylgnbu_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_ylgn() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::ylgn_red,
    _["green"] = colourvalues::palette::ylgn_green,
    _["blue"] = colourvalues::palette::ylgn_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_reds() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::reds_red,
     _["green"] = colourvalues::palette::reds_green,
     _["blue"] = colourvalues::palette::reds_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_rdpu() {
    return Rcpp::DataFrame::create(
   _["red"] = colourvalues::palette::rdpu_red,
   _["green"] = colourvalues::palette::rdpu_green,
   _["blue"] = colourvalues::palette::rdpu_blue
);
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_purples() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::purples_red,
     _["green"] = colourvalues::palette::purples_green,
     _["blue"] = colourvalues::palette::purples_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_purd() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::purd_red,
     _["green"] = colourvalues::palette::purd_green,
     _["blue"] = colourvalues::palette::purd_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_pubugn() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::pubugn_red,
     _["green"] = colourvalues::palette::pubugn_green,
     _["blue"] = colourvalues::palette::pubugn_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_pubu() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::pubu_red,
     _["green"] = colourvalues::palette::pubu_green,
     _["blue"] = colourvalues::palette::pubu_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_orrd() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::orrd_red,
     _["green"] = colourvalues::palette::orrd_green,
     _["blue"] = colourvalues::palette::orrd_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_oranges() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::oranges_red,
     _["green"] = colourvalues::palette::oranges_green,
     _["blue"] = colourvalues::palette::oranges_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_greys() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::greys_red,
     _["green"] = colourvalues::palette::greys_green,
     _["blue"] = colourvalues::palette::greys_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_greens() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::greens_red,
     _["green"] = colourvalues::palette::greens_green,
     _["blue"] = colourvalues::palette::greens_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_gnbu() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::gnbu_red,
     _["green"] = colourvalues::palette::gnbu_green,
     _["blue"] = colourvalues::palette::gnbu_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_bupu() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::bupu_red,
     _["green"] = colourvalues::palette::bupu_green,
     _["blue"] = colourvalues::palette::bupu_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_bugn() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::bugn_red,
     _["green"] = colourvalues::palette::bugn_green,
     _["blue"] = colourvalues::palette::bugn_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_blues() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::blues_red,
     _["green"] = colourvalues::palette::blues_green,
     _["blue"] = colourvalues::palette::blues_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_spectral() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::spectral_red,
     _["green"] = colourvalues::palette::spectral_green,
     _["blue"] = colourvalues::palette::spectral_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_rdylgn() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::rdylgn_red,
     _["green"] = colourvalues::palette::rdylgn_green,
     _["blue"] = colourvalues::palette::rdylgn_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_rdylbu() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::rdylbu_red,
     _["green"] = colourvalues::palette::rdylbu_green,
     _["blue"] = colourvalues::palette::rdylbu_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_rdgy() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::rdgy_red,
     _["green"] = colourvalues::palette::rdgy_green,
     _["blue"] = colourvalues::palette::rdgy_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_rdbu() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::rdbu_red,
     _["green"] = colourvalues::palette::rdbu_green,
     _["blue"] = colourvalues::palette::rdbu_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_puor() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::puor_red,
     _["green"] = colourvalues::palette::puor_green,
     _["blue"] = colourvalues::palette::puor_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_prgn() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::prgn_red,
     _["green"] = colourvalues::palette::prgn_green,
     _["blue"] = colourvalues::palette::prgn_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_piyg() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::piyg_red,
     _["green"] = colourvalues::palette::piyg_green,
     _["blue"] = colourvalues::palette::piyg_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_brbg() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::brbg_red,
     _["green"] = colourvalues::palette::brbg_green,
     _["blue"] = colourvalues::palette::brbg_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_cm() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::cm_red,
     _["green"] = colourvalues::palette::cm_green,
     _["blue"] = colourvalues::palette::cm_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_rainbow() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::rainbow_red,
     _["green"] = colourvalues::palette::rainbow_green,
     _["blue"] = colourvalues::palette::rainbow_blue
  );
}
// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_ygobb() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::ygobb_red,
     _["green"] = colourvalues::palette::ygobb_green,
     _["blue"] = colourvalues::palette::ygobb_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_matlab_like2() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::matlab_like2_red,
     _["green"] = colourvalues::palette::matlab_like2_green,
     _["blue"] = colourvalues::palette::matlab_like2_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_matlab_like() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::matlab_like_red,
     _["green"] = colourvalues::palette::matlab_like_green,
     _["blue"] = colourvalues::palette::matlab_like_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_magenta2green() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::magenta2green_red,
     _["green"] = colourvalues::palette::magenta2green_green,
     _["blue"] = colourvalues::palette::magenta2green_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_cyan2yellow() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::cyan2yellow_red,
     _["green"] = colourvalues::palette::cyan2yellow_green,
     _["blue"] = colourvalues::palette::cyan2yellow_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_blue2yellow() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::blue2yellow_red,
     _["green"] = colourvalues::palette::blue2yellow_green,
     _["blue"] = colourvalues::palette::blue2yellow_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_green2red() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::green2red_red,
     _["green"] = colourvalues::palette::green2red_green,
     _["blue"] = colourvalues::palette::green2red_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_blue2green() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::blue2green_red,
     _["green"] = colourvalues::palette::blue2green_green,
     _["blue"] = colourvalues::palette::blue2green_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_blue2red() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::blue2red_red,
     _["green"] = colourvalues::palette::blue2red_green,
     _["blue"] = colourvalues::palette::blue2red_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_diverge_hcl() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::diverge_hcl_red,
     _["green"] = colourvalues::palette::diverge_hcl_green,
     _["blue"] = colourvalues::palette::diverge_hcl_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_diverge_hsv() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::diverge_hsv_red,
     _["green"] = colourvalues::palette::diverge_hsv_green,
     _["blue"] = colourvalues::palette::diverge_hsv_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_terrain_hcl() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::terrain_hcl_red,
     _["green"] = colourvalues::palette::terrain_hcl_green,
     _["blue"] = colourvalues::palette::terrain_hcl_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_heat_hcl() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::heat_hcl_red,
     _["green"] = colourvalues::palette::heat_hcl_green,
     _["blue"] = colourvalues::palette::heat_hcl_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_sequential_hcl() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::sequential_hcl_red,
     _["green"] = colourvalues::palette::sequential_hcl_green,
     _["blue"] = colourvalues::palette::sequential_hcl_blue
  );
}

// [[Rcpp::export]]
  Rcpp::DataFrame rcpp_rainbow_hcl() {
    return Rcpp::DataFrame::create(
     _["red"] = colourvalues::palette::rainbow_hcl_red,
     _["green"] = colourvalues::palette::rainbow_hcl_green,
     _["blue"] = colourvalues::palette::rainbow_hcl_blue
  );
}
