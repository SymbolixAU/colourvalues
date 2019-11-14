
#include "colourvalues/alpha/alpha.hpp"

#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::NumericVector rcpp_validate_alpha( Rcpp::NumericVector alpha, int alpha_type ) {
  return colourvalues::alpha::validate_alpha( alpha, alpha_type );
}

