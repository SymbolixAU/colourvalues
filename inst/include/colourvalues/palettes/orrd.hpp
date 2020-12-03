#ifndef R_COLOURVALUES_ORRD_H
#define R_COLOURVALUES_ORRD_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector orrd_red = {
    1,0.996078431372549,0.992156862745098,
    0.992156862745098,0.988235294117647,0.937254901960784,
    0.843137254901961,0.701960784313725,0.498039215686275
  };

  const Rcpp::NumericVector orrd_green = {
    0.968627450980392,0.909803921568627,0.831372549019608,
    0.733333333333333,0.552941176470588,0.396078431372549,
    0.188235294117647,0,0
  };

  const Rcpp::NumericVector orrd_blue = {
    0.925490196078431,0.784313725490196,0.619607843137255,
    0.517647058823529,0.349019607843137,0.282352941176471,
    0.12156862745098,0,0
  };

  // const Rcpp::List orrd = Rcpp::List::create(
  //   _["r"] = orrd_red,
  //   _["g"] = orrd_green,
  //   _["b"] = orrd_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
