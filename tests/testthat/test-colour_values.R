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

  ## string data
  expect_true( all( colour_values(letters[1:5], palette = m) == colour_values(1:5, palette = m) ) )

})

test_that("alpha values applied", {
  expect_true(all(substr(colour_values(1:5),8,9) == "FF"))
  expect_true(all(substr(colour_values(1:5, alpha = 0.0),8,9) == "00"))
  expect_true(all(substr(colour_values(1:5, alpha = 128),8,9) == "80"))
  expect_true(all(substr(colour_values(1:5, alpha = 64),8,9) == "40"))
  expect_true(all(substr(colour_values(1:5, alpha = 192),8,9) == "C0"))

  expect_true(all(substr(colour_values(1:5, alpha = 0),8,9) == "00"))

  expect_error(colour_values(1:5, alpha = c(100,200)),"alpha must either be a single value, or the same length as x")

  expect_true(all(colour_values(letters) == colour_values(letters, alpha = 255)))
  expect_true(all(substr( colour_values(letters, alpha = 0),8,9) == "00"))

  ## individual values for each value
  expect_true(all(substr(colour_values(1:5, alpha = c(0, 128, 64, 192, 255)),8,9) == c("00","80","40","C0","FF")))

  ## alpha scaled according to numeric variable
  colour_values(1:5, alpha = 256:260)

})

test_that("rgb matrix returned", {

  m <- colour_values(1:5, return = "rgb")
  expect_true(all(m[,1] == c(68,59,33,93,253)))
  expect_true(all(m[,2] == c(1,82,144,201,231)))
  expect_true(all(m[,3] == c(84,139,140,99,37)))
  expect_true(all(m[,4] == 255))

  m <- colour_values(letters[1:5], return = "rgb")
  expect_true(all(m[,1] == c(68,59,33,93,253)))
  expect_true(all(m[,2] == c(1,82,144,201,231)))
  expect_true(all(m[,3] == c(84,139,140,99,37)))
  expect_true(all(m[,4] == 255))

  m <- colour_values(1:5, palette = "inferno", return = "rgb")
  expect_true(all(m[,1] == c(0,87,187,249,252)))
  expect_true(all(m[,2] == c(0,16,55,141,255)))
  expect_true(all(m[,3] == c(4,109,85,10,164)))
  expect_true(all(m[,4] == 255))

  m <- colour_values(letters[1:5], palette = "inferno", return = "rgb")
  expect_true(all(m[,1] == c(0,87,187,249,252)))
  expect_true(all(m[,2] == c(0,16,55,141,255)))
  expect_true(all(m[,3] == c(4,109,85,10,164)))
  expect_true(all(m[,4] == 255))

  m <- colour_values(1:5, palette = "inferno", alpha = 100, return = "rgb")
  expect_true(all(m[,1] == c(0,87,187,249,252)))
  expect_true(all(m[,2] == c(0,16,55,141,255)))
  expect_true(all(m[,3] == c(4,109,85,10,164)))
  expect_true(all(m[,4] == 100))

  m <- colour_values(letters[1:5], palette = "inferno", alpha = 100, return = "rgb")
  expect_true(all(m[,1] == c(0,87,187,249,252)))
  expect_true(all(m[,2] == c(0,16,55,141,255)))
  expect_true(all(m[,3] == c(4,109,85,10,164)))
  expect_true(all(m[,4] == 100))

  ## TODO(Why are these plots different, why is m2 different to m, why are there negatives?)
  ## matrix palette
  alpha <- c(0, 100, 150, 200, 255)
  m <- cbind( grDevices::colorRamp(c("red","green","blue"))(0:9/9), alpha )
  m2 <- colour_values(1:10, palette = m, return = "rgb")
  ## m2 is the interpolated palette; we are not using m[1:10,] as the palette for the values
  h <- colour_values(1:10, palette = m)
  ## h is the hex values returned from colour_values
  m1 <- t(grDevices::col2rgb(h))

  ## expect results to be within 1 of each other
  expect_true(sum(abs(m1[,1] - m2[,1])) <= length(m[,1]))
  expect_true(sum(abs(m1[,2] - m2[,2])) <= length(m[,2]))
  expect_true(sum(abs(m1[,3] - m2[,3])) <= length(m[,3]))

  df <- data.frame(a = 10, x = 1:5)
  df2 <- data.frame(a = 10, x = 1:5)

  ## plot using the raw palette
  df$col <- colour_values(df$x, palette = m)
  barplot(height = df$a, col = df$col, border = NA, space = 0)

  df2$col <- colour_values(df2$x, palette = m2)
  barplot(height = df2$a, col = df2$col, border = NA, space = 0)
  ## they are different because 'm' gets interpolated, then 'm2' gets interpolated
  ## and since they are different to start with, the plots are different

  ## TODO
  ## matrix with an alpha-column. The alpha column needs to be interpolated along wtih
  ## the RGB values
  df <- data.frame(a = 10, x = 1:20)
  m <- matrix(c(rep(100, 4*25)), ncol = 4)
  df$col <- colour_values(df$x, palette = m)
  barplot(height = df$a, col = df$col, border = NA, space = 0)

  df <- data.frame(a = 10, x = 1:20)

  alpha <- seq(0,255,length.out = 10)
  m <- cbind( grDevices::colorRamp(c("red","green","blue"))(0:9/9), alpha )

  df$col <- colour_values(df$x, palette = m)
  ## THIS IS THE ERROR
  barplot(height = df$a, col = df$col, border = NA, space = 0)
  ## ths plot ^^ and this plot vv should be the same (without alpha)

  df <- data.frame(a = 10, x = 1:20)

  m <- grDevices::colorRamp(c("red","green","blue"))(0:9/9)

  df$col <- colour_values(df$x, palette = m)
  ## THIS IS THE ERROR
  barplot(height = df$a, col = df$col, border = NA, space = 0)


  ## TODO: another error?
  ## maybe from my (255 - r :: r + 255) stuff
  df <- data.frame(a = 10, x = 1:20)

  m <- grDevices::colorRamp(c("red","green"))(0:9/9)

  df$col <- colour_values(df$x, palette = m)
  ## THIS IS THE ERROR
  barplot(height = df$a, col = df$col, border = NA, space = 0)


})

