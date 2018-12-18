#ifndef R_COLOURVALUES_GREENS_H
#define R_COLOURVALUES_GREENS_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector greens_red = {
    0.968627450980392,0.898039215686275,0.780392156862745,
    0.631372549019608,0.454901960784314,0.254901960784314,
    0.137254901960784,0,0
  };

  const Rcpp::NumericVector greens_green = {
    0.988235294117647,0.96078431372549,0.913725490196078,
    0.850980392156863,0.768627450980392,0.670588235294118,
    0.545098039215686,0.427450980392157,0.266666666666667
  };

  const Rcpp::NumericVector greens_blue = {
    0.96078431372549,0.87843137254902,0.752941176470588,
    0.607843137254902,0.462745098039216,0.364705882352941,
    0.270588235294118,0.172549019607843,0.105882352941176
  };

const Rcpp::List greens = Rcpp::List::create(
  _["r"] = greens_red,
  _["g"] = greens_green,
  _["b"] = greens_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
