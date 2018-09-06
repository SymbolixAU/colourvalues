#include <Rcpp.h>
#include "RcppViridis.hpp"
#include "RcppViridis_Base.hpp"
#include "RcppViridisMagma.hpp"
#include "RcppViridisInferno.hpp"
#include "RcppViridisPlasma.hpp"
#include "RcppViridisViridis.hpp"
#include "RcppViridisCividis.hpp"

using namespace Rcpp;
using namespace viridis;

//[[Rcpp::depends(BH)]]

#include <boost/math/interpolators/cubic_b_spline.hpp>


void replace_nas( Rcpp::IntegerVector& out, int na_value ) {
  int int_s = NA_INTEGER;
  std::replace( out.begin(), out.end(), na_value, int_s);
}

Rcpp::StringVector colour_variable_hex( Rcpp::StringVector x, std::string palette, std::string na_colour ) {

  bool anyNa = any(is_na(x));
  Rcpp::StringVector lvls = sort_unique( x );
  Rcpp::IntegerVector out = match(x, lvls);

  if ( anyNa ) {
    int na_value = max( out );
    replace_nas(out, na_value);
  }

  Rcpp::NumericVector out_nv = as< Rcpp::NumericVector >(out);

  return colour_variable_hex( out_nv, palette, na_colour );
}


Rcpp::StringVector colour_variable_hex( Rcpp::NumericVector x, std::string palette, std::string na_colour ) {

  int n = x.size();

  // TODO(this throws an error on Travis)
  // if(!is_hex_colour(na_colour)) {
  //   Rcpp::stop("invalid NA Colour");
  // }


  //Rcpp::NumericVector vals = m_unique(x);
  Rcpp::NumericVector scaledVals = m_rescale(x);
  Rcpp::StringVector hex_strings(n);

  /*
  double max_x = max( na_omit( x ) ) ;
  double scale_x = 255 / max_x;
  */

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
  } else if ( palette == "cividis" ) {
    red = cividis::cividis_red;
    green = cividis::cividis_green;
    blue = cividis::cividis_blue;
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
    //this_x = x[i] * scale_x;
    // mat_colours(i, 0) = round( spline_red( this_x ) * 255) ;
    // mat_colours(i, 1) = round( spline_green( this_x ) * 255);
    // mat_colours(i, 2) = round( spline_blue( this_x ) * 255);

    this_x = scaledVals[i] * 255;

    if ( R_IsNA( this_x) || R_IsNaN( this_x ) ) {
      hex_strings[i] = na_colour;
    } else {
      r = round( spline_red( this_x ) * 255 ) ;
      g = round( spline_green( this_x ) * 255 );
      b = round( spline_blue( this_x ) * 255 );
      hex_strings[i] = ConvertRGBtoHex(r, g, b);
    }
  }
  return hex_strings;
}

/*
 * colour values
 *
 * Colours values
 */
// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_num_variable_hex( Rcpp::NumericVector x, std::string palette, std::string na_colour) {
  return colour_variable_hex( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_str_variable_hex( Rcpp::StringVector x, std::string palette, std::string na_colour) {
  return colour_variable_hex( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_dte_variable_hex( Rcpp::DateVector x, std::string palette, std::string na_colour) {
  Rcpp::NumericVector y = as< Rcpp::NumericVector>(x);
  return colour_variable_hex( y, palette, na_colour );
}



