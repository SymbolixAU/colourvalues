#
# x <- 1:10
# pal <- "viridis"
# alpha <- 1
# repeats <- c(2,2,2,2,5,3,2,1,1,10)
# total <- sum( repeats )
#
# colourvalues:::rcpp_colour_values_rgb_interleaved(
#   x, pal, alpha, repeats, total, n_summaries = 5
# )
#
#
# library(sf)
# library(mapdeck)
#
# set_token( secret::get_secret("mapbox") )
#
# nc <- sf::st_read( system.file("./shape/nc.shp", package = "sf"))
#
# sf_poly <- sfheaders::sf_cast( nc, "POLYGON", close = TRUE )
#
# df <- sfheaders::sf_to_df( sf_poly, fill = TRUE )
# df$colour <- df$x ## use longitude as colour
# df$colour2 <- sample( 1:nrow( df ) )
#
# sf_poly <- sfheaders::sf_polygon(
#   obj = df
#   , x = "x"
#   , y = "y"
#   , keep = TRUE
#   , list_columns = c("colour")
#   , polygon_id = "polygon_id"
#   , linestring_id = "linestring_id"
# )
#
# res <- interleave:::rcpp_interleave_triangle( sf_poly$geometry, list( sf_poly$colour ) )
#
# colourvalues:::rcpp_colour_values_rgb_interleaved(
#   res$properties, "viridis", 1,
# )
# res$properties
#
#
