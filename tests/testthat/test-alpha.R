context("alpha")

test_that("[0,1) alpha values treated as percentage", {
  expect_true( colour_values(1, alpha = 0.5) == colour_values(1, alpha = 255 / 2) )
  expect_true( colour_values(1, alpha = 1) == colour_values(1, alpha = 255 / 255 ) )
})

test_that("alpha values > 255 are scaled", {
  expect_true( colour_values(1, alpha = 255 ) == colour_values(1, alpha = 255 * 2 + 1 ) )
  expect_true( colour_values(1, alpha = 255 ) == colour_values(1, alpha = 255 * 3 + 2 ) )
  expect_true( colour_values(1, alpha = 255 ) == colour_values(1, alpha = 255 * 10 + 9 ) )
})

test_that("alpha vector scaled to [0-255]", {
  expect_true( all( colour_values( 1:10 , alpha = 0:9 ) == colour_values( 1:10, alpha = 256:265 ) ) )
})

test_that("alpha not updated by reference", {

  v <- 1
  o <- 1
  colour_values(x = v, alpha = o)
  expect_equal( o, 1 )

  v <- c(1,1)
  o <- c(1,1)
  colour_values(x = v, alpha = o)
  expect_equal( o, c(1,1) )

  v <- 1:5
  o <- 1:5
  colour_values(x = v, alpha = o)
  expect_equal( o, 1:5 )

  v <- 1:5
  o <- rep(5,5)
  colour_values(x = v, alpha = o)
  expect_equal( o, rep(5,5) )

  df <- data.frame(id = 1:5, o = rep(5,5) )
  cols <- colour_values(x = df$id, alpha = df$o )
  expect_equal( df$o, rep(5,5) )

})


test_that("alpha is validated",{

  #define ALPHA_UNKNOWN  0
  #define ALPHA_PALETTE  1  // the alpha is on the palette
  #define ALPHA_VECTOR   2  // the alpha is a variable / vector
  #define ALPHA_CONSTANT 3  // the alpha is a constant

  x <- 1:5
  expect_equal( colourvalues:::rcpp_validate_alpha(x, 1), 1:5 )

  a <- colourvalues:::rcpp_validate_alpha(x, 2)
  expect_true( a[1] == 0.0 )
  expect_true( a[5] == 255.0 )

  expect_equal( colourvalues:::rcpp_validate_alpha(x, 3), rep(1,5) )

  x <- 1:3
  expect_equal( colourvalues:::rcpp_validate_alpha(x, 1), 1:3 )

  a <- colourvalues:::rcpp_validate_alpha(x, 2)     ## < 5 vals get filled with mean
  b <- colourvalues:::rcpp_validate_alpha(c(1,2,3,2,2), 2)
  expect_equal(a, b)

  expect_equal( colourvalues:::rcpp_validate_alpha(x, 3), rep(1,5) )

  x <- 1:10
  expect_equal( colourvalues:::rcpp_validate_alpha(x, 1), 1:10 )

  a <- colourvalues:::rcpp_validate_alpha(x, 2)
  expect_true( a[1] == 0.0 )
  expect_true( a[10] == 255.0 )

  expect_equal( colourvalues:::rcpp_validate_alpha(x, 3), rep(1,5) )

  x <- 3:4
  expect_equal( colourvalues:::rcpp_validate_alpha(x, 3), rep(x[1], 5) )

})
