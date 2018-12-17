#ifndef R_COLOURVALUES_PUOR_H
#define R_COLOURVALUES_PUOR_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector puor_red = {
    0.498039215686275,
    0.701960784313725,
    0.87843137254902,
    0.992156862745098,
    0.996078431372549,
    0.968627450980392,
    0.847058823529412,
    0.698039215686274,
    0.501960784313725,
    0.329411764705882,
    0.176470588235294
  };

  const Rcpp::NumericVector puor_green = {
    0.231372549019608,
    0.345098039215686,
    0.509803921568627,
    0.72156862745098,
    0.87843137254902,
    0.968627450980392,
    0.854901960784314,
    0.670588235294118,
    0.450980392156863,
    0.152941176470588,
    0
  };

  const Rcpp::NumericVector puor_blue = {
    0.0313725490196078,
    0.0235294117647059,
    0.0784313725490196,
    0.388235294117647,
    0.713725490196078,
    0.968627450980392,
    0.92156862745098,
    0.823529411764706,
    0.674509803921569,
    0.533333333333333,
    0.294117647058824
  };

const Rcpp::List puor = Rcpp::List::create(
  _["r"] = puor_red,
  _["g"] = puor_green,
  _["b"] = puor_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
