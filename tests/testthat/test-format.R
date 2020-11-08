context("format")

test_that("correct format_type is determined",{

  expect_equal( colourvalues:::rcpp_get_format_type("abc"), "character")
  expect_equal( colourvalues:::rcpp_get_format_type(T), "character")
  expect_equal( colourvalues:::rcpp_get_format_type(factor(1)), "numeric")
  expect_equal( colourvalues:::rcpp_get_format_type(as.Date("2018-01-01")), "Date")
  expect_equal( colourvalues:::rcpp_get_format_type(as.POSIXct("2018-01-01")), "POSIXct")
  expect_equal( colourvalues:::rcpp_get_format_type(as.POSIXlt("2018-01-01")), "POSIXct")
  expect_equal( colourvalues:::rcpp_get_format_type(123), "numeric")

  ## TODO
  ## - does it make sense for a list to have a format type, should it only work on vectors?
  # expect_equal( colourvalues:::rcpp_get_format_type( list("a") ), "character")
  # colourvalues:::rcpp_get_r_class( list("a") )


  })

