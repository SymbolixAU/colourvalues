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
  expect_true(all(colour_values(1:5, palette = m) == c("#FF0000FF", "#808000FF", "#00FF00FF", "#008080FF", "#0000FFFF")))
  ## This doesn't exactly equal
  #grDevices::colorRampPalette(c("red","green","blue"))(5)
  ## I 'think' because of boost's interpolation

  expect_error(
    colour_values(1:5, palette = m[,1:2])
    #, "Matrix palette needs either 3 (R, G, B) or 4 (R, G, B, A) columns"
    )

  alpha <- c(0, 100, 150, 200, 255)
  m <- cbind( grDevices::colorRamp(c("red","green","blue"))(0:4/4), alpha )
  expect_true(all(colour_values(1:5, palette = m) == c("#FF000000", "#80800064", "#00FF0096", "#008080C8", "#0000FFFF")))

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

  #expect_error(colour_values(1:5, alpha = c(100,200)),"alpha must either be a single value, or the same length as x")
  expect_error(colour_values(1:5, alpha = c(100,200)),"Unknown alpha definition")

  expect_true(all(colour_values(letters) == colour_values(letters, alpha = 255)))
  expect_true(all(substr( colour_values(letters, alpha = 0),8,9) == "00"))

  ## individual values for each value
  expect_true(all(substr(colour_values(1:5, alpha = c(0, 128, 64, 192, 255) ),8,9) == c("00","80","40","C0","FF")))

  ## alpha scaled according to numeric variable
  colour_values(1:5, alpha = 256:260)

})

test_that("rgb matrix returned", {

  m <- colour_values_rgb(1:5)
  expect_true(all(m[,1] == c(68,59,33,93,253)))
  expect_true(all(m[,2] == c(1,82,144,201,231)))
  expect_true(all(m[,3] == c(84,139,140,99,37)))
  expect_true(all(m[,4] == 255))

  m <- colour_values_rgb(letters[1:5])
  expect_true(all(m[,1] == c(68,59,33,93,253)))
  expect_true(all(m[,2] == c(1,82,144,201,231)))
  expect_true(all(m[,3] == c(84,139,140,99,37)))
  expect_true(all(m[,4] == 255))

  m <- colour_values_rgb(1:5, palette = "inferno")
  expect_true(all(m[,1] == c(0,87,187,249,252)))
  expect_true(all(m[,2] == c(0,16,55,141,255)))
  expect_true(all(m[,3] == c(4,109,85,10,164)))
  expect_true(all(m[,4] == 255))

  m <- colour_values_rgb(letters[1:5], palette = "inferno")
  expect_true(all(m[,1] == c(0,87,187,249,252)))
  expect_true(all(m[,2] == c(0,16,55,141,255)))
  expect_true(all(m[,3] == c(4,109,85,10,164)))
  expect_true(all(m[,4] == 255))

  m <- colour_values_rgb(1:5, palette = "inferno", alpha = 100)
  expect_true(all(m[,1] == c(0,87,187,249,252)))
  expect_true(all(m[,2] == c(0,16,55,141,255)))
  expect_true(all(m[,3] == c(4,109,85,10,164)))
  expect_true(all(m[,4] == 100))

  m <- colour_values_rgb(letters[1:5], palette = "inferno", alpha = 100)
  expect_true(all(m[,1] == c(0,87,187,249,252)))
  expect_true(all(m[,2] == c(0,16,55,141,255)))
  expect_true(all(m[,3] == c(4,109,85,10,164)))
  expect_true(all(m[,4] == 100))

})

test_that("rgb to hex to rgb works", {

  alpha <- c(0, 100, 150, 200, 255)
  m <- cbind( grDevices::colorRamp(c("red","green","blue"))(0:9/9), alpha )
  h <- colour_values(1:10, palette = m)

  mh <- t(grDevices::col2rgb(h))

  m2 <- colour_values_rgb(1:10, palette = m)

  expect_true(sum(abs(m[,1] - m2[,1])) <= nrow(m))
  expect_true(sum(abs(m[,2] - m2[,2])) <= nrow(m))
  expect_true(sum(abs(m[,3] - m2[,3])) <= nrow(m))
  expect_true(sum(abs(m[,4] - m2[,4])) <= nrow(m))

  expect_true(sum(abs(m[,1] - mh[,1])) <= nrow(m))
  expect_true(sum(abs(m[,2] - mh[,2])) <= nrow(m))
  expect_true(sum(abs(m[,3] - mh[,3])) <= nrow(m))

})


test_that("different sizes of variables and palettes work", {

  ## - very few variables - large palette
  df <- data.frame(x = 1:2)
  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:500/500)
  df$col <- colour_values(df$x, palette = m)
  expect_true(all(df$col == c("#FF0000FF","#FFFF00FF")))  ## shoudl be extremeties of palette
  # df$a <- 10
  # barplot(df$a, col = df$col)

  ## - lots of variables - small palette
  df <- data.frame(x = 1:10000)
  m <- grDevices::colorRamp(c("red"))(0:4/4)
  df$col <- colour_values(df$x, palette = m)
  expect_true(unique(df$col == "#FF0000FF"))

  ## - few variables - small palette
  df <- data.frame(x = 1:2)
  m <- grDevices::colorRamp(c("red"))(0:4/4)
  df$col <- colour_values(df$x, palette = m)
  expect_true(unique(df$col == "#FF0000FF"))

  ## - lots of variables - large palette
  df <- data.frame(x = rnorm(n = 1e6))
  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)
  expect_silent(df$col <- colour_values(df$x))

})

test_that("small range of values give distinct palette", {
  expect_true(all(colour_values(c(0.00001, 0.00002)) == c("#440154FF","#FDE725FF")))
})

test_that("256 variables produce 'unique' palette", {
  ##  because of 'splining' and rounding I think it's OK it's not exactly 256 colours
  expect_true(abs(256 - length(unique(colour_values(1:256)))) <= 2)
})

test_that("NA handled in RGB return", {
  expect_true(all(colour_values_rgb(NA) == c(rep(128,3), 255))) ## default "#808080FF
  expect_true(all(colour_values_rgb(NA, na_colour = "#FF000000") == c(255, 0, 0, 0)))
})

test_that("alpha can be excluded from results", {

  expect_true(all(substr(colour_values(1:5),1,7) == colour_values(1:5, include_alpha = F)))
  expect_true(all(substr(colour_values(letters[1:5]),1,7) == colour_values(letters[1:5], include_alpha = F)))
  m <- matrix(rep(255,4 * 5),ncol = 4)
  expect_true(all(substr(colour_values(1:5, palette = m),1,7) == colour_values(1:5, palette = m, include_alpha = F)))
  expect_true(all(substr(colour_values(letters[1:5], palette = m),1,7) == colour_values(letters[1:5], palette = m, include_alpha = F)))

  expect_true(all(colour_values_rgb(1:5)[,1:3] == colour_values_rgb(1:5, include_alpha = F)))
  expect_true(all(colour_values_rgb(letters[1:5])[,1:3] == colour_values_rgb(letters[1:5], include_alpha = F)))
  m <- matrix(rep(255,4 * 5),ncol = 4)
  expect_true(all(colour_values_rgb(1:5, palette = m)[,1:3] == colour_values_rgb(1:5, palette = m, include_alpha = F)))
  expect_true(all(colour_values_rgb(letters[1:5], palette = m)[,1:3] == colour_values_rgb(letters[1:5], palette = m, include_alpha = F)))

})

test_that("original vectors returned",{
  ## https://github.com/SymbolixAU/colourvalues/issues/24
  x <- 1L:10L
  y <- 1L:10L
  invisible( colour_values(x) )
  expect_true( all(x == y) )
  invisible( colour_values_rgb(x))
  expect_true( all(x == y))

  set.seed(1)
  x <- as.numeric( sample.int(100, 10))
  set.seed(1)
  y <- as.numeric( sample.int(100, 10))
  expect_true( all( x == y ))
  invisible( colour_values(x) )
  expect_true( all( x == y ))


  set.seed(1)
  x <- as.numeric( sample.int(100, 10))
  set.seed(1)
  y <- as.numeric( sample.int(100, 10))
  expect_true( all( x == y ))
  invisible( colour_values_rgb(x) )
  expect_true( all( x == y ))

})
