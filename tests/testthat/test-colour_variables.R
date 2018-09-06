context("colourvalues")

test_that("numeric values mapped to colours", {
  expect_true(colour_values(1) == "#440154")
  expect_true(all(colour_values(1:2) == c("#440154","#FDE725")))
  ## NAs
  expect_true(colour_values(NA) == "#808080")
  expect_true("#808080" %in% colour_values(c(1,2,NA,4)))
  expect_true(sum("#808080" == colour_values(c(1, NA)))==1)
  expect_true(sum("#808080" == colour_values(c(1,NA,NaN,Inf,-Inf,1))) == 6)
  expect_true("#000000" == colour_values(NA, na_colour = "#000000"))
})

test_that("character values mapped to colours", {
  expect_true(all(colour_values(c("a","b")) == colour_values(1:2)))
  expect_true(all(colour_values(letters) == colour_values(1:26)))
  ## NAs
  expect_true(colour_values(NA_character_) == "#808080")
  expect_true(sum("#808080" == colour_values(c(1,"a",NA)) ) == 1)
  expect_true(sum("#808080" == colour_values(c("a",NA, "d","f",NA))) == 2)
})

test_that("factor values mapped to colours", {
  f <- as.factor(letters)
  expect_true(all(colour_values(f) == colour_values(1:26)))
  ## NAs
  f <- as.factor(c(NA, letters, NA))
  expect_true(all(colour_values(f) == c("#808080", colour_values(1:26), "#808080")))
})

test_that("logical values mapped to colours", {
  expect_true(all(colour_values(c(F,T)) == colour_values(1:2)))
  ## NAs
  expect_true(all(colour_values(c(F,T,NA)) == colour_values(c(1:2, NA))))
})

test_that("date values mapped to colours", {
  d <- as.Date(c("2018-01-01","2018-01-01","2018-01-02"))
  expect_true(all(colour_values(d) == colour_values(c(1,1,2))))
  ## NAs
  expect_true(all(colour_values(c(NA,d,NA)) == colour_values(c(NA,1,1,2,NA))))
})

test_that("posix values mapped to colours", {
  d <- as.POSIXct(c("2018-01-01","2018-01-01","2018-01-02"))
  expect_true(all(colour_values(d) == colour_values(c(1,1,2))))
  ## NAs
  expect_true(all(colour_values(c(NA,d,NA)) == colour_values(c(NA,1,1,2,NA))))
})


