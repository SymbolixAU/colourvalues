#ifndef RCPP_VIRIDIS_COLOURS_H
#define RCPP_VIRIDIS_COLOURS_H

#include "RcppViridis/scale/scale.hpp"
#include "RcppViridis/utils/utils.hpp"
#include "RcppViridis/palette_utils/palette_utils.hpp"
#include "RcppViridis/convert_colours/convert_colours.hpp"

//[[Rcpp::depends(BH)]]
#include <boost/math/interpolators/cubic_b_spline.hpp>

#define ALPHA_PALETTE  0  // the alpha is on the palette
#define ALPHA_VECTOR   1  // the alpha is a variable / vector
#define ALPHA_CONSTANT 2  // the alpha is a constant

#endif
