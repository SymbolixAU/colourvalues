#ifndef R_COLOURVALUES_UTILS_H
#define R_COLOURVALUES_UTILS_H

#include <Rcpp.h>

namespace colourvalues {
namespace utils {

  inline bool is_in( const char* x, Rcpp::CharacterVector v ) {
    int n = v.size();
    int i;
    for( i = 0; i < n; i++ ) {
      if( v[i] == x ) {
        return true;
      }
    }
    return false;
  }

  template < int RTYPE >
  inline Rcpp::CharacterVector rClass( Rcpp::Vector< RTYPE > v ) {
    if( Rf_isNull( v.attr("class")) ) {
      return "";
    }
    return v.attr("class");
  }

  inline Rcpp::CharacterVector getRClass( SEXP obj ) {

    switch( TYPEOF( obj ) ) {
      case REALSXP:
        return rClass< REALSXP >( obj );
      case VECSXP:
        return rClass< VECSXP >( obj );
      case INTSXP: {
          Rcpp::CharacterVector intcls = rClass< INTSXP >( obj );
          if( intcls.size() == 1 && intcls[0] == "" ) {
            return "integer";
          }
          return intcls;
      }
      case LGLSXP:
        return "logical";
      case STRSXP:
        return "character";
    }
    return "";
  }

  inline void matrix_palette_check( Rcpp::NumericMatrix& pal ) {
    if( pal.nrow() < 5 ) {
      Rcpp::stop("colourvalues - Matrix palettes must have at least 5 rows");
    }
  }

  inline void validate_hex( const char* hex ) {
    if ( strncmp(hex, "#", 1) != 0 ) {
      Rcpp::stop("colourvalues - unknown hex string, expecting # symbol");
    }
  }

  inline void replace_nas( Rcpp::IntegerVector& out, int na_value ) {
    int int_s = NA_INTEGER;
    std::replace( out.begin(), out.end(), na_value, int_s);
  }

  inline Rcpp::NumericVector resolve_string_vector( Rcpp::StringVector& x, Rcpp::StringVector& lvls ) {
    bool anyNa = Rcpp::any( is_na( x ) );

    Rcpp::IntegerVector out = Rcpp::match( x, lvls );

    if ( anyNa ) {
      int na_value = Rcpp::max( out );
      colourvalues::utils::replace_nas( out, na_value );
    }
    return Rcpp::as< Rcpp::NumericVector >( out );
  }

} // namespace utils
} // namespace colourvalues


#endif
