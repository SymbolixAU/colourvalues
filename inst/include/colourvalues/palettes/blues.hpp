#ifndef R_COLOURVALUES_BLUES_H
#define R_COLOURVALUES_BLUES_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector blues_red = {
    0.968627450980392,0.870588235294118,0.776470588235294,
    0.619607843137255,0.419607843137255,0.258823529411765,
    0.129411764705882,0.0313725490196078,0.0313725490196078
  };

  const Rcpp::NumericVector blues_green = {
    0.984313725490196,0.92156862745098,0.858823529411765,
    0.792156862745098,0.682352941176471,0.572549019607843,
    0.443137254901961,0.317647058823529,0.188235294117647
  };

  const Rcpp::NumericVector blues_blue = {
    1,0.968627450980392,0.937254901960784,
    0.882352941176471,0.83921568627451,0.776470588235294,
    0.709803921568627,0.611764705882353,0.419607843137255
  };

  // inline Rcpp::DataFrame blues() {
  //   return Rcpp::DataFrame::create(
  //     _["r"] = blues_red,
  //     _["g"] = blues_green,
  //     _["b"] = blues_blue
  //   );
  // }
} // namespace palette
} // namepsace colourvalues

#endif
