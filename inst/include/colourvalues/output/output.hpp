#ifndef R_COLOURVALUES_OUTPUT_H
#define R_COLOURVALUES_OUTPUT_H

#include <Rcpp.h>

namespace colourvalues {
namespace output {

  inline Rcpp::List create_summary_output(
      Rcpp::StringVector& full_hex,
      Rcpp::StringVector& summary_values,
      Rcpp::StringVector& summary_hex
  ) {
    return Rcpp::List::create(
      Rcpp::_["colours"] = full_hex,
      Rcpp::_["summary_values"] = summary_values,
      Rcpp::_["summary_colours"] = summary_hex
    );
  }

  inline Rcpp::List create_summary_output(
      Rcpp::StringVector& full_hex,
      SEXP& summary_values,
      Rcpp::StringVector& summary_hex
  ) {
    return Rcpp::List::create(
      Rcpp::_["colours"] = full_hex,
      Rcpp:: _["summary_values"] = summary_values,
      Rcpp::_["summary_colours"] = summary_hex
    );
  }

  inline Rcpp::List create_summary_output(
      Rcpp::NumericMatrix& full_rgb,
      Rcpp::StringVector& summary_values,
      Rcpp::NumericMatrix& summary_rgb
  ) {
    return Rcpp::List::create(
      Rcpp::_["colours"] = full_rgb,
      Rcpp::_["summary_values"] = summary_values,
      Rcpp::_["summary_colours"] = summary_rgb
    );
  }

  inline Rcpp::List create_summary_output(
      Rcpp::NumericMatrix& full_rgb,
      SEXP& summary_values,
      Rcpp::NumericMatrix& summary_rgb
  ) {
    return Rcpp::List::create(
      Rcpp::_["colours"] = full_rgb,
      Rcpp::_["summary_values"] = summary_values,
      Rcpp::_["summary_colours"] = summary_rgb
    );
  }

  inline Rcpp::List create_summary_output(
      Rcpp::IntegerVector& full_rgb,
      Rcpp::StringVector& summary_values,
      Rcpp::NumericMatrix& summary_rgb
  ) {
    return Rcpp::List::create(
      Rcpp::_["colours"] = full_rgb,
      Rcpp::_["summary_values"] = summary_values,
      Rcpp::_["summary_colours"] = summary_rgb
    );
  }

  inline Rcpp::List create_summary_output(
      Rcpp::IntegerVector& full_rgb,
      SEXP& summary_values,
      Rcpp::NumericMatrix& summary_rgb
  ) {
    return Rcpp::List::create(
      Rcpp::_["colours"] = full_rgb,
      Rcpp::_["summary_values"] = summary_values,
      Rcpp::_["summary_colours"] = summary_rgb
    );
  }

  inline Rcpp::List create_summary_output(
      Rcpp::NumericVector& full_rgb,
      Rcpp::StringVector& summary_values,
      Rcpp::NumericMatrix& summary_rgb
  ) {
    return Rcpp::List::create(
      Rcpp::_["colours"] = full_rgb,
      Rcpp::_["summary_values"] = summary_values,
      Rcpp::_["summary_colours"] = summary_rgb
    );
  }

  inline Rcpp::List create_summary_output(
      Rcpp::NumericVector& full_rgb,
      SEXP& summary_values,
      Rcpp::NumericMatrix& summary_rgb
  ) {
    return Rcpp::List::create(
      Rcpp::_["colours"] = full_rgb,
      Rcpp::_["summary_values"] = summary_values,
      Rcpp::_["summary_colours"] = summary_rgb
    );
  }

} // output
} // colourvalues

#endif
