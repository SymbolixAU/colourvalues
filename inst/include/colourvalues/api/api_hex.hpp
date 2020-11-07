#ifndef R_COLOURVALUES_HEX_API_H
#define R_COLOURVALUES_HEX_API_H

#include <Rcpp.h>

#include "colourvalues/colours/colours_hex.hpp"
#include "colourvalues/list/list.hpp"

// *************** HEX ****************
namespace colourvalues {
namespace api {

  /*
   * list with matrix palette
   */
  inline SEXP colour_values_hex(
      Rcpp::List lst,
      Rcpp::NumericMatrix& palette,
      Rcpp::NumericVector& alpha,
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
    std::string format_type = "numeric";
    // follow heirarchy of classes:
    //
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

      SEXP coloured_values = colourvalues::colours_hex::colour_value_hex(
        colours, palette, na_colour, include_alpha, format_type, n_summaries, format, digits
      );

      position = 0;
      Rcpp::StringVector colour_vector;

      if( n_summaries > 0 ) {
        Rcpp::List res = Rcpp::as< Rcpp::List >( coloured_values );
        colour_vector = res["colours"];
        res["colours"] = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
        return res;
      } else {
        colour_vector = Rcpp::as< Rcpp::StringVector >( coloured_values );
        Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
        return res;
      }


    }
    default: {

      summary = n_summaries > 0;
      // if( n_summaries > 0 ) {
      //   // issue 68
      //   // Rcpp::warning("colourvalues - n_summaries not valid for character values, using summary = T");
      //   summary = true;
      // }

      Rcpp::StringVector colours( total_size );
      colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

      SEXP coloured_values = colourvalues::colours_hex::colour_value_hex(
        colours, palette, na_colour, include_alpha, summary
      );

      position = 0;
      Rcpp::StringVector colour_vector;

      if( summary ) {
        Rcpp::List res = Rcpp::as< Rcpp::List >( coloured_values );
        colour_vector = res["colours"];
        res["colours"] = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
        return res;
      } else {
        colour_vector = Rcpp::as< Rcpp::StringVector >( coloured_values );
        Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
        return res;
      }
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  /*
   * list with string palette
   */
  inline SEXP colour_values_hex(
      Rcpp::List lst,
      std::string& palette,
      Rcpp::NumericVector& alpha,
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
    std::string format_type = "numeric";

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

        SEXP coloured_values = colourvalues::colours_hex::colour_value_hex(
          colours, palette, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
        );

        position = 0;
        Rcpp::StringVector colour_vector;

        if( n_summaries > 0 ) {
          Rcpp::List res = Rcpp::as< Rcpp::List >( coloured_values );
          colour_vector = res["colours"];
          res["colours"] = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
          return res;
        } else {
          colour_vector = Rcpp::as< Rcpp::StringVector >( coloured_values );
          Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
          return res;
        }

      }
      default: {

        summary = n_summaries > 0;
        // if( n_summaries > 0 ) {
        //   // issue 68
        //   //Rcpp::warning("colourvalues - n_summaries not valid for character values, using summary = T");
        //   summary = true;
        // }

        Rcpp::StringVector colours( total_size );
        colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

        SEXP coloured_values = colourvalues::colours_hex::colour_value_hex(
          colours, palette, na_colour, alpha, include_alpha, summary
        );

        position = 0;
        Rcpp::StringVector colour_vector;

        if( summary ) {
          Rcpp::List res = Rcpp::as< Rcpp::List >( coloured_values );
          colour_vector = res["colours"];
          res["colours"] = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
          return res;
        } else {
          colour_vector = Rcpp::as< Rcpp::StringVector >( coloured_values );
          Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_vector, position );
          return res;
        }
      }
    }
    return Rcpp::List::create(); // never reaches
  }

  /*
   * when palette is unknown, but vector is numeric
   */
  inline SEXP colour_values_hex(
      Rcpp::NumericVector& x,
      SEXP palette,
      Rcpp::NumericVector& alpha,
      std::string& format_type,
      std::string& na_colour,
      bool include_alpha = true,
      bool format = false,
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
          x, pal, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
        );
      }
      case INTSXP: {}
      case REALSXP: {
        if( !Rf_isMatrix( palette ) ) {
        Rcpp::stop("colourvalues - Unknown palette type - expecting a matrix");
      }
        Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
        return colourvalues::colours_hex::colour_value_hex(
          x, pal, na_colour, include_alpha, format_type, n_summaries, format, digits
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
  inline SEXP colour_values_hex(
      Rcpp::StringVector& x,
      SEXP palette,
      Rcpp::NumericVector& alpha,
      std::string& format_type,
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
      return colourvalues::colours_hex::colour_value_hex(
        x, pal, na_colour, alpha, include_alpha, summary
      );
    }
    case INTSXP: {}
    case REALSXP: {
      if( !Rf_isMatrix( palette ) ) {
      Rcpp::stop("colourvalues - Unknown palette type - expecting a matrix");
    }
      Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
      return colourvalues::colours_hex::colour_value_hex(
        x, pal, na_colour, alpha, summary
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
  inline SEXP colour_values_hex(
      SEXP x,
      Rcpp::NumericMatrix& palette,
      Rcpp::NumericVector& alpha,
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

      return colourvalues::colours_hex::colour_value_hex(
        iv, lvls, palette, na_colour, include_alpha, summary
      );

    } else {
      Rcpp::NumericVector nv = Rcpp::clone(x);
      return colourvalues::colours_hex::colour_value_hex(
        nv, palette, na_colour, include_alpha, format_type, n_summaries, format, digits
      );
    }
    }
    case REALSXP: {
      //Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      Rcpp::NumericVector nv = Rcpp::clone(x);
      return colourvalues::colours_hex::colour_value_hex(
        nv, palette, na_colour, include_alpha, format_type, n_summaries, format, digits
      );
    }
    case VECSXP: { // list
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      return colour_values_hex( lst, palette, alpha, na_colour, include_alpha, format, digits, summary, n_summaries );

    }
    case LGLSXP: {} // as.character
    default: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
      return colourvalues::colours_hex::colour_value_hex(
        sv, palette, na_colour, include_alpha, summary
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

      return colourvalues::colours_hex::colour_value_hex(
        iv, lvls, pal, na_colour, alpha, include_alpha, summary
      );

    } else {
      Rcpp::NumericVector nv = Rcpp::clone(x);
      return colourvalues::colours_hex::colour_value_hex(
        nv, pal, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
      );
    }
    }
    case REALSXP: {
      //Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      Rcpp::NumericVector nv = Rcpp::clone(x);
      return colourvalues::colours_hex::colour_value_hex(
        nv, pal, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
      );
    }
    case VECSXP: { // list
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      return colour_values_hex( lst, pal, alpha, na_colour, include_alpha, format, digits, summary, n_summaries );
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
      int digits = 2,
      bool summary = false,
      int n_summaries = 0
  ) {

    std::string format_type = colourvalues::format::get_format_type( x );

    switch( TYPEOF( palette ) ) {
    case INTSXP: {}
    case REALSXP: {
      Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
      return colour_values_hex(
        x, pal, alpha, na_colour, include_alpha, format, digits, summary, n_summaries
      );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
      return colour_values_hex(
        x, sv, alpha, na_colour, include_alpha, format, digits, summary, n_summaries
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
