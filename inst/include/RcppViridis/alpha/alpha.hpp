#ifndef RCPP_VIRIDIS_HEADERS_ALPHA_H
#define RCPP_VIRIDIS_HEADERS_ALPHA_H

#include <Rcpp.h>
#include "RcppViridis/scale/scale.hpp"

#define ALPHA_UNKNOWN  0
#define ALPHA_PALETTE  1  // the alpha is on the palette
#define ALPHA_VECTOR   2  // the alpha is a variable / vector
#define ALPHA_CONSTANT 3  // the alpha is a constant

namespace rcppviridis {
namespace alpha {

  inline int make_alpha_type( int alpha_size, int x_size, int palette_cols ) {

    if (palette_cols == 4 ) {
      // Rcpp::Rcout << "alpha PALETTE" << std::endl;
      return ALPHA_PALETTE;
    } else if (alpha_size <= 1) {  // covers NULL alpha (from R)
      // Rcpp::Rcout << "alpha CONSTANT" << std::endl;
      return ALPHA_CONSTANT;

    } else if ( alpha_size == x_size ) {
      // Rcpp::Rcout << "alpha VECTOR" << std::endl;
      return ALPHA_VECTOR;
    }
    // Rcpp::Rcout << "alpha UNKNOWN" << std::endl;
    return ALPHA_UNKNOWN;
  }

  inline Rcpp::NumericVector validate_alpha( Rcpp::NumericVector& alpha, int& alpha_type, int& x_size ) {

    if ( alpha_type == ALPHA_CONSTANT ) {
      Rcpp::NumericVector alpha_full( 5, alpha[0] ); // initialise with 5 vals (so i can create a spline object);
      return alpha_full;
    } else if ( alpha_type == ALPHA_PALETTE ) {
      return alpha;
    } else if (alpha_type == ALPHA_VECTOR ) {
      rcppviridis::scale::rescale( alpha );
      alpha = alpha * 255;
      // Rcpp::Rcout << "alpha scaled: " << alpha << std::endl;
      return alpha;
    } else if ( alpha_type == ALPHA_UNKNOWN ) {
      Rcpp::stop("Unknown alpha definition");
    }
    return 0;
  }

} // namespace alpha
} // namespace rcppviridis

#endif
