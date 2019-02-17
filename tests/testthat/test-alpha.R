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
