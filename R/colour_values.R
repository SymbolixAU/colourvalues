#' Colour Values
#'
#' maps colours to values
#'
#' @param x vector of values to map to a colour
#' @param palette palette to use
#' @param na_colour hex string colour to use for NA values
#'
#' @examples
#'
#' colour_values(x = 1:5) ## default is "viridis"
#' colour_values(x = 1:5, palette = "inferno")
#' colour_values(x = 1:5, palette = "plasma")
#' colour_values(x = 1:5, palette = "magma")
#' colour_values(x = 1:5, palette = "cividis")
#'
#' @export
colour_values <- function( x, palette = "viridis", na_colour = "#808080" ) {
  palette <- match.arg(palette, choices  = c("viridis","inferno","plasma","magma","cividis"))
  UseMethod("colour_values")
}

#' color values
#' maps colours to values
#' @describeIn
#' @inheritParams colour_values
#' @seealso colour_values
#' @export
color_values <- colour_values

#' @export
colour_values.character <- function( x, palette = "viridis", na_colour = "#808080" ) {
  rcpp_colour_str_variable_hex( x, palette, na_colour )
}

#' @export
colour_values.default <- function( x, palette = "viridis", na_colour = "#808080" ) {
  rcpp_colour_num_variable_hex( x, palette, na_colour )
}

