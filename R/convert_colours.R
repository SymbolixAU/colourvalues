#' Convert Colour
#'
#' Converts colours between RRGGBBAA and hex strings, in both directions.
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
#' convert_colour(c("#FFAA00","#FF00AAFF"))
#'
#' convert_colour(matrix(c(255,170,0),ncol = 3))
#' convert_colour(matrix(c(255,170,0,255),ncol = 4))
#'
#'
#' @export
convert_colour <- function( x ) UseMethod("convert_colour")

#' @export
convert_colour.matrix <- function( x ) rcpp_convert_rgb_mat_to_hex( x )

#' @export
convert_colour.numeric <- function( x ) rcpp_convert_rgb_vec_to_hex( x )

#' @export
convert_colour.character <- function( x ) rcpp_convert_hex_to_rgb( x )

#' @export
convert_colour.default <- function( x ) stop("unsupported type")

#' @rdname convert_colour
#' @export
convert_colours <- convert_colour

#' @rdname convert_colour
#' @export
convert_color <- convert_colour

#' @rdname convert_colour
#' @export
convert_colors <- convert_colour
