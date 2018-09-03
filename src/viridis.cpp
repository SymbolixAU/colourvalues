#include <Rcpp.h>
#include "RcppViridis.hpp"
using namespace Rcpp;
using namespace magma;


// [[Rcpp::export]]
Rcpp::List colour_test() {
  Rcpp::List lst = Rcpp::List::create(
    _["r"] = magma_red,
    _["g"] = magma_green,
    _["b"] = magma_blue
  );
  //Rcpp::Rcout << m << std::endl;
  return lst;
}


