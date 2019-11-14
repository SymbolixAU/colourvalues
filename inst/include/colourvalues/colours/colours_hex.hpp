#ifndef R_COLOURVALUES_COLOURS_HEX_H
#define R_COLOURVALUES_COLOURS_HEX_H

#include <Rcpp.h>
#include "colourvalues/colours.hpp"
#include "colourvalues/utils/utils.hpp"
#include "colourvalues/alpha/alpha.hpp"
#include "colourvalues/summary/summary.hpp"
#include "colourvalues/format/format.hpp"
#include "colourvalues/colours/generate_colours.hpp"
#include "colourvalues/output/output.hpp"

namespace colourvalues {
namespace colours_hex {

  // if palette is a string; it's using in-built palettes; nothing to do
  // if palette is function or vectors, force rescaling

  inline SEXP colours_with_summary(
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
      bool& include_alpha
  ) {
    Rcpp::StringVector full_hex = colourvalues::generate_colours::colour_values_to_hex(
      full_values, red, green, blue, full_alpha, alpha_type, na_colour, include_alpha
    );
    Rcpp::StringVector summary_hex = colourvalues::generate_colours::colour_values_to_hex(
      summary, red, green, blue, summary_alpha, alpha_type, na_colour, include_alpha
    ); // uses full opacity

    return colourvalues::output::create_summary_output(full_hex, summary_values, summary_hex );
  }

  inline SEXP colours_with_summary(
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
      bool& include_alpha
  ) {

    Rcpp::StringVector full_hex = colourvalues::generate_colours::colour_values_to_hex(
      full_values, red, green, blue, full_alpha, alpha_type, na_colour, include_alpha
    );
    Rcpp::StringVector summary_hex = colourvalues::generate_colours::colour_values_to_hex(
      summary, red, green, blue, summary_alpha, alpha_type, na_colour, include_alpha
    ); // uses full opacity

    return colourvalues::output::create_summary_output(full_hex, summary_values, summary_hex );
  }




  inline SEXP colour_value_hex(
    Rcpp::NumericVector& x,
    Rcpp::NumericMatrix& palette,
    std::string& na_colour,
    bool include_alpha,
    std::string& format_type,
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
    Rcpp::NumericVector alpha( x.size(), 255.0 );

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue, alpha );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type );

    if ( n_summaries > 0 ) {
      Rcpp::NumericVector summary = colourvalues::summary::numeric_summary( x, n_summaries );
      SEXP summary_values = Rcpp::clone( summary );

      n_summaries = summary.size() < n_summaries ? summary.size() : n_summaries;

      if( format ) {
        summary_values = colourvalues::format::format_summary( summary_values, format_type, n_summaries, digits );
      }

      int n_alpha_summary = n_summaries < 5 ? 5 : n_summaries;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 255.0 );

      return colours_with_summary(
        x, summary, summary_values, red, green, blue, alpha_full, alpha_summary, alpha_type, na_colour, include_alpha
      );

    }

    return colourvalues::generate_colours::colour_values_to_hex( x, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha );
  }

// TODO remove when spatialwidget 0.3 is on CRAN
// this is so the old version can be installed
inline SEXP colour_value_hex(
    Rcpp::NumericVector& x,
    Rcpp::NumericMatrix& palette,
    std::string& na_colour,
    bool include_alpha,
    int n_summaries,
    bool format,
    std::string& format_type,
    int digits = 2
) {
  return colour_value_hex(
    x, palette, na_colour, include_alpha, format_type, n_summaries, format, digits
  );
}



  inline SEXP colour_value_hex(
      Rcpp::NumericVector& x,
      std::string& palette,
      std::string& na_colour,
      Rcpp::NumericVector& alpha,
      bool include_alpha,
      std::string& format_type,
      int n_summaries = 0,
      bool format = false,
      int digits = 2
   ) {

    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( alpha.size(), x_size, 0 );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type );

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
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 255.0 );

      return colours_with_summary(
        x, summary, summary_values, red, green, blue, alpha_full, alpha_summary, alpha_type, na_colour, include_alpha
      );

    }
    return colourvalues::generate_colours::colour_values_to_hex(x, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha);
  }


// TODO remove when spatialwidget 0.3 is on CRAN
// this is so the old version can be installed
inline SEXP colour_value_hex(
    Rcpp::NumericVector& x,
    std::string& palette,
    std::string& na_colour,
    Rcpp::NumericVector& alpha,
    bool include_alpha,
    int n_summaries,
    bool format,
    std::string& format_type,
    int digits = 2
) {
  return colour_value_hex(
    x, palette, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
  );
}



  inline SEXP colour_value_hex (
      Rcpp::StringVector& x,
      Rcpp::NumericMatrix& palette,
      std::string& na_colour,
      bool include_alpha,
      bool summary = false,
      int is_factor = false
  ) {

    colourvalues::utils::matrix_palette_check( palette );
    int alpha_type = colourvalues::alpha::make_alpha_type( 0, x.size(), palette.ncol() );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha(palette.nrow(), 255.0);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue, alpha );
    Rcpp::StringVector lvls = Rcpp::sort_unique( x ); // moved outside resolve so can use in a summary
    lvls = na_omit( lvls );
    Rcpp::NumericVector out_nv = colourvalues::utils::resolve_string_vector( x, lvls );

    if ( summary ) {
      Rcpp::IntegerVector summary_values = Rcpp::seq_len( lvls.length() );
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( summary_values );

      int red_size = red.size();
      int n_alpha_summary = red_size < 5 ? 5 : red_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 255.0 );

      return colours_with_summary(
        out_nv, nv, lvls, red, green, blue, alpha, alpha_summary, alpha_type, na_colour, include_alpha
      );
    }

    return colourvalues::generate_colours::colour_values_to_hex( out_nv, red, green, blue, alpha, alpha_type, na_colour, include_alpha );
  }

  inline SEXP colour_value_hex(
      Rcpp::StringVector& x,
      std::string& palette,
      std::string& na_colour,
      Rcpp::NumericVector& alpha,
      bool include_alpha,
      bool summary = false
  ) {

    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( alpha.size(), x_size, 0 );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue );

    Rcpp::StringVector lvls = Rcpp::sort_unique( x ); // moved outside resolve so can use in a summary;
    lvls = na_omit( lvls );
    Rcpp::NumericVector out_nv = colourvalues::utils::resolve_string_vector( x, lvls );

    if ( summary ) {
      Rcpp::IntegerVector summary_values = Rcpp::seq_len( lvls.length() );
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( summary_values );

      int x_size = x.size();
      int n_alpha_summary = x_size < 5 ? 5 : x_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 255.0 );

      return colours_with_summary(
        out_nv, nv, lvls, red, green, blue, alpha_full, alpha_summary, alpha_type, na_colour, include_alpha
      );
    }

    return colourvalues::generate_colours::colour_values_to_hex( out_nv, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha );
  }

  /*
   * i.e, factors
   */
  inline SEXP colour_value_hex(
      Rcpp::IntegerVector& x,
      Rcpp::StringVector lvls,
      Rcpp::NumericMatrix& palette,
      std::string& na_colour,
      bool include_alpha,
      bool summary = false
  ) {

    Rcpp::NumericVector x_nv = Rcpp::as< Rcpp::NumericVector >( x );
    colourvalues::utils::matrix_palette_check( palette );

    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( 0, x_size, palette.ncol() );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha( x.size(), 255.0 );

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue, alpha );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type );

    Rcpp::IntegerVector summary_values = Rcpp::sort_unique( x );
    Rcpp::NumericVector summary_numbers = Rcpp::as< Rcpp::NumericVector >( summary_values );

    if ( summary ) {
      int x_size = x.size();
      int n_alpha_summary = x_size < 5 ? 5 : x_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 255.0 );

      return colours_with_summary(
        x_nv, summary_numbers, lvls, red, green, blue, alpha_full, alpha_summary, alpha_type, na_colour, include_alpha
      );
    }

    return colourvalues::generate_colours::colour_values_to_hex( x_nv, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha );
  }

  /*
   * i.e, factors
   */
  inline SEXP colour_value_hex(
      Rcpp::IntegerVector& x,
      Rcpp::StringVector lvls,
      std::string& palette,
      std::string& na_colour,
      Rcpp::NumericVector& alpha,
      bool include_alpha,
      bool summary = false
  ) {

    Rcpp::NumericVector x_nv = Rcpp::as< Rcpp::NumericVector >( x );
    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( alpha.size(), x_size, 0 );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue );

    //Rcpp::Rcout << "x: " << x << std::endl;

    Rcpp::IntegerVector summary_values = Rcpp::sort_unique( x );
    //Rcpp::Rcout << "summary_values: " << summary_values << std::endl;
    Rcpp::NumericVector summary_numbers = Rcpp::as< Rcpp::NumericVector >( summary_values );

    if ( summary ) {
      int x_size = x.size();
      int n_alpha_summary = x_size < 5 ? 5 : x_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 255.0 );

      // Rcpp::Rcout << "x_nv: " << x_nv << std::endl;
      // Rcpp::Rcout << "summary_numbers: " << summary_numbers << std::endl;
      // Rcpp::Rcout << "lvls: " << lvls << std::endl;

      return colours_with_summary(
        x_nv, summary_numbers, lvls, red, green, blue, alpha_full, alpha_summary, alpha_type, na_colour, include_alpha
      );
    }

    return colourvalues::generate_colours::colour_values_to_hex( x_nv, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha );
  }

} // namespace colours
} // namespace colourvalues

#endif

