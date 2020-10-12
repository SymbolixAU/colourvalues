#ifndef R_COLOURVALUES_CONVERT_COLOURS_H
#define R_COLOURVALUES_CONVERT_COLOURS_H

#include <iostream>
#include <string>
#include <sstream>

#include "colourvalues/utils/utils.hpp"

// grDevices code
// https://github.com/SurajGupta/r-source/blob/master/src/library/grDevices/src/colors.c

namespace colourvalues {
namespace convert {

  // https://www.dreamincode.net/forums/topic/58058-converting-rgb-to-hex/
  inline std::string convert_rgb_to_hex( int num, bool include_alpha ) {
    std::string rgb;
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

  inline static unsigned int hexdigit( int digit ) {
    if('0' <= digit && digit <= '9') return digit - '0';
    if('A' <= digit && digit <= 'F') return 10 + digit - 'A';
    if('a' <= digit && digit <= 'f') return 10 + digit - 'a';
    return digit;
  }

  inline unsigned int hex_to_rgba( const char *hex, unsigned int ele1, unsigned int ele2 ) {
    return 16 * hexdigit( hex[ele1] ) + hexdigit( hex[ele2] );
  }

  inline Rcpp::IntegerMatrix convert_hex_to_rgb( Rcpp::StringVector hex_strings ) {
    int i;
    int n = hex_strings.size();
    Rcpp::IntegerMatrix mat(n, 4);
    bool any_alpha = false;

    for( i = 0; i < n; i++ ) {
      Rcpp::String this_hex = hex_strings[i];
      const char* hex = this_hex.get_cstring();

      colourvalues::utils::validate_hex( hex );

      switch( strlen( hex ) ) {
      case 9: {
        any_alpha = true;
        mat(i, 0) = hex_to_rgba( hex, 1, 2 );
        mat(i, 1) = hex_to_rgba( hex, 3, 4 );
        mat(i, 2) = hex_to_rgba( hex, 5, 6 );
        mat(i, 3) = hex_to_rgba( hex, 7, 8 );
        break;
      }
      case 7: {
        mat(i, 0) = hex_to_rgba( hex, 1, 2 );
        mat(i, 1) = hex_to_rgba( hex, 3, 4 );
        mat(i, 2) = hex_to_rgba( hex, 5, 6 );
        mat(i, 3) = 255;
        break;
      }
      case 5: {
        any_alpha = true;
        mat(i, 0) = hex_to_rgba( hex, 1, 1 );
        mat(i, 1) = hex_to_rgba( hex, 2, 2 );
        mat(i, 2) = hex_to_rgba( hex, 3, 3 );
        mat(i, 3) = hex_to_rgba( hex, 4, 4 );
        break;
      }
      case 4: {
        mat(i, 0) = hex_to_rgba( hex, 1, 1 );
        mat(i, 1) = hex_to_rgba( hex, 2, 2 );
        mat(i, 2) = hex_to_rgba( hex, 3, 3 );
        mat(i, 3) = 255;
        break;
      }
      default: {
        Rcpp::stop("colourvalues - Unsupported hex string");
      }
      }

    }

    if ( !any_alpha ) {
      mat = mat(Rcpp::_, Rcpp::Range(0,2) );
    }
    return mat;
  }


} // namespace convert
} // namespace colourvalues

#endif
