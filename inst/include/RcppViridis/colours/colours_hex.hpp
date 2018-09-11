#ifndef RCPP_VIRIDIS_HEADERS_COLOURS_HEX_H
#define RCPP_VIRIDIS_HEADERS_COLOURS_HEX_H

#include <Rcpp.h>
#include "RcppViridis/colours.hpp"
#include "RcppViridis/utils/utils.hpp"

namespace rcppviridis {
namespace colours_hex {

  // if palette is a string; it's using in-built palettes; nothing to do
  // if palette is function or vectors, force rescaling

  inline Rcpp::StringVector colour_values_to_hex(
      Rcpp::NumericVector x,
      Rcpp::NumericVector red,
      Rcpp::NumericVector green,
      Rcpp::NumericVector blue,
      Rcpp::NumericVector alpha,
      std::string na_colour) {
    int n = x.size();
    double colours = red.size();

    //resolve_na_colour( na_colour );
    na_colour = na_colour.length() == 9 ? na_colour : na_colour + "FF";

    rcppviridis::scale::rescale(x);
    Rcpp::StringVector hex_strings(n);
    double step = 256 / colours;

    // cublic_b_spoine :: vec.start, vec.end, start.time, step
    boost::math::cubic_b_spline< double > spline_red(   red.begin(),   red.end(),   0, step );
    boost::math::cubic_b_spline< double > spline_green( green.begin(), green.end(), 0, step );
    boost::math::cubic_b_spline< double > spline_blue(  blue.begin(),  blue.end(),  0, step );

    double this_x;
    int i, r, g, b, a;
    std::string hex_str;

    for( i = 0; i < n; i++ ) {

      this_x = x[i] * 255;

      if ( R_IsNA( this_x) || R_IsNaN( this_x ) ) {
        hex_strings[i] = na_colour;
      } else {
        r = round( spline_red( this_x ) * 255 ) ;
        g = round( spline_green( this_x ) * 255 );
        b = round( spline_blue( this_x ) * 255 );
        a = alpha[i];
        hex_strings[i] = rcppviridis::convert::convert_rgb_to_hex(r, g, b, a);
      }
    }
    return hex_strings;
  }

  // in this function the colour vectors will already be scaled [0,1]
  inline Rcpp::StringVector colour_value_hex(
    Rcpp::NumericVector x,
    Rcpp::NumericMatrix palette,
    std::string na_colour ) {

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha(x.size(), 255.0);

    rcppviridis::palette_utils::resolve_palette( palette, red, green, blue, alpha );

    return colour_values_to_hex( x, red, green, blue, alpha, na_colour );
  }

  inline Rcpp::StringVector colour_value_hex(
      Rcpp::NumericVector x,
      std::string palette,
      std::string na_colour,
      Rcpp::NumericVector alpha) {

    // TODO(this throws an error on Travis)
    // if(!is_hex_colour(na_colour)) {
    //   Rcpp::stop("invalid NA Colour");
    // }

    int x_size = x.size();
    Rcpp::NumericVector alpha_full( x_size );
    rcppviridis::palette_utils::validate_alpha( alpha, alpha_full, x_size );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    rcppviridis::palette_utils::resolve_palette( palette, red, green, blue );

    return colour_values_to_hex(x, red, green, blue, alpha_full, na_colour);
  }

  Rcpp::StringVector colour_value_hex (
      Rcpp::StringVector x,
      Rcpp::NumericMatrix palette,
      std::string na_colour ) {

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha(x.size(), 255.0);

    rcppviridis::palette_utils::resolve_palette( palette, red, green, blue, alpha );
    Rcpp::NumericVector out_nv = rcppviridis::utils::resolve_string_vector( x );

    return colour_values_to_hex( out_nv, red, green, blue, alpha, na_colour );
  }

  inline Rcpp::StringVector colour_value_hex(
      Rcpp::StringVector x,
      std::string palette,
      std::string na_colour,
      Rcpp::NumericVector alpha ) {

    // TODO(this throws an error on Travis)
    // if(!is_hex_colour(na_colour)) {
    //   Rcpp::stop("invalid NA Colour");
    // }
    int x_size = x.size();
    Rcpp::NumericVector alpha_full( x_size );
    rcppviridis::palette_utils::validate_alpha( alpha, alpha_full, x_size );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    rcppviridis::palette_utils::resolve_palette( palette, red, green, blue );
    Rcpp::NumericVector out_nv = rcppviridis::utils::resolve_string_vector( x );

    return colour_values_to_hex( out_nv, red, green, blue, alpha_full, na_colour );
  }

} // namespace colours
} // namespace rcppviridis

#endif

