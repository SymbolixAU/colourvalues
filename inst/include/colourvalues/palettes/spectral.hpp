#ifndef R_COLOURVALUES_SPECTRAL_H
#define R_COLOURVALUES_SPECTRAL_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector spectral_red = {
    0.619607843137255,
    0.835294117647059,
    0.956862745098039,
    0.992156862745098,
    0.996078431372549,
    1,
    0.901960784313726,
    0.670588235294118,
    0.4,
    0.196078431372549,
    0.368627450980392
  };

  const Rcpp::NumericVector spectral_green = {
    0.00392156862745098,
    0.243137254901961,
    0.427450980392157,
    0.682352941176471,
    0.87843137254902,
    1,
    0.96078431372549,
    0.866666666666667,
    0.76078431372549,
    0.533333333333333,
    0.309803921568627
  };

  const Rcpp::NumericVector spectral_blue = {
    0.258823529411765,
    0.309803921568627,
    0.262745098039216,
    0.380392156862745,
    0.545098039215686,
    0.749019607843137,
    0.596078431372549,
    0.643137254901961,
    0.647058823529412,
    0.741176470588235,
    0.635294117647059
  };

  // const Rcpp::List spectral = Rcpp::List::create(
  //   _["r"] = spectral_red,
  //   _["g"] = spectral_green,
  //   _["b"] = spectral_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
