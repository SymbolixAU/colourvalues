#include <Rcpp.h>

#include "RcppViridis/colours/colours_hex.hpp"
#include "RcppViridis/colours/colours_rgb.hpp"

using namespace Rcpp;

// -----------------------------------------------------------------------------
// return HEX

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_num_value_string_palette_hex(
    Rcpp::NumericVector x,
    std::string palette,
    std::string na_colour,
    Rcpp::NumericVector alpha ) {
  return rcppviridis::colours_hex::colour_value_hex( x, palette, na_colour, alpha );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_num_value_rgb_palette_hex(
    Rcpp::NumericVector x,
    Rcpp::NumericMatrix palette,
    std::string na_colour ) {
  return rcppviridis::colours_hex::colour_value_hex( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_str_value_string_palette_hex(
    Rcpp::StringVector x,
    std::string palette,
    std::string na_colour,
    Rcpp::NumericVector alpha  ) {
    return rcppviridis::colours_hex::colour_value_hex( x, palette, na_colour, alpha );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_str_value_rgb_palette_hex(
    Rcpp::StringVector x,
    Rcpp::NumericMatrix palette,
    std::string na_colour ) {
  return rcppviridis::colours_hex::colour_value_hex( x, palette, na_colour );
}


// -----------------------------------------------------------------------------
// return RGB


// [[Rcpp::export]]
Rcpp::NumericMatrix rcpp_colour_num_value_string_palette_rgb(
    Rcpp::NumericVector x,
    std::string palette,
    std::string na_colour,
    Rcpp::NumericVector alpha ) {
  return rcppviridis::colours_rgb::colour_value_rgb( x, palette, na_colour, alpha );
}

// [[Rcpp::export]]
Rcpp::NumericMatrix rcpp_colour_num_value_rgb_palette_rgb(
    Rcpp::NumericVector x,
    Rcpp::NumericMatrix palette,
    std::string na_colour ) {
  return rcppviridis::colours_rgb::colour_value_rgb( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::NumericMatrix rcpp_colour_str_value_string_palette_rgb(
    Rcpp::StringVector x,
    std::string palette,
    std::string na_colour,
    Rcpp::NumericVector alpha  ) {
  return rcppviridis::colours_rgb::colour_value_rgb( x, palette, na_colour, alpha );
}

// [[Rcpp::export]]
Rcpp::NumericMatrix rcpp_colour_str_value_rgb_palette_rgb(
    Rcpp::StringVector x,
    Rcpp::NumericMatrix palette,
    std::string na_colour ) {
  return rcppviridis::colours_rgb::colour_value_rgb( x, palette, na_colour );
}
