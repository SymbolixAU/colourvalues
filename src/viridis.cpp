#include <Rcpp.h>
#include "RcppViridisMagma.hpp"
#include "RcppViridisInferno.hpp"
#include "RcppViridisPlasma.hpp"
#include "RcppViridisViridis.hpp"

using namespace Rcpp;
using namespace viridis;

//[[Rcpp::depends(BH)]]

#include <boost/math/interpolators/cubic_b_spline.hpp>


unsigned long rgbaToHex(int r, int g, int b, int a) {
  return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (a & 0xff);
}

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
  int rgbNum = ((r & 0xff) << 16)
  | ((g & 0xff) << 8)
  | (b & 0xff);

  return '#' + ConvertRGBtoHex(rgbNum);
}



/*
 * colour variable
 *
 * Colours variables
 */
// [[Rcpp::export]]
Rcpp::StringVector colour_variable_rgb( Rcpp::NumericVector x, std::string palette) {
  int n = x.size();
  Rcpp::NumericMatrix mat_colours(n, 3);

  Rcpp::StringVector hex_strings(n);

  double max_x = max(x);
  double scale_x = 255 / max_x;
  int i = 0;

  // TODO(allow user to select start and end points of the vectors)
  Rcpp::NumericVector red(256);
  Rcpp::NumericVector green(256);
  Rcpp::NumericVector blue(256);

  if( palette == "viridis" ) {
    red = viridis::viridis_red;
    green = viridis::viridis_green;
    blue = viridis::viridis_blue;
  } else if ( palette == "inferno" ) {
    red = inferno::inferno_red;
    green = inferno::inferno_green;
    blue = inferno::inferno_blue;
  } else if ( palette == "plasma" ) {
    red = plasma::plasma_red;
    green = plasma::plasma_green;
    blue = plasma::plasma_blue;
  } else if ( palette == "magma" ) {
    red = magma::magma_red;
    green = magma::magma_green;
    blue = magma::magma_blue;
  } else {
    Rcpp::stop("unknown palette");
  }

  boost::math::cubic_b_spline< double > spline_red( red.begin(), red.end(), 0, 1 );
  boost::math::cubic_b_spline< double > spline_green( green.begin(), green.end(), 0, 1 );
  boost::math::cubic_b_spline< double > spline_blue( blue.begin(), blue.end(), 0, 1 );

  double this_x;
  int r, g, b;
  std::string hex_str;

  for( i = 0; i < n; i ++ ) {
    this_x = x[i] * scale_x;
    // mat_colours(i, 0) = round( spline_red( this_x ) * 255) ;
    // mat_colours(i, 1) = round( spline_green( this_x ) * 255);
    // mat_colours(i, 2) = round( spline_blue( this_x ) * 255);

    r = round( spline_red( this_x ) * 255) ;
    g = round( spline_green( this_x ) * 255);
    b = round( spline_blue( this_x ) * 255);

    hex_strings[i] = ConvertRGBtoHex(r, g, b);
  }

  return hex_strings;
}

