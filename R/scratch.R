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
