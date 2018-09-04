#ifndef RCPP_VIRIDIS_H
#define RCPP_VIRIDIS_H


#include <Rcpp.h>
using namespace Rcpp;

std::string ConvertRGBtoHex(int num);

std::string ConvertRGBtoHex(int r, int g, int b);

Rcpp::StringVector colour_variable_rgb( Rcpp::NumericVector x, std::string palette );

#endif
