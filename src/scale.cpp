#include <Rcpp.h>
#include "colourvalues/scale/scale.hpp"

// [[Rcpp::export]]
Rcpp::NumericVector rcpp_scale( Rcpp::NumericVector x ) {
  colourvalues::scale::rescale( x );
  return x;
}
