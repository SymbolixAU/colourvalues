#' Colour Values
#'
#' maps colours to values
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
#' @seealso colour_values_rgb
#'
#' @details
#'
#' The palette can either be
#' \itemize{
#'   \item{String - }{"viridis", "inferno", "plasma", "magma", "cividis"}
#'   \item{Matrix - }{At least 5 rows, and 3 (or 4) columns representing the red, green and blue (and alpha) values}
#' }
#'
#' The \code{palette} (and \code{alpha} argument when using a vector) requires 5
#' rows because the colours are interpolated using a cubic b-spline. This method
#' requires 5 values.
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
#' ## returning a summary palette
#' colour_values(-10:10, n_summaries = 5)
#'
#' @export
colour_values <- function( x, palette = "viridis", na_colour = "#808080FF", alpha = 255, include_alpha = TRUE, ... ) {
  alpha_check( alpha )
  colour_values_to_hex( x, palette, na_colour, alpha, include_alpha, ... )
}

#' @rdname colour_values
#' @export
color_values <- colour_values



### HEX ------------------------------------------------------------------------

colour_num_values_with_palette_hex <- function( palette, x, na_colour, alpha, include_alpha, ... ) {
  UseMethod("colour_num_values_with_palette_hex")
}

#' @export
colour_num_values_with_palette_hex.character <- function( palette, x, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits ) {
  if ( n_summaries > 0 ) {
    return( rcpp_colour_num_value_string_palette_summary_hex( x, palette, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits ) )
  } else {
    return( rcpp_colour_num_value_string_palette_hex( x, palette, na_colour, alpha, include_alpha ) )
  }
}

#' @export
colour_num_values_with_palette_hex.matrix <- function( palette, x, na_colour, alpha, include_alpha, n_summaries, format, format_type, digits ) {
  palette_check( palette )
  if( n_summaries > 0 ) {
    return( rcpp_colour_num_value_rgb_palette_summary_hex( x, palette, na_colour, include_alpha, n_summaries, format, format_type, digits ) )
  } else {
    return( rcpp_colour_num_value_rgb_palette_hex( x, palette, na_colour, include_alpha ) )
  }

}

colour_str_values_with_palette_hex <- function( palette, x, na_colour, alpha, include_alpha, ... ) {
  UseMethod("colour_str_values_with_palette_hex")
}

#' @export
colour_str_values_with_palette_hex.character <- function( palette, x, na_colour, alpha, include_alpha, summary ) {
  if( summary ) {
    return( rcpp_colour_str_value_string_palette_summary_hex(x, palette, na_colour, alpha, include_alpha, summary ) )
  } else {
    rcpp_colour_str_value_string_palette_hex(x, palette, na_colour, alpha, include_alpha )
  }

}

#' @export
colour_str_values_with_palette_hex.matrix <- function( palette, x, na_colour, alpha, include_alpha, summary ) {
  palette_check( palette )
  if ( summary ) {
    return( rcpp_colour_str_value_rgb_palette_summary_hex( x, palette, na_colour, include_alpha, summary ) )
  } else {
    return( rcpp_colour_str_value_rgb_palette_hex( x, palette, na_colour, include_alpha ) )
  }
}


colour_values_to_hex <- function( x, palette = "viridis", na_colour, alpha, include_alpha, ... ) {
  UseMethod("colour_values_to_hex")
}

#' @rdname colour_values
#' @param summary logical indicating if a summary of the colours should be returned as
#' well as the full colour mapping. This will be the unique elements of \code{x} mapped to the colour.
#' @export
colour_values_to_hex.character <- function( x, palette, na_colour, alpha, include_alpha, summary = FALSE ) {
  colour_str_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha, summary )
}

#' @rdname colour_values
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
colour_values_to_hex.default <- function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE, digits = 2 ) {
  colour_num_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "numeric", digits )
}

#' #' @rdname colour_values_rgb
#' #' @export
#' colour_values_to_hex.integer <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, ...) {
#'   colour_num_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha, n_summaries, FALSE, "integer", 0)
#' }

#' @rdname colour_values
#' @export
colour_values_to_hex.logical <-  function( x, palette, na_colour, alpha, include_alpha, summary = FALSE ) {
  colour_values_to_hex.character(x, palette, na_colour, alpha, include_alpha, summary)
}

#' @rdname colour_values
#' @export
colour_values_to_hex.factor <-  function( x, palette, na_colour, alpha, include_alpha, summary = FALSE ) {
  colour_values_to_hex.character(x, palette, na_colour, alpha, include_alpha, summary)
}

#' @rdname colour_values
#' @export
colour_values_to_hex.Date <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE ) {
  colour_num_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "Date", 0 )
}

#' @rdname colour_values
#' @export
colour_values_to_hex.POSIXct <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE ) {
  colour_num_values_with_palette_hex( palette, x, na_colour, alpha, include_alpha, n_summaries, format, "POSIXct", 0 )
}

#' @rdname colour_values
#' @export
colour_values_to_hex.POSIXlt <-  function( x, palette, na_colour, alpha, include_alpha, n_summaries = 0, format = TRUE ) {
  colour_num_values_with_palette_hex( palette, as.POSIXct(x), na_colour, alpha, include_alpha, n_summaries, format, "POSIXct", 0 )
}


### end HEX --------------------------------------------------------------------

