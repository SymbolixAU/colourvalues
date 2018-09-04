#' Colour Variables
#'
#' maps a colours to variables
#'
#' @param x vector of values to map to a colour
#' @param palette palette to use
#'
#' @examples
#'
#' colour_variables(x = 1:5) ## default is "viridis"
#' colour_variables(x = 1:5, palette = "inferno")
#' colour_variables(x = 1:5, palette = "plasma")
#' colour_variables(x = 1:5, palette = "magma")
#' colour_variables(x = 1:5, palette = "cividis")
#'
#' @export
colour_variables <- function( x, palette = c("viridis","inferno","plasma","magma","cividis") ) {
  palette <- match.arg(palette)
  rcpp_colour_variable_hex(x, palette)
}
