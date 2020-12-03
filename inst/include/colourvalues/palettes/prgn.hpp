#ifndef R_COLOURVALUES_PRGN_H
#define R_COLOURVALUES_PRGN_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector prgn_red = {
    0.250980392156863,
    0.462745098039216,
    0.6,
    0.76078431372549,
    0.905882352941176,
    0.968627450980392,
    0.850980392156863,
    0.650980392156863,
    0.352941176470588,
    0.105882352941176,
    0
  };

  const Rcpp::NumericVector prgn_green = {
    0,
    0.164705882352941,
    0.43921568627451,
    0.647058823529412,
    0.831372549019608,
    0.968627450980392,
    0.941176470588235,
    0.858823529411765,
    0.682352941176471,
    0.470588235294118,
    0.266666666666667
  };

  const Rcpp::NumericVector prgn_blue = {
    0.294117647058824,
    0.513725490196078,
    0.670588235294118,
    0.811764705882353,
    0.909803921568627,
    0.968627450980392,
    0.827450980392157,
    0.627450980392157,
    0.380392156862745,
    0.215686274509804,
    0.105882352941176
  };

  // const Rcpp::List prgn = Rcpp::List::create(
  //   _["r"] = prgn_red,
  //   _["g"] = prgn_green,
  //   _["b"] = prgn_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
