#ifndef COLOURVALUES_SUMMARY_H
#define COLOURVALUES_SUMMARY_H

#include <Rcpp.h>

namespace colourvalues {
namespace summary {

  /*
   * Returns evenly spaced values from a vector
   * The idea is to use the same palette as the vector to then get the values and colours
   * to use in a legend
   */
  inline Rcpp::NumericVector numeric_summary( Rcpp::NumericVector& nv, R_xlen_t n ) {

    Rcpp::NumericVector clean_nv = na_omit( nv );
    R_xlen_t nv_length = clean_nv.length();
    R_xlen_t n_summaries = n < nv_length ? n : nv_length;

    if ( n_summaries == 1 ) {
      return clean_nv;
    }

    Rcpp::NumericVector vals( n_summaries );

    double x = Rcpp::min( clean_nv );
    double y = Rcpp::max( clean_nv );
    double h = ( y - x ) / static_cast< double >( n_summaries - 1 );
    Rcpp::NumericVector::iterator it;
    double val;
    for ( it = vals.begin(), val = x; it != vals.end(); it++, val += h ) {
      *it = val;
    }
    return vals;
  }


} // namespace summary
} // namespace colourvalues

#endif
