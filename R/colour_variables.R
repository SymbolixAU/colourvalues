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
colour_variables <- function( x, palette = "viridis" ) {
  palette <- match.arg(palette, choices  = c("viridis","inferno","plasma","magma","cividis"))
  UseMethod("colour_variables")
}

#' @export
colour_variables.character <- function(x, palette = "viridis" ) {
  rcpp_colour_str_variable_hex(x, palette)
}

#' @export
colour_variables.default <- function(x, palette = "viridis" ) {
  rcpp_colour_num_variable_hex(x, palette)
}

