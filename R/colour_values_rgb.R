#' Colour Values RGB
#'
#' Maps colours to variables, returning a matrix of RGB(A) values
#'
#' @param x vector of values to map to a colour
#' @param palette colour palette. See details and examples
#' @param na_colour hex string colour to use for NA values in the form \code{#RRGGBBAA}.
#' @param alpha optional. Single value in [0,255] applied to all colours, or
#' a vector of numeric values the same length as \code{x} and at least length 5.
#' The numeric vector will be scaled into the range [0,255].
#' If a matrix palette is supplied this argument is ignored.
#' @param include_alpha logical indicating if the returned hex or matrix should include
#' the alpha values. Defaults to \code{TRUE}.
#' @param ... other arguments possed to methods
#'
#' @seealso colour_values
#'
#' @examples
#'
#' colour_values_rgb(1:5)
#' colour_values_rgb(1:5, include_alpha = FALSE)
#' colour_values_rgb(-25:25, n_summaries = 5)
#'
#'
#' @export
colour_values_rgb <- function( x, palette = "viridis", na_colour = "#808080FF", alpha = 255, include_alpha = TRUE, ... ) {
  palette <- palette_check( palette )
  colour_values_to_rgb( x, palette, na_colour, alpha, include_alpha, ... )
}

#' @rdname colour_values_rgb
#' @export
color_values_rgb <- colour_values_rgb


### RGB ------------------------------------------------------------------------

colour_num_values_with_palette_rgb <- function( palette, x, na_colour, alpha, include_alpha, ... ) {
  UseMethod("colour_num_values_with_palette_rgb")
}

#' @export
colour_num_values_with_palette_rgb.character <- function( palette, x, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits ) {
  if ( n_summaries > 0 ) {
    return( rcpp_colour_num_value_string_palette_summary_rgb( x, palette, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits ) )
  } else {
    return( rcpp_colour_num_value_string_palette_rgb( x, palette, na_colour, alpha, include_alpha ) )
  }
}

#' @export
colour_num_values_with_palette_rgb.matrix <- function( palette, x, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits ) {
  #palette_check( palette )
  if ( n_summaries > 0 ) {
    return( rcpp_colour_num_value_rgb_palette_summary_rgb( x, palette, na_colour, include_alpha, n_summaries, format, format_type, digits ) )
  } else {
    return( rcpp_colour_num_value_rgb_palette_rgb( x, palette, na_colour, include_alpha ) )
  }
}

colour_str_values_with_palette_rgb <- function( palette, x, na_colour, alpha, include_alpha, ... ) {
  UseMethod("colour_str_values_with_palette_rgb")
}

#' @export
colour_str_values_with_palette_rgb.character <- function( palette, x, na_colour, alpha, include_alpha, summary ) {
  if ( summary ) {
    return( rcpp_colour_str_value_string_palette_summary_rgb(x, palette, na_colour, alpha, include_alpha, summary ) )
  } else {
    return( rcpp_colour_str_value_string_palette_rgb(x, palette, na_colour, alpha, include_alpha ) )
  }
}

#' @export
colour_str_values_with_palette_rgb.matrix <- function( palette, x, na_colour, alpha, include_alpha, summary ) {
  #palette_check( palette )
  if ( summary ) {
    return( rcpp_colour_str_value_rgb_palette_summary_rgb( x, palette, na_colour, include_alpha, summary ) )
  } else {
    return( rcpp_colour_str_value_rgb_palette_rgb( x, palette, na_colour, include_alpha ) )
  }
}

colour_values_to_rgb <- function( x, palette = "viridis", na_colour, alpha, include_alpha, ... ) {
  UseMethod("colour_values_to_rgb")
}

#' @rdname colour_values_rgb
#' @param summary logical indicating if a summary of the colours should be returned as
#' well as the full colour mapping. This will be the unique elements of \code{x} mapped to the colour.
#' @export
colour_values_to_rgb.character <- function( x, palette, na_colour, alpha, include_alpha, summary = FALSE ) {
  colour_str_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha, summary )
}

#' @rdname colour_values_rgb
#' @param n_summaries positive integer. If supplied a summary colour palette will be returned
#' in a list, containing \code{n_summaries} equally spaced values of \code{x} in the range \code{[min(x),max(x)]},
#' and their associated colours. If a non-numeric \code{x} is used this value is ignored
#' @param format logical indicating if the summary values should be formatted. See details
#' @param digits Integer. When summarising a numeric vector you can specify
#' the number of decimal places to include in the summary values
#'
#' @details
#'
#' when \code{summary = TRUE}, the following rules are applied to the summary values
#' \itemize{
#'   \item{logical vectors are converted to "TRUE" or "FALSE" strings}
#'   \item{all other types remain as-is, unless \code{format = T} is used}
#' }
#'
#' when \code{format = TRUE},
#' \itemize{
#'   \item{numbers are converted to strings with the specified number of decimal places (using \code{digits} argument) }
#'   \item{Dates are formatted as "yyyy-mm-dd"}
#' }
#'
#' @export
colour_values_to_rgb.default <- function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE, digits = 2 ) {
  colour_num_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "numeric", digits )
}

#' #' @rdname colour_values_rgb
#' #' @export
#' colour_values_to_rgb.integer <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, ... ) {
#'   colour_num_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha, n_summaries, FALSE, "integer", 0)
#' }

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.logical <-  function( x, palette, na_colour, alpha, include_alpha, summary = FALSE ) {
  colour_values_to_rgb.character(x, palette, na_colour, alpha, include_alpha, summary)
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.factor <-  function( x, palette, na_colour, alpha, include_alpha, summary = FALSE ) {
  colour_values_to_rgb.character(x, palette, na_colour, alpha, include_alpha, summary)
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.Date <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format  = TRUE ) {
  colour_num_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "Date", 0 )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.POSIXct <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE ) {
  colour_num_values_with_palette_rgb( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "POSIXct", 0 )
}

#' @rdname colour_values_rgb
#' @export
colour_values_to_rgb.POSIXlt <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE ) {
  colour_num_values_with_palette_rgb( palette, as.POSIXct(x), na_colour, alpha, include_alpha, n_summaries, format, "POSIXct", 0 )
}


### end RGB --------------------------------------------------------------------
