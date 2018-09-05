#ifndef RCPP_VIRIDIS_H
#define RCPP_VIRIDIS_H

#include <regex>
#include <Rcpp.h>
using namespace Rcpp;

namespace RcppViridis {

  //static const std::string DEFAULT_NA_HEX_COLOUR = "#808080";
  static const std::regex HEX_COLOUR_REGEX("^#(?:[0-9a-fA-F]{3}){1,2}$|^#(?:[0-9a-fA-F]{4}){1,2}$");

}; // namespace viridis

// bool is_hex_colour(std::string hex);

std::string ConvertRGBtoHex(int num);

std::string ConvertRGBtoHex(int r, int g, int b);

Rcpp::StringVector colour_variable_hex( Rcpp::NumericVector x, std::string palette, std::string na_colour );

#endif
