

# library(microbenchmark)
#
# l <- list(
#   x = 1:100
#   , y = letters
#   , z = list( list( x = letters ) )
#   , a = list( list( list( x = list( letters ) ) ) )
# )
#
# microbenchmark(
#   me = { colourvalues:::list_size( l ) }
#   , base = { rapply(l, length) }
#   , times = 25
# )
