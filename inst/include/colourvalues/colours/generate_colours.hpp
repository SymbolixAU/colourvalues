#ifndef R_COLOURVALUES_GENERATE_COLOURS_H
#define R_COLOURVALUES_GENERATE_COLOURS_H

#include <Rcpp.h>
#include "colourvalues/colours.hpp"
#include "colourvalues/alpha/alpha.hpp"
//#include "colourvalues/scale/scale.hpp"

//#include "colourvalues/spline.hpp" // TODO

#include "cardinal_cubic_b_spline.hpp"
//#include "boost/math/interpolators/cardinal_cubic_b_spline.hpp"

namespace colourvalues {
namespace generate_colours {

  inline Rcpp::StringVector colour_values_to_hex(
      Rcpp::NumericVector& x,
      Rcpp::NumericVector& red,
      Rcpp::NumericVector& green,
      Rcpp::NumericVector& blue,
      Rcpp::NumericVector& alpha,
      int& alpha_type,
      std::string& na_colour,
      bool& include_alpha
  ) {

    int n = x.size();
    double colours = red.size();
    na_colour = na_colour.length() == 9 ? na_colour : na_colour + "FF";

    colourvalues::scale::rescale( x );
    Rcpp::StringVector hex_strings( n );
    double step = 1 / ( colours - 1 );  // TODO(test)

    // Rcpp::Rcout << red << std::endl;

    // cublic_b_spoine :: vec.start, vec.end, start.time, step
    boost::math::interpolators::cardinal_cubic_b_spline< double > spline_red(   red.begin(),   red.end(),   0, step );
    boost::math::interpolators::cardinal_cubic_b_spline< double > spline_green( green.begin(), green.end(), 0, step );
    boost::math::interpolators::cardinal_cubic_b_spline< double > spline_blue(  blue.begin(),  blue.end(),  0, step );
    boost::math::interpolators::cardinal_cubic_b_spline< double > spline_alpha( alpha.begin(),  alpha.end(),  0, step );

    double this_x;
    int i, r, g, b;
    std::string hex_str;

    for( i = 0; i < n; i++ ) {

      this_x = x[i];

      if ( R_IsNA( this_x) || R_IsNaN( this_x ) ) {
        hex_strings[i] = na_colour;
      } else {
        r = round( spline_red( this_x ) * 255 ) ;
        g = round( spline_green( this_x ) * 255 );
        b = round( spline_blue( this_x ) * 255 );

        // Rcpp::Rcout << "this_x: " << this_x << std::endl;
        // Rcpp::Rcout << "splined_r: " << r << std::endl;

        colourvalues::palette_utils::validate_rgb_spline(r);
        colourvalues::palette_utils::validate_rgb_spline(g);
        colourvalues::palette_utils::validate_rgb_spline(b);

        if (include_alpha) {
          int a;
          if ( alpha_type == ALPHA_PALETTE ) {
            a = round( spline_alpha( this_x ) * 255 );
          } else if (alpha_type == ALPHA_VECTOR ){
            a = alpha[i];
          } else {
            a = alpha[0];  // should be length 5, but all the same
          }
          hex_strings[i] = colourvalues::convert::convert_rgb_to_hex(r, g, b, a);
        } else {
          hex_strings[i] = colourvalues::convert::convert_rgb_to_hex(r, g, b);
        }
      }
    }
    return hex_strings;
  }

  inline Rcpp::NumericMatrix colour_values_to_rgb(
      Rcpp::NumericVector& x,
      Rcpp::NumericVector& red,
      Rcpp::NumericVector& green,
      Rcpp::NumericVector& blue,
      Rcpp::NumericVector& alpha,
      int& alpha_type,
      std::string& na_colour,
      bool& include_alpha
  ) {

    int n = x.size();
    double colours = red.size();
    na_colour = na_colour.length() == 9 ? na_colour : na_colour + "FF";

    colourvalues::scale::rescale( x );
    int cols = include_alpha ? 4 : 3;
    Rcpp::NumericMatrix rgb_mat(n, cols);
    double step = 1 / ( colours - 1 );  // TODO(test)

    // cublic_b_spoine :: vec.start, vec.end, start.time, step
    boost::math::interpolators::cardinal_cubic_b_spline< double > spline_red(   red.begin(),   red.end(),   0, step );
    boost::math::interpolators::cardinal_cubic_b_spline< double > spline_green( green.begin(), green.end(), 0, step );
    boost::math::interpolators::cardinal_cubic_b_spline< double > spline_blue(  blue.begin(),  blue.end(),  0, step );
    boost::math::interpolators::cardinal_cubic_b_spline< double > spline_alpha( alpha.begin(), alpha.end(), 0, step );

    double this_x;
    int i, r, g, b;
    std::string hex_str;

    Rcpp::IntegerMatrix na_mat = colourvalues::convert::convert_hex_to_rgb( na_colour );

    for( i = 0; i < n; i++ ) {

      this_x = x[i];

      if ( R_IsNA( this_x) || R_IsNaN( this_x ) ) {
        rgb_mat(i, _) = na_mat;

      } else {
        r = round( spline_red( this_x ) * 255 ) ;
        g = round( spline_green( this_x ) * 255 );
        b = round( spline_blue( this_x ) * 255 );

        r = colourvalues::palette_utils::validate_rgb_range( r );
        g = colourvalues::palette_utils::validate_rgb_range( g );
        b = colourvalues::palette_utils::validate_rgb_range( b );

        if (include_alpha) {
          int a;
          if ( alpha_type == ALPHA_PALETTE ) {
            a = round( spline_alpha( this_x ) * 255 );
          } else if (alpha_type == ALPHA_VECTOR ){
            a = alpha[i];
          } else {
            a = alpha[0];  // should be length 5, but all the same
          }
          rgb_mat(i, _) = Rcpp::NumericVector::create(r,g,b,a);
        } else {
          rgb_mat(i, _) = Rcpp::NumericVector::create(r,g,b);
        }
      }
    }
    return rgb_mat;
  }

} // generate_colours
} // colourvalues


#endif
