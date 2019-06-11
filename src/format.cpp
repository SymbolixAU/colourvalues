#include <Rcpp.h>
using namespace Rcpp;

#include "colourvalues/format/format.hpp"
#include "colourvalues/utils/utils.hpp"


// [[Rcpp::export]]
std::string rcpp_get_format_type( SEXP palette_type ) {
  return colourvalues::format::get_format_type( palette_type );
}

// [[Rcpp::export]]
Rcpp::CharacterVector rcpp_get_r_class( SEXP obj ) {
  return colourvalues::utils::getRClass( obj );
}
