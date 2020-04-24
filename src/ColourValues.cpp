#include <Rcpp.h>

#include "colourvalues/api/api.hpp"

// [[Rcpp::export]]
SEXP rcpp_colour_values_hex(
    SEXP x,
    SEXP palette,
    Rcpp::NumericVector& alpha,
    std::string na_colour = "#808080",
    bool include_alpha = true,
    bool format = false,
    int digits = 2,
    bool summary = false,
    int n_summaries = 0
  ) {
  return colourvalues::api::colour_values_hex(
    x, palette, alpha, na_colour, include_alpha, format, digits, summary, n_summaries
  );
}


// [[Rcpp::export]]
SEXP rcpp_colour_values_rgb(
    SEXP x,
    SEXP palette,
    Rcpp::NumericVector& alpha,
    std::string na_colour = "#808080",
    bool include_alpha = true,
    bool format = false,
    int digits = 2,
    bool summary = false,
    int n_summaries = 0
) {

  return colourvalues::api::colour_values_rgb(
    x, palette, alpha, na_colour, include_alpha, format, digits, summary, n_summaries
  );
}

// [[Rcpp::export]]
SEXP rcpp_colour_values_rgb_interleaved(
    SEXP x,
    SEXP palette,
    Rcpp::NumericVector& alpha,
    Rcpp::IntegerVector& repeats,
    R_xlen_t& total_colours,
    std::string na_colour = "#808080",
    bool include_alpha = true,
    bool format = false,
    int digits = 2,
    bool summary = false,
    int n_summaries = 0
) {

  return colourvalues::api::colour_values_rgb_interleaved(
    x, palette, alpha, repeats, total_colours, na_colour, include_alpha, format, digits, summary, n_summaries
  );
}
