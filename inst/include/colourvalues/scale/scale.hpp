#ifndef R_COLOURVALUES_SCALE_H
#define R_COLOURVALUES_SCALE_H

#include <Rcpp.h>

namespace colourvalues {
namespace scale {

  inline Rcpp::NumericVector range(Rcpp::NumericVector& x) {
    Rcpp::NumericVector rng(2);
    rng[0] = min(na_omit(x));
    rng[1] = max(na_omit(x));
    return rng;
  }


  // Always rescales to (0, 1)
  // used for variables
  inline void rescale( Rcpp::NumericVector& x ) {
    int n = x.size();
    //::NumericVector rescaled(n);
    Rcpp::NumericVector rng = range(x);
    Rcpp::NumericVector diff_from = Rcpp::diff(rng); // should only be one value!

    double this_diff = diff_from[0] == 0 ? 1.0 : diff_from[0];

    this_diff = 1 / this_diff;
    int i = 0;
    double this_range = rng[0];

    for (i = 0; i < n; i++) {
      x[i] = (x[i] - this_range) * this_diff;
    }
    //return rescaled;
  }

  // need a separate rescale for rescaling colours,
  // where, if the range == 0, it's a single colour and should remain as-is?
  // so if red = 100,100,100,100
  // the scaled values will be 100 / 255
  // COLOUR PALETTES should always be specified in [0,255]

} // namespace scale
} // namespace colourvalues
#endif
