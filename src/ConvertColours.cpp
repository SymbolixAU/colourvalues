#include <Rcpp.h>

#include "colourvalues/convert_colours/convert_colours.hpp"

//[[Rcpp::export]]
Rcpp::NumericMatrix rcpp_convert_hex_to_rgb( Rcpp::StringVector hex_strings ) {
  int n = hex_strings.size();
  Rcpp::NumericMatrix mat(n, 4);
  for( int i = 0; i < n; i++ ) {
    Rcpp::String this_hex = hex_strings[i];
    mat(i, Rcpp::_) = colourvalues::convert::convert_hex_to_rgb( this_hex );
  }
  return mat;
}
