#ifndef R_COLOURVALUES_ALPHA_H
#define R_COLOURVALUES_ALPHA_H

#include <Rcpp.h>
#include "colourvalues/scale/scale.hpp"

#define ALPHA_UNKNOWN  0
#define ALPHA_PALETTE  1  // the alpha is on the palette
#define ALPHA_VECTOR   2  // the alpha is a variable / vector
#define ALPHA_CONSTANT 3  // the alpha is a constant

namespace colourvalues {
namespace alpha {

  inline int make_alpha_type( int alpha_size, int x_size, int palette_cols ) {

    if (palette_cols == 4 ) {
      return ALPHA_PALETTE;
    } else if (alpha_size <= 1) {  // covers NULL alpha (from R)
      return ALPHA_CONSTANT;

    } else if ( alpha_size == x_size ) {
      return ALPHA_VECTOR;
    }
    return ALPHA_UNKNOWN;
  }

  inline Rcpp::NumericVector validate_alpha( Rcpp::NumericVector& alpha, int& alpha_type, int& x_size ) {

    if ( alpha_type == ALPHA_CONSTANT ) {
      Rcpp::NumericVector alpha_full( 5, alpha[0] ); // initialise with 5 vals (so i can create a spline object);
      return alpha_full;

    } else if ( alpha_type == ALPHA_PALETTE ) {
      return alpha;

    } else if (alpha_type == ALPHA_VECTOR ) {
      colourvalues::scale::rescale( alpha );
      alpha = alpha * 255;
      return alpha;

    } else if ( alpha_type == ALPHA_UNKNOWN ) {
      Rcpp::stop("Unknown alpha definition");
    }
    return 0;  // never reached
  }

} // namespace alpha
} // namespace colourvalues

#endif
