#' Convert
#'
#' Converts colours between RRGGBBAA and hex strings, in both directions
#'
#' @param x character vector of hex strings, or numeric matrix of RRGGBBAA values
#'
#'
#' @details
#' If a combination of hex strings with and without alpha values are supplied, those
#' without are assumed to have an alpha value of \code{FF} and will be returned in the
#' RRGGBBAA matrix
#'
#' @examples
#'
#' convert_colour(c("#FFAA00"))
#'
#'
#' @export
convert_colour <- function( x ) UseMethod("convert_colour")

#' @export
convert_colour.matrix <- function( x ) {
  ## TODO( convert RGBA to hex )
}


#' @export
convert_colour.character <- function( x ) {
  ## TODO (convert hex to RGBA matrix)
  rcpp_convert_hex_to_rgb( x )
}
