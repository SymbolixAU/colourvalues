#ifndef R_COLOURVALUES_YLGNBU_H
#define R_COLOURVALUES_YLGNBU_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector ylgnbu_red = {
    1,0.929411764705882,0.780392156862745,
    0.498039215686275,0.254901960784314,0.113725490196078,
    0.133333333333333,0.145098039215686,0.0313725490196078
  };

  const Rcpp::NumericVector ylgnbu_green = {
    1,0.972549019607843,0.913725490196078,
    0.803921568627451,0.713725490196078,0.568627450980392,
    0.368627450980392,0.203921568627451,0.113725490196078
  };

  const Rcpp::NumericVector ylgnbu_blue = {
    0.850980392156863,0.694117647058824,0.705882352941177,
    0.733333333333333,0.768627450980392,0.752941176470588,
    0.658823529411765,0.580392156862745,0.345098039215686
  };

const Rcpp::List ylgnbu = Rcpp::List::create(
  _["r"] = ylgnbu_red,
  _["g"] = ylgnbu_green,
  _["b"] = ylgnbu_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
