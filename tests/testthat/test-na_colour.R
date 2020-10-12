context("na_colour")

test_that("na_colour doesn't include alpha if include_alpha = FALSE (issue 69)",{

  res <- colourvalues::color_values(c(NA), include_alpha = FALSE, na_colour = "#808080")
  expect_equal( res, "#808080")
  res <- colourvalues::color_values(c(NA), include_alpha = FALSE, na_colour = "#808080FF")
  expect_equal( res, "#808080")
  res <- colourvalues::color_values_rgb(c(NA), include_alpha = FALSE, na_colour = "#808080FF")
  expect_equal( res,  colourvalues::convert_color( "#808080") )

})
