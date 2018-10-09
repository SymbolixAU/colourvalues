#ifndef R_COLOURVALUES_CONVERT_COLOURS_H
#define R_COLOURVALUES_CONVERT_COLOURS_H

#include <iostream>
#include <string>
#include <sstream>

// grDevices code
// https://github.com/SurajGupta/r-source/blob/master/src/library/grDevices/src/colors.c

#define CV_RGBA(r,g,b,a) ((r & 0xff) << 24) | ((g & 0xff) << 16) | (b & 0xff) << 8 | (a & 0xff);
#define CV_RGB(r,g,b)    ((r & 0xff) << 16) | ((g & 0xff) << 8 ) | (b & 0xff);

#define CV_RED(col)      (((col)     )  &255);
#define CV_GREEN(col)    (((col) >> 8)  &255);
#define CV_BLUE(col)     (((col) >> 16) &255);
#define CV_ALPHA(col)    (((col) >> 24) &255);

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
    //int rgbNum = ((r & 0xff) << 24) | ((g & 0xff) << 16) | (b & 0xff) << 8 | (a & 0xff);
    int rgbNum = CV_RGBA(r,g,b,a);
    return '#' + convert_rgb_to_hex(rgbNum, true);
  }

  inline std::string convert_rgb_to_hex(int r, int g, int b) {
    //int rgbNum = ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
    int rgbNum = CV_RGB(r,g,b);
    return '#' + convert_rgb_to_hex(rgbNum, false);
  }

  // inline int hex_element( std::string& hex, int pos ) {
  //   return std::stoul( hex.substr(pos, 2), nullptr, 16 );
  // }

  inline static unsigned int hexdigit( int digit ) {
    if('0' <= digit && digit <= '9') return digit - '0';
    if('A' <= digit && digit <= 'F') return 10 + digit - 'A';
    if('a' <= digit && digit <= 'f') return 10 + digit - 'a';
    return digit;
  }

  inline unsigned int hex_to_rgba( const char *hex, unsigned int ele1, unsigned int ele2 ) {
    return 16 * hexdigit( hex[ele1] ) + hexdigit( hex[ele2] );
  }

  inline Rcpp::IntegerMatrix convert_hex_to_rgb( const char* hex, bool& any_alpha ) {
    Rcpp::IntegerMatrix mat(1, 4);

    if ( strncmp(hex, "#", 1) != 0 ) {
      Rcpp::stop("unknown hex string, expecting # symbol");
    }
    switch( strlen( hex ) ) {
    case 9: {
      any_alpha = true;
      mat(0, 0) = colourvalues::convert::hex_to_rgba( hex, 1, 2 );
      mat(0, 1) = colourvalues::convert::hex_to_rgba( hex, 3, 4 );
      mat(0, 2) = colourvalues::convert::hex_to_rgba( hex, 5, 6 );
      mat(0, 3) = colourvalues::convert::hex_to_rgba( hex, 7, 8 );
      break;
    }
    case 7: {
      mat(0, 0) = colourvalues::convert::hex_to_rgba( hex, 1, 2 );
      mat(0, 1) = colourvalues::convert::hex_to_rgba( hex, 3, 4 );
      mat(0, 2) = colourvalues::convert::hex_to_rgba( hex, 5, 6 );
      mat(0, 3) = 255;
      break;
    }
    case 5: {
      any_alpha = true;
      mat(0, 0) = colourvalues::convert::hex_to_rgba( hex, 1, 1 );
      mat(0, 1) = colourvalues::convert::hex_to_rgba( hex, 2, 2 );
      mat(0, 2) = colourvalues::convert::hex_to_rgba( hex, 3, 3 );
      mat(0, 3) = colourvalues::convert::hex_to_rgba( hex, 4, 4 );
      break;
    }
    case 4: {
      mat(0, 0) = colourvalues::convert::hex_to_rgba( hex, 1, 1 );
      mat(0, 1) = colourvalues::convert::hex_to_rgba( hex, 2, 2 );
      mat(0, 2) = colourvalues::convert::hex_to_rgba( hex, 3, 3 );
      mat(0, 3) = 255;
      break;
    }
    default: {
      Rcpp::stop("Unsupported hex string");
    }
    }
    return mat;
  }

  // // TODO(3-character hex ("#0F0") and alpha channel)
  // // can this be sped-up?
  // inline Rcpp::IntegerVector convert_hex_to_rgb( std::string& hex ) {
  //
  //   // int hasHash = 1;
  //   // //int r, g, b, a;
  //   //
  //   // if ( hex[0] == '#') {
  //   //  hasHash = 1;
  //   // } else {
  //   //  hasHash = 0;
  //   // }
  //   //
  //   // int  r = hex_element( hex, 0 + hasHash );
  //   // int  g = hex_element( hex, 2 + hasHash );
  //   // int  b = hex_element( hex, 4 + hasHash );
  //   // int  a = hex_element( hex, 6 + hasHash );
  //   //
  //   // return Rcpp::IntegerVector::create(r,g,b,a);
  //   return Rcpp::IntegerVector::create(0,0,0,0);
  // }

} // namespace convert
} // namespace colourvalues

#endif
