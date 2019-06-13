#ifndef R_COLOURVALUES_PALETTE_UTILS_H
#define R_COLOURVALUES_PALETTE_UTILS_H

#include <Rcpp.h>
#include "colourvalues/scale/scale.hpp"
#include "colourvalues/palettes.hpp"

namespace colourvalues {
namespace palette_utils {

  inline int validate_rgb_range( int x ) {
    if ( x < 0 ) {
      x += 255;
    } else if ( x > 255 ) {
      x -= 255;
    }
    return x;
  }

  inline void validate_rgb_spline( int& x ) {
    if ( x < 0 ) {
      x = 0;
    } else if ( x > 255 ) {
      x = 255;
    }
  }

  /*
   * extract vectors from palette
   */
  inline void resolve_palette(
      Rcpp::NumericMatrix& palette,
      Rcpp::NumericVector& red,
      Rcpp::NumericVector& green,
      Rcpp::NumericVector& blue,
      Rcpp::NumericVector& alpha ) {

    int n_col = palette.ncol();
    if ( n_col < 3 ) {
      Rcpp::stop("colourvalues - Matrix palette needs either 3 (R, G, B) or 4 (R, G, B, A) columns");
    }

    if ( n_col > 4 ) {
      Rcpp::warning("colourvalues - Only using the first 4 columns of the palette (R, G, B, A) values");
    }

    double scale = 1.0 / 255.0;

    red = palette(_, 0);
    green = palette(_, 1);
    blue = palette(_, 2);
    red = red * scale;
    green = green * scale;
    blue = blue * scale;

    if (n_col == 4) {
      alpha = palette(_, 3);
      alpha = alpha * scale;
    }
    //resolve_palette( red, green, blue, alpha );
  }

  /*
   * return in-built vectors
   */
  inline void resolve_palette(
      std::string& palette,
      Rcpp::NumericVector& red,
      Rcpp::NumericVector& green,
      Rcpp::NumericVector& blue ) {

    if( palette == "viridis" ) {
      red = colourvalues::palette::viridis_red;
      green = colourvalues::palette::viridis_green;
      blue = colourvalues::palette::viridis_blue;
    } else if ( palette == "inferno" ) {
      red = colourvalues::palette::inferno_red;
      green = colourvalues::palette::inferno_green;
      blue = colourvalues::palette::inferno_blue;
    } else if ( palette == "plasma" ) {
      red = colourvalues::palette::plasma_red;
      green = colourvalues::palette::plasma_green;
      blue = colourvalues::palette::plasma_blue;
    } else if ( palette == "magma" ) {
      red = colourvalues::palette::magma_red;
      green = colourvalues::palette::magma_green;
      blue = colourvalues::palette::magma_blue;
    } else if ( palette == "cividis" ) {
      red = colourvalues::palette::cividis_red;
      green = colourvalues::palette::cividis_green;
      blue = colourvalues::palette::cividis_blue;
    } else if ( palette == "terrain" ) {
      red = colourvalues::palette::terrain_red;
      green = colourvalues::palette::terrain_green;
      blue = colourvalues::palette::terrain_blue;
    } else if ( palette == "topo" ) {
      red = colourvalues::palette::topo_red;
      green = colourvalues::palette::topo_green;
      blue = colourvalues::palette::topo_blue;
    } else if ( palette == "heat" ) {
      red = colourvalues::palette::heat_red;
      green = colourvalues::palette::heat_green;
      blue = colourvalues::palette::heat_blue;
    } else if ( palette == "ylorrd" ) {
      red = colourvalues::palette::ylorrd_red;
      green = colourvalues::palette::ylorrd_green;
      blue = colourvalues::palette::ylorrd_blue;
    } else if ( palette == "ylorbr" ) {
      red = colourvalues::palette::ylorbr_red;
      green = colourvalues::palette::ylorbr_green;
      blue = colourvalues::palette::ylorbr_blue;
    } else if ( palette == "ylgnbu" ) {
      red = colourvalues::palette::ylgnbu_red;
      green = colourvalues::palette::ylgnbu_green;
      blue = colourvalues::palette::ylgnbu_blue;
    } else if ( palette == "ylgn" ) {
      red = colourvalues::palette::ylgn_red;
      green = colourvalues::palette::ylgn_green;
      blue = colourvalues::palette::ylgn_blue;
    } else if ( palette == "reds" ) {
      red = colourvalues::palette::reds_red;
      green = colourvalues::palette::reds_green;
      blue = colourvalues::palette::reds_blue;
    } else if ( palette == "rdpu" ) {
      red = colourvalues::palette::rdpu_red;
      green = colourvalues::palette::rdpu_green;
      blue = colourvalues::palette::rdpu_blue;
    } else if ( palette == "purples" ) {
      red = colourvalues::palette::purples_red;
      green = colourvalues::palette::purples_green;
      blue = colourvalues::palette::purples_blue;
    } else if ( palette == "purd" ) {
      red = colourvalues::palette::purd_red;
      green = colourvalues::palette::purd_green;
      blue = colourvalues::palette::purd_blue;
    } else if ( palette == "pubugn" ) {
      red = colourvalues::palette::pubugn_red;
      green = colourvalues::palette::pubugn_green;
      blue = colourvalues::palette::pubugn_blue;
    } else if ( palette == "pubu" ) {
      red = colourvalues::palette::pubu_red;
      green = colourvalues::palette::pubu_green;
      blue = colourvalues::palette::pubu_blue;
    } else if ( palette == "orrd" ) {
      red = colourvalues::palette::orrd_red;
      green = colourvalues::palette::orrd_green;
      blue = colourvalues::palette::orrd_blue;
    } else if ( palette == "oranges" ) {
      red = colourvalues::palette::oranges_red;
      green = colourvalues::palette::oranges_green;
      blue = colourvalues::palette::oranges_blue;
    } else if ( palette == "greys" ) {
      red = colourvalues::palette::greys_red;
      green = colourvalues::palette::greys_green;
      blue = colourvalues::palette::greys_blue;
    } else if ( palette == "greens" ) {
      red = colourvalues::palette::greens_red;
      green = colourvalues::palette::greens_green;
      blue = colourvalues::palette::greens_blue;
    } else if ( palette == "gnbu" ) {
      red = colourvalues::palette::gnbu_red;
      green = colourvalues::palette::gnbu_green;
      blue = colourvalues::palette::gnbu_blue;
    } else if ( palette == "bupu" ) {
      red = colourvalues::palette::bupu_red;
      green = colourvalues::palette::bupu_green;
      blue = colourvalues::palette::bupu_blue;
    } else if ( palette == "bugn" ) {
      red = colourvalues::palette::bugn_red;
      green = colourvalues::palette::bugn_green;
      blue = colourvalues::palette::bugn_blue;
    } else if ( palette == "blues" ) {
      red = colourvalues::palette::blues_red;
      green = colourvalues::palette::blues_green;
      blue = colourvalues::palette::blues_blue;
    } else if ( palette == "spectral" ) {
      red = colourvalues::palette::spectral_red;
      green = colourvalues::palette::spectral_green;
      blue = colourvalues::palette::spectral_blue;
    } else if ( palette == "spectral" ) {
      red = colourvalues::palette::spectral_red;
      green = colourvalues::palette::spectral_green;
      blue = colourvalues::palette::spectral_blue;
    } else if ( palette == "rdylgn" ) {
      red = colourvalues::palette::rdylgn_red;
      green = colourvalues::palette::rdylgn_green;
      blue = colourvalues::palette::rdylgn_blue;
    } else if ( palette == "rdylbu" ) {
      red = colourvalues::palette::rdylbu_red;
      green = colourvalues::palette::rdylbu_green;
      blue = colourvalues::palette::rdylbu_blue;
    } else if ( palette == "rdgy" ) {
      red = colourvalues::palette::rdgy_red;
      green = colourvalues::palette::rdgy_green;
      blue = colourvalues::palette::rdgy_blue;
    } else if ( palette == "rdbu" ) {
      red = colourvalues::palette::rdbu_red;
      green = colourvalues::palette::rdbu_green;
      blue = colourvalues::palette::rdbu_blue;
    } else if ( palette == "puor" ) {
      red = colourvalues::palette::puor_red;
      green = colourvalues::palette::puor_green;
      blue = colourvalues::palette::puor_blue;
    } else if ( palette == "prgn" ) {
      red = colourvalues::palette::prgn_red;
      green = colourvalues::palette::prgn_green;
      blue = colourvalues::palette::prgn_blue;
    } else if ( palette == "piyg" ) {
      red = colourvalues::palette::piyg_red;
      green = colourvalues::palette::piyg_green;
      blue = colourvalues::palette::piyg_blue;
    } else if ( palette == "brbg" ) {
      red = colourvalues::palette::brbg_red;
      green = colourvalues::palette::brbg_green;
      blue = colourvalues::palette::brbg_blue;
    } else if ( palette == "cm" ) {
      red = colourvalues::palette::cm_red;
      green = colourvalues::palette::cm_green;
      blue = colourvalues::palette::cm_blue;
    } else if ( palette == "rainbow" ) {
      red = colourvalues::palette::rainbow_red;
      green = colourvalues::palette::rainbow_green;
      blue = colourvalues::palette::rainbow_blue;
    } else if ( palette == "ygobb" ) {
      red = colourvalues::palette::ygobb_red;
      green = colourvalues::palette::ygobb_green;
      blue = colourvalues::palette::ygobb_blue;
    } else if ( palette == "matlab_like2" ) {
      red = colourvalues::palette::matlab_like2_red;
      green = colourvalues::palette::matlab_like2_green;
      blue = colourvalues::palette::matlab_like2_blue;
    } else if ( palette == "matlab_like" ) {
      red = colourvalues::palette::matlab_like_red;
      green = colourvalues::palette::matlab_like_green;
      blue = colourvalues::palette::matlab_like_blue;
    } else if ( palette == "magenta2green" ) {
      red = colourvalues::palette::magenta2green_red;
      green = colourvalues::palette::magenta2green_green;
      blue = colourvalues::palette::magenta2green_blue;
    } else if ( palette == "cyan2yellow" ) {
      red = colourvalues::palette::cyan2yellow_red;
      green = colourvalues::palette::cyan2yellow_green;
      blue = colourvalues::palette::cyan2yellow_blue;
    } else if ( palette == "blue2yellow" ) {
      red = colourvalues::palette::blue2yellow_red;
      green = colourvalues::palette::blue2yellow_green;
      blue = colourvalues::palette::blue2yellow_blue;
    } else if ( palette == "green2red" ) {
      red = colourvalues::palette::green2red_red;
      green = colourvalues::palette::green2red_green;
      blue = colourvalues::palette::green2red_blue;
    } else if ( palette == "blue2green" ) {
      red = colourvalues::palette::blue2green_red;
      green = colourvalues::palette::blue2green_green;
      blue = colourvalues::palette::blue2green_blue;
    } else if ( palette == "blue2red" ) {
      red = colourvalues::palette::blue2red_red;
      green = colourvalues::palette::blue2red_green;
      blue = colourvalues::palette::blue2red_blue;
    } else if ( palette == "diverge_hcl" ) {
      red = colourvalues::palette::diverge_hcl_red;
      green = colourvalues::palette::diverge_hcl_green;
      blue = colourvalues::palette::diverge_hcl_blue;
    } else if ( palette == "diverge_hsv" ) {
      red = colourvalues::palette::diverge_hsv_red;
      green = colourvalues::palette::diverge_hsv_green;
      blue = colourvalues::palette::diverge_hsv_blue;
    } else if ( palette == "terrain_hcl" ) {
      red = colourvalues::palette::terrain_hcl_red;
      green = colourvalues::palette::terrain_hcl_green;
      blue = colourvalues::palette::terrain_hcl_blue;
    } else if ( palette == "heat_hcl" ) {
      red = colourvalues::palette::heat_hcl_red;
      green = colourvalues::palette::heat_hcl_green;
      blue = colourvalues::palette::heat_hcl_blue;
    } else if ( palette == "sequential_hcl" ) {
      red = colourvalues::palette::sequential_hcl_red;
      green = colourvalues::palette::sequential_hcl_green;
      blue = colourvalues::palette::sequential_hcl_blue;
    } else if ( palette == "rainbow_hcl" ) {
      red = colourvalues::palette::rainbow_hcl_red;
      green = colourvalues::palette::rainbow_hcl_green;
      blue = colourvalues::palette::rainbow_hcl_blue;
    } else {
      Rcpp::stop("colourvalues - unknown palette");
    }
  }

} // namespace palette_utils
} // namespace colourvalues


#endif
