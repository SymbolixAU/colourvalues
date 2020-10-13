context("interleaved")

test_that("interleaved results in [0,1]", {

  repeats <- c(1)
  totals <- sum(repeats)
  res <- colourvalues:::rcpp_colour_values_rgb_interleaved(1, "viridis", 1.0, repeats, totals)
  expect_true( all( res <= 1.0 ) )

})

test_that("interleaved vector returned", {

  repeats <- c(1,2,3,4,5)
  totals <- sum(repeats)
  res <- colourvalues:::rcpp_colour_values_rgb_interleaved(1:5, "viridis", 1.0, repeats, totals)
  expect_true(length(res) == totals * 4)
  m <- matrix( res, byrow = T, ncol = 4)

  x <- c(1,2,2,3,3,3,4,4,4,4,5,5,5,5,5)
  y <- colour_values_rgb(x) / 255
  # expect_equal( m, y )

  ## Testing where repeats is a different length
  ## TODO:
  ## - test where repeats.length != x.length
  # x <- 1:5
  # repeats <- c(1)
  # totals <- sum(repeats)
  # res <- colourvalues:::rcpp_colour_values_rgb_interleaved(x, "viridis", 1.0, repeats, totals)
  # expect_true(length(res) == totals * 4)
  # m <- matrix( res, byrow = T, ncol = 4)
  #
  # x <- c(1,2,2,3,3,3,4,4,4,4,5,5,5,5,5)
  # y <- colour_values_rgb(x)
  # expect_equal( m, y )

})


