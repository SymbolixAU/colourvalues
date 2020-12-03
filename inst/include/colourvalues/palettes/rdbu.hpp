#ifndef R_COLOURVALUES_RDBU_H
#define R_COLOURVALUES_RDBU_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector rdbu_red = {
    0.403921568627451,
    0.698039215686274,
    0.83921568627451,
    0.956862745098039,
    0.992156862745098,
    0.968627450980392,
    0.819607843137255,
    0.572549019607843,
    0.262745098039216,
    0.129411764705882,
    0.0196078431372549
  };

  const Rcpp::NumericVector rdbu_green = {
    0,
    0.0941176470588235,
    0.376470588235294,
    0.647058823529412,
    0.858823529411765,
    0.968627450980392,
    0.898039215686275,
    0.772549019607843,
    0.576470588235294,
    0.4,
    0.188235294117647
  };

  const Rcpp::NumericVector rdbu_blue = {
    0.12156862745098,
    0.168627450980392,
    0.301960784313725,
    0.509803921568627,
    0.780392156862745,
    0.968627450980392,
    0.941176470588235,
    0.870588235294118,
    0.764705882352941,
    0.674509803921569,
    0.380392156862745
  };

  // const Rcpp::List rdbu = Rcpp::List::create(
  //   _["r"] = rdbu_red,
  //   _["g"] = rdbu_green,
  //   _["b"] = rdbu_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
