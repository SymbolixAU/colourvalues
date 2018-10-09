#include <Rcpp.h>

#include "colourvalues/convert/convert_colours.hpp"


//
// static unsigned int hexdigit( int digit ) {
//   if('0' <= digit && digit <= '9') return digit - '0';
//   if('A' <= digit && digit <= 'F') return 10 + digit - 'A';
//   if('a' <= digit && digit <= 'f') return 10 + digit - 'a';
//   return digit;
// }
//
// unsigned int hex_to_rgba( const char *hex, unsigned int ele1, unsigned int ele2 ) {
//   return 16 * hexdigit( hex[ele1] ) + hexdigit( hex[ele2] );
// }

// unsigned int hex_to_rgb( const char *hex ) {
//   int r = 0;
//   int g = 0;
//   int b = 0;
//   int a = 0;
//   r = 16 * hexdigit( hex[1] ) + hexdigit( hex[2] );
//   g = 16 * hexdigit( hex[3] ) + hexdigit( hex[4] );
//   b = 16 * hexdigit( hex[5] ) + hexdigit( hex[6] );
//   a = 16 * hexdigit( hex[7] ) + hexdigit( hex[8] );
//   //return r;
//
//   Rcpp::Rcout << r << ", " << g << ", " << b << ", " << a << std::endl;
//
//   return CV_RGBA(r,g,b,a);
//
//   //return std::stoul( hex, nullptr, 16);
// }

// // [[Rcpp::export]]
// int test_hex_to_rgb( std::string hex ) {
//   return hex_to_rgb( hex.c_str() );
// }



// [[Rcpp::export]]
Rcpp::IntegerMatrix rcpp_convert_hex_to_rgb( Rcpp::StringVector hex_strings ) {
  int i;
  int n = hex_strings.size();
  Rcpp::IntegerMatrix mat(n, 4);
  bool any_alpha = false;

  for( i = 0; i < n; i++ ) {
    Rcpp::String this_hex = hex_strings[i];
    const char* cs = this_hex.get_cstring();
    mat(i, Rcpp::_) = colourvalues::convert::convert_hex_to_rgb( cs, any_alpha );
  }

  if ( !any_alpha ) {
    mat = mat(Rcpp::_, Rcpp::Range(0,2) );
  }
  return mat;
}
