// #include <Rcpp.h>
// #include "RcppViridis.hpp"
// #include "RcppViridis_Base.hpp"
// #include "RcppViridisMagma.hpp"
// #include "RcppViridisInferno.hpp"
// #include "RcppViridisPlasma.hpp"
// #include "RcppViridisViridis.hpp"
// #include "RcppViridisCividis.hpp"
//
// // [[Rcpp::depends(BH)]]
// #include <boost/math/interpolators/cubic_b_spline.hpp>
//
// using namespace Rcpp;
//
// void palette_vectors( Rcpp::NumericVector& red, Rcpp::NumericVector& green,
//                      Rcpp::NumericVector& blue, int n, std::string palette ) {
//
//   if( palette == "viridis" ) {
//     red = viridis::viridis_red;
//     green = viridis::viridis_green;
//     blue = viridis::viridis_blue;
//   } else if ( palette == "inferno" ) {
//     red = inferno::inferno_red;
//     green = inferno::inferno_green;
//     blue = inferno::inferno_blue;
//   } else if ( palette == "plasma" ) {
//     red = plasma::plasma_red;
//     green = plasma::plasma_green;
//     blue = plasma::plasma_blue;
//   } else if ( palette == "magma" ) {
//     red = magma::magma_red;
//     green = magma::magma_green;
//     blue = magma::magma_blue;
//   } else if ( palette == "cividis" ) {
//     red = cividis::cividis_red;
//     green = cividis::cividis_green;
//     blue = cividis::cividis_blue;
//   } else {
//     Rcpp::stop("unknown palette");
//   }
// }
//
//
// // [[Rcpp::export]]
// Rcpp::StringVector hex_palette( std::string palette ) {
//
//   Rcpp::NumericVector red(256);
//   Rcpp::NumericVector green(256);
//   Rcpp::NumericVector blue(256);
//
//   palette_vectors(red, green, blue, 256, palette);
//   Rcpp::StringVector hex_strings(256);
//
//   boost::math::cubic_b_spline< double > spline_red( red.begin(), red.end(), 0, 1 );
//   boost::math::cubic_b_spline< double > spline_green( green.begin(), green.end(), 0, 1 );
//   boost::math::cubic_b_spline< double > spline_blue( blue.begin(), blue.end(), 0, 1 );
//
//   int i = 0;
//   int r, g, b;
//   for (i = 0; i < 256; i++) {
//     r = round( spline_red( i ) * 255 ) ;
//     g = round( spline_green( i ) * 255 );
//     b = round( spline_blue( i ) * 255 );
//     hex_strings[i] = ConvertRGBtoHex(r, g, b);
//   }
//
//   return hex_strings;
//
// }
