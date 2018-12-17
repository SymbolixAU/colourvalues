#ifndef R_COLOURVALUES_GNBU_H
#define R_COLOURVALUES_GNBU_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector gnbu_red = {
    0.968627450980392,0.87843137254902,0.8,
    0.658823529411765,0.482352941176471,0.305882352941176,
    0.168627450980392,0.0313725490196078,0.0313725490196078
  };

  const Rcpp::NumericVector gnbu_green = {
    0.988235294117647,0.952941176470588,0.92156862745098,
    0.866666666666667,0.8,0.701960784313725,
    0.549019607843137,0.407843137254902,0.250980392156863
  };

  const Rcpp::NumericVector gnbu_blue = {
    0.941176470588235,0.858823529411765,0.772549019607843,
    0.709803921568627,0.768627450980392,0.827450980392157,
    0.745098039215686,0.674509803921569,0.505882352941176
  };

const Rcpp::List gnbu = Rcpp::List::create(
  _["r"] = gnbu_red,
  _["g"] = gnbu_green,
  _["b"] = gnbu_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
