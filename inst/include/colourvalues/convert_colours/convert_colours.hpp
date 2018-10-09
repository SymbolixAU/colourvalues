#ifndef R_COLOURVALUES_CONVERT_COLOURS_H
#define R_COLOURVALUES_CONVERT_COLOURS_H

#include <iostream>
#include <string>
#include <sstream>

namespace colourvalues {
namespace convert {

  // https://www.dreamincode.net/forums/topic/58058-converting-rgb-to-hex/
  inline std::string convert_rgb_to_hex( int num, bool include_alpha ) {
    std::string rgb;
//    int cols = include_alpha ? 4 : 3;
//    cols = ( cols * 2 ) - 1;
    int cols = include_alpha ? 7 : 5;
    for (int i = cols; i >= 0; i--) {
      rgb += "0123456789ABCDEF"[((num >> i*4) & 0xF)];
    }
    return rgb;
  }

  // notes: https://stackoverflow.com/a/3723917/5977215
  inline std::string convert_rgb_to_hex(int r, int g, int b, int a) {
    int rgbNum = ((r & 0xff) << 24) | ((g & 0xff) << 16) | (b & 0xff) << 8 | (a & 0xff);
    return '#' + convert_rgb_to_hex(rgbNum, true);
  }

  inline std::string convert_rgb_to_hex(int r, int g, int b) {
    int rgbNum = ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
    return '#' + convert_rgb_to_hex(rgbNum, false);
  }

  inline int hex_element( std::string& hex, int pos ) {
    return std::stoul( hex.substr(pos, 2), nullptr, 16 );
  }

  inline int hex_element_single( std::string& hex, int pos ) {
    std::string s = hex.substr(pos, 1);
    s = s + s;
    return std::stoul(s, nullptr, 16);
  }

  // TODO(3-character hex ("#0F0") and alpha channel)
  // can this be sped-up?
  inline Rcpp::IntegerVector convert_hex_to_rgb( std::string hex ) {

    //int hasHash = 1;
    //int r, g, b, a;

    //if ( hex[0] == '#') {
    //  hasHash = 1;
    //} else {
    //  hasHash = 0;
    //}
    //int n = hex.length();
    // Rcpp::Rcout << "hex size: " << n << std::endl;
    //
    // if ( n < 3 || n == 7 || n > 8 || ( n > 4 && n < 6 ) ) {
    //   Rcpp::stop("invalid hex string");
    // }

    // 3-chars == rgb
    // 4-chars == rgba

    // in 3 & 4 the rgb values need to be replicated

    // 6-chars == RRGGBB
    // 8-chars == RRGGBBAA

    //if ( n == 9 ) {
    int  r = hex_element( hex, 1 );
    int  g = hex_element( hex, 3 );
    int  b = hex_element( hex, 5 );
    int  a = hex_element( hex, 7 );
    // } else if ( n == 7 ) {
    //   r = hex_element( hex, 0 + hasHash );
    //   g = hex_element( hex, 2 + hasHash );
    //   b = hex_element( hex, 4 + hasHash );
    //   a = 255;
    // } else if ( n == 5 ) {
    //   r = hex_element_single( hex, 0 + hasHash );
    //   g = hex_element_single( hex, 1 + hasHash );
    //   b = hex_element_single( hex, 2 + hasHash );
    //   a = hex_element_single( hex, 3 + hasHash );
    // } else if ( n == 4 ) {
    //   r = hex_element_single( hex, 0 + hasHash );
    //   g = hex_element_single( hex, 1 + hasHash );
    //   b = hex_element_single( hex, 2 + hasHash );
    //   a = 255;
    // } else {
    //   Rcpp::stop("invalid hex string");
    // }

    return Rcpp::IntegerVector::create(r,g,b,a);
  }

} // namespace convert
} // namespace colourvalues

#endif
