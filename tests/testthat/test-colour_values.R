context("colourvalues")

test_that("numeric values mapped to colours", {
  expect_true(colour_values(1) == "#440154FF")
  expect_true(all(colour_values(1:2) == c("#440154FF","#FDE725FF")))
  ## NAs
  expect_true(colour_values(NA) == "#808080FF")
  expect_true("#808080FF" %in% colour_values(c(1,2,NA,4)))
  expect_true(sum("#808080FF" == colour_values(c(1, NA)))==1)
  expect_true(sum("#808080FF" == colour_values(c(1,NA,NaN,Inf,-Inf,1))) == 6)
  expect_true("#000000FF" == colour_values(NA, na_colour = "#000000FF"))
})

test_that("character values mapped to colours", {
  expect_true(all(colour_values(c("a","b")) == colour_values(1:2)))
  expect_true(all(colour_values(letters) == colour_values(1:26)))
  ## NAs
  expect_true(colour_values(NA_character_) == "#808080FF")
  expect_true(sum("#808080FF" == colour_values(c(1,"a",NA)) ) == 1)
  expect_true(sum("#808080FF" == colour_values(c("a",NA, "d","f",NA))) == 2)
})

test_that("factor values mapped to colours", {
  f <- as.factor(letters)
  expect_true(all(colour_values(f) == colour_values(1:26)))
  ## NAs
  f <- as.factor(c(NA, letters, NA))
  expect_true(all(colour_values(f) == c("#808080FF", colour_values(1:26), "#808080FF")))
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

test_that("matrix palette accepted", {
  ##
  m <- grDevices::colorRamp(c("red","green","blue"))(0:4/4)
  expect_true(all(colour_values(1:5, palette = m) == c("#FF0000FF", "#57B1F7FF", "#F6D435FF", "#041AE1FF", "#F5E921FF")))
  ## This doesn't exactly equal
  #grDevices::colorRampPalette(c("red","green","blue"))(5)
  ## because of boost's interpolation
  ## TODO(is this correct?)

  expect_error(
    colour_values(1:5, palette = m[,1:2])
    #, "Matrix palette needs either 3 (R, G, B) or 4 (R, G, B, A) columns"
    )

  alpha <- c(0, 100, 150, 200, 255)
  m <- cbind( grDevices::colorRamp(c("red","green","blue"))(0:4/4), alpha )
  colour_values(1:5, palette = m)
  expect_true(all(colour_values(1:5, palette = m) == c("#FF000000", "#57B1F764", "#F6D43596", "#041AE1C8", "#F5E921FF")))

})

test_that("alpha values applied", {
  expect_true(all(substr(colour_values(1:5),8,9) == "FF"))
  expect_true(all(substr(colour_values(1:5, alpha = 0.0),8,9) == "00"))
  expect_true(all(substr(colour_values(1:5, alpha = 128),8,9) == "80"))
  expect_true(all(substr(colour_values(1:5, alpha = 64),8,9) == "40"))
  expect_true(all(substr(colour_values(1:5, alpha = 192),8,9) == "C0"))

  expect_true(all(substr(colour_values(1:5, alpha = 0),8,9) == "00"))

  expect_error(colour_values(1:5, alpha = c(100,200)),"alpha must be a single value")

  expect_true(all(colour_values(letters) == colour_values(letters, alpha = 255)))
  expect_true(all(substr( colour_values(letters, alpha = 0),8,9 ) == "00"))
})



