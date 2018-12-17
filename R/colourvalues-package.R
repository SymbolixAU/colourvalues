#' @useDynLib colourvalues, .registration = TRUE
#' @importFrom Rcpp sourceCpp
NULL

palette_check <- function( palette ) {
  if ( nrow( palette ) < 5 )
    stop("A matrix palette must contain at least 5 rows")
}

