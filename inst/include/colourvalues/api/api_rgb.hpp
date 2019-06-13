#ifndef R_COLOURVALUES_RGB_API_H
#define R_COLOURVALUES_RGB_API_H

#include <Rcpp.h>

#include "colourvalues/colours/colours_rgb.hpp"
#include "colourvalues/list/list.hpp"

// *************** RGB ****************
namespace colourvalues {
namespace api {

  /*
   * list with string palette
   */
  inline SEXP colour_values_rgb(
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
    std::string format_type = "character";

    Rcpp::List lst_sizes = colourvalues::list::list_size( lst, total_size, existing_type, format_type );

    switch( existing_type ) {
    case INTSXP: { } // 13
    case REALSXP: { // 14

      Rcpp::NumericVector colours( total_size );
      colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

      if( summary ) {
        int option = 5;
        Rcpp::warning("colourvalues - summary not valid for numeric values, using n_summaries = 5");
        n_summaries = std::min( total_size, option );
      }

      SEXP coloured_values = colourvalues::colours_rgb::colour_value_rgb(
        colours, palette, na_colour, include_alpha, format_type, n_summaries, format, digits
      );

      position = 0;
      Rcpp::NumericMatrix colour_matrix;

      if( n_summaries > 0 ) {
        Rcpp::List res = Rcpp::as< Rcpp::List >( coloured_values );
        colour_matrix = Rcpp::as< Rcpp::NumericMatrix >( res["colours"] );
        res["colours"] = colourvalues::list::refil_list( lst_sizes, colour_matrix, position );
        return res;
      } else {
        colour_matrix = Rcpp::as< Rcpp::NumericMatrix >( coloured_values );
        Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_matrix, position );
        return res;
      }

    }
    default: {

      if( n_summaries > 0 ) {
      Rcpp::warning("colourvalues - n_summaries not valid for character values, using summary = T");
      summary = true;
    }

      Rcpp::StringVector colours( total_size );
      colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

      SEXP coloured_values = colourvalues::colours_rgb::colour_value_rgb(
        colours, palette, na_colour, include_alpha, summary
      );

      position = 0;
      Rcpp::NumericMatrix colour_matrix;

      if( summary ) {
        Rcpp::List res = Rcpp::as< Rcpp::List >( coloured_values );
        colour_matrix = Rcpp::as< Rcpp::NumericMatrix >( res["colours"] );
        res["colours"] = colourvalues::list::refil_list( lst_sizes, colour_matrix, position );
        return res;
      } else {
        colour_matrix = Rcpp::as< Rcpp::NumericMatrix >( coloured_values );
        Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_matrix, position );
        return res;
      }

    }
    }
    return Rcpp::List::create(); // never reaches
  }


  /*
   * list with string palette
   */
  inline SEXP colour_values_rgb(
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

    //Rcpp::Rcout << "now doing list " << std::endl;


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
        Rcpp::warning("colourvalues - summary not valid for numeric values, using n_summaries = 5");
        n_summaries = std::min( total_size, option );
      }

      //Rcpp::Rcout << "colouring values" << std::endl;
      SEXP coloured_values = colourvalues::colours_rgb::colour_value_rgb(
        colours, palette, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
      );
      //Rcpp::Rcout << "coloured values" << std::endl;

      position = 0;
      Rcpp::NumericMatrix colour_matrix;

      if( n_summaries > 0 ) {
        Rcpp::List res = Rcpp::as< Rcpp::List >( coloured_values );
        colour_matrix = Rcpp::as< Rcpp::NumericMatrix >( res["colours"] );
        res["colours"] = colourvalues::list::refil_list( lst_sizes, colour_matrix, position );
        return res;
      } else {
        colour_matrix = Rcpp::as< Rcpp::NumericMatrix >( coloured_values );
        Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_matrix, position );
        return res;
      }

    }
    default: {

      if( n_summaries > 0 ) {
      Rcpp::warning("colourvalues - n_summaries not valid for character values, using summary = T");
      summary = true;
    }

      Rcpp::StringVector colours( total_size );
      colourvalues::list::unlist_list( lst, lst_sizes, colours, position );

      SEXP coloured_values = colourvalues::colours_rgb::colour_value_rgb(
        colours, palette, na_colour, alpha, include_alpha, summary
      );

      position = 0;
      Rcpp::NumericMatrix colour_matrix;

      if( summary ) {
        Rcpp::List res = Rcpp::as< Rcpp::List >( coloured_values );
        colour_matrix = Rcpp::as< Rcpp::NumericMatrix >( res["colours"] );
        res["colours"] = colourvalues::list::refil_list( lst_sizes, colour_matrix, position );
        return res;
      } else {
        colour_matrix = Rcpp::as< Rcpp::NumericMatrix >( coloured_values );
        Rcpp::List res = colourvalues::list::refil_list( lst_sizes, colour_matrix, position );
        return res;
      }

    }
    }
    return Rcpp::List::create(); // never reaches
  }

  /*
   * when palette is unknown, but vector is numeric
   */
  inline SEXP colour_values_rgb(
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

    //Rcpp::Rcout << "NumericVector x, SEXP palette " << std::endl;

    switch( TYPEOF( palette ) ) {
    // STringVector - needs to get std::string
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
      Rcpp::String s = sv[0];
      std::string pal = s;
      return colourvalues::colours_rgb::colour_value_rgb(
        x, pal, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
      );
    }
    case INTSXP: {}
    case REALSXP: {
      if( !Rf_isMatrix( palette ) ) {
      Rcpp::stop("colourvalues - Unknown palette type - expecting a matrix");
    }
      Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
      return colourvalues::colours_rgb::colour_value_rgb(
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
  inline SEXP colour_values_rgb(
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
    //Rcpp::Rcout << "stringVector x, SEXP palette " << std::endl;

    switch( TYPEOF( palette ) ) {
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
      Rcpp::String s = sv[0];
      std::string pal = s;
      return colourvalues::colours_rgb::colour_value_rgb(
        x, pal, na_colour, alpha, include_alpha, summary
      );
    }
    case INTSXP: {}
    case REALSXP: {
      if( !Rf_isMatrix( palette ) ) {
      Rcpp::stop("colourvalues - Unknown palette type - expecting a matrix");
    }
      Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
      return colourvalues::colours_rgb::colour_value_rgb(
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
  inline SEXP colour_values_rgb(
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
    //Rcpp::Rcout << "SEXP x, NumericMatrix palette " << std::endl;
    //Rcpp::Rcout << "include_alpha: " << include_alpha << std::endl;

    std::string format_type = colourvalues::format::get_format_type( x );

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isFactor( x ) ) {

      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      Rcpp::StringVector lvls = iv.attr("levels");

      return colourvalues::colours_rgb::colour_value_rgb(
        iv, lvls, palette, na_colour, include_alpha, summary
      );

    } else {
      Rcpp::NumericVector nv = Rcpp::clone(x);
      return colourvalues::colours_rgb::colour_value_rgb(
        nv, palette, na_colour, include_alpha, format_type, n_summaries, format, digits
      );
    }
    }
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return colourvalues::colours_rgb::colour_value_rgb(
        nv, palette, na_colour, include_alpha, format_type, n_summaries, format, digits
      );
    }
    case VECSXP: { // list
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      // TODO list
      Rcpp::stop("colourvalues -  list not supported yet ");

    }
    case LGLSXP: {} // as.character
    default: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
      return colourvalues::colours_rgb::colour_value_rgb(
        sv, palette, na_colour, include_alpha, summary
      );
    }
    }

  }

  /*
   * When the palette is a string, but vector is unknown
   */
  inline SEXP colour_values_rgb(
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

    // Rcpp::Rcout << "SEXP x, StringVector palette " << std::endl;
    // Rcpp::Rcout << "typeof x: " << TYPEOF( x ) << std::endl;
    std::string format_type = colourvalues::format::get_format_type( x );

    Rcpp::String p = palette[0];
    std::string pal = p;

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isFactor( x ) ) {

      //Rcpp::Rcout << "is factor " << std::endl;

      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      Rcpp::StringVector lvls = iv.attr("levels");

      return colourvalues::colours_rgb::colour_value_rgb(
        iv, lvls, pal, na_colour, alpha, include_alpha, summary
      );

    } else {
      Rcpp::NumericVector nv = Rcpp::clone(x);
      return colourvalues::colours_rgb::colour_value_rgb(
        nv, pal, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
      );
    }
    }
    case REALSXP: {
      //Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      Rcpp::NumericVector nv = Rcpp::clone(x);
      return colourvalues::colours_rgb::colour_value_rgb(
        nv, pal, na_colour, alpha, include_alpha, format_type, n_summaries, format, digits
      );
    }
    case VECSXP: { // list
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      //Rcpp::Rcout << "starting list " << std::endl;
      return colour_values_rgb( lst, pal, alpha, na_colour, include_alpha, format, digits, summary, n_summaries );

    }
    case LGLSXP: {} // as.character
    default: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
      return colourvalues::colours_rgb::colour_value_rgb(
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
  inline SEXP colour_values_rgb(
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

    //Rcpp::Rcout << "SEXP x, SEXP palette " << std::endl;

    switch( TYPEOF( palette ) ) {
    case INTSXP: {}
    case REALSXP: {
      Rcpp::NumericMatrix pal = Rcpp::as< Rcpp::NumericMatrix >( palette );
      return colour_values_rgb(
        x, pal, alpha, na_colour, include_alpha, format, digits, summary, n_summaries
      );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( palette );
      return colour_values_rgb(
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
