#ifndef R_COLOURVALUES_BRBG_H
#define R_COLOURVALUES_BRBG_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector brbg_red = {
    0.329411764705882,
    0.549019607843137,
    0.749019607843137,
    0.874509803921569,
    0.964705882352941,
    0.96078431372549,
    0.780392156862745,
    0.501960784313725,
    0.207843137254902,
    0.00392156862745098,
    0
  };

  const Rcpp::NumericVector brbg_green = {
    0.188235294117647,
    0.317647058823529,
    0.505882352941176,
    0.76078431372549,
    0.909803921568627,
    0.96078431372549,
    0.917647058823529,
    0.803921568627451,
    0.592156862745098,
    0.4,
    0.235294117647059
  };

  const Rcpp::NumericVector brbg_blue = {
    0.0196078431372549,
    0.0392156862745098,
    0.176470588235294,
    0.490196078431373,
    0.764705882352941,
    0.96078431372549,
    0.898039215686275,
    0.756862745098039,
    0.56078431372549,
    0.368627450980392,
    0.188235294117647
  };

const Rcpp::List brbg = Rcpp::List::create(
  _["r"] = brbg_red,
  _["g"] = brbg_green,
  _["b"] = brbg_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
