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
    return ALPHA_UNKNOWN;    // #nocov
  }

  inline Rcpp::NumericVector validate_alpha( Rcpp::NumericVector& a, int& alpha_type ) {

    if( a.size() < 1 ) {
      Rcpp::stop("colourvalues - invalid alpha vector");
    }

    if ( alpha_type == ALPHA_UNKNOWN ) {                // #nocov
      Rcpp::stop("colourvalues - Unknown alpha definition");   // #nocov
    }

    // Issue 47
    Rcpp::NumericVector alpha = Rcpp::clone( a );
    if ( alpha_type == ALPHA_PALETTE ) {
      return alpha;
    }

    if ( alpha_type == ALPHA_CONSTANT ) {
      if ( alpha[0] >= 0 && alpha[0] < 1 ) {
        alpha = alpha * 255;
      }

      Rcpp::NumericVector alpha_full( 5, alpha[0] ); // initialise with 5 vals (so i can create a spline object);
      return alpha_full;

    } else if ( alpha_type == ALPHA_VECTOR ) {

      colourvalues::scale::rescale( alpha );
      alpha = alpha * 255;

      // If length( alpha ) < 5; fill with mean
      int n_alpha = alpha.size();

      if ( n_alpha < 5 ) {
        double mean_alpha = Rcpp::mean( alpha );
        Rcpp::NumericVector alpha_fill( 5, mean_alpha );
        int i = 0;
        for ( i = 0; i < n_alpha; i++ ) {
          alpha_fill[i] = alpha[i];
        }
        return alpha_fill;
      }
      return alpha;
    }

    Rcpp::NumericVector out;
    return out;  // #nocov never reached
  }

} // namespace alpha
} // namespace colourvalues

#endif
