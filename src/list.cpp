#include <Rcpp.h>

// [[Rcpp::export]]
int vector_type( int new_type, int existing_type ) {

  // can't change from STRSXP
  if( existing_type == 16 ) {
    return existing_type;
  }

  std::vector< int > valid_types{10, 13, 14, 16};
  bool new_is_valid = ( std::find( valid_types.begin(), valid_types.end(), new_type ) != valid_types.end() );
  bool existing_is_valid = ( std::find( valid_types.begin(), valid_types.end(), existing_type ) != valid_types.end() );

  if( new_type == existing_type && new_is_valid ) {
    return existing_type;
  }

  // convert new type up to existing type
  if( new_type < existing_type && existing_is_valid ) {
    return existing_type;
  }

  if( new_type > existing_type && new_is_valid ) {
    return new_type;
  }

  if( new_type > existing_type && !new_is_valid ) {
    return 16;
  }

  if( existing_is_valid ) {
    return existing_type;
  }

  return 16;
}

/*
 * returns the size of each element, and the given depth of each list element
 *
 * existing_type starts at 10 (LGLSXP), and continues in order 13 (INTSXP), 14 (REALSXP), 16 (STRSXP)
 * Anything outside those numbers is converted to STRSXP
 */
// [[Rcpp::export]]
Rcpp::List list_size( const Rcpp::List& lst, double& total_size, int& existing_type ) {
  std::size_t n = lst.size();
  Rcpp::List res( n ); // create a list to store the size corresponding to each list element
  std::size_t i;
  for( i = 0; i < n; i++ ) {
    switch( TYPEOF( lst[i] ) ) {
    case VECSXP: {
      res[ i ] = list_size( lst[i], total_size, existing_type );
      break;
    }
    default: {
      double n = Rf_length( lst[i] );
      int new_type = TYPEOF( lst[i] );
      existing_type = vector_type( new_type, existing_type );
      res[i] = n;
      total_size += n;
    }
    }
  }
  //Rcpp::Rcout << "vector type: " << existing_type <<  std::endl;
  //Rcpp::Rcout << "total_size: " << total_size << std::endl;
  return res;
}
