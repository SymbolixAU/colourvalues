#ifndef R_COLOURVALUES_RDYLBU_H
#define R_COLOURVALUES_RDYLBU_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector rdylbu_red = {
    0.647058823529412,
    0.843137254901961,
    0.956862745098039,
    0.992156862745098,
    0.996078431372549,
    1,
    0.87843137254902,
    0.670588235294118,
    0.454901960784314,
    0.270588235294118,
    0.192156862745098
  };

  const Rcpp::NumericVector rdylbu_green = {
    0,
    0.188235294117647,
    0.427450980392157,
    0.682352941176471,
    0.87843137254902,
    1,
    0.952941176470588,
    0.850980392156863,
    0.67843137254902,
    0.458823529411765,
    0.211764705882353
  };

  const Rcpp::NumericVector rdylbu_blue = {
    0.149019607843137,
    0.152941176470588,
    0.262745098039216,
    0.380392156862745,
    0.564705882352941,
    0.749019607843137,
    0.972549019607843,
    0.913725490196078,
    0.819607843137255,
    0.705882352941177,
    0.584313725490196
  };

const Rcpp::List rdylbu = Rcpp::List::create(
  _["r"] = rdylbu_red,
  _["g"] = rdylbu_green,
  _["b"] = rdylbu_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
