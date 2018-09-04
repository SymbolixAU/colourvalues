#ifndef RCPP_VIRIDIS_H
#define RCPP_VIRIDIS_H


#include <Rcpp.h>
using namespace Rcpp;

namespace RcppViridis {
  static const std::string NA_HEX_COLOUR = "#808080";
}; // namespace viridis

std::string ConvertRGBtoHex(int num);

std::string ConvertRGBtoHex(int r, int g, int b);

Rcpp::StringVector colour_variable_hex( Rcpp::NumericVector x, std::string palette );

#endif
