#ifndef R_COLOURVALUES_PUBU_H
#define R_COLOURVALUES_PUBU_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector pubu_red = {
    1,0.925490196078431,0.815686274509804,
    0.650980392156863,0.454901960784314,0.211764705882353,
    0.0196078431372549,0.0156862745098039,0.00784313725490196
  };

  const Rcpp::NumericVector pubu_green = {
    0.968627450980392,0.905882352941176,0.819607843137255,
    0.741176470588235,0.662745098039216,0.564705882352941,
    0.43921568627451,0.352941176470588,0.219607843137255
  };

  const Rcpp::NumericVector pubu_blue = {
    0.984313725490196,0.949019607843137,0.901960784313726,
    0.858823529411765,0.811764705882353,0.752941176470588,
    0.690196078431373,0.552941176470588,0.345098039215686
  };

  // const Rcpp::List pubu = Rcpp::List::create(
  //   _["r"] = pubu_red,
  //   _["g"] = pubu_green,
  //   _["b"] = pubu_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
