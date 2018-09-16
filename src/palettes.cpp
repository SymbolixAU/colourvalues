#include <Rcpp.h>
#include "colourvalues/palettes.hpp"
using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_viridis() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::viridis_red,
    _["green"] = colourvalues::palette::viridis_green,
    _["blue"] = colourvalues::palette::viridis_blue
  );
}


// [[Rcpp::export]]
Rcpp::DataFrame rcpp_inferno() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::inferno_red,
    _["green"] = colourvalues::palette::inferno_green,
    _["blue"] = colourvalues::palette::inferno_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_magma() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::magma_red,
    _["green"] = colourvalues::palette::magma_green,
    _["blue"] = colourvalues::palette::magma_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_plasma() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::plasma_red,
    _["green"] = colourvalues::palette::plasma_green,
    _["blue"] = colourvalues::palette::plasma_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_cividis() {
  return Rcpp::DataFrame::create(
    _["red"] = colourvalues::palette::cividis_red,
    _["green"] = colourvalues::palette::cividis_green,
    _["blue"] = colourvalues::palette::cividis_blue
  );
}
