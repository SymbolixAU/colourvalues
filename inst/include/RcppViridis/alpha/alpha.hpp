#ifndef RCPP_VIRIDIS_HEADERS_ALPHA_H
#define RCPP_VIRIDIS_HEADERS_ALPHA_H

#include <Rcpp.h>

#define ALPHA_UNKNOWN  0
#define ALPHA_PALETTE  1  // the alpha is on the palette
#define ALPHA_VECTOR   2  // the alpha is a variable / vector
#define ALPHA_CONSTANT 3  // the alpha is a constant

namespace rcppviridis {
namespace alpha {

  inline int make_alpha_type( int alpha_size, int x_size, int palette_cols ) {
    // Rcpp::Rcout << "alpha_size: " << alpha_size << std::endl;
    // Rcpp::Rcout << "x_size: " << x_size << std::endl;
    // Rcpp::Rcout << "palette_cols " << palette_cols << std::endl;

    if (palette_cols == 4 ) {
      Rcpp::Rcout << "alpha PALETTE" << std::endl;
      return ALPHA_PALETTE;
    } else if (alpha_size <= 1) {  // covers NULL alpha (from R)
      Rcpp::Rcout << "alpha CONSTANT" << std::endl;
      return ALPHA_CONSTANT;

    } else if ( alpha_size == x_size ) {
      // colour_values(1:10) is constant alpha
      // colour_values(1:10, m[,1:3]) should also be constant, not a vector
      Rcpp::Rcout << "alpha VECTOR" << std::endl;
      return ALPHA_VECTOR;
    }
    Rcpp::Rcout << "alpha UNKNOWN" << std::endl;
    return ALPHA_UNKNOWN;
  }

  inline Rcpp::NumericVector validate_alpha( Rcpp::NumericVector& alpha, int& alpha_type, int& x_size ) {

    if ( alpha_type == ALPHA_CONSTANT ) {
      Rcpp::NumericVector alpha_full( 5, alpha[0] ); // initialise with 5 vals (so i can create a spline object);
      return alpha_full;
    } else if ( alpha_type == ALPHA_PALETTE ) {
      return alpha;
    } else if (alpha_type == ALPHA_VECTOR ) {
      rcppviridis::scale::rescale( alpha );
      alpha = alpha * 255;
    } else if ( alpha_type == ALPHA_UNKNOWN ) {
      Rcpp::stop("Unknown alpha definition");
    }
    return 0;

    // int alpha_size = alpha.size();
    // // Rcpp::Rcout << "alpha size  " << alpha_size << std::endl;
    // // Rcpp::Rcout << "alpha: " << alpha << std::endl;
    //
    // // if ( !( alpha_size == 1 || alpha_size == x_size ) ){
    // //   Rcpp::stop("alpha must either be a single value, or the same length as x");
    // // }
    //
    // if ( alpha_size > 1 && alpha_type != ALPHA_CONSTANT) {  // TODO: use ALPHA_CONSTANT
    //   //alpha_full = alpha;
    //   // Rcpp::Rcout << "rescaling alpha: " << alpha << std::endl;
    //
    //   // TODO(IFF ALPHA_VECTOR - rescale to [0,1])
    //   // IFF ALPHA_CONSTANT - leave as-is (shoudl be between [0,255])
    //   rcppviridis::scale::rescale( alpha );
    //
    //   if (alpha_type == ALPHA_VECTOR) { // ALPHA_VECTOR
    //     alpha = alpha * 255;
    //   }
    //   // vector of values - gets resaceld and needs * 255
    //   // on the palette, doesn't need *255
    //
    //   return alpha;
    // } else {
    //   Rcpp::NumericVector alpha_full( 5, alpha[0] ); // initialise with 5 vals (so i can create a spline object);
    //   return alpha_full;
    // }
    // return 0;
  }

} // namespace alpha
} // namespace rcppviridis

#endif
