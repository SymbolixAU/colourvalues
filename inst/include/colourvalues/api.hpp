#include <Rcpp.h>

#include "colourvalues/colours/colours_hex.hpp"
#include "colourvalues/colours/colours_rgb.hpp"

namespace colourvalues {
namespace api {

  /*
   * when palette is unknown, but vector is numeric
   */
  inline SEXP colour_values_hex(
    Rcpp::NumericVector& x,
    SEXP palette,
    Rcpp::NumericVector& alpha,
    std::string& na_colour,
    bool include_alpha = true,
    bool format = false,
    std::string format_type = "numeric",
    int digits = 2,
    int n_summaries = 0
  ) {

    switch( TYPEOF( palette ) ) {
      // STringVector - needs to get std::string
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
      Rcpp::String s = sv[0];
      std::string pal = s;
      return colourvalues::colours_hex::colour_value_hex(
        x, pal, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits
      );
    }
    case INTSXP: {}
    case REALSXP: {
      if( !Rf_isMatrix( palette ) ) {
        Rcpp::stop("Unknown palette type - expecting a matrix");
      }
      Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
      return colourvalues::colours_hex::colour_value_hex(
        x, pal, na_colour, include_alpha, n_summaries, format, format_type, digits
      );
    }
    default: {
      Rcpp::stop("Unknown palette type");
    }
    }

  }

  /*
   * When palette is unknown, but vector is string
   */
  inline SEXP colour_values_hex(
      Rcpp::StringVector& x,
      SEXP palette,
      Rcpp::NumericVector& alpha,
      std::string na_colour = "#808080",
      bool include_alpha = true,
      bool format = false,
      std::string format_type = "numeric",
      int digits = 2,
      bool summary = false
  ) {
    switch( TYPEOF( palette ) ) {
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
      Rcpp::String s = sv[0];
      std::string pal = s;
      return colourvalues::colours_hex::colour_value_hex(
        x, pal, na_colour, alpha, include_alpha, summary
      );
    }
    case INTSXP: {}
    case REALSXP: {
      if( !Rf_isMatrix( palette ) ) {
      Rcpp::stop("Unknown palette type - expecting a matrix");
    }
      Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
      return colourvalues::colours_hex::colour_value_hex(
        x, pal, na_colour, alpha, summary
      );
    }
    default: {
      Rcpp::stop("Unknown palette type");
    }
    }

  }

  /*
   * When the palette is a matrix, but vector is unknown
   */
  inline SEXP colour_values_hex(
      SEXP x,
      Rcpp::NumericMatrix& palette,
      Rcpp::NumericVector& alpha,
      std::string na_colour = "#808080",
      bool include_alpha = true,
      bool format = false,
      std::string format_type = "numeric",
      int digits = 2,
      bool summary = false,
      int n_summaries = 0
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {}
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return colourvalues::colours_hex::colour_value_hex(
        nv, palette, na_colour, include_alpha, n_summaries, format, format_type, digits
      );
    }
    case VECSXP: { // list
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      // TODO list

    }
    case LGLSXP: {} // as.character
    default: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
      return colourvalues::colours_hex::colour_value_hex(
        sv, palette, na_colour, alpha, summary
      );
    }
    }

  }

  /*
   * When the palette is a string, but vector is unknown
   */
  inline SEXP colour_values_hex(
      SEXP x,
      Rcpp::StringVector& palette,
      Rcpp::NumericVector& alpha,
      std::string na_colour = "#808080",
      bool include_alpha = true,
      bool format = false,
      std::string format_type = "numeric",
      int digits = 2,
      bool summary = false,
      int n_summaries = 0
  ) {

    Rcpp::String p = palette[0];
    std::string pal = p;
    switch( TYPEOF( x ) ) {
    case INTSXP: {}
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return colourvalues::colours_hex::colour_value_hex(
        nv, pal, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits
      );
    }
    case VECSXP: { // list
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );

    }
    case LGLSXP: {} // as.character
    default: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
      return colourvalues::colours_hex::colour_value_hex(
        sv, pal, na_colour, alpha, include_alpha, summary
      );
    }
    }

    Rcpp::StringVector sv;
    return sv; // never reaches
  }

  /*
   * When neither type of vector/list or palette is known
   */
  inline SEXP colour_values_hex(
      SEXP x,
      SEXP palette,
      Rcpp::NumericVector& alpha,
      std::string na_colour = "#808080",
      bool include_alpha = true,
      bool format = false,
      std::string format_type = "numeric",
      int digits = 2,
      bool summary = false,
      int n_summaries = 0
  ) {

    switch( TYPEOF( palette ) ) {
    case INTSXP: {}
    case REALSXP: {
      Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
      return colour_values_hex(
        x, pal, alpha, na_colour, include_alpha, format, format_type, digits, summary, n_summaries
      );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
//      Rcpp::String s = sv[0];
//      std::string pal = s;
      return colour_values_hex(
        x, sv, alpha, na_colour, include_alpha, format, format_type, digits, summary, n_summaries
      );
      break;
    }
    default: {
      Rcpp::stop("Unknown palette type");
    }
    }

    Rcpp::StringVector sv;
    return sv; // never reaches

  }


} // api
} // colourvalues
