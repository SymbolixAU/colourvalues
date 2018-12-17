#ifndef R_COLOURVALUES_BUPU_H
#define R_COLOURVALUES_BUPU_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector bupu_red = {
    0.968627450980392,0.87843137254902,0.749019607843137,
    0.619607843137255,0.549019607843137,0.549019607843137,
    0.533333333333333,0.505882352941176,0.301960784313725
  };

  const Rcpp::NumericVector bupu_green = {
    0.988235294117647,0.925490196078431,0.827450980392157,
    0.737254901960784,0.588235294117647,0.419607843137255,
    0.254901960784314,0.0588235294117647,0
  };

  const Rcpp::NumericVector bupu_blue = {
    0.992156862745098,0.956862745098039,0.901960784313726,
    0.854901960784314,0.776470588235294,0.694117647058824,
    0.615686274509804,0.486274509803922,0.294117647058824
  };

const Rcpp::List bupu = Rcpp::List::create(
  _["r"] = bupu_red,
  _["g"] = bupu_green,
  _["b"] = bupu_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
