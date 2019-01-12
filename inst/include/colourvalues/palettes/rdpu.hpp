#ifndef R_COLOURVALUES_RDPU_H
#define R_COLOURVALUES_RDPU_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector rdpu_red = {
    1,0.992156862745098,0.988235294117647,
    0.980392156862745,0.968627450980392,0.866666666666667,
    0.682352941176471,0.47843137254902,0.286274509803922
  };

  const Rcpp::NumericVector rdpu_green = {
    0.968627450980392,0.87843137254902,0.772549019607843,
    0.623529411764706,0.407843137254902,0.203921568627451,
    0.00392156862745098,0.00392156862745098,0
  };

  const Rcpp::NumericVector rdpu_blue = {
    0.952941176470588,0.866666666666667,0.752941176470588,
    0.709803921568627,0.631372549019608,0.592156862745098,
    0.494117647058824,0.466666666666667,0.415686274509804
  };

const Rcpp::List rdpu = Rcpp::List::create(
  _["r"] = rdpu_red,
  _["g"] = rdpu_green,
  _["b"] = rdpu_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
