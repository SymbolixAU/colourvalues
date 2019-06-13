#include <Rcpp.h>

#include "colourvalues/convert/convert_colours.hpp"


// [[Rcpp::export]]
Rcpp::IntegerMatrix rcpp_convert_hex_to_rgb( Rcpp::StringVector hex_strings ) {
  return colourvalues::convert::convert_hex_to_rgb( hex_strings );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_convert_rgb_mat_to_hex( Rcpp::IntegerMatrix rgb ) {
  int n = rgb.nrow();
  int ncol = rgb.ncol();
  int i;
  Rcpp::StringVector hex_strings(n);
  if (ncol == 3 ) {

    for ( i = 0; i < n; i++ ) {
      hex_strings[i] = colourvalues::convert::convert_rgb_to_hex(
        rgb(i,0), rgb(i,1), rgb(i,2)
      );
    }

  } else if ( ncol == 4 ) {

    for ( i = 0; i < n; i++ ) {
      hex_strings[i] = colourvalues::convert::convert_rgb_to_hex(
        rgb(i,0), rgb(i,1), rgb(i,2), rgb(i,3)
      );
    }

  } else {
    Rcpp::stop("colourvalues - unknown RGB matrix");
  }

  return hex_strings;
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_convert_rgb_vec_to_hex( Rcpp::IntegerVector rgb ) {
  int n = rgb.size();
  if (n == 3 ) {
    return colourvalues::convert::convert_rgb_to_hex( rgb[0], rgb[1], rgb[2] );
  } else if (n == 4) {
    return colourvalues::convert::convert_rgb_to_hex( rgb[0], rgb[1], rgb[2], rgb[3] );
  } else {
    Rcpp::stop("colourvalues - unknown RGB vector");
  }
  return ""; // never reached
}
