#ifndef R_COLOURVALUES_YLGN_H
#define R_COLOURVALUES_YLGN_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector ylgn_red = {
    1,0.968627450980392,0.850980392156863,
    0.67843137254902,0.470588235294118,0.254901960784314,
    0.137254901960784,0,0
  };

  const Rcpp::NumericVector ylgn_green = {
    1,0.988235294117647,0.941176470588235,
    0.866666666666667,0.776470588235294,0.670588235294118,
    0.517647058823529,0.407843137254902,0.270588235294118
  };

  const Rcpp::NumericVector ylgn_blue = {
    0.898039215686275,0.725490196078431,0.63921568627451,
    0.556862745098039,0.474509803921569,0.364705882352941,
    0.262745098039216,0.215686274509804,0.16078431372549
  };

  // const Rcpp::List ylgn = Rcpp::List::create(
  //   _["r"] = ylgn_red,
  //   _["g"] = ylgn_green,
  //   _["b"] = ylgn_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
