#ifndef R_COLOURVALUES_ORANGES_H
#define R_COLOURVALUES_ORANGES_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector oranges_red = {
    1,0.996078431372549,0.992156862745098,
    0.992156862745098,0.992156862745098,0.945098039215686,
    0.850980392156863,0.650980392156863,0.498039215686275
  };

  const Rcpp::NumericVector oranges_green = {
    0.96078431372549,0.901960784313726,0.815686274509804,
    0.682352941176471,0.552941176470588,0.411764705882353,
    0.282352941176471,0.211764705882353,0.152941176470588
  };

  const Rcpp::NumericVector oranges_blue = {
    0.92156862745098,0.807843137254902,0.635294117647059,
    0.419607843137255,0.235294117647059,0.0745098039215686,
    0.00392156862745098,0.0117647058823529,0.0156862745098039
  };

  // const Rcpp::List oranges = Rcpp::List::create(
  //   _["r"] = oranges_red,
  //   _["g"] = oranges_green,
  //   _["b"] = oranges_blue
  // );
} // namespace palette
} // namepsace colourvalues

#endif
