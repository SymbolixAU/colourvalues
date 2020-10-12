context("hex_string")

test_that("hex string input is valid (issue 70)", {

  expect_error(
    colourvalues::color_values(c(0, 1, NA), include_alpha = FALSE, na_colour = "808080")
    , "colourvalues - unknown hex string, expecting # symbol"
  )
})
