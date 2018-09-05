context("colourvariables")


test_that("variables mapped to colours", {
  # scales::col_numeric(palette = viridisLite::viridis, domain = 1)(1)
  #
  # colour_variables(1)
})

test_that("NAs are handled", {
  expect_true(colour_variables(NA) == "#808080")
  expect_true("#808080" %in% colour_variables(c(1,2,NA,4)))
  expect_true(sum("#808080" == colour_variables(c(1, NA)))==1)
  expect_true(sum("#808080" == colour_variables(c(1,NA,NaN,Inf,-Inf,1))) == 4)
})
