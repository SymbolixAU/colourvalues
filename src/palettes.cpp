#include <Rcpp.h>
#include "RcppViridis/palettes.hpp"
using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_viridis() {
  return Rcpp::DataFrame::create(
    _["red"] = rcppviridis::palette::viridis_red,
    _["green"] = rcppviridis::palette::viridis_green,
    _["blue"] = rcppviridis::palette::viridis_blue
  );
}


// [[Rcpp::export]]
Rcpp::DataFrame rcpp_inferno() {
  return Rcpp::DataFrame::create(
    _["red"] = rcppviridis::palette::inferno_red,
    _["green"] = rcppviridis::palette::inferno_green,
    _["blue"] = rcppviridis::palette::inferno_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_magma() {
  return Rcpp::DataFrame::create(
    _["red"] = rcppviridis::palette::magma_red,
    _["green"] = rcppviridis::palette::magma_green,
    _["blue"] = rcppviridis::palette::magma_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_plasma() {
  return Rcpp::DataFrame::create(
    _["red"] = rcppviridis::palette::plasma_red,
    _["green"] = rcppviridis::palette::plasma_green,
    _["blue"] = rcppviridis::palette::plasma_blue
  );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_cividis() {
  return Rcpp::DataFrame::create(
    _["red"] = rcppviridis::palette::cividis_red,
    _["green"] = rcppviridis::palette::cividis_green,
    _["blue"] = rcppviridis::palette::cividis_blue
  );
}
