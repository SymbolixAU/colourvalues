#' @useDynLib colourvalues, .registration = TRUE
#' @importFrom Rcpp sourceCpp
NULL


alpha_check <- function( alpha ) {
  if ( length( alpha ) > 1 & length( alpha ) < 5 )
    stop("A vector of alpha values must contain at least 5 values")
}

palette_check <- function( palette ) {
  if ( nrow( palette ) < 5 )
    stop("A matrix palette must contain at least 5 rows")
}

