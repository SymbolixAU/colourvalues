#
#
# library(Rcpp)
# library(colourvalues)
#
# cppFunction(
#   depends = "colourvalues"
#   , includes = c('#include "colourvalues/spline.hpp"')
#   , code = '
#
#     Rcpp::NumericVector tk_spline( Rcpp::NumericVector x, Rcpp::NumericVector colours, Rcpp::NumericVector values ) {
#
#       R_xlen_t n = colours.size();
#       std::vector< double > dbl_colours( n );
#       std::vector< double > x_seq( n );
#       R_xlen_t i;
#
#       for( i = 0; i < n; ++i ) {
#         dbl_colours[ i ] = colours[ i ];
#         x_seq[ i ] = x[ i ];
#       }
#
#       tk::spline s;
#       s.set_points( x_seq, dbl_colours );
#
#       //double y = 0.7;
#       R_xlen_t vn = values.size();
#       Rcpp::NumericVector res( vn );
#
#       for(i = 0; i < vn; ++i ) {
#         double xi = values[ i ];
#         res[ i ] = s( xi );
#       }
#       return res;
#     }
#   '
# )
#
# cppFunction(
#   depends = c("BH", "colourvalues")
#   , includes = c('#include "colourvalues/colours.hpp"')
#   , code = '
#
#     Rcpp::NumericVector bh_spline( Rcpp::NumericVector values, Rcpp::NumericVector red ) {
#
#       double colours = red.size();
#       double step = 1 / ( colours - 1 );
#
#
#       // cublic_b_spoine :: vec.start, vec.end, start.time, step
#       boost::math::interpolators::cardinal_cubic_b_spline< double > spline_red( red.begin(), red.end(), 0, step );
#
#       R_xlen_t n = values.size();
#       R_xlen_t i;
#       Rcpp::NumericVector res( n  );
#       for( i = 0; i < n; ++i ) {
#         double this_x = values[ i ];
#         res[ i ] = spline_red( this_x );
#       }
#
#       return res;
#     }
#   '
# )
#
# red <- colourvalues::get_palette("viridis")[,1]
# ## the colours don't necessarily need to be scaled
# red <- red / 255
#
# # x <- c(0.1, 0.4, 1.2, 1.8, 2.0)
# # y <- c(0.1, 0.7, 0.6, 1.1, 0.9)
# #
# # tk_spline(x, y, 1.5)
# # bh_spline()
#
# start <- red[1]
# end <- red[ length( red ) ]
# step <- 1 / ( length(red) + 1)
#
# x <- seq(0, end, step)
# y <- red
# values <- 1:10
# values <- colourvalues:::rcpp_scale( values )
#
# tk_spline( x = x, colours = red, values = scaled )
# bh_spline( scaled, red )
#
# round( tk_spline(x = x, colours = red, values = scaled)  )
# round( bh_spline(scaled, red)  )
#
#
#
# values <- 1:1e2
# values <- c( values, rev(values) )
# scaled <- colourvalues:::rcpp_scale( values )
#
# tk_res <- tk_spline( scaled, red )
# bh_res <- bh_spline( scaled, red )
#
#
# all.equal( tk_res, bh_res )
#
# microbenchmark::microbenchmark(
#   bh = {
#     bh_res <- bh_spline( values, red )
#   },
#   tk = {
#     tk_res <- tk_spline( values, red )
#   },
#   times = 10
# )
#
#
# library(pracma)
#
# pracma::cubicspline( x = 1:length(red), y = red, xi = values )
