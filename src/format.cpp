#include <Rcpp.h>
using namespace Rcpp;

#include "colourvalues/format/format.hpp"


// [[Rcpp::export]]
std::string rcpp_get_format_type( SEXP palette_type ) {
  return colourvalues::format::get_format_type( palette_type );
}


