#include <Rcpp.h>

#include "RcppViridis/colours/colours.hpp"

using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_num_value_hex(
    Rcpp::NumericVector x,
    std::string palette,
    std::string na_colour) {
  return rcppviridis::colours::colour_value_hex( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_str_value_hex(
    Rcpp::StringVector x,
    std::string palette,
    std::string na_colour) {
  return rcppviridis::colours::colour_value_hex( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_num_value_string_palette_hex(
    Rcpp::NumericVector x,
    std::string palette,
    std::string na_colour ) {
  return rcppviridis::colours::colour_value_hex( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_num_value_rgb_palette_hex(
    Rcpp::NumericVector x,
    Rcpp::NumericVector red,
    Rcpp::NumericVector green,
    Rcpp::NumericVector blue,
    std::string na_colour ) {
  return rcppviridis::colours::colour_value_hex( x, red, green, blue, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_str_value_string_palette_hex(
    Rcpp::StringVector x,
    std::string palette,
    std::string na_colour ) {
    return rcppviridis::colours::colour_value_hex( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_str_value_rgb_palette_hex(
    Rcpp::StringVector x,
    Rcpp::NumericVector red,
    Rcpp::NumericVector green,
    Rcpp::NumericVector blue,
    std::string na_colour ) {
  return rcppviridis::colours::colour_value_hex( x, red, green, blue, na_colour );
}




