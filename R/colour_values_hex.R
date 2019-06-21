#' Colour Values
#'
#' maps colours to values
#'
#' @param x vector of values to map to a colour
#' @param palette colour palette. See details and examples
#' @param na_colour hex string colour to use for NA values in the form \code{#RRGGBBAA}.
#' @param alpha optional. Single value in [0,255] applied to all colours,
#' or a decimal in [0, 1) (to indicate a percentage, noting 1 is excluded),
#' or a vector of numeric values the same length as \code{x}.
#' The numeric vector will be scaled into the range [0,255].
#' If a matrix palette is supplied this argument is ignored.
#' @param include_alpha logical indicating if the returned hex or matrix should include
#' the alpha values. Defaults to \code{TRUE}.
#' @param ... other arguments possed to methods
#'
#' @seealso colour_values_rgb
#'
#' @details
#'
#' The palette can either be
#' \itemize{
#'   \item{String - }{use \code{colour_palettes()} to view available palettes}
#'   \item{Matrix - }{At least 5 rows, and 3 (or 4) columns representing the red, green and blue (and alpha) values}
#' }
#'
#' The matrix \code{palette} requires 5 rows because the colours are interpolated using a
#' cubic b-spline. This method requires 5 values.
#'
#' @examples
#'
#' ## in-built palettes
#' colour_values(x = 1:5) ## default is "viridis"
#' colour_values(x = 1:5, palette = "inferno")
#' colour_values(x = 1:5, palette = "plasma")
#' colour_values(x = 1:5, palette = "magma")
#' colour_values(x = 1:5, palette = "cividis")
#' colour_values(x = 1:5, palette = "rainbow")
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
#' ## returning a summary palette
#' colour_values(-10:10, n_summaries = 5)
#'
#' @export
colour_values <- function( x, palette = "viridis", alpha = 255, na_colour = "#808080FF", include_alpha = TRUE, ... ) {
  palette <- palette_check( palette )
  colour_values_to_hex(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , ...
  )
}


#' @rdname colour_values
#' @export
color_values <- colour_values

colour_values_to_hex <- function( x, palette = "viridis", na_colour, alpha, include_alpha, ... ) {
  UseMethod("colour_values_to_hex")
}

#' @rdname colour_values
#' @param summary logical indicating if a summary of the colours should be returned as
#' well as the full colour mapping. This will be the unique elements of \code{x} mapped to the colour.
#' @export
colour_values_to_hex.character <- function( x, palette, alpha, na_colour, include_alpha, summary = FALSE ) {
  # rcpp_colour_values_hex( palette, x, na_colour, alpha, include_alpha, summary )
  # print( ".character" )
  # print( include_alpha )
  colour_values_to_hex.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
  )
}

#' @rdname colour_values
#' @export
colour_values_to_hex.logical <- function( x, palette, alpha, na_colour, include_alpha, summary = FALSE ) {
  colour_values_to_hex.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
  )
}

#' @rdname colour_values
#' @export
colour_values_to_hex.factor <- function( x, palette, alpha, na_colour, include_alpha, summary = FALSE ) {
  colour_values_to_hex.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
  )
}

#' @rdname colour_values
#' @param n_summaries positive integer. If supplied a summary colour palette will be returned
#' in a list, containing \code{n_summaries} equally spaced values of \code{x} in the range \code{[min(x),max(x)]},
#' and their associated colours. If a non-numeric \code{x} is used this value is ignored
#' @param format logical indicating if the summary values should be formatted. See details
#' @export
colour_values_to_hex.Date <-  function( x, palette, alpha, na_colour, include_alpha, n_summaries = 0, format = TRUE ) {
  # colour_num_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "Date", 0 )
  colour_values_to_hex.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , n_summaries = n_summaries
    , format = format
    , digits = 0
  )
}

#' @rdname colour_values
#' @export
colour_values_to_hex.POSIXct <-  function( x, palette, alpha, na_colour, include_alpha, n_summaries = 0, format = TRUE ) {
  #colour_num_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "POSIXct", 0 )

  colour_values_to_hex.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , n_summaries = n_summaries
    , format = format
    , digits = 0
    )
}

#' @rdname colour_values
#' @export
colour_values_to_hex.POSIXlt <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE ) {
  # colour_num_values_with_palette_hex( palette, as.POSIXct(x), na_colour, alpha, include_alpha, n_summaries, format, "POSIXct", 0 )
  colour_values_to_hex.default(
    x = as.POSIXct( x )
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , n_summaries = n_summaries
    , format = format
    , digits = 0
  )
}


#' @export
colour_values_to_hex.default <- function(
  x,
  palette,
  alpha,
  na_colour,
  include_alpha,
  format = TRUE,
  digits = 2,
  summary = FALSE,
  n_summaries = 0
  ) {

  rcpp_colour_values_hex(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , format = format
    , digits = digits
    , summary = summary
    , n_summaries = n_summaries
    )
}

