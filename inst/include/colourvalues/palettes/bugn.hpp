#ifndef R_COLOURVALUES_BUGN_H
#define R_COLOURVALUES_BUGN_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector bugn_red = {
    0.968627450980392,0.898039215686275,0.8,
    0.6,0.4,0.254901960784314,
    0.137254901960784,0,0
  };

  const Rcpp::NumericVector bugn_green = {
    0.988235294117647,0.96078431372549,0.925490196078431,
    0.847058823529412,0.76078431372549,0.682352941176471,
    0.545098039215686,0.427450980392157,0.266666666666667
  };

  const Rcpp::NumericVector bugn_blue = {
    0.992156862745098,0.976470588235294,0.901960784313726,
    0.788235294117647,0.643137254901961,0.462745098039216,
    0.270588235294118,0.172549019607843,0.105882352941176
  };

  // inline Rcpp::DataFrame bugn() {
  //     Rcpp::List::create(
  //     _["r"] = bugn_red,
  //     _["g"] = bugn_green,
  //     _["b"] = bugn_blue
  //   );
  // }
} // namespace palette
} // namepsace colourvalues

#endif
