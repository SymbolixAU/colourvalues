#ifndef R_COLOURVALUES_YLORBR_H
#define R_COLOURVALUES_YLORBR_H

#include <Rcpp.h>
using namespace Rcpp;

namespace colourvalues {
namespace palette {

  const Rcpp::NumericVector ylorbr_red = {
    1,1,0.996078431372549,
    0.996078431372549,0.996078431372549,0.925490196078431,
    0.8,0.6,0.4
  };

  const Rcpp::NumericVector ylorbr_green = {
    1,0.968627450980392,0.890196078431372,
    0.768627450980392,0.6,0.43921568627451,
    0.298039215686275,0.203921568627451,0.145098039215686
  };

  const Rcpp::NumericVector ylorbr_blue = {
    0.898039215686275,0.737254901960784,0.568627450980392,
    0.309803921568627,0.16078431372549,0.0784313725490196,
    0.00784313725490196,0.0156862745098039,0.0235294117647059
  };

const Rcpp::List ylorbr = Rcpp::List::create(
  _["r"] = ylorbr_red,
  _["g"] = ylorbr_green,
  _["b"] = ylorbr_blue
);
} // namespace palette
} // namepsace colourvalues

#endif
