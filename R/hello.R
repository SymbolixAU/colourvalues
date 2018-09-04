# Hello, world!
#
# This is an example function named 'hello'
# which prints 'Hello, world!'.
#
# You can learn more about package authoring with RStudio at:
#
#   http://r-pkgs.had.co.nz/
#
# Some useful keyboard shortcuts for package authoring:
#
#   Build and Reload Package:  'Cmd + Shift + B'
#   Check Package:             'Cmd + Shift + E'
#   Test Package:              'Cmd + Shift + T'

hello <- function() {
  print("Hello, world!")
}



# library(microbenchmark)
#
# microbenchmark(
#   viridis = { viridisLite::viridis(256) },
#   rcpp = { RcppViridis:::colour_test()  }
# )

# a == magma
# B == inferno
# c == plasma
# d == viridis
# E == cividis
#
# map <- viridisLite::viridis.map[viridisLite::viridis.map$opt == "D", ]
# head(as.data.frame(RcppViridis:::colour_test()))
# head(map)
# map_cols <- grDevices::rgb(map$R, map$G, map$B)  ## converts to hex
#
# fn_cols <- grDevices::colorRamp(map_cols, space = "Lab",interpolate = "spline")
#
# begin <- 0
# end <- 1
# n <- 300
# cols <- fn_cols(seq(begin, end, length.out = n))/255
#
# grDevices::rgb(cols[, 1], cols[, 2], cols[, 3], alpha = alpha)


# df <- as.data.frame( RcppViridis:::colour_test() )

## pass the 'normalised' variables into the spline functino? to get the actual rgb values?


# myVar <- sample(1:10, size = 20, replace = T)
# RcppViridis:::colour_variable( myVar, 'plasma' )

