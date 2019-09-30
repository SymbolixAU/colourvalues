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

  m <- grDevices::colorRamp(c("red","green","blue"))(0:3/3)
  expect_error(
    colour_values(1:5, palette = m)
    , "A matrix palette must contain at least 5 rows"
  )

})

test_that("short vecors are coloured", {

  expect_equal( colour_values(1), "#440154FF")
  expect_equal( colour_values("a"), "#440154FF")

  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)
  expect_equal( colour_values(1, palette = m ), "#FF0000FF")
  expect_equal( colour_values("a", palette = m), "#FF0000FF")

})

test_that("alpha values applied", {
  expect_true(all(substr(colour_values(1:5),8,9) == "FF"))
  expect_true(all(substr(colour_values(1:5, alpha = 0.0),8,9) == "00"))
  expect_true(all(substr(colour_values(1:5, alpha = 128),8,9) == "80"))
  expect_true(all(substr(colour_values(1:5, alpha = 64),8,9) == "40"))
  expect_true(all(substr(colour_values(1:5, alpha = 192),8,9) == "C0"))

  expect_true(all(substr(colour_values(1:5, alpha = 0),8,9) == "00"))

  ## No longe valid since v0.2.1 (issue 25)
  #expect_error(colour_values(1:5, alpha = c(100,200)),"alpha must either be a single value, or the same length as x")
  #expect_error(colour_values( 1:5, alpha = c(100,200) ), "A vector of alpha values must contain at least 5 values")
  #expect_error(colour_values( 1:3, alpha = c(1:3)), "A vector of alpha values must contain at least 5 values")

  expect_true(all(colour_values(letters) == colour_values(letters, alpha = 255)))
  expect_true(all(substr( colour_values(letters, alpha = 0),8,9) == "00"))

  ## individual values for each value
  expect_true(all(substr(colour_values(1:5, alpha = c(0, 128, 64, 192, 255) ),8,9) == c("00","80","40","C0","FF")))

  ## alpha scaled according to numeric variable
  colour_values(1:5, alpha = 256:260)

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


test_that("alpha can be excluded from results", {

  expect_true(all(substr(colour_values(1:5),1,7) == colour_values(1:5, include_alpha = F)))
  expect_true(all(substr(colour_values(letters[1:5]),1,7) == colour_values(letters[1:5], include_alpha = F)))
  m <- matrix(rep(255,4 * 5),ncol = 4)
  expect_true(all(substr(colour_values(1:5, palette = m),1,7) == colour_values(1:5, palette = m, include_alpha = F)))
  expect_true(all(substr(colour_values(letters[1:5], palette = m),1,7) == colour_values(letters[1:5], palette = m, include_alpha = F)))

})

test_that("original vectors returned",{
  ## https://github.com/SymbolixAU/colourvalues/issues/24
  x <- 1L:10L
  y <- 1L:10L
  invisible( colour_values(x) )
  expect_true( all(x == y) )
  invisible( colour_values_rgb(x) )
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

test_that("summary values returned", {

  lst <- colour_values(1:10, n_summaries = 2, format = F)
  expect_true(all( lst$summary_values == c(1,10) ) )
  expect_true( all( colour_values(c(1,10)) == lst$summary_colours ) )
  lst <- colour_values(-10:10, n_summaries = 5, format = F)
  expect_true(all( lst$summary_values == c(-10,-5,0,5,10) ) )
  expect_true( all( colour_values(c(-10,-5,0,5,10)) == lst$summary_colours ) )

  lst <- colour_values(letters, summary = T)
  expect_true(all(lst$colours == lst$summary_colours))
  expect_true(all(lst$summary_values == letters))

  lst <- colour_values(sample(letters, size = 100, replace = T), summary = T)
  expect_true(all(lst$summary_values == letters))
  expect_true(all(lst$summary_colours == colour_values(letters) ))
})

test_that("summary hex values are formatted", {

  dte <- seq(as.Date("2018-01-01"), as.Date("2018-02-01"), by = 1)
  cv <- colour_values( dte, n_summaries = 5, format = T)
  expect_true( all( cv$summary_values == c("2018-01-01","2018-01-08","2018-01-16","2018-01-24","2018-02-01") ) )

  psx <- seq(as.POSIXct("2018-01-01 00:00:00", tz = "Australia/Melbourne"),
             as.POSIXct("2018-02-01 00:00:00", tz = "Australia/Melbourne"),
             by = 60 * 60 * 24)
  cv <- colour_values( psx, n_summaries = 5, format = T)
  ## TODO( timezones! )
  expect_true(all(cv$summary_values == c("2017-12-31T13:00:00", "2018-01-08T07:00:00", "2018-01-16T01:00:00",
                             "2018-01-23T19:00:00", "2018-01-31T13:00:00")))

  plt <- c(as.POSIXlt("2018-01-01 03:00:00", tz = "Australia/Melbourne"),
           as.POSIXlt("2018-02-01 06:00:00", tz = "Australia/Melbourne"),
           as.POSIXlt("2018-03-01 09:00:00", tz = "Australia/Melbourne"),
           as.POSIXlt("2018-04-01 12:00:00", tz = "Australia/Melbourne"),
           as.POSIXlt("2018-05-01 15:00:00", tz = "Australia/Melbourne"),
           as.POSIXlt("2018-06-01 18:00:00", tz = "Australia/Melbourne")
           )
  cv <- colour_values( plt, n_summaries = 5, format = T)
  # expect_true(all(cv$summary_values == c("2017-12-31T13:00:00", "2018-01-08T07:00:00", "2018-01-16T01:00:00",
  #                                        "2018-01-23T19:00:00", "2018-01-31T13:00:00")))


  psx <- seq(as.POSIXct("2018-01-01 00:00:00", tz = "UTC"),
             as.POSIXct("2018-02-01 00:00:00", tz = "UTC"),
             by = 60 * 60 * 24)
  cv <- colour_values( psx, n_summaries = 5, format = T)
  expect_true(all(cv$summary_values == c("2018-01-01T00:00:00", "2018-01-08T18:00:00", "2018-01-16T12:00:00",
                                         "2018-01-24T06:00:00", "2018-02-01T00:00:00")))

  psx <- seq(as.POSIXct("2018-01-01 01:23:45", tz = "UTC"),
             as.POSIXct("2018-02-01 23:23:23", tz = "UTC"),
             by = 60 * 60 * 24)
  cv <- colour_values( psx, n_summaries = 5, format = T)
  expect_true(all(cv$summary_values == c("2018-01-01T01:23:45", "2018-01-08T19:23:45", "2018-01-16T13:23:45",
                                         "2018-01-24T07:23:45", "2018-02-01T01:23:45")))

  plt <- seq(as.POSIXlt("2018-01-01 00:00:00", tz = "UTC"),
             as.POSIXlt("2018-02-01 00:00:00", tz = "UTC"),
             by = 60 * 60 * 24)
  cv <- colour_values( plt, n_summaries = 5, format = T)
  expect_true(all(cv$summary_values == c("2018-01-01T00:00:00", "2018-01-08T18:00:00", "2018-01-16T12:00:00",
                                         "2018-01-24T06:00:00", "2018-02-01T00:00:00")))

  lv <- c(T,F,F,T,F)
  cv <- colour_values(lv, summary = T)
  expect_true( all (cv$summary_values == c("FALSE","TRUE") ) )

  fct <- factor(letters)
  cv <- colour_values( fct, summary = T )
  expect_true( all( cv$summary_values  == letters ) )

})

test_that("summary hex values are formatted with palette matrix", {

  df <- data.frame(x = 0:20)
  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)

  cv <- colour_values( df$x, palette = m, n_summaries = 5, format = T)
  expect_true(all(cv$summary_values == c("0.00","5.00","10.00","15.00","20.00")))

})

test_that("n_summaries is the min of 5 or length(x) ", {

  cv <- colour_values( 1, n_summaries = 5, format = F )
  expect_true( cv$summary_values == 1 )

  cv <- colour_values( 1:50, n_summaries = 500 )
  expect_true( length( cv$summary_values ) == 50 )

  cv <- colour_values(c("a","b"), summary = T )
  expect_true(all(cv$summary_values == c("a","b")))

})

test_that("ints aren't formatted", {

  cv <- colour_values(1L:20L, n_summaries = 5, format = T)
  expect_true(all(cv$summary_values == c("1.00","5.75","10.50","15.25","20.00")))

})

test_that("cpp vectors correctly re-sized", {

  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)
  cv <- colour_values(1, palette = m, include_alpha = F)
  expect_true( convert_color(m[1, ]) == cv )
  cv <- colour_values(1:2, palette = m, include_alpha = F)
  expect_true( convert_color(m[1, ]) == cv[1] )
  expect_true( convert_color(m[nrow(m), ]) == cv[2] )
})

test_that("summary values contain FF alphas", {

  cv <- colour_values( 1, n_summaries = 5 )
  expect_true(cv$summary_colours == "#440154FF")
  cv <- colour_values( 1, n_summaries = 5, alpha = 1 )
  expect_true(cv$summary_colours == "#440154FF")
  cv <- colour_values( 1:100, n_summaries = 5 )
  expect_true( all( substr( cv$summary_colours, 8,10 ) == "FF") )
  cv <- colour_values( 1:100, n_summaries = 5, alpha = 1:100 )
  expect_true( all( substr( cv$summary_colours, 8,10 ) == "FF") )
  cv <- colour_values( 1:100, n_summaries = 100, alpha = 1:100 )
  expect_true( all( substr( cv$summary_colours, 8,10 ) == "FF") )

  cv <- colour_values( 1, n_summaries = 5, include_alpha = F )
  expect_true(cv$summary_colours == "#440154")
  cv <- colour_values( 1, n_summaries = 5, alpha = 1, include_alpha = F )
  expect_true(cv$summary_colours == "#440154")
  cv <- colour_values( 1:100, n_summaries = 5, include_alpha = F )
  expect_true( all( nchar( cv$summary_colours ) == 7) )
  cv <- colour_values( 1:100, n_summaries = 5, alpha = 1:100, include_alpha = F )
  expect_true( all( nchar( cv$summary_colours ) == 7 ) )
  cv <- colour_values( 1:100, n_summaries = 100, alpha = 1:100, include_alpha = F )
  expect_true( all( nchar( cv$summary_colours ) == 7 ) )


  cv <- colour_values( "a", summary = T)
  expect_true(cv$summary_colours == "#440154FF")
  cv <- colour_values( "a", summary = T, alpha = 1 )
  expect_true(cv$summary_colours == "#440154FF")
  cv <- colour_values( letters, summary = T)
  expect_true( all( substr( cv$summary_colours, 8,10 ) == "FF") )
  cv <- colour_values( letters, summary = T, alpha = 1:26)
  expect_true( all( substr( cv$summary_colours, 8,10 ) == "FF") )

  cv <- colour_values( "a", summary = T, include_alpha = F )
  expect_true(cv$summary_colours == "#440154")
  cv <- colour_values( "a", summary = T, alpha = 1, include_alpha = F  )
  expect_true(cv$summary_colours == "#440154")
  cv <- colour_values( letters, summary = T, include_alpha = F )
  expect_true( all( nchar( cv$summary_colours ) == 7 ) )
  cv <- colour_values( letters, summary = T, alpha = 1:26, include_alpha = F )
  expect_true( all( nchar( cv$summary_colours ) == 7 ) )


  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)
  cv <- colour_values( "a", summary = T, palette = m)
  expect_true(cv$summary_colours == "#FF0000FF")
  cv <- colour_values( "a", summary = T, alpha = 1, palette = m )
  expect_true(cv$summary_colours == "#FF0000FF")
  cv <- colour_values( letters, summary = T, palette = m )
  expect_true( all( substr( cv$summary_colours, 8,10 ) == "FF") )
  cv <- colour_values( letters, summary = T, alpha = 1:26, palette = m )
  expect_true( all( substr( cv$summary_colours, 8,10 ) == "FF") )

  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)
  cv <- colour_values( "a", summary = T, palette = m, include_alpha = F)
  expect_true(cv$summary_colours == "#FF0000")
  cv <- colour_values( "a", summary = T, alpha = 1, palette = m, include_alpha = F)
  expect_true(cv$summary_colours == "#FF0000")
  cv <- colour_values( letters, summary = T, palette = m, include_alpha = F)
  expect_true( all( nchar( cv$summary_colours ) == 7 ) )
  cv <- colour_values( letters, summary = T, alpha = 1:26, palette = m, include_alpha = F )
  expect_true( all( nchar( cv$summary_colours ) == 7) )
})
