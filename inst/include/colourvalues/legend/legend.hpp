#ifndef COLOURVALUES_LEGEND_H
#define COLOURVALUES_LEGEND_H

#include <Rcpp.h>

namespace colourvalues {
namespace legend {

  /*
   * Returns evenly spaced values from a vector
   * The idea is to use the same palette as the vector to then get the values and colours
   * to use in a legend
   */
  inline Rcpp::NumericVector numeric_summary(Rcpp::NumericVector& nv, std::size_t n) {
    double x = Rcpp::min( nv );
    double y = Rcpp::max( nv );
    double h = ( y - x ) / static_cast< double >( n - 1 );
    Rcpp::NumericVector vals( n );
    Rcpp::NumericVector::iterator it;
    double val;
    for ( it = vals.begin(), val = x; it != vals.end(); it++, val += h ) {
      *it = val;
    }
    return vals;
  }


} // namespace legend
} // namespace colourvalues

#endif
