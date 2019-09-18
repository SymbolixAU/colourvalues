#include <Rcpp.h>
#include "colourvalues/palette_utils/palette_utils.hpp"

// [[Rcpp::export]]
int rcpp_validate_rgb_range( int x ) {
  return colourvalues::palette_utils::validate_rgb_range( x );
}

// [[Rcpp::export]]
int rcpp_validate_rgb_spline( int x ) {
  colourvalues::palette_utils::validate_rgb_spline( x );
  return x;
}
