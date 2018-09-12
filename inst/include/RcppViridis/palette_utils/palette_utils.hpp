#ifndef RCPP_VIRIDIS_HEADERS_PALETTE_UTILS_H
#define RCPP_VIRIDIS_HEADERS_PALETTE_UTILS_H

#include <Rcpp.h>
#include "RcppViridis/scale/scale.hpp"
#include "RcppViridis/palettes.hpp"

namespace rcppviridis {
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
      Rcpp::stop("Matrix palette needs either 3 (R, G, B) or 4 (R, G, B, A) columns");
    }

    if ( n_col > 4 ) {
      Rcpp::warning("Only using the first 4 columns of the palette (R, G, B, A) values");
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
      red = rcppviridis::palette::viridis_red;
      green = rcppviridis::palette::viridis_green;
      blue = rcppviridis::palette::viridis_blue;
    } else if ( palette == "inferno" ) {
      red = rcppviridis::palette::inferno_red;
      green = rcppviridis::palette::inferno_green;
      blue = rcppviridis::palette::inferno_blue;
    } else if ( palette == "plasma" ) {
      red = rcppviridis::palette::plasma_red;
      green = rcppviridis::palette::plasma_green;
      blue = rcppviridis::palette::plasma_blue;
    } else if ( palette == "magma" ) {
      red = rcppviridis::palette::magma_red;
      green = rcppviridis::palette::magma_green;
      blue = rcppviridis::palette::magma_blue;
    } else if ( palette == "cividis" ) {
      red = rcppviridis::palette::cividis_red;
      green = rcppviridis::palette::cividis_green;
      blue = rcppviridis::palette::cividis_blue;
    } else {
      Rcpp::stop("unknown palette");
    }
  }

} // namespace palette_utils
} // namespace rcppviridis


#endif
