#' Colour Variables
#'
#' @param x
#' @param palette
#' @export
colour_variables <- function( x, palette = c("viridis","inferno","plasma","magma","cividis") ) {
  rcpp_colour_variable_rgb(x, palette)
}
