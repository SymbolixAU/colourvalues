#ifndef R_COLOURVALUES_YLORRD_H
#define R_COLOURVALUES_YLORRD_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector ylorrd_red = {
    1.0,1.0,0.996078431372549,
    0.996078431372549,0.992156862745098,0.988235294117647,
    0.890196078431372,0.741176470588235,0.501960784313725
  };

  const Rcpp::NumericVector ylorrd_green = {
    1.0,0.929411764705882,0.850980392156863,
    0.698039215686274,0.552941176470588,0.305882352941176,
    0.101960784313725,0,0
  };

  const Rcpp::NumericVector ylorrd_blue = {
    0.8,0.627450980392157,0.462745098039216,
    0.298039215686275,0.235294117647059,0.164705882352941,
    0.109803921568627,0.149019607843137,0.149019607843137
  };

  // inline Rcpp::DataFrame ylorrd() {
  //   return Rcpp::DataFrame::create(
  //     _["r"] = ylorrd_red,
  //     _["g"] = ylorrd_green,
  //     _["b"] = ylorrd_blue
  //   );
  // }

} // namespace palette
} // namepsace colourvalues

#endif
