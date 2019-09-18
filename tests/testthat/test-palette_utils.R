context("palette_utils")

test_that("rgb values validated",{

  expect_equal( colourvalues:::rcpp_validate_rgb_range( 1 ), 1 )
  expect_equal( colourvalues:::rcpp_validate_rgb_range( 255 ), 255 )
  expect_equal( colourvalues:::rcpp_validate_rgb_range( 256 ), 1 )
  expect_equal( colourvalues:::rcpp_validate_rgb_range( -1 ), 254 )

  expect_equal( colourvalues:::rcpp_validate_rgb_spline( 1 ), 1 )
  expect_equal( colourvalues:::rcpp_validate_rgb_spline( -1 ), 0 )
  expect_equal( colourvalues:::rcpp_validate_rgb_spline( -100 ), 0 )
  expect_equal( colourvalues:::rcpp_validate_rgb_spline( 255 ), 255 )
  expect_equal( colourvalues:::rcpp_validate_rgb_spline( 100000 ), 255 )
})


