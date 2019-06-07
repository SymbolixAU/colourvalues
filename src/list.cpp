
#include "colourvalues/list/list.hpp"
#include <Rcpp.h>

// [[Rcpp::export]]
int rcpp_vector_type( int new_type, int existing_type ) {
  return colourvalues::list::vector_type( new_type, existing_type );
}

/*
 * returns the size of each element, and the given depth of each list element
 *
 * existing_type starts at 10 (LGLSXP), and continues in order 13 (INTSXP), 14 (REALSXP), 16 (STRSXP)
 * Anything outside those numbers is converted to STRSXP
 */
// [[Rcpp::export]]
Rcpp::List rcpp_list_size( const Rcpp::List& lst, double& total_size, int& existing_type ) {
  return colourvalues::list::list_size( lst, total_size, existing_type );
}


/*
 * Creates a list of the same dimensions as the original list, but all the elements are now
 * StringVectors of hex colours
 */
// [[Rcpp::export]]
Rcpp::List rcpp_refil_list( const Rcpp::List& lst_sizes, Rcpp::StringVector& colours, int& vector_position ) {
  return colourvalues::list::refil_list( lst_sizes, colours, vector_position );
}


// [[Rcpp::export]]
Rcpp::List colour_list( Rcpp::List lst ) {
  double total_size = 0;
  int existing_type = 10;

  int position = 0;

  Rcpp::List lst_sizes = colourvalues::list::list_size( lst, total_size, existing_type );

  //return lst_sizes;

  //Rcpp::Rcout << "total_size: " << total_size << std::endl;
  //Rcpp::Rcout << "vector type: " << existing_type << std::endl;

  // iterate again through the list and fill a vector with the values
  // wrapping to the correct type
  // the 'existing_type' is now the type of the vector which will go into 'colour_values_hex()'
  //
  switch( existing_type ) {
  /* logical treated as character
  case LGLSXP: { // 10

  }
  */
  case INTSXP: { } // 13
  case REALSXP: { // 14
    Rcpp::NumericVector colours( total_size );
    colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

    //Rcpp::Rcout << "colours: " << colours << std::endl;
    // TODO - 'colours' now goes into 'colour_values_hex()
    std::string palette = "viridis";
    std::string na_colour = "#808080";
    //Rcpp::NumericVector alpha( total_size, 255 );
    Rcpp::NumericVector alpha(1, 255.0);
    bool include_alpha = true;
    int n_summaries = 0;
    bool format = false;
    std::string format_type = "numeric";
    int digits = 2;

    Rcpp::StringVector colour_vector = colourvalues::colours_hex::colour_value_hex(
      colours, palette, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits
    );

    position = 0;
    Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
    return res;

  }
  default: {
    Rcpp::StringVector colours( total_size );
    colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

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
    Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
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
