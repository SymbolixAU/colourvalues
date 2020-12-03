#ifndef R_COLOURVALUES_PURD_H
#define R_COLOURVALUES_PURD_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector purd_red = {
    0.968627450980392,0.905882352941176,0.831372549019608,
    0.788235294117647,0.874509803921569,0.905882352941176,
    0.807843137254902,0.596078431372549,0.403921568627451
  };

  const Rcpp::NumericVector purd_green = {
    0.956862745098039,0.882352941176471,0.725490196078431,
    0.580392156862745,0.396078431372549,0.16078431372549,
    0.0705882352941176,0,0
  };

  const Rcpp::NumericVector purd_blue = {
    0.976470588235294,0.937254901960784,0.854901960784314,
    0.780392156862745,0.690196078431373,0.541176470588235,
    0.337254901960784,0.262745098039216,0.12156862745098
  };

  // const Rcpp::List purd = Rcpp::List::create(
  //   _["r"] = purd_red,
  //   _["g"] = purd_green,
  //   _["b"] = purd_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
