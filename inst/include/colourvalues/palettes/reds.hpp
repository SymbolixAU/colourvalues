#ifndef R_COLOURVALUES_REDS_H
#define R_COLOURVALUES_REDS_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector reds_red = {
    1,0.996078431372549,0.988235294117647,
    0.988235294117647,0.984313725490196,0.937254901960784,
    0.796078431372549,0.647058823529412,0.403921568627451
  };

  const Rcpp::NumericVector reds_green = {
    0.96078431372549,0.87843137254902,0.733333333333333,
    0.572549019607843,0.415686274509804,0.231372549019608,
    0.0941176470588235,0.0588235294117647,0
  };

  const Rcpp::NumericVector reds_blue = {
    0.941176470588235,0.823529411764706,0.631372549019608,
    0.447058823529412,0.290196078431373,0.172549019607843,
    0.113725490196078,0.0823529411764706,0.0509803921568627
  };

  // const Rcpp::List reds = Rcpp::List::create(
  //   _["r"] = reds_red,
  //   _["g"] = reds_green,
  //   _["b"] = reds_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
