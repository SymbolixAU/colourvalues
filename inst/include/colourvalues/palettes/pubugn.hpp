#ifndef R_COLOURVALUES_PUBUGN_H
#define R_COLOURVALUES_PUBUGN_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector pubugn_red = {
    1,0.925490196078431,0.815686274509804,
    0.650980392156863,0.403921568627451,0.211764705882353,
    0.00784313725490196,0.00392156862745098,0.00392156862745098
  };

  const Rcpp::NumericVector pubugn_green = {
    0.968627450980392,0.886274509803922,0.819607843137255,
    0.741176470588235,0.662745098039216,0.564705882352941,
    0.505882352941176,0.423529411764706,0.274509803921569
  };

  const Rcpp::NumericVector pubugn_blue = {
    0.984313725490196,0.941176470588235,0.901960784313726,
    0.858823529411765,0.811764705882353,0.752941176470588,
    0.541176470588235,0.349019607843137,0.211764705882353
  };

  // const Rcpp::List pubugn = Rcpp::List::create(
  //   _["r"] = pubugn_red,
  //   _["g"] = pubugn_green,
  //   _["b"] = pubugn_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
