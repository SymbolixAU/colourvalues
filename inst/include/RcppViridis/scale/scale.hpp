#ifndef RCPP_VIRIDIS_HEADERS_SCALE_H
#define RCPP_VIRIDIS_HEADERS_SCALE_H

#include <Rcpp.h>

namespace rcppviridis {
namespace scale {

  Rcpp::NumericVector range(Rcpp::NumericVector x) {
    Rcpp::NumericVector rng(2);
    rng[0] = min(na_omit(x));
    rng[1] = max(na_omit(x));
    return rng;
  }


  // Always rescales to (0, 1)
  void rescale( Rcpp::NumericVector& x ) {
    int n = x.size();
    //::NumericVector rescaled(n);
    Rcpp::NumericVector rng = range(x);
    Rcpp::NumericVector diff_from = Rcpp::diff(rng); // should only be one value!

    double this_diff = std::max(1.0, diff_from[0]);  // TODO(is this right? what am I doing?)
    this_diff = 1 / this_diff;
    int i = 0;
    double this_range = rng[0];

    for (i = 0; i < n; i++) {
      x[i] = (x[i] - this_range) * this_diff;
    }
    //return rescaled;
  }
} // namespace scale
} // namespace rcppviridis
#endif
