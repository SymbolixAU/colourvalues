#ifndef R_COLOURVALUES_RDYLGN_H
#define R_COLOURVALUES_RDYLGN_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector rdylgn_red = {
    0.647058823529412,
    0.843137254901961,
    0.956862745098039,
    0.992156862745098,
    0.996078431372549,
    1,
    0.850980392156863,
    0.650980392156863,
    0.4,
    0.101960784313725,
    0
  };

  const Rcpp::NumericVector rdylgn_green = {
    0,
    0.188235294117647,
    0.427450980392157,
    0.682352941176471,
    0.87843137254902,
    1,
    0.937254901960784,
    0.850980392156863,
    0.741176470588235,
    0.596078431372549,
    0.407843137254902
  };

  const Rcpp::NumericVector rdylgn_blue = {
    0.149019607843137,
    0.152941176470588,
    0.262745098039216,
    0.380392156862745,
    0.545098039215686,
    0.749019607843137,
    0.545098039215686,
    0.415686274509804,
    0.388235294117647,
    0.313725490196078,
    0.215686274509804
  };

  // const Rcpp::List rdylgn = Rcpp::List::create(
  //   _["r"] = rdylgn_red,
  //   _["g"] = rdylgn_green,
  //   _["b"] = rdylgn_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
