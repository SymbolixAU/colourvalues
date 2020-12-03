#ifndef R_COLOURVALUES_PURPLES_H
#define R_COLOURVALUES_PURPLES_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector purples_red = {
    0.988235294117647,0.937254901960784,0.854901960784314,
    0.737254901960784,0.619607843137255,0.501960784313725,
    0.415686274509804,0.329411764705882,0.247058823529412
  };

  const Rcpp::NumericVector purples_green = {
    0.984313725490196,0.929411764705882,0.854901960784314,
    0.741176470588235,0.603921568627451,0.490196078431373,
    0.317647058823529,0.152941176470588,0
  };

  const Rcpp::NumericVector purples_blue = {
    0.992156862745098,0.96078431372549,0.92156862745098,
    0.862745098039216,0.784313725490196,0.729411764705882,
    0.63921568627451,0.56078431372549,0.490196078431373
  };

  // const Rcpp::List purples = Rcpp::List::create(
  //   _["r"] = purples_red,
  //   _["g"] = purples_green,
  //   _["b"] = purples_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
