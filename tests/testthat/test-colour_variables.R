context("colourvariables")

test_that("numeric variables mapped to colours", {
  expect_true(colour_variables(1) == "#440154")
  expect_true(all(colour_variables(1:2) == c("#440154","#FDE725")))
  ## NAs
  expect_true(colour_variables(NA) == "#808080")
  expect_true("#808080" %in% colour_variables(c(1,2,NA,4)))
  expect_true(sum("#808080" == colour_variables(c(1, NA)))==1)
  expect_true(sum("#808080" == colour_variables(c(1,NA,NaN,Inf,-Inf,1))) == 6)
  expect_true("#000000" == colour_variables(NA, na_colour = "#000000"))
})

test_that("character variables mapped to colours", {
  expect_true(all(colour_variables(c("a","b")) == colour_variables(1:2)))
  expect_true(all(colour_variables(letters) == colour_variables(1:26)))
  ## NAs
  expect_true(colour_variables(NA_character_) == "#808080")
  expect_true(sum("#808080" == colour_variables(c(1,"a",NA)) ) == 1)
  expect_true(sum("#808080" == colour_variables(c("a",NA, "d","f",NA))) == 2)
})

test_that("factor variables mapped to colours", {
  f <- as.factor(letters)
  expect_true(all(colour_variables(f) == colour_variables(1:26)))
  ## NAs
  f <- as.factor(c(NA, letters, NA))
  expect_true(all(colour_variables(f) == c("#808080", colour_variables(1:26), "#808080")))
})

test_that("logical variables mapped to colours", {
  expect_true(all(colour_variables(c(F,T)) == colour_variables(1:2)))
  ## NAs
  expect_true(all(colour_variables(c(F,T,NA)) == colour_variables(c(1:2, NA))))
})

test_that("date variables mapped to colours", {
  d <- as.Date(c("2018-01-01","2018-01-01","2018-01-02"))
  expect_true(all(colour_variables(d) == colour_variables(c(1,1,2))))
  ## NAs
  expect_true(all(colour_variables(c(NA,d,NA)) == colour_variables(c(NA,1,1,2,NA))))
})

test_that("posix variables mapped to colours", {
  d <- as.POSIXct(c("2018-01-01","2018-01-01","2018-01-02"))
  expect_true(all(colour_variables(d) == colour_variables(c(1,1,2))))
  ## NAs
  expect_true(all(colour_variables(c(NA,d,NA)) == colour_variables(c(NA,1,1,2,NA))))
})


