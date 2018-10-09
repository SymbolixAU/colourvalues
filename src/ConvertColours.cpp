#include <Rcpp.h>

#include "colourvalues/convert_colours/convert_colours.hpp"

// grDevices code
// https://github.com/SurajGupta/r-source/blob/master/src/library/grDevices/src/colors.c

static unsigned int hexdigit( int digit ) {
  if('0' <= digit && digit <= '9') return digit - '0';
  if('A' <= digit && digit <= 'F') return 10 + digit - 'A';
  if('a' <= digit && digit <= 'f') return 10 + digit - 'a';
  return digit; /* never occurs (-Wall) */
}

unsigned int hex_to_r( const char *hex ) {
  return 16 * hexdigit( hex[1] ) + hexdigit( hex[2] );
}

unsigned int hex_to_g( const char *hex ) {
  return 16 * hexdigit( hex[3] ) + hexdigit( hex[4] );
}

unsigned int hex_to_b( const char *hex ) {
  return 16 * hexdigit( hex[5] ) + hexdigit( hex[6] );
}

unsigned int hex_to_a( const char *hex ) {
  return 16 * hexdigit( hex[7] )+ hexdigit( hex[8] );
}

unsigned int hex_to_rgb( const char *hex ) {
  int r = 0;
  int g = 0;
  int b = 0;
  int a = 0;
  r = 16 * hexdigit( hex[1] ) + hexdigit( hex[2] );
  g = 16 * hexdigit( hex[3] ) + hexdigit( hex[4] );
  b = 16 * hexdigit( hex[5] ) + hexdigit( hex[6] );
  a = 16 * hexdigit( hex[7] ) + hexdigit( hex[8] );
  //return r;

  Rcpp::Rcout << r << ", " << g << ", " << b << ", " << a << std::endl;

  return CV_RGBA(r,g,b,a);

  //return std::stoul( hex, nullptr, 16);
}

// [[Rcpp::export]]
int test_hex_to_rgb( std::string hex ) {
  return hex_to_rgb( hex.c_str() );
}


//[[Rcpp::export]]
Rcpp::IntegerMatrix rcpp_convert_hex_to_rgb( Rcpp::StringVector hex_strings ) {
  int n = hex_strings.size();
  int i;
  unsigned int colour;
  Rcpp::IntegerMatrix mat(n, 4);
  for( i = 0; i < n; i++ ) {
    Rcpp::String this_hex = hex_strings[i];
    //colour = hex_to_rgb( this_hex.get_cstring() );
    //
    // mat(i,0) = CV_RED( colour );
    // mat(i,1) = CV_GREEN( colour );
    // mat(i,2) = CV_BLUE( colour );
    // mat(i,3) = CV_ALPHA( colour );

    const char* cs = this_hex.get_cstring();

    mat(i, 0) = hex_to_r( cs );
    mat(i, 1) = hex_to_g( cs );
    mat(i, 2) = hex_to_b( cs );
    mat(i, 3) = hex_to_a( cs );

    //mat(i, Rcpp::_) = colourvalues::convert::convert_hex_to_rgb( this_hex );
  }
  return mat;
}
