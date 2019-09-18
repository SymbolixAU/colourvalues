
#include "colourvalues/list/list.hpp"
#include <Rcpp.h>

// [[Rcpp::export]]
int rcpp_vector_type(
    int new_type,
    int existing_type
  ) {
  return colourvalues::list::vector_type( new_type, existing_type );
}

/*
 * returns the size of each element, and the given depth of each list element
 *
 * existing_type starts at 10 (LGLSXP), and continues in order 13 (INTSXP), 14 (REALSXP), 16 (STRSXP)
 * Anything outside those numbers is converted to STRSXP
 */
// [[Rcpp::export]]
Rcpp::List rcpp_list_size(
    const Rcpp::List& lst,
    int& total_size,
    int& existing_type,
    std::string& format_type
  ) {
  return colourvalues::list::list_size( lst, total_size, existing_type, format_type );
}


/*
 * Creates a list of the same dimensions as the original list, but all the elements are now
 * StringVectors of hex colours
 */
// [[Rcpp::export]]
Rcpp::List rcpp_refil_list(
    const Rcpp::List& lst_sizes,
    Rcpp::StringVector& colours,
    int& vector_position
  ) {
  return colourvalues::list::refil_list( lst_sizes, colours, vector_position );
}
