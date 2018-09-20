#' Colour Values
#'
#' maps colours to values
#'
#' @param x vector of values to map to a colour
#' @param palette colour palette. See details and examples
#' @param na_colour hex string colour to use for NA values in the form \code{#RRGGBBAA}.
#' @param alpha optional. Single value in [0,255] applied to all colours, or
#' a vector of numeric values the same length as \code{x}. The numeric vector
#' will be scaled into the range [0,255].
#' If a matrix palette is supplied this argument is ignored.
#' @param include_alpha logical indicating if the returned hex or matrix should include
#' the alpha values. Defaults to \code{TRUE}
#'
#' @details
#'
#' The palette can either be
#' \itemize{
#'   \item{String - }{"viridis", "inferno", "plasma", "magma", "cividis"}
#'   \item{Matrix - }{At least 5 rows, and 3 (or 4) columns representing the red, green and blue (and alpha) values}
#' }
#'
#' @return string vector of hex colours
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
#' ## vector of alpha values
#' df <- data.frame(a = 10, x = 1:300, y = rep(c(1:50, 50:1), 3) )
#' df$col <- colour_values(df$x, alpha = df$y)
#' barplot(height = df$a, col = df$col, border = NA, space = 0)
#'
#' @export
colour_values <- function( x, palette = "viridis", na_colour = "#808080FF", alpha = 255, include_alpha = TRUE ) {
  colour_values_to_hex( x, palette, na_colour, alpha, include_alpha )
}

#' Colour Values RGB
#'
#' Maps colours to variables, returning a matrix of RGB(A) values
#'
#' @inheritParams colour_values
#'
#' @return matrix with the same number of rows as \code{length(x)}, and either 3 or 4 columns in
#' the order red, green, blue (and alpha). Rach row corresponds to each element of \code{x}
#'
#' @seealso colour_values
#'
#' @examples
#'
#' colour_values_rgb(1:5)
#' colour_values_rgb(1:5, include_alpha = FALSE)
#'
#'
#' @export
colour_values_rgb <- function( x, palette = "viridis", na_colour = "#808080FF", alpha = 255, include_alpha = TRUE ) {
  colour_values_to_rgb( x, palette, na_colour, alpha, include_alpha )
}

#' Color Values
#'
#' maps colours to values
#' @describeIn Colour Values
#' @inheritParams colour_values
#' @seealso colour_values
#' @export
color_values <- colour_values

#' Color Values RGB
#'
#' maps colours to values, returning a matrix of RGB(A) values
#' @inheritParams colour_values_rgb
#' @seealso colour_values_rgb
#' @export
color_values_rgb <- colour_values_rgb

### HEX ------------------------------------------------------------------------

colour_num_values_with_palette_hex <- function( palette, x, na_colour, alpha, include_alpha ) {
  UseMethod("colour_num_values_with_palette_hex")
}

#' @export
colour_num_values_with_palette_hex.character <- function( palette, x, na_colour, alpha, include_alpha ) {
  rcpp_colour_num_value_string_palette_hex( x, palette, na_colour, alpha, include_alpha )
}

#' @export
colour_num_values_with_palette_hex.matrix <- function( palette, x, na_colour, alpha, include_alpha ) {
  rcpp_colour_num_value_rgb_palette_hex( x, palette, na_colour, include_alpha )
}

colour_str_values_with_palette_hex <- function( palette, x, na_colour, alpha, include_alpha ) {
  UseMethod("colour_str_values_with_palette_hex")
}

#' @export
colour_str_values_with_palette_hex.character <- function( palette, x, na_colour, alpha, include_alpha ) {
  rcpp_colour_str_value_string_palette_hex(x, palette, na_colour, alpha, include_alpha )
}

#' @export
colour_str_values_with_palette_hex.matrix <- function( palette, x, na_colour, alpha, include_alpha ) {
  rcpp_colour_str_value_rgb_palette_hex( x, palette, na_colour, include_alpha )
}


colour_values_to_hex <- function( x, palette = "viridis", na_colour, alpha, include_alpha ) {
  UseMethod("colour_values_to_hex")
}

#' @export
colour_values_to_hex.character <- function( x, palette, na_colour, alpha, include_alpha ) {
  colour_str_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha )
}

#' @export
colour_values_to_hex.default <- function( x, palette, na_colour, alpha, include_alpha ) {
  colour_num_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha )
}

### end HEX --------------------------------------------------------------------

### RGB ------------------------------------------------------------------------

colour_num_values_with_palette_rgb <- function( palette, x, na_colour, alpha, include_alpha ) {
  UseMethod("colour_num_values_with_palette_rgb")
}

#' @export
colour_num_values_with_palette_rgb.character <- function( palette, x, na_colour, alpha, include_alpha ) {
  rcpp_colour_num_value_string_palette_rgb( x, palette, na_colour, alpha, include_alpha )
}

#' @export
colour_num_values_with_palette_rgb.matrix <- function( palette, x, na_colour, alpha, include_alpha ) {
  rcpp_colour_num_value_rgb_palette_rgb( x, palette, na_colour, include_alpha )
}

colour_str_values_with_palette_rgb <- function( palette = "viridis", x, na_colour, alpha, include_alpha ) {
  UseMethod("colour_str_values_with_palette_rgb")
}

#' @export
colour_str_values_with_palette_rgb.character <- function( palette, x, na_colour, alpha, include_alpha ) {
  rcpp_colour_str_value_string_palette_rgb(x, palette, na_colour, alpha, include_alpha )
}

#' @export
colour_str_values_with_palette_rgb.matrix <- function( palette, x, na_colour, alpha, include_alpha ) {
  rcpp_colour_str_value_rgb_palette_rgb( x, palette, na_colour, include_alpha )
}

colour_values_to_rgb <- function( x, palette = "viridis", na_colour, alpha, include_alpha ) {
  UseMethod("colour_values_to_rgb")
}

#' @export
colour_values_to_rgb.character <- function( x, palette, na_colour, alpha, include_alpha ) {
  colour_str_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha )
}

#' @export
colour_values_to_rgb.default <- function( x, palette, na_colour, alpha, include_alpha ) {
  colour_num_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha )
}

### end RGB --------------------------------------------------------------------
