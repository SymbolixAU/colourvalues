context("palettes")

test_that("palettes are returned", {

  dfv <- viridis()
  dfp <- plasma()
  dfi <- inferno()
  dfm <- magma()
  dfc <- cividis()
  expect_true(nrow(dfv) == 256 & ncol(dfv) == 3)
  expect_true(nrow(dfp) == 256 & ncol(dfp) == 3)
  expect_true(nrow(dfi) == 256 & ncol(dfi) == 3)
  expect_true(nrow(dfm) == 256 & ncol(dfm) == 3)
  expect_true(nrow(dfc) == 256 & ncol(dfc) == 3)

  expect_error(colour_values(1:5, palette = "mypalette"), "unknown palette")

  expect_silent(colour_values(1, palette = "viridis"))
  expect_silent(colour_values(1, palette = "plasma"))
  expect_silent(colour_values(1, palette = "inferno"))
  expect_silent(colour_values(1, palette = "magma"))
  expect_silent(colour_values(1, palette = "cividis"))

})
