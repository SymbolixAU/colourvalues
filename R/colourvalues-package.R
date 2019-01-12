#' @useDynLib colourvalues, .registration = TRUE
#' @importFrom Rcpp sourceCpp
NULL

# palette_check <- function( palette ) {
#   if ( nrow( palette ) < 5 )
#     stop("A matrix palette must contain at least 5 rows")
# }

palette_check <- function( palette ) UseMethod("palette_check")

#' @export
palette_check.character <- function( palette ) tolower( gsub("\\.","_", palette ) )

#' @export
palette_check.default <- function( palette ) palette

#' @export
palette_check.matrix <- function( palette ) {
  if ( nrow( palette ) < 5 )
    stop("A matrix palette must contain at least 5 rows")
  return( palette )
}
