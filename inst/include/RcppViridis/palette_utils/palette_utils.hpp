#ifndef RCPP_VIRIDIS_HEADERS_PALETTE_UTILS_H
#define RCPP_VIRIDIS_HEADERS_PALETTE_UTILS_H

#include <Rcpp.h>
#include "RcppViridis/scale/scale.hpp"
#include "RcppViridis/palettes/palettes.hpp"

namespace rcppviridis {
namespace palette_utils {

  void validate_alpha( Rcpp::NumericVector& alpha, Rcpp::NumericVector& alpha_full, int x_size ) {

    int alpha_size = alpha.size();

    if ( !( alpha_size == 1 || alpha_size == x_size ) ){
        Rcpp::stop("alpha must either be a single value, or the same length as x");
      }
    if ( alpha_size > 1 ) {
      alpha_full = alpha;
      rcppviridis::scale::rescale( alpha_full );
      alpha = alpha * 255;
    } else {
      alpha_full.fill( alpha[0] );
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

    // RGB palettes are scaled so they can be interpolated
    rcppviridis::scale::rescale( red );
    rcppviridis::scale::rescale( green );
    rcppviridis::scale::rescale( blue );
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
