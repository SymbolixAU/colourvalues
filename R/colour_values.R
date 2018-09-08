#' Colour Values
#'
#' maps colours to values
#'
#' @param x vector of values to map to a colour
#' @param palette colour palette. See details and examples
#' @param na_colour hex string colour to use for NA values
#'
#' @details
#'
#' The palette can either be
#' \itemize{
#'   \item{String - }{"viridis", "inferno", "plasma", "magma", "cividis"}
#'   \item{Matrix - }{3 columns representing the red, green and blue values in the range [0,1]}
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
#'
#' df <- data.frame(a = 10, x = 1:20)
#' df$col <- colour_values(df$x, palette = m)
#'
#' barplot(height = df$a, col = df$col, border = NA, space = 0)
#'
#' n <- 100
#' m <- grDevices::colorRamp(c("red", "green"))( (0:n)/n ) / 255
#' df <- data.frame(a = 10, x = 1:n)
#' df$col <- colour_values(df$x, palette = m)
#' barplot(height = df$a, col = df$col, border = NA, space = 0)
#'
#'
#' @export
colour_values <- function( x, palette = "viridis", na_colour = "#808080" ) {
  #palette <- match.arg(palette, choices  = c("viridis","inferno","plasma","magma","cividis"))
  UseMethod("colour_values")
}

## palette can be
## - string :: match.arg()
## - matrix - rgb values

colour_num_values_with_palette <- function( palette, x, na_colour ) {
  UseMethod("colour_num_values_with_palette")
}

#' @export
colour_num_values_with_palette.character <- function( palette, x, na_colour ) {
  palette <- match.arg(palette, choices  = c("viridis","inferno","plasma","magma","cividis"))
  rcpp_colour_num_value_string_palette_hex( x, palette, na_colour )
}

#' @export
colour_num_values_with_palette.matrix <- function( palette, x, na_colour ) {
  rcpp_colour_num_value_rgb_palette_hex( x, palette[,1], palette[,2], palette[,3], na_colour )
}

colour_str_values_with_palette <- function( palette, x, na_colour ) {
  UseMethod("colour_str_values_with_palette")
}

#' @export
colour_str_values_with_palette.character <- function( palette, x, na_colour ) {
  rcpp_colour_str_value_string_palette_hex(x, palette, na_colour)
}

#' @export
colour_str_values_with_palette.matrix <- function( palette, x, na_colour ) {
  rcpp_colour_str_value_rgb_palette_hex( x, palette[,1], palette[,2], palette[,3], na_colour )
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
  #rcpp_colour_str_value_hex( x, palette, na_colour )
  colour_str_values_with_palette( palette, x, na_colour )
}

#' @export
colour_values.default <- function( x, palette = "viridis", na_colour = "#808080" ) {
  #rcpp_colour_num_value_hex( x, palette, na_colour )
  colour_num_values_with_palette( palette, x, na_colour )
}

