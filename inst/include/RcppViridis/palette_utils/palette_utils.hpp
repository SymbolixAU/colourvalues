#ifndef RCPP_VIRIDIS_HEADERS_PALETTE_UTILS_H
#define RCPP_VIRIDIS_HEADERS_PALETTE_UTILS_H

#include <Rcpp.h>
#include "RcppViridis/scale/scale.hpp"
#include "RcppViridis/palettes/palettes.hpp"

namespace rcppviridis {
namespace palette_utils {

  void validate_alpha( Rcpp::NumericVector alpha ) {
    if ( alpha.size() != 1 ) {
        Rcpp::stop("alpha must be a single value");
      }
  }

  /*
   * rescale all vectors 0,1]
   */
  void resolve_palette(
      Rcpp::NumericVector& red,
      Rcpp::NumericVector& green,
      Rcpp::NumericVector& blue,
      Rcpp::NumericVector& alpha ) {

    //double scale = 1 / 255;
    // red = red * scale;
    // blue = blue * scale;
    // green = green * scale;
    //alpha = alpha * scale;
    // TODO(ensure in range [0,1])
    rcppviridis::scale::rescale( red );
    rcppviridis::scale::rescale( green );
    rcppviridis::scale::rescale( blue );
    //rcppviridis::scale::rescale( alpha );
    // alpha doesn't get scaled, just converted to [0,1];
    //alpha = alpha / 255;
  }

  /*
   * extract vectors from palette
   */
  void resolve_palette(
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

    red = palette(_, 0);
    green = palette(_, 1);
    blue = palette(_, 2);
    if (n_col == 4) {
      alpha = palette(_, 3);
    }

    //Rcpp::Rcout << "alpha: " << alpha << std::endl;

    resolve_palette( red, green, blue, alpha );
  }

  /*
   * return in-built vectors
   */
  void resolve_palette(
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
