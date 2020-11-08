#ifndef R_COLOURVALUES_COLOURS_RGB_INTERLEAVED_H
#define R_COLOURVALUES_COLOURS_RGB_INTERLEAVED_H

#include <Rcpp.h>
#include "colourvalues/colours.hpp"
#include "colourvalues/utils/utils.hpp"
#include "colourvalues/alpha/alpha.hpp"
#include "colourvalues/summary/summary.hpp"
#include "colourvalues/format/format.hpp"
#include "colourvalues/colours/generate_colours.hpp"
#include "colourvalues/output/output.hpp"

namespace colourvalues {
namespace colours_rgb_interleaved {

  inline SEXP colours_with_summary_interleaved(
      Rcpp::NumericVector& full_values,
      Rcpp::NumericVector& summary,
      Rcpp::StringVector& summary_values,
      Rcpp::NumericVector& red,
      Rcpp::NumericVector& green,
      Rcpp::NumericVector& blue,
      Rcpp::NumericVector& full_alpha,
      Rcpp::NumericVector& summary_alpha,
      int& alpha_type,
      std::string& na_colour,
      bool& include_alpha,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours
  ) {

    Rcpp::NumericVector full_rgb = colourvalues::generate_colours::colour_values_to_rgb_interleaved(
      full_values, red, green, blue, full_alpha, alpha_type, na_colour, include_alpha, repeats, total_colours
    );

    Rcpp::NumericMatrix summary_rgb = colourvalues::generate_colours::colour_values_to_rgb(
      summary, red, green, blue, summary_alpha, alpha_type, na_colour, include_alpha
    ); // uses full opacity

    return colourvalues::output::create_summary_output( full_rgb, summary_values, summary_rgb );
  }


  inline SEXP colours_with_summary_interleaved(
      Rcpp::NumericVector& full_values,
      Rcpp::NumericVector& summary,
      SEXP& summary_values,
      Rcpp::NumericVector& red,
      Rcpp::NumericVector& green,
      Rcpp::NumericVector& blue,
      Rcpp::NumericVector& full_alpha,
      Rcpp::NumericVector& summary_alpha,
      int& alpha_type,
      std::string& na_colour,
      bool& include_alpha,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours
  ) {

    Rcpp::NumericVector full_rgb = colourvalues::generate_colours::colour_values_to_rgb_interleaved(
      full_values, red, green, blue, full_alpha, alpha_type, na_colour, include_alpha, repeats, total_colours
    );

    Rcpp::NumericMatrix summary_rgb = colourvalues::generate_colours::colour_values_to_rgb(
      summary, red, green, blue, summary_alpha, alpha_type, na_colour, include_alpha
    ); // uses full opacity

    return colourvalues::output::create_summary_output(full_rgb, summary_values, summary_rgb );
  }

  // in this function the colour vectors will already be scaled [0,1]
  inline SEXP colour_value_rgb_interleaved(
      Rcpp::NumericVector& x,
      Rcpp::NumericMatrix& palette,
      std::string& na_colour,
      bool include_alpha,
      std::string& format_type,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      int n_summaries = 0,
      bool format = false,
      int digits = 2
  ) {

    colourvalues::utils::matrix_palette_check( palette );
    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( 0, x_size, palette.ncol() );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha(x.size(), 1.0);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue, alpha );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type, true );

    if ( n_summaries > 0 ) {
      Rcpp::NumericVector summary = colourvalues::summary::numeric_summary( x, n_summaries );
      SEXP summary_values = Rcpp::clone( summary );

      n_summaries = summary.size() < n_summaries ? summary.size() : n_summaries;

      if( format ) {
        summary_values = colourvalues::format::format_summary( summary_values, format_type, n_summaries, digits );
      }

      int n_alpha_summary = n_summaries < 5 ? 5 : n_summaries;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 1.0 );

      return colours_with_summary_interleaved(
        x, summary, summary_values, red, green, blue, alpha_full, alpha_summary,
        alpha_type, na_colour, include_alpha, repeats, total_colours
      );
    }

    return colourvalues::generate_colours::colour_values_to_rgb_interleaved(
      x, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha, repeats, total_colours
      );
  }

  inline SEXP colour_value_rgb_interleaved(
      Rcpp::NumericVector& x,
      std::string& palette,
      std::string& na_colour,
      Rcpp::NumericVector& alpha,
      bool include_alpha,
      std::string& format_type,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      int n_summaries = 0,
      bool format = false,
      int digits = 2
  ) {

    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( alpha.size(), x_size, 0 );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type, true );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue );

    if ( n_summaries > 0 ) {
      Rcpp::NumericVector summary = colourvalues::summary::numeric_summary( x, n_summaries );
      SEXP summary_values = Rcpp::clone( summary );

      n_summaries = summary.size() < n_summaries ? summary.size() : n_summaries;

      if( format ) {
        summary_values = colourvalues::format::format_summary( summary_values, format_type, n_summaries, digits );
      }

      int n_alpha_summary = n_summaries < 5 ? 5 : n_summaries;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 1.0 );

      return colours_with_summary_interleaved(
        x, summary, summary_values, red, green, blue, alpha_full, alpha_summary,
        alpha_type, na_colour, include_alpha, repeats, total_colours
      );
    }

    return colourvalues::generate_colours::colour_values_to_rgb_interleaved(
      x, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha, repeats, total_colours
      );
  }

  inline SEXP colour_value_rgb_interleaved(
      Rcpp::StringVector& x,
      Rcpp::NumericMatrix& palette,
      std::string& na_colour,
      bool include_alpha,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      bool summary = false
  ) {

    colourvalues::utils::matrix_palette_check( palette );
    int alpha_type = colourvalues::alpha::make_alpha_type( 0, x.size(), palette.ncol() );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha(palette.nrow(), 1.0);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue, alpha );
    Rcpp::StringVector lvls = Rcpp::sort_unique( x ); // moved outside resolve so can use in a legend
    Rcpp::NumericVector out_nv = colourvalues::utils::resolve_string_vector( x, lvls );

    if ( summary ) {
      Rcpp::IntegerVector summary_values = Rcpp::seq_len( lvls.length() );
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( summary_values );

      int red_size = red.size();
      int n_alpha_summary = red_size < 5 ? 5 : red_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 1.0 );

      return colours_with_summary_interleaved(
        out_nv, nv, lvls, red, green, blue, alpha, alpha_summary, alpha_type,
        na_colour, include_alpha, repeats, total_colours
      );
    }

    return colourvalues::generate_colours::colour_values_to_rgb_interleaved(
      out_nv, red, green, blue, alpha, alpha_type, na_colour, include_alpha, repeats, total_colours
      );
  }

  inline SEXP colour_value_rgb_interleaved(
      Rcpp::StringVector& x,
      std::string& palette,
      std::string& na_colour,
      Rcpp::NumericVector& alpha,
      bool include_alpha,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      bool summary = false
  ) {

    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( alpha.size(), x_size, 0 );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type, true );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue );
    Rcpp::StringVector lvls = Rcpp::sort_unique( x ); // moved outside resolve so can use in a legend
    Rcpp::NumericVector out_nv = colourvalues::utils::resolve_string_vector( x, lvls );

    if ( summary ) {
      Rcpp::IntegerVector summary_values = Rcpp::seq_len( lvls.length() );
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( summary_values );

      int x_size = x.size();
      int n_alpha_summary = x_size < 5 ? 5 : x_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 1.0 );

      return colours_with_summary_interleaved(
        out_nv, nv, lvls, red, green, blue, alpha_full, alpha_summary, alpha_type,
        na_colour, include_alpha, repeats, total_colours
      );
    }

    return colourvalues::generate_colours::colour_values_to_rgb_interleaved(
      out_nv, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha,
      repeats, total_colours
      );
  }

  /*
   * i.e, factors
   */
  inline SEXP colour_value_rgb_interleaved(
      Rcpp::IntegerVector& x,
      Rcpp::StringVector lvls,
      Rcpp::NumericMatrix& palette,
      std::string& na_colour,
      bool include_alpha,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      bool summary = false
  ) {

    Rcpp::NumericVector x_nv = Rcpp::as< Rcpp::NumericVector >( x );
    colourvalues::utils::matrix_palette_check( palette );

    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( 0, x_size, palette.ncol() );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha( x.size(), 1.0 );

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue, alpha );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type, true );

    Rcpp::IntegerVector summary_values = Rcpp::sort_unique( x );
    Rcpp::NumericVector summary_numbers = Rcpp::as< Rcpp::NumericVector >( summary_values );

    if ( summary ) {
      int x_size = x.size();
      int n_alpha_summary = x_size < 5 ? 5 : x_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 1.0 );

      return colours_with_summary_interleaved(
        x_nv, summary_numbers, lvls, red, green, blue, alpha_full, alpha_summary,
        alpha_type, na_colour, include_alpha, repeats, total_colours
      );
    }

    return colourvalues::generate_colours::colour_values_to_rgb_interleaved(
      x_nv, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha,
      repeats, total_colours
      );
  }

  /*
   * i.e, factors
   */
  inline SEXP colour_value_rgb_interleaved(
      Rcpp::IntegerVector& x,
      Rcpp::StringVector lvls,
      std::string& palette,
      std::string& na_colour,
      Rcpp::NumericVector& alpha,
      bool include_alpha,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      bool summary = false
  ) {

    Rcpp::NumericVector x_nv = Rcpp::as< Rcpp::NumericVector >( x );
    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( alpha.size(), x_size, 0 );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type, true );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue );

    Rcpp::IntegerVector summary_values = Rcpp::sort_unique( x );
    Rcpp::NumericVector summary_numbers = Rcpp::as< Rcpp::NumericVector >( summary_values );

    if ( summary ) {
      int x_size = x.size();
      int n_alpha_summary = x_size < 5 ? 5 : x_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 1.0 );

      return colours_with_summary_interleaved(
        x_nv, summary_numbers, lvls, red, green, blue, alpha_full, alpha_summary,
        alpha_type, na_colour, include_alpha, repeats, total_colours
      );
    }

    return colourvalues::generate_colours::colour_values_to_rgb_interleaved(
      x_nv, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha,
      repeats, total_colours
      );
  }

} // namespace colours
} // namespace colourvalues

#endif

