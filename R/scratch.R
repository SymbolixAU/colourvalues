#
#
# ## benchmarking numbers vs categories
# n <- 1e7
# x <- rnorm(n = n)
#
# library(stringi)
# y <- do.call(paste0, Map(stri_rand_strings, n=n, length=c(5, 4, 1),
#                          pattern = c('[A-Z]', '[0-9]', '[A-Z]')))
#
#
# library(microbenchmark)
#
# microbenchmark(
#   numeric = { v1 <- colourvalues::colour_values( x ) },
#   character = { v2 <- colourvalues::colour_values( y ) },
#   times = 5
# )
#
# # Unit: seconds
# #       expr       min        lq      mean    median       uq       max neval
# #   numeric  1.609049  1.627812  1.849422  1.635453  1.67614  2.698658     5
# # character 11.787047 11.852525 12.743274 12.068627 13.64671 14.361460     5
#
#
# library(Rcpp)
#
# cppFunction('Rcpp::NumericVector range_sort( Rcpp::NumericVector x) {
#   //NumericVector y = clone(x);
#   int n = x.size() - 1;
#   std::sort(x.begin(), x.end());
#   Rcpp::NumericVector rng(2);
#   rng[0] = x[0];
#   rng[1] = x[n];
#   return rng;
# }')
#
# cppFunction('Rcpp::NumericVector range_min_max( Rcpp::NumericVector x) {
#   //NumericVector y = clone(x);
#   Rcpp::NumericVector rng(2);
#   rng[0] = min( na_omit(x) );
#   rng[1] = max( na_omit(x) );
#   return rng;
# }')
#
# cppFunction('Rcpp::NumericVector for_min_max( Rcpp::NumericVector x ) {
#   //NumericVector y = clone(x);
#   int n = x.size();
#
#   double min;
#   double max;
#   bool first_value = false;
#
#   for( int i = 0; i < n; i++) {
#
#     if( !ISNAN( x[i] ) ) {
#       if( !first_value ) {
#         min = x[i];
#         max = x[i];
#         first_value = true;
#       } else {
#         if( x[i] < min ) {
#           min = x[i];
#         } else if ( x[i] > max) {
#           max = x[i];
#         }
#       }
#     }
#   }
#   return NumericVector::create(min, max);
# }')
#
# cppFunction('Rcpp::NumericVector rng( Rcpp::NumericVector x) {
#   NumericVector y = clone(x);
#   return range(x);
# }')
#
# for_min_max(1:20)
# rng(1:20)
#
# n <- 1e7
# x <- rnorm(n = n)
#
# microbenchmark(
#   range_sort = { range_sort( x ) },
#   range_min_max = { range_min_max( x ) },
#   for_min_max = { for_min_max( x ) },
#   rng = { rng( x ) },
#   times = 25
# )
#
# # Unit: milliseconds
# #          expr      min       lq     mean   median       uq      max neval
# #    range_sort 10.59129 11.61915 12.53094 12.47773 13.46021 14.14382    25
# # range_min_max 78.81943 79.62402 83.29948 83.36582 85.20105 90.31657    25
# #   for_min_max 33.78131 34.10332 35.19830 35.19227 35.75790 37.37187    25
# #           rng 43.45526 46.92417 48.55556 48.48253 49.81096 53.31669    25
#
#
# x <- sample(1:10, size = 10)
# x[1] <- NA
# x[3] <- NA
# x[10] <- NA
#
# range_sort( x )
# range_min_max( x )
# for_min_max( x )
# rng( x )
#
# microbenchmark(
#   range_sort = { range_sort( x ) },
#   range_min_max = { range_min_max( x ) },
#   for_min_max = { for_min_max( x ) },
#   times = 2
# )
#
#
# cppFunction('Rcpp::NumericVector stl_sort( Rcpp::NumericVector x) {
#   NumericVector y = clone(x);
#   //int n = x.size() - 1;
#   std::sort(y.begin(), y.end());
#   return y;
# }')
#
# stl_sort( 20:1 )
# stl_sort( x )
#


# ## stirng vectors
#
# library(Rcpp)
# library(stringi)
#
# n <- 1e6
# x <- rnorm(n = n)
# y <- do.call(paste0, Map(stri_rand_strings, n=n, length=c(5, 4, 1),
#                          pattern = c('[A-Z]', '[0-9]', '[A-Z]')))
#
# cppFunction('Rcpp::NumericVector resolve_string_vector( Rcpp::StringVector x ) {
#     bool anyNa = Rcpp::any( is_na( x ) );
#
#     Rcpp::StringVector lvls = Rcpp::sort_unique( x );
#     Rcpp::IntegerVector out = Rcpp::match( x, lvls );
#
#     if ( anyNa ) {
#       int na_value = Rcpp::max( out );
#       int int_s = NA_INTEGER;
#       std::replace( out.begin(), out.end(), na_value, int_s);
#     }
#     return Rcpp::as< Rcpp::NumericVector >( out );
# }')
#
#
# res <- resolve_string_vector( x )
#
# microbenchmark(
#   numeric = { v1 <- colourvalues::colour_values( x ) },
#   character = { v2 <- colourvalues::colour_values( y ) },
#   internals = { v3 <- resolve_string_vector( y ) },
#   times = 5
# )
#
# n <- 1e6
# y <- do.call(paste0, Map(stri_rand_strings, n=n, length=c(5, 4, 1),
#                          pattern = c('[A-Z]', '[0-9]', '[A-Z]')))
#
# cppFunction('Rcpp::StringVector rcpp_sort( Rcpp::StringVector x ) {
#   Rcpp::StringVector lvls = Rcpp::sort_unique( x );
#   return lvls;
# }')
#
# cppFunction('Rcpp::StringVector std_sort( Rcpp::StringVector x ) {
#   Rcpp::StringVector y = clone( x );
#   std::sort(y.begin(), y.end());
#   y.erase( std::unique( y.begin(), y.end()), y.end());
#   return y;
# }')
#
# microbenchmark(
#   rcpp = { res1 <- rcpp_sort( y ) },
#   std = { res2 <- std_sort( y ) },
#   times = 10
# )
#
# # Unit: seconds
# # expr     min       lq     mean   median       uq      max neval
# # rcpp 7.71686 7.836721 8.321830 7.945700 7.985845 12.09966    10
# #  std 3.29611 3.416647 4.582591 3.841523 4.440750 11.43789    10
#
# ## TODO( how are NAs sorted in both )
#
# y2 <- y[1:5]
#
# y2[1] <- NA
# y2[3] <- NA
#
# rcpp_sort( y2 )
# std_sort( y2 )
#
# ## the same...

#
# col <- "#00FF00FF"
# col <- rep(col, 1e6)
#
# library(microbenchmark)
#
# microbenchmark(
#   cv = { colourvalues::convert_colours( col) },
#   gr = { grDevices::col2rgb(col, alpha = TRUE) },
#   times = 10
# )

# Unit: milliseconds
#   expr       min        lq     mean    median        uq       max neval
#     cv  30.81213  32.73352  47.4408  35.59811  76.95149  81.37984    10
# cv_old 272.52093 276.65413 290.7468 285.09019 295.67034 327.61521    10
#     gr  36.80980  39.10075  41.6736  41.57528  44.91530  46.51591    10


## differences:
## - colourvalues automatically handles alpha?

# ## hex_to_rgb
# library(Rcpp)
#
# #"FF" ->
#
# cppFunction('int hex_to_rgb( const char* col) {
#   return std::stoul( col, nullptr, 16);
# }')
#
# hex_to_rgb("0A")



