#include <Rcpp.h>
#include "RcppViridisMagma.hpp"
#include "RcppViridisInferno.hpp"
#include "RcppViridisPlasma.hpp"
#include "RcppViridisViridis.hpp"

using namespace Rcpp;
using namespace viridis;

//[[Rcpp::depends(BH)]]

#include <boost/math/interpolators/cubic_b_spline.hpp>



/*
 * colour variable
 *
 * Colours variables
 */
// [[Rcpp::export]]
Rcpp::List colour_variable( Rcpp::NumericVector x, std::string palette) {
  int n = x.size();
  Rcpp::NumericVector result_red(n);
  Rcpp::NumericVector result_green(n);
  Rcpp::NumericVector result_blue(n);

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
  // int r, g, b;

  for( i = 0; i < n; i ++ ) {
    this_x = x[i] * scale_x;
    result_red[i] = round( spline_red( this_x ) * 255) ;
    result_green[i] = round( spline_green( this_x ) * 255);
    result_blue[i] = round( spline_blue( this_x ) * 255);

    // r = round( spline_red( this_x ) * 255) ;
    // g = round( spline_green( this_x ) * 255);
    // b = round( spline_blue( this_x ) * 255);


  }
  return Rcpp::List::create(
    _["r"] = result_red,
    _["g"] = result_green,
    _["b"] = result_blue
  );



}

// TODO(convert to RGB [0,255], & HEX)
