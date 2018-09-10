#ifndef RCPP_VIRIDIS_HEADERS_CONVERT_COLOURS_H
#define RCPP_VIRIDIS_HEADERS_CONVERT_COLOURS_H

#include <iostream>
#include <string>
#include <sstream>

namespace rcppviridis {
namespace convert {

  // https://www.dreamincode.net/forums/topic/58058-converting-rgb-to-hex/
  inline std::string convert_rgb_to_hex( int num ) {
    std::string rgb;
    for (int i=(4*2) - 1; i>=0; i--) {
      rgb += "0123456789ABCDEF"[((num >> i*4) & 0xF)];
    }
    return rgb;
  }

  // notes: https://stackoverflow.com/a/3723917/5977215
  inline std::string convert_rgb_to_hex(int r, int g, int b, int a) {
    int rgbNum = ((r & 0xff) << 24) | ((g & 0xff) << 16) | (b & 0xff) << 8 | (a & 0xff);
    return '#' + convert_rgb_to_hex(rgbNum);
  }

} // namespace convert
} // namespace rcppviridis

#endif
