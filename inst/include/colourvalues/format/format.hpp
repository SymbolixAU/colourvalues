#ifndef R_COLOURVALUES_FORMAT_H
#define R_COLOURVALUES_FORMAT_H

#include <Rcpp.h>
#include <iostream>

#include "colourvalues/utils/utils.hpp"

namespace colourvalues {
namespace format {

  /*
   * Determins the type of formatting requried for summary values (legend)
   *
   */
  inline std::string get_format_type( SEXP x ) {

    std::string format_type;

    Rcpp::CharacterVector cls = colourvalues::utils::getRClass( x );

    //Rcpp::Rcout << "cls: " << cls << std::endl;

    if( colourvalues::utils::is_in( "Date", cls ) ) {
      format_type = "Date";
    } else if ( colourvalues::utils::is_in("POSIXct", cls) ) {
      format_type = "POSIXct";
    } else if ( colourvalues::utils::is_in("POSIXlt", cls) ) {
      format_type = "POSIXct";
    } else if ( colourvalues::utils::is_in("logical", cls) ) {
      format_type = "character";
    } else if ( colourvalues::utils::is_in("character", cls) ) {
      format_type = "character";
    } else {
      format_type = "numeric";
    }
    return format_type;
  }

  inline std::string format_date( Rcpp::Date& d ) {
    int yyyy = d.getYear();
    int mm = d.getMonth();
    int dd = d.getDay();
    std::ostringstream os;
    os << std::setfill('0') << std::setw(4) << yyyy << "-";
    os << std::setfill('0') << std::setw(2) << mm << "-";
    os << std::setfill('0') << std::setw(2) << dd;
    return os.str();
  }

  inline std::string format_datetime( Rcpp::Datetime& d ) {
    int yyyy = d.getYear();
    int mm = d.getMonth();
    int dd = d.getDay();
    int h = d.getHours();
    int m = d.getMinutes();
    int s = d.getSeconds();
    std::ostringstream os;
    //sprintf( res, "%04d-%02d-%02dT%02d:%02d:%02d", yyyy, mm, dd, h, m, s);
    os << std::setfill('0') << std::setw(4) << yyyy << "-";
    os << std::setfill('0') << std::setw(2) << mm << "-";
    os << std::setfill('0') << std::setw(2) << dd << "T";
    os << std::setfill('0') << std::setw(2) << h << ":";
    os << std::setfill('0') << std::setw(2) << m << ":";
    os << std::setfill('0') << std::setw(2) << s;
    return os.str();
  }

  inline Rcpp::StringVector date_to_string( SEXP v, int n ) {

    int i;
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
    Rcpp::StringVector sv( n );

    for ( i = 0; i < n; ++i ) {
      Rcpp::Date d = nv[i];
      sv[i] = format_date( d );
    }
    return sv;
  }

  inline Rcpp::StringVector posixct_to_string( SEXP v, int n ) {

    int i;
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
    Rcpp::StringVector sv( n );

    for( i = 0; i < n; ++i ) {
      Rcpp::Datetime d = nv[ i ];
      sv[i] = format_datetime( d );
    }
    return sv;
  }

  inline Rcpp::StringVector numeric_to_string( SEXP v, int n, int dp) {
    int i;
    Rcpp::StringVector sv( n );
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
    // TODO( implement decimal-places )
    for ( i = 0; i < n; i++ ) {
      std::ostringstream os;
      os << std::fixed << std::setprecision( dp ) << nv[i];
      std::string s = os.str();
      sv[i] = s.c_str();
    }
    return sv;
  }

  inline SEXP format_summary( SEXP summary_values, std::string& format_type, int n_summaries, int digits ) {

    //std::string format_type = get_format_type( summary_values );

    if (format_type == "numeric" ) {
      return colourvalues::format::numeric_to_string( summary_values, n_summaries, digits);
    // } else if ( format_type == "integer" ) {
    //   return summary_values; // ints are nice already
    } else if ( format_type == "Date" ) {
      return colourvalues::format::date_to_string( summary_values, n_summaries );
    } else if ( format_type == "POSIXct" ) {
      return colourvalues::format::posixct_to_string( summary_values, n_summaries );
    // } else if ( format_type == "posixlt" ) {
    //   return colourvalues::format::posixlt_to_string( summary_values, n_summaries );
    } else {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( summary_values );
      return sv;
    }

    return R_NilValue; // never reacehd
  }
} // namespace format
} // namespace colourvalues



#endif
