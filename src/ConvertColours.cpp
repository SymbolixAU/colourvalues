#include <Rcpp.h>

#include "colourvalues/convert/convert_colours.hpp"


// [[Rcpp::export]]
Rcpp::IntegerMatrix rcpp_convert_hex_to_rgb( Rcpp::StringVector hex_strings ) {
  return colourvalues::convert::convert_hex_to_rgb( hex_strings );
}
