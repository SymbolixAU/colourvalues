#ifndef R_COLOURVALUES_FORMAT_H
#define R_COLOURVALUES_FORMAT_H

#include <Rcpp.h>
#include <iostream>
#include <boost/date_time.hpp>

#include "colourvalues/utils/utils.hpp"

// #include <boost/lexical_cast.hpp>

// [[Rcpp::depends(BH)]]

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

  inline Rcpp::StringVector date_to_string( SEXP v, int n ) {

    int i;
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
    Rcpp::StringVector sv( n );

    for ( i = 0; i < n; i++ ) {
      Rcpp::Date d = nv[i];
      boost::gregorian::date gd = boost::gregorian::date( d.getYear(), d.getMonth(), d.getDay() );
      std::string s = boost::gregorian::to_iso_extended_string( gd );
      sv[i] = s.c_str();
    }
    return sv;
  }

  inline Rcpp::StringVector posixct_to_string( SEXP v, int n ) {

    int i;
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
    Rcpp::StringVector sv( n );

    for ( i = 0; i < n; i++ ) {
      Rcpp::Datetime d = nv[i];
      boost::gregorian::date dt( d.getYear(), d.getMonth(), d.getDay() );
      boost::posix_time::hours h( d.getHours() );
      boost::posix_time::minutes mins( d.getMinutes() );
      boost::posix_time::seconds sec( d.getSeconds() );
      boost::posix_time::time_duration td = h + mins + sec;

      boost::posix_time::ptime pt = boost::posix_time::ptime( dt, td );
      std::string s = boost::posix_time::to_iso_extended_string( pt );
      sv[i] = s.c_str();
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
