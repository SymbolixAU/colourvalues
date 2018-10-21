#ifndef R_COLOURVALUES_UTILS_H
#define R_COLOURVALUES_UTILS_H

#include <Rcpp.h>

namespace colourvalues {
namespace utils {

  inline void replace_nas( Rcpp::IntegerVector& out, int na_value ) {
    int int_s = NA_INTEGER;
    std::replace( out.begin(), out.end(), na_value, int_s);
  }

  inline Rcpp::NumericVector resolve_string_vector( Rcpp::StringVector& x, Rcpp::StringVector& lvls ) {
    bool anyNa = Rcpp::any( is_na( x ) );

    Rcpp::IntegerVector out = Rcpp::match( x, lvls );

    if ( anyNa ) {
      int na_value = Rcpp::max( out );
      colourvalues::utils::replace_nas( out, na_value );
    }
    return Rcpp::as< Rcpp::NumericVector >( out );
  }

} // namespace utils
} // namespace colourvalues


#endif
