#include <Rcpp.h>
using namespace Rcpp;

#include "colourvalues/list/list.hpp"

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_list_types( const Rcpp::List& lst ) {
  return colourvalues::list::list_types( lst );
}
