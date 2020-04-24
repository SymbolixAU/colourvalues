context("interleaved")


test_that("rgb vector returned", {

  repeats <- c(1,2,3,4,5)
  totals <- sum(repeats)
  res <- colourvalues:::rcpp_colour_values_rgb_interleaved(1:5, "viridis", 255, repeats, totals)
  expect_true(length(res) == totals * 4)
  m <- matrix( res, byrow = T, ncol = 4)


  x <- c(1,2,2,3,3,3,4,4,4,4,5,5,5,5,5)
  y <- colour_values_rgb(x)
  expect_equal( m, y )



})
