#include "colourvalues/colours/colours_hex.hpp"
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
      int n_elements = Rf_length( lst[i] );
      int new_type = TYPEOF( lst[i] );
      existing_type = vector_type( new_type, existing_type );
      res[i] = n_elements;
      total_size += n_elements;
    }
    }
  }
  //Rcpp::Rcout << "vector type: " << existing_type <<  std::endl;
  //Rcpp::Rcout << "total_size: " << total_size << std::endl;
  return res;
}


/*
 * Creates a list of the same dimensions as the original list, but all the elements are now
 * StringVectors of hex colours
 */
// [[Rcpp::export]]
Rcpp::List refil_list( const Rcpp::List& lst_sizes, Rcpp::StringVector& colours, int& vector_position ) {

  // iterate through the list, if size > 0, fill with that many values from the vector

  size_t n = lst_sizes.size();
  Rcpp::List res( n );
  std::size_t i;

  for( i = 0; i < n; i++ ) {
    switch( TYPEOF( lst_sizes[ i ] ) ) {
    case VECSXP: {
      res[ i ] = refil_list( lst_sizes[ i ], colours, vector_position );
      break;
    }
    case INTSXP: {
      Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
      int end_position = vector_position + n_elements[0] - 1;
      Rcpp::IntegerVector elements = Rcpp::seq( vector_position, end_position );
      Rcpp::StringVector these_colours = colours[ elements ];
      res[ i ] = these_colours;
      vector_position = end_position + 1;
      break;
    }
    default: {
      Rcpp::stop("Unknown list element type");
    }
    }
  }
  return res;
}

Rcpp::LogicalVector unlist_list( const Rcpp::List& lst, Rcpp::LogicalVector& colours ) {

}

Rcpp::IntegerVector unlist_list( const Rcpp::List& lst, Rcpp::IntegerVector& colours ) {

}

Rcpp::NumericVector unlist_list( const Rcpp::List& lst, Rcpp::NumericVector& colours ) {

}

/*
 * @param lst - the original input list
 * @param lst_sizes - the dimensions of the list
 * @param colorus - vector of values which will go into colour_values_hex()
 */
void unlist_list( const Rcpp::List& lst, const Rcpp::List& lst_sizes, Rcpp::StringVector& colours, int& list_position ) {

  // - iterate through original list
  // - extract each element and insert into 'colours'
  size_t n = lst.size();
  Rcpp::List res( n );
  std::size_t i;
  for( i = 0; i < n; i++ ) {
    switch( TYPEOF( lst[i] ) ) {
    case VECSXP: {
      unlist_list( lst[ i ], lst_sizes[ i ], colours, list_position );
      break;
    }
    default: {
      Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
      int end_position = list_position + n_elements[0] - 1;
      Rcpp::IntegerVector elements = Rcpp::seq( list_position, end_position );
      colours[ elements ] = Rcpp::as< Rcpp::StringVector >( lst[ i ] );

      list_position = end_position + 1;
      break;
    }
    }
  }
}


// [[Rcpp::export]]
Rcpp::List colour_list( Rcpp::List lst ) {
  double total_size = 0;
  int existing_type = 10;

  int position = 0;

  Rcpp::List lst_sizes = list_size( lst, total_size, existing_type );

  //return lst_sizes;

  //Rcpp::Rcout << "total_size: " << total_size << std::endl;
  //Rcpp::Rcout << "vector type: " << existing_type << std::endl;

  // iterate again through the list and fill a vector with the values
  // wrapping to the correct type
  // the 'existing_type' is now the type of the vector which will go into 'colour_values_hex()'
  //
  switch( existing_type ) {
  case 10: {

  }
  default: {
    Rcpp::StringVector colours( total_size );
    unlist_list( lst, lst_sizes, colours, position );

    //Rcpp::Rcout << "colours: " << colours << std::endl;
    // TODO - 'colours' now goes into 'colour_values_hex()
    std::string palette = "viridis";
    std::string na_colour = "#808080";
    //Rcpp::NumericVector alpha( total_size, 255 );
    Rcpp::NumericVector alpha(1, 255.0);
    bool include_alpha = true;
    bool summary = false;

    Rcpp::StringVector colour_vector = colourvalues::colours_hex::colour_value_hex(
      colours, palette, na_colour, alpha, include_alpha, summary
    );

    position = 0;
    Rcpp::List res = refil_list( lst_sizes, colour_vector, position );
    return res;
  }
  }

  // given the vector of colours, need to re-build the existing list shape
  // by filling 'lst_sizes' with the colours
  //position = 0;
  //Rcpp::List res = refil_list( lst_sizes, colours, position );
  //return res;

  return Rcpp::List::create(); // never reaches
}
