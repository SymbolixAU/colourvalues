#ifndef RCPP_VIRIDIS_HEADERS_COLOURS_H
#define RCPP_VIRIDIS_HEADERS_COLOURS_H

#include <Rcpp.h>
#include "RcppViridis/palettes/viridis.hpp"
#include "RcppViridis/palettes/cvidis.hpp"
#include "RcppViridis/palettes/magma.hpp"
#include "RcppViridis/palettes/inferno.hpp"
#include "RcppViridis/palettes/plasma.hpp"
#include "RcppViridis/scale/scale.hpp"
#include "RcppViridis/utils/utils.hpp"
#include "RcppViridis/convert_colours/convert_colours.hpp"

//[[Rcpp::depends(BH)]]
#include <boost/math/interpolators/cubic_b_spline.hpp>

namespace rcppviridis {
namespace colours {

  Rcpp::StringVector colour_value_hex(
    Rcpp::NumericVector x,
    Rcpp::NumericVector red,
    Rcpp::NumericVector green,
    Rcpp::NumericVector blue,
    std::string na_colour
  ) {

    int n = x.size();
    double colours = red.size();

    Rcpp::NumericVector scaledVals = rcppviridis::scale::rescale(x);
    Rcpp::StringVector hex_strings(n);
    double step = 256 / colours;

    // cublic_b_spoine :: vec.start, vec.end, start.time, step
    // - step is 1 because it's rows of vector
    boost::math::cubic_b_spline< double > spline_red(   red.begin(),   red.end(),   0, step );
    boost::math::cubic_b_spline< double > spline_green( green.begin(), green.end(), 0, step );
    boost::math::cubic_b_spline< double > spline_blue(  blue.begin(),  blue.end(),  0, step );

    double this_x;
    int i, r, g, b;
    std::string hex_str;

    for( i = 0; i < n; i ++ ) {

      this_x = scaledVals[i] * 255;

      if ( R_IsNA( this_x) || R_IsNaN( this_x ) ) {
        hex_strings[i] = na_colour;
      } else {
        r = round( spline_red( this_x ) * 255 ) ;
        g = round( spline_green( this_x ) * 255 );
        b = round( spline_blue( this_x ) * 255 );
        hex_strings[i] = rcppviridis::convert::convert_rgb_to_hex(r, g, b);
      }
    }
    return hex_strings;
  }

  Rcpp::StringVector colour_value_hex(
      Rcpp::NumericVector x,
      std::string palette,
      std::string na_colour ) {

    int n = x.size();

    // TODO(verify sequence %[0,255])

    // TODO(this throws an error on Travis)
    // if(!is_hex_colour(na_colour)) {
    //   Rcpp::stop("invalid NA Colour");
    // }

    int i = 0;

    // TODO(allow user to select start and end points of the vectors)
    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    if( palette == "viridis" ) {
      red = rcppviridis::palette::viridis_red;
      green = rcppviridis::palette::viridis_green;
      blue = rcppviridis::palette::viridis_blue;
    } else if ( palette == "inferno" ) {
      red = rcppviridis::palette::inferno_red;
      green = rcppviridis::palette::inferno_green;
      blue = rcppviridis::palette::inferno_blue;
    } else if ( palette == "plasma" ) {
      red = rcppviridis::palette::plasma_red;
      green = rcppviridis::palette::plasma_green;
      blue = rcppviridis::palette::plasma_blue;
    } else if ( palette == "magma" ) {
      red = rcppviridis::palette::magma_red;
      green = rcppviridis::palette::magma_green;
      blue = rcppviridis::palette::magma_blue;
    } else if ( palette == "cividis" ) {
      red = rcppviridis::palette::cividis_red;
      green = rcppviridis::palette::cividis_green;
      blue = rcppviridis::palette::cividis_blue;
    } else {
      Rcpp::stop("unknown palette");
    }

    // TODO(index palettes on palette_sequence)
    return colour_value_hex(x, red, green, blue, na_colour);
  }

  // Rcpp::StringVector colour_value_hex( Rcpp::StringVector x, Function palette, std::string na_colour ) {
  //
  //   // TODO(call palette convert to RGB, interpolate, convert to hex)
  //
  //
  //   return "";
  // }

  Rcpp::StringVector colour_value_hex(
      Rcpp::StringVector x,
      Rcpp::NumericVector red,
      Rcpp::NumericVector green,
      Rcpp::NumericVector blue,
      std::string na_colour ) {

    bool anyNa = any(is_na(x));
    Rcpp::StringVector lvls = sort_unique( x );
    Rcpp::IntegerVector out = match(x, lvls);

    if ( anyNa ) {
      int na_value = max( out );
      rcppviridis::utils::replace_nas(out, na_value);
    }
    Rcpp::NumericVector out_nv = as< Rcpp::NumericVector >(out);

    return colour_value_hex( out_nv, red, green, blue, na_colour );
  }

  Rcpp::StringVector colour_value_hex(
      Rcpp::StringVector x,
      std::string palette,
      std::string na_colour ) {

    bool anyNa = any(is_na(x));
    Rcpp::StringVector lvls = sort_unique( x );
    Rcpp::IntegerVector out = match(x, lvls);

    if ( anyNa ) {
      int na_value = max( out );
      rcppviridis::utils::replace_nas(out, na_value);
    }
    Rcpp::NumericVector out_nv = as< Rcpp::NumericVector >(out);

    return colour_value_hex( out_nv, palette, na_colour );
  }

} // namespace colours
} // namespace rcppviridis

#endif

