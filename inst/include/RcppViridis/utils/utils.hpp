#ifndef RCPP_VIRIDIS_HEADERS_UTILS_H
#define RCPP_VIRIDIS_HEADERS_UTILS_H

#include <Rcpp.h>

namespace rcppviridis {
namespace utils {

  inline void replace_nas( Rcpp::IntegerVector& out, int na_value ) {
    int int_s = NA_INTEGER;
    std::replace( out.begin(), out.end(), na_value, int_s);
  }

} // namespace utils
} // namespace rcppviridis


#endif
