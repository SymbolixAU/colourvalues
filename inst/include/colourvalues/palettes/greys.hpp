#ifndef R_COLOURVALUES_GREYS_H
#define R_COLOURVALUES_GREYS_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector greys_red = {
    1,0.941176470588235,0.850980392156863,
    0.741176470588235,0.588235294117647,0.450980392156863,
    0.32156862745098,0.145098039215686,0
  };

  const Rcpp::NumericVector greys_green = {
    1,0.941176470588235,0.850980392156863,
    0.741176470588235,0.588235294117647,0.450980392156863,
    0.32156862745098,0.145098039215686,0
  };

  const Rcpp::NumericVector greys_blue = {
    1,0.941176470588235,0.850980392156863,
    0.741176470588235,0.588235294117647,0.450980392156863,
    0.32156862745098,0.145098039215686,0
  };

const Rcpp::List greys = Rcpp::List::create(
  _["r"] = greys_red,
  _["g"] = greys_green,
  _["b"] = greys_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
