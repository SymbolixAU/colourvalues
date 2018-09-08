#ifndef RCPP_VIRIDIS_HEADERS_COLOUR_HEX_H
#define RCPP_VIRIDIS_HEADERS_COLOUR_HEX_H

#include <iostream>
#include <string>
#include <sstream>

namespace rcppviridis {
namespace convert {

  std::string convert_rgb_to_hex( int num ) {
    std::string rgb;
    for (int i=(3*2) - 1; i>=0; i--) {
      rgb += "0123456789ABCDEF"[((num >> i*4) & 0xF)];
    }
    return rgb;
  }

  std::string convert_rgb_to_hex(int r, int g, int b) {
    int rgbNum = ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
    return '#' + convert_rgb_to_hex(rgbNum);
  }

} // namespace convert
} // namespace rcppviridis

#endif
