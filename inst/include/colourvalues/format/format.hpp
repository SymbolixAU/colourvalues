#ifndef R_COLOURVALUES_FORMAT_H
#define R_COLOURVALUES_FORMAT_H

#include <Rcpp.h>
#include <iostream>
#include <boost/date_time.hpp>
// #include <boost/lexical_cast.hpp>

// [[Rcpp::depends(BH)]]

namespace colourvalues {
namespace format {

  template< int RTYPE >
  Rcpp::StringVector date_to_string( const Rcpp::Vector< RTYPE >& nv ) {

    int n = nv.size();
    int i;
    Rcpp::StringVector sv( n );

    for ( i = 0; i < n; i++ ) {
      //std::string s = boost::lexical_cast< std::string >( nv[i] );
      // boost::gregorian::date d( nv[i] );
      //
      // std::string s = boost::gregorian::to_iso_string( d );
      // Rcpp::Rcout << s.c_str()  << std::endl;

      //boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
      //boost::gregorian::date today = now.date();
      // std::string s = boost::gregorian::to_iso_string( today );
      // Rcpp::Rcout << s.c_str() << std::endl;

      Rcpp::Date d = nv[i];
      boost::gregorian::date gd = boost::gregorian::date(d.getYear(), d.getMonth(), d.getDay());
      std::string s = boost::gregorian::to_iso_string( gd );
      Rcpp::Rcout << s.c_str() << std::endl;

      // // create your formatting
      //boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%Y%m%d_%H%M%S");
      //
      // // set your formatting
      // std::ostringstream is;
      // is.imbue(std::locale(is.getloc(), df));
      // is << d << std::endl;
      //
      // // get string
      // Rcpp::Rcout << "output :" << is.str() << std::endl;
    }

    return sv;
  }


} // namespace format
} // namespace colourvalues



#endif
