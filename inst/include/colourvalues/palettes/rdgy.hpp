#ifndef R_COLOURVALUES_RDGY_H
#define R_COLOURVALUES_RDGY_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector rdgy_red = {
    0.403921568627451,
    0.698039215686274,
    0.83921568627451,
    0.956862745098039,
    0.992156862745098,
    1,
    0.87843137254902,
    0.729411764705882,
    0.529411764705882,
    0.301960784313725,
    0.101960784313725
  };

  const Rcpp::NumericVector rdgy_green = {
    0,
    0.0941176470588235,
    0.376470588235294,
    0.647058823529412,
    0.858823529411765,
    1,
    0.87843137254902,
    0.729411764705882,
    0.529411764705882,
    0.301960784313725,
    0.101960784313725
  };

  const Rcpp::NumericVector rdgy_blue = {
    0.12156862745098,
    0.168627450980392,
    0.301960784313725,
    0.509803921568627,
    0.780392156862745,
    1,
    0.87843137254902,
    0.729411764705882,
    0.529411764705882,
    0.301960784313725,
    0.101960784313725
  };

  // const Rcpp::List rdgy = Rcpp::List::create(
  //   _["r"] = rdgy_red,
  //   _["g"] = rdgy_green,
  //   _["b"] = rdgy_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
