#include <Rcpp.h>

/*
 * returns the size of each element, and the given depth of each list element
 */
// [[Rcpp::export]]
Rcpp::List list_size( const Rcpp::List& lst ) {
  std::size_t n = lst.size();
  Rcpp::List res( n ); // create a list to store the size corresponding to each list element
  std::size_t i;
  for( i = 0; i < n; i++ ) {
    switch( TYPEOF( lst[i] ) ) {
    case VECSXP: {
      res[ i ] = list_size( lst[i] );
      break;
    }
    default: {
      res[i] = Rf_length( lst[i] );
    }
    }
  }
  return res;
}
