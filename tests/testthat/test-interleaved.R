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
  m_palette <- colourvalues::get_palette("viridis")
  res <- colourvalues:::rcpp_colour_values_rgb_interleaved(1:5, "viridis", 1.0, repeats, totals)
  res_pal <- colourvalues:::rcpp_colour_values_rgb_interleaved(1:5, m_palette, 1.0, repeats, totals)
  expect_true(length(res) == totals * 4)
  expect_equal( res, res_pal )
  m <- matrix( res, byrow = T, ncol = 4)

  # x <- c(1,2,2,3,3,3,4,4,4,4,5,5,5,5,5)
  # y <- colour_values_rgb(x) / 255
  # expect_equal( m, y )

  ## Testing where repeats is a different length
  ## In this case, the list is just treated as-is,
  ## nothing is repeated
  x <- 1:5
  repeats <- c(1,2)
  totals <- sum(repeats)
  res <- colourvalues:::rcpp_colour_values_rgb_interleaved(x, "viridis", 1.0, repeats, totals)

  ## This is the same as repeate == 1
  expect_equal(
    res
    , colourvalues:::rcpp_colour_values_rgb_interleaved(x, "viridis", 1.0, repeats = 1, total_colours = 1)
  )

  ## The result is one colour per element
  expect_true(length(res) == length(1:5) * 4)
  m <- matrix( res, byrow = T, ncol = 4)

})

test_that("interleaved supports lists and matrix palette", {

  lst <- list(
    1:5, 5:1
  )

  pal <- matrix(
    c(
      1,0,0,
      0,1,0,
      0,0,1,
      0,0,0,
      1,0,0
    )
    , ncol = 3
    , byrow = T
  )

  pal <- ( pal * 255.0 )

  repeats <- c(1)
  totals <- sum(repeats)

  res <- colourvalues:::rcpp_colour_values_rgb_interleaved(
    x = lst[[1]], palette = pal, alpha = 1.0, repeats = repeats, total_colours = totals
  )

  res_mat <- matrix( res, ncol = 4, byrow = T) * 255
  expected_mat <- colourvalues::colour_values_rgb( 1:5, palette = pal )

  expect_equal( res_mat, expected_mat )

  res <- colourvalues:::rcpp_colour_values_rgb_interleaved(
    x = lst, palette = pal, alpha = 1.0, repeats = repeats, total_colours = totals
  )

  ## repeats is 1, so nothing has been repeated
  ## so the result matrix should have 10 rows
  res_mat <- matrix( res, ncol = 4, byrow = T)
  expect_true( sum( lengths( lst ) ) == nrow( res_mat ) )

})


