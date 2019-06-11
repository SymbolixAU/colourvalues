#' Colour Values RGB
#'
#' Maps colours to variables, returning a matrix of RGB(A) values
#'
#' @inheritParams colour_values
#'
#' @seealso colour_values
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
#' colour_values_rgb(1:5)
#' colour_values_rgb(1:5, include_alpha = FALSE)
#' colour_values_rgb(-25:25, n_summaries = 5)
#'
#'
#' @export
colour_values_rgb <- function( x, palette = "viridis", alpha = 255, na_colour = "#808080FF", include_alpha = TRUE, ... ) {
  palette <- palette_check( palette )
  colour_values_to_rgb(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , ...
  )
}


#' @rdname colour_values_rgb
#' @export
color_values_rgb <- colour_values_rgb

colour_values_to_rgb <- function( x, palette = "viridis", na_colour, alpha, include_alpha, ... ) {
  UseMethod("colour_values_to_rgb")
}

#' @rdname colour_values_rgb
#' @param summary logical indicating if a summary of the colours should be returned as
#' well as the full colour mapping. This will be the unique elements of \code{x} mapped to the colour.
#' @export
colour_values_to_rgb.character <- function( x, palette, alpha, na_colour, include_alpha, summary = FALSE ) {
  # rcpp_colour_values_rgb( palette, x, na_colour, alpha, include_alpha, summary )
  # print( ".character" )
  # print( include_alpha )
  colour_values_to_rgb.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
  )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.logical <- function( x, palette, alpha, na_colour, include_alpha, summary = FALSE ) {
  colour_values_to_rgb.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
  )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.factor <- function( x, palette, alpha, na_colour, include_alpha, summary = FALSE ) {
  colour_values_to_rgb.default(
    x = x
    , palette = palette
    , alpha = alpha
    , na_colour = na_colour
    , include_alpha = include_alpha
    , summary = summary
  )
}

#' @rdname colour_values_rgb
#' @param n_summaries positive integer. If supplied a summary colour palette will be returned
#' in a list, containing \code{n_summaries} equally spaced values of \code{x} in the range \code{[min(x),max(x)]},
#' and their associated colours. If a non-numeric \code{x} is used this value is ignored
#' @param format logical indicating if the summary values should be formatted. See details
#' @export
colour_values_to_rgb.Date <-  function( x, palette, alpha, na_colour, include_alpha, n_summaries = 0, format = TRUE ) {
  # colour_num_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "Date", 0 )
  colour_values_to_rgb.default(
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

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.POSIXct <-  function( x, palette, alpha, na_colour, include_alpha, n_summaries = 0, format = TRUE ) {
  #colour_num_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "POSIXct", 0 )

  colour_values_to_rgb.default(
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

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.POSIXlt <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE ) {
  # colour_num_values_with_palette_rgb( palette, as.POSIXct(x), na_colour, alpha, include_alpha, n_summaries, format, "POSIXct", 0 )
  colour_values_to_rgb.default(
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
colour_values_to_rgb.default <- function(
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

  # print("default")
  # print( include_alpha )
  # print( n_summaries )
  # print( summary )
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

