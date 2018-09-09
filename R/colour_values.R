#' Colour Values
#'
#' maps colours to values
#'
#' @param x vector of values to map to a colour
#' @param palette colour palette. See details and examples
#' @param na_colour hex string colour to use for NA values
#' @param alpha optional. Single value in [0,1] applied to all colours.
#' Defaults to 1. If a matrix palette is supplied this argument is ignored.
#'
#' @details
#'
#' The palette can either be
#' \itemize{
#'   \item{String - }{"viridis", "inferno", "plasma", "magma", "cividis"}
#'   \item{Matrix - }{At least 5 rows, and 3 (or 4) columns representing the red, green and blue (and alpha) values}
#' }
#'
#' @examples
#'
#' ## in-built palettes
#' colour_values(x = 1:5) ## default is "viridis"
#' colour_values(x = 1:5, palette = "inferno")
#' colour_values(x = 1:5, palette = "plasma")
#' colour_values(x = 1:5, palette = "magma")
#' colour_values(x = 1:5, palette = "cividis")
#'
#' ## matrix palette
#' r <- seq(0, 1, length.out = 20)
#' g <- seq(0.75, 0.1, length.out = 20)
#' b <- seq(0, 0.5, length.out = 20)
#' m <- cbind(r,g,b)
#' df <- data.frame(a = 10, x = 1:20)
#' df$col <- colour_values(df$x, palette = m)
#' barplot(height = df$a, col = df$col, border = NA, space = 0)
#'
#' n <- 100
#' m <- grDevices::colorRamp(c("red", "green"))( (1:n)/n )
#' df <- data.frame(a = 10, x = 1:n)
#' df$col <- colour_values(df$x, palette = m)
#' barplot(height = df$a, col = df$col, border = NA, space = 0)
#'
#' ## with an alpha column on the palette
#' n <- 100
#' m <- grDevices::colorRamp(c("red", "green"))( (1:n)/n )
#' m <- cbind(m, seq(0, 255, length.out = 100))
#' df <- data.frame(a = 10, x = 1:n)
#' df$col <- colour_values(df$x, palette = m)
#' barplot(height = df$a, col = df$col, border = NA, space = 0)
#'
#' ## single alpha value for all colours
#' df <- data.frame(a = 10, x = 1:255)
#' df$col <- colour_values(df$x, alpha = 50)
#' barplot(height = df$a, col = df$col, border = NA, space = 0)
#'
#' @export
colour_values <- function( x, palette = "viridis", na_colour = "#808080FF", alpha = 1) {
  UseMethod("colour_values")
}

colour_num_values_with_palette <- function( palette, x, na_colour, alpha = 1) {
  UseMethod("colour_num_values_with_palette")
}

#' @export
colour_num_values_with_palette.character <- function( palette, x, na_colour, alpha = 1 ) {
  palette <- match.arg(palette, choices  = c("viridis","inferno","plasma","magma","cividis"))
  rcpp_colour_num_value_string_palette_hex( x, palette, na_colour, alpha )
}

#' @export
colour_num_values_with_palette.matrix <- function( palette, x, na_colour, alpha = 1 ) {
  rcpp_colour_num_value_rgb_palette_hex( x, palette, na_colour )
}

#' @export
colour_num_values_with_palette.function <- function( palette, x, na_colour, alpha = 1 ) {
  print ("functional palette")
}

colour_str_values_with_palette <- function( palette, x, na_colour, alpha = 1 ) {
  UseMethod("colour_str_values_with_palette")
}

#' @export
colour_str_values_with_palette.character <- function( palette, x, na_colour, alpha = 1 ) {
  palette <- match.arg(palette, choices  = c("viridis","inferno","plasma","magma","cividis"))
  rcpp_colour_str_value_string_palette_hex(x, palette, na_colour, alpha )
}

#' @export
colour_str_values_with_palette.matrix <- function( palette, x, na_colour, alpha = 1 ) {
  rcpp_colour_str_value_rgb_palette_hex( x, palette, na_colour )
}

#' @export
colour_str_values_with_palette.function <- function( palette, x, na_colour, alpha = 1 ) {
  print ("functional palette")
}

#' color values
#' maps colours to values
#' @describeIn
#' @inheritParams colour_values
#' @seealso colour_values
#' @export
color_values <- colour_values

#' @export
colour_values.character <- function( x, palette = "viridis", na_colour = "#808080FF", alpha = 1 ) {
  colour_str_values_with_palette( palette, x, na_colour, alpha )
}

#' @export
colour_values.default <- function( x, palette = "viridis", na_colour = "#808080FF", alpha = 1 ) {
  colour_num_values_with_palette( palette, x, na_colour, alpha )
}

