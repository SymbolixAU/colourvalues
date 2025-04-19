#' Colour Values RGB
#'
#' Maps colours to values, returning a matrix of RGB(A) values
#'
#' @inheritParams colour_values
#'
#' @seealso colour_values
#'
#' @details
#'
#' The palette can either be
#'  * String - use \code{colour_palettes()} to view available palettes
#'  * Matrix - At least 5 rows, and 3 (or 4) columns representing the red, green and blue (and alpha) values
#'
#' The matrix \code{palette} requires 5 rows because the colours are interpolated using a
#' cubic b-spline. This method requires 5 values.
#'
#' @examples
#'
#' colour_values_rgb(1:5)
#' colour_values_rgb(1:5, include_alpha = FALSE)
#' colour_values_rgb(-25:25, n_summaries = 5)
#'
#'
#' @export
colour_values_rgb <- function( x, palette = "viridis", alpha = 255, na_colour = "#808080FF",
                               include_alpha = TRUE, summary = FALSE, n_summaries = 0,
                               format = TRUE, digits = 2 ) {
  palette <- palette_check( palette )
  colour_values_to_rgb(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
    , n_summaries = n_summaries
    , format = format
    , digits = digits
  )
}


#' @rdname colour_values_rgb
#' @export
color_values_rgb <- colour_values_rgb

colour_values_to_rgb <- function( x, palette, alpha, na_colour, include_alpha, summary, n_summaries, format, digits ) {
  UseMethod("colour_values_to_rgb")
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.character <- function( x, palette, alpha, na_colour, include_alpha, summary, n_summaries, format, digits ) {
  colour_values_to_rgb.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
    , n_summaries = n_summaries
    , format = format
    , digits = digits
  )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.logical <- function( x, palette, alpha, na_colour, include_alpha, summary, n_summaries, format, digits ) {
  colour_values_to_rgb.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
    , n_summaries = n_summaries
    , format = format
    , digits = digits
  )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.factor <- function( x, palette, alpha, na_colour, include_alpha, summary, n_summaries, format, digits ) {
  colour_values_to_rgb.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
    , n_summaries = n_summaries
    , format = format
    , digits = digits
  )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.Date <-  function( x, palette, alpha, na_colour, include_alpha, summary, n_summaries, format, digits ) {
  colour_values_to_rgb.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
    , n_summaries = n_summaries
    , format = format
    , digits = 0
  )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.POSIXct <-  function( x, palette, alpha, na_colour, include_alpha, summary, n_summaries, format, digits ) {

  colour_values_to_rgb.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
    , n_summaries = n_summaries
    , format = format
    , digits = 0
  )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.POSIXlt <-  function( x, palette, alpha, na_colour, include_alpha, summary, n_summaries, format, digits ) {
  colour_values_to_rgb.default(
    x = as.POSIXct( x )
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
    , n_summaries = n_summaries
    , format = format
    , digits = 0
  )
}


#' @export
colour_values_to_rgb.default <- function(
    x,
    palette,
    alpha,
    na_colour,
    include_alpha,
    summary,
    n_summaries,
    format,
    digits
) {

  rcpp_colour_values_rgb(
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

