#ifndef R_COLOURVALUES_PIYG_H
#define R_COLOURVALUES_PIYG_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector piyg_red = {
    0.556862745098039,
    0.772549019607843,
    0.870588235294118,
    0.945098039215686,
    0.992156862745098,
    0.968627450980392,
    0.901960784313726,
    0.72156862745098,
    0.498039215686275,
    0.301960784313725,
    0.152941176470588
  };

  const Rcpp::NumericVector piyg_green = {
    0.00392156862745098,
    0.105882352941176,
    0.466666666666667,
    0.713725490196078,
    0.87843137254902,
    0.968627450980392,
    0.96078431372549,
    0.882352941176471,
    0.737254901960784,
    0.572549019607843,
    0.392156862745098
  };

  const Rcpp::NumericVector piyg_blue = {
    0.32156862745098,
    0.490196078431373,
    0.682352941176471,
    0.854901960784314,
    0.937254901960784,
    0.968627450980392,
    0.815686274509804,
    0.525490196078431,
    0.254901960784314,
    0.129411764705882,
    0.0980392156862745
  };

const Rcpp::List piyg = Rcpp::List::create(
  _["r"] = piyg_red,
  _["g"] = piyg_green,
  _["b"] = piyg_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
