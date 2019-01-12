#ifndef R_COLOURVALUES_COLOURS_HEX_H
#define R_COLOURVALUES_COLOURS_HEX_H

#include <Rcpp.h>
#include "colourvalues/colours.hpp"
#include "colourvalues/utils/utils.hpp"
#include "colourvalues/alpha/alpha.hpp"
#include "colourvalues/summary/summary.hpp"
#include "colourvalues/format/format.hpp"

namespace colourvalues {
namespace colours_hex {

  // if palette is a string; it's using in-built palettes; nothing to do
  // if palette is function or vectors, force rescaling

  inline Rcpp::StringVector colour_values_to_hex(
      Rcpp::NumericVector& x,
      Rcpp::NumericVector& red,
      Rcpp::NumericVector& green,
      Rcpp::NumericVector& blue,
      Rcpp::NumericVector& alpha,
      int& alpha_type,
      std::string& na_colour,
      bool& include_alpha) {

    int n = x.size();
    double colours = red.size();

    na_colour = na_colour.length() == 9 ? na_colour : na_colour + "FF";

    colourvalues::scale::rescale( x );
    Rcpp::StringVector hex_strings( n );
    double step = 1 / ( colours - 1 );  // TODO(test)

    // cublic_b_spoine :: vec.start, vec.end, start.time, step
    boost::math::cubic_b_spline< double > spline_red(   red.begin(),   red.end(),   0, step );
    boost::math::cubic_b_spline< double > spline_green( green.begin(), green.end(), 0, step );
    boost::math::cubic_b_spline< double > spline_blue(  blue.begin(),  blue.end(),  0, step );
    boost::math::cubic_b_spline< double > spline_alpha(  alpha.begin(),  alpha.end(),  0, step );

    double this_x;
    int i, r, g, b;
    std::string hex_str;

    for( i = 0; i < n; i++ ) {

      this_x = x[i];

      if ( R_IsNA( this_x) || R_IsNaN( this_x ) ) {
        hex_strings[i] = na_colour;
      } else {
        r = round( spline_red( this_x ) * 255 ) ;
        g = round( spline_green( this_x ) * 255 );
        b = round( spline_blue( this_x ) * 255 );

        colourvalues::palette_utils::validate_rgb_spline(r);
        colourvalues::palette_utils::validate_rgb_spline(g);
        colourvalues::palette_utils::validate_rgb_spline(b);

        if (include_alpha) {
          int a;
          if ( alpha_type == ALPHA_PALETTE ) {
            a = round( spline_alpha( this_x ) * 255 );
          } else if (alpha_type == ALPHA_VECTOR ){
            a = alpha[i];
          } else {
            a = alpha[0];  // should be length 5, but all the same
          }
          hex_strings[i] = colourvalues::convert::convert_rgb_to_hex(r, g, b, a);
        } else {
          hex_strings[i] = colourvalues::convert::convert_rgb_to_hex(r, g, b);
        }
      }
    }
    return hex_strings;
  }

  inline SEXP colour_value_hex(
    Rcpp::NumericVector& x,
    Rcpp::NumericMatrix& palette,
    std::string& na_colour,
    bool include_alpha,
    int n_summaries = 0,
    bool format = false,
    std::string format_type = "numeric",
    int digits = 2) {

    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( 0, x_size, palette.ncol() );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha( x.size(), 255.0 );

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue, alpha );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type, x_size );
    // Rcpp::Rcout << "alpha: " << alpha << std::endl;

    if ( n_summaries > 0 ) {
      Rcpp::NumericVector summary = colourvalues::summary::numeric_summary( x, n_summaries );
      SEXP summary_values = Rcpp::clone( summary );

      n_summaries = summary.size() < n_summaries ? summary.size() : n_summaries;

      if( format ) {
        summary_values = colourvalues::format::format_summary( summary_values, format_type, n_summaries, digits );
      }

      int n_alpha_summary = n_summaries < 5 ? 5 : n_summaries;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 255.0 );

      Rcpp::StringVector summary_hex = colour_values_to_hex( summary, red, green, blue, alpha_summary, alpha_type, na_colour, include_alpha ); // uses full opacity
      Rcpp::StringVector full_hex = colour_values_to_hex( x, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha );
      return Rcpp::List::create(
        _["colours"] = full_hex,
        _["summary_values"] = summary_values,
        _["summary_colours"] = summary_hex
      );
    }
    return colour_values_to_hex( x, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha );
  }

  inline SEXP colour_value_hex(
      Rcpp::NumericVector& x,
      std::string& palette,
      std::string& na_colour,
      Rcpp::NumericVector& alpha,
      bool include_alpha,
      int n_summaries = 0,
      bool format = false,
      std::string format_type = "numeric",
      int digits = 2) {

    // TODO(this throws an error on Travis)
    // if(!is_hex_colour(na_colour)) {
    //   Rcpp::stop("invalid NA Colour");
    // }

    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( alpha.size(), x_size, 0 );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type, x_size );

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

      Rcpp::StringVector summary_hex = colour_values_to_hex(summary, red, green, blue, alpha_summary, alpha_type, na_colour, include_alpha);
      Rcpp::StringVector full_hex = colour_values_to_hex(x, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha);

      // alpha_summary = colourvalues::summary::numeric_summary( alpha_full, n_summaries );
      // Rcpp::Rcout << "alpha summary: " << alpha_summary << std::endl;
      //

      // Rcpp::StringVector summary_alpha_hex =

      return Rcpp::List::create(
        _["colours"] = full_hex,
        _["summary_values"] = summary_values,
        _["summary_colours"] = summary_hex
        );
    }
    return colour_values_to_hex(x, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha);
  }

  inline SEXP colour_value_hex (
      Rcpp::StringVector& x,
      Rcpp::NumericMatrix& palette,
      std::string& na_colour,
      bool include_alpha,
      bool summary = false) {

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

      Rcpp::StringVector summary_hex = colour_values_to_hex( nv, red, green, blue, alpha_summary, alpha_type, na_colour, include_alpha );
      Rcpp::StringVector full_hex = colour_values_to_hex( out_nv, red, green, blue, alpha, alpha_type, na_colour, include_alpha );
      return Rcpp::List::create(
        _["colours"] = full_hex,
        _["summary_values"] = lvls,
        _["summary_colours"] = summary_hex
      );
    }

    return colour_values_to_hex( out_nv, red, green, blue, alpha, alpha_type, na_colour, include_alpha );
  }

  inline SEXP colour_value_hex(
      Rcpp::StringVector& x,
      std::string& palette,
      std::string& na_colour,
      Rcpp::NumericVector& alpha,
      bool include_alpha,
      bool summary = false) {

    // TODO(this throws an error on Travis)
    // if(!is_hex_colour(na_colour)) {
    //   Rcpp::stop("invalid NA Colour");
    // }
    int x_size = x.size();
    int alpha_type = colourvalues::alpha::make_alpha_type( alpha.size(), x_size, 0 );

    Rcpp::NumericVector alpha_full = colourvalues::alpha::validate_alpha( alpha, alpha_type, x_size );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    colourvalues::palette_utils::resolve_palette( palette, red, green, blue );

    Rcpp::StringVector lvls = Rcpp::sort_unique( x ); // moved outside resolve so can use in a legend
    lvls = na_omit( lvls );
    Rcpp::NumericVector out_nv = colourvalues::utils::resolve_string_vector( x, lvls );

    if ( summary ) {
      Rcpp::IntegerVector summary_values = Rcpp::seq_len( lvls.length() );
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( summary_values );

      int x_size = x.size();
      int n_alpha_summary = x_size < 5 ? 5 : x_size;
      Rcpp::NumericVector alpha_summary( n_alpha_summary, 255.0 );

      Rcpp::StringVector summary_hex = colour_values_to_hex( nv, red, green, blue, alpha_summary, alpha_type, na_colour, include_alpha );
      Rcpp::StringVector full_hex = colour_values_to_hex( out_nv, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha );

      return Rcpp::List::create(
        _["colours"] = full_hex,
        _["summary_values"] = lvls,
        _["summary_colours"] = summary_hex
      );
    }

    return colour_values_to_hex( out_nv, red, green, blue, alpha_full, alpha_type, na_colour, include_alpha );
  }

} // namespace colours
} // namespace colourvalues

#endif

