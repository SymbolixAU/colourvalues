#include <Rcpp.h>
#include "RcppViridis.hpp"
using namespace Rcpp;

// https://www.dreamincode.net/forums/topic/58058-converting-rgb-to-hex/
std::string ConvertRGBtoHex(int num) {
  static std::string hexDigits = "0123456789ABCDEF";
  std::string rgb;
  for (int i=(3*2) - 1; i>=0; i--) {
    rgb += hexDigits[((num >> i*4) & 0xF)];
  }
  return rgb;
}

std::string ConvertRGBtoHex(int r, int g, int b) {
  int rgbNum = ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
  return '#' + ConvertRGBtoHex(rgbNum);
}

// bool is_hex_colour( std::string hex ) {
//   return std::regex_match( hex, RcppViridis::HEX_COLOUR_REGEX );
// }
//
// Rcpp::LogicalVector is_hex_colour( Rcpp::StringVector hex ) {
//   int i;
//   int n = hex.size();
//   Rcpp::LogicalVector out(n);
//   std::string this_hex;
//   for ( i = 0; i < n; i ++) {
//     this_hex = hex[i];
//     out[i] = is_hex_colour( this_hex );
//   }
//   return out;
// }
//
// // [[Rcpp::export]]
// Rcpp::LogicalVector rcpp_is_hex_colour( Rcpp::StringVector hex ) {
//   return is_hex_colour( hex );
// }
