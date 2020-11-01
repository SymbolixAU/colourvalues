#ifndef R_COLOURVALUES_RGB_INTERLEAVED_API_H
#define R_COLOURVALUES_RGB_INTERLEAVED_API_H

#include <Rcpp.h>

#include "colourvalues/colours/colours_rgb_interleaved.hpp"
#include "colourvalues/list/list.hpp"

// *************** INTERLEAVED ****************
namespace colourvalues {
namespace api {

  /*
   * list with matrix palette
   */
  inline SEXP colour_values_rgb_interleaved(
      Rcpp::List lst,
      Rcpp::NumericMatrix& palette,
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

    int total_size = 0;
    int existing_type = 10;

    int position = 0;


    // TODO: get format_type depending on the type of list elements
    std::string format_type = "character";

    Rcpp::List lst_sizes = colourvalues::list::list_size( lst, total_size, existing_type, format_type );

    switch( existing_type ) {
      case INTSXP: { } // 13
      case REALSXP: { // 14

        Rcpp::NumericVector colours( total_size );
        colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

        if( summary ) {
          int option = 5;
          //Rcpp::warning("colourvalues - summary not valid for numeric values, using n_summaries = 5");
          n_summaries = std::min( total_size, option );
        }

        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          colours, palette, na_colour, include_alpha, format_type, repeats, total_colours, n_summaries, format, digits
        );
      }
      default: {

        if( n_summaries > 0 ) {
          // issue 68
          //Rcpp::warning("colourvalues - n_summaries not valid for character values, using summary = T");
          summary = true;
        }

        Rcpp::StringVector colours( total_size );
        colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          colours, palette, na_colour, include_alpha, repeats, total_colours, summary
        );

      }
    }
    return Rcpp::List::create(); // never reaches
  }


  /*
   * list with string palette
   */
  inline SEXP colour_values_rgb_interleaved(
      Rcpp::List lst,
      std::string& palette,
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

    int total_size = 0;
    int existing_type = 10;

    int position = 0;

    // TODO: get format_type depending on the type of list elements
    std::string format_type = "character";

    Rcpp::List lst_sizes = colourvalues::list::list_size( lst, total_size, existing_type, format_type );

    switch( existing_type ) {
      case INTSXP: { } // 13
      case REALSXP: { // 14

        Rcpp::NumericVector colours( total_size );
        colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

        if( summary ) {
          int option = 5;
          //Rcpp::warning("colourvalues - summary not valid for numeric values, using n_summaries = 5");
          n_summaries = std::min( total_size, option );
        }

        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          colours, palette, na_colour, alpha, include_alpha, format_type, repeats, total_colours, n_summaries, format, digits
        );

      }
      default: {

        if( n_summaries > 0 ) {
          // issue 68
          //Rcpp::warning("colourvalues - n_summaries not valid for character values, using summary = T");
          summary = true;
        }

        Rcpp::StringVector colours( total_size );
        colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          colours, palette, na_colour, alpha, include_alpha, repeats, total_colours, summary
        );
      }
    }
    return Rcpp::List::create(); // never reaches
  }

  /*
   * when palette is unknown, but vector is numeric
   */
  inline SEXP colour_values_rgb_interleaved(
      Rcpp::NumericVector& x,
      SEXP palette,
      Rcpp::NumericVector& alpha,
      std::string& format_type,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      std::string& na_colour,
      bool include_alpha = true,
      bool format = false,
      int digits = 2,
      int n_summaries = 0
  ) {

    switch( TYPEOF( palette ) ) {
      case STRSXP: {
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
        Rcpp::String s = sv[0];
        std::string pal = s;
        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          x, pal, na_colour, alpha, include_alpha, format_type, repeats, total_colours, n_summaries, format, digits
        );
      }
      case INTSXP: {}
      case REALSXP: {
        if( !Rf_isMatrix( palette ) ) {
        Rcpp::stop("colourvalues - Unknown palette type - expecting a matrix");
      }
        Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          x, pal, na_colour, include_alpha, format_type, repeats, total_colours, n_summaries, format, digits
        );
      }
      default: {
        Rcpp::stop("colourvalues - Unknown palette type");
      }
    }

  }

  /*
   * When palette is unknown, but vector is string
   */
  inline SEXP colour_values_rgb_interleaved(
      Rcpp::StringVector& x,
      SEXP palette,
      Rcpp::NumericVector& alpha,
      std::string& format_type,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      std::string na_colour = "#808080",
      bool include_alpha = true,
      bool format = false,
      int digits = 2,
      bool summary = false
  ) {

    switch( TYPEOF( palette ) ) {
      case STRSXP: {
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
        Rcpp::String s = sv[0];
        std::string pal = s;
        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          x, pal, na_colour, alpha, include_alpha, repeats, total_colours, summary
        );
      }
      case INTSXP: {}
      case REALSXP: {
        if( !Rf_isMatrix( palette ) ) {
        Rcpp::stop("colourvalues - Unknown palette type - expecting a matrix");
      }
        Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          x, pal, na_colour, alpha, repeats, total_colours, summary
        );
      }
      default: {
        Rcpp::stop("colourvalues - Unknown palette type");
      }
    }
  }

  /*
   * When the palette is a matrix, but vector is unknown
   */
  inline SEXP colour_values_rgb_interleaved(
      SEXP x,
      Rcpp::NumericMatrix& palette,
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

    std::string format_type = colourvalues::format::get_format_type( x );

    switch( TYPEOF( x ) ) {
      case INTSXP: {
        if( Rf_isFactor( x ) ) {

          Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
          Rcpp::StringVector lvls = iv.attr("levels");

          return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
            iv, lvls, palette, na_colour, include_alpha, repeats, total_colours, summary
          );

        } else {
          Rcpp::NumericVector nv = Rcpp::clone(x);
          return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
            nv, palette, na_colour, include_alpha, format_type, repeats, total_colours, n_summaries, format, digits
          );
        }
      }
      case REALSXP: {
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          nv, palette, na_colour, include_alpha, format_type, repeats, total_colours, n_summaries, format, digits
        );
      }
      case VECSXP: { // list
        Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
        return colour_values_rgb_interleaved(
          lst, palette, alpha, repeats, total_colours, na_colour, include_alpha, format, digits, summary, n_summaries
        );

      }
      case LGLSXP: {} // as.character
      default: {
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          sv, palette, na_colour, include_alpha, repeats, total_colours, summary
        );
      }
    }

  }

  /*
   * When the palette is a string, but vector is unknown
   */
  inline SEXP colour_values_rgb_interleaved(
      SEXP x,
      Rcpp::StringVector& palette,
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

    std::string format_type = colourvalues::format::get_format_type( x );

    Rcpp::String p = palette[0];
    std::string pal = p;

    switch( TYPEOF( x ) ) {
      case INTSXP: {
        if( Rf_isFactor( x ) ) {
          Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
          Rcpp::StringVector lvls = iv.attr("levels");

          return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
            iv, lvls, pal, na_colour, alpha, include_alpha, repeats, total_colours, summary
          );

        } else {
          Rcpp::NumericVector nv = Rcpp::clone(x);
          return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
            nv, pal, na_colour, alpha, include_alpha, format_type, repeats, total_colours, n_summaries, format, digits
          );
        }
      }
      case REALSXP: {
        Rcpp::NumericVector nv = Rcpp::clone(x);
        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          nv, pal, na_colour, alpha, include_alpha, format_type, repeats, total_colours, n_summaries, format, digits
        );
      }
      case VECSXP: { // list
        Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
        return colour_values_rgb_interleaved(
          lst, pal, alpha, repeats, total_colours, na_colour, include_alpha, format, digits, summary, n_summaries
          );

      }
      case LGLSXP: {} // as.character
      default: {
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
        return colourvalues::colours_rgb_interleaved::colour_value_rgb_interleaved(
          sv, pal, na_colour, alpha, include_alpha, repeats, total_colours, summary
        );
      }
    }

    Rcpp::StringVector sv;
    return sv; // never reaches
  }

  /*
   * When neither type of vector/list or palette is known
   */
  inline SEXP colour_values_rgb_interleaved(
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

    switch( TYPEOF( palette ) ) {
      case INTSXP: {}
      case REALSXP: {
        Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
        return colour_values_rgb_interleaved(
          x, pal, alpha, repeats, total_colours, na_colour, include_alpha, format, digits, summary, n_summaries
        );
        break;
      }
      case STRSXP: {
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
        return colour_values_rgb_interleaved(
          x, sv, alpha, repeats, total_colours, na_colour, include_alpha, format, digits, summary, n_summaries
        );
        break;
      }
      default: {
        Rcpp::stop("colourvalues - Unknown palette type");
      }
    }

    Rcpp::StringVector sv;
    return sv; // never reaches

  }


} // api
} // colourvalues

#endif
