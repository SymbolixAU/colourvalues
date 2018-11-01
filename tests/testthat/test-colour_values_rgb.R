context("rgb")



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

test_that("NA handled in RGB return", {
  expect_true(all(colour_values_rgb(NA) == c(rep(128,3), 255))) ## default "#808080FF
  expect_true(all(colour_values_rgb(NA, na_colour = "#FF000000") == c(255, 0, 0, 0)))
})

test_that("alpha can be excluded from results", {

  expect_true(all(colour_values_rgb(1:5)[,1:3] == colour_values_rgb(1:5, include_alpha = F)))
  expect_true(all(colour_values_rgb(letters[1:5])[,1:3] == colour_values_rgb(letters[1:5], include_alpha = F)))
  m <- matrix(rep(255,4 * 5),ncol = 4)
  expect_true(all(colour_values_rgb(1:5, palette = m)[,1:3] == colour_values_rgb(1:5, palette = m, include_alpha = F)))
  expect_true(all(colour_values_rgb(letters[1:5], palette = m)[,1:3] == colour_values_rgb(letters[1:5], palette = m, include_alpha = F)))

})

test_that("summary values returned", {

  lst <- colour_values_rgb(1:10, n_summaries = 2, format = F)
  expect_true(all( lst$summary_values == c(1,10) ) )
  expect_true( all( colour_values_rgb(c(1,10)) == lst$summary_colours ) )
  lst <- colour_values_rgb(-10:10, n_summaries = 5, format = F)
  expect_true(all( lst$summary_values == c(-10,-5,0,5,10) ) )
  expect_true( all( colour_values_rgb(c(-10,-5,0,5,10)) == lst$summary_colours ) )


  lst <- colour_values_rgb(letters, summary = T)
  expect_true(all(lst$colours == lst$summary_colours))
  expect_true(all(lst$summary_values == letters))

  lst <- colour_values_rgb(sample(letters, size = 100, replace = T), summary = T)
  expect_true(all(lst$summary_values == letters))
  expect_true(all(lst$summary_colours == colour_values_rgb(letters) ))

})

test_that("short vecors are coloured", {

  expect_equal( colour_values_rgb(1), convert_colour("#440154FF") )
  expect_equal( colour_values_rgb("a"), convert_colour( "#440154FF") )

  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)
  expect_equal( colour_values_rgb(1, palette = m ), convert_colour("#FF0000FF"))
  expect_equal( colour_values_rgb("a", palette = m), convert_colour("#FF0000FF"))

})



test_that("summary rgb values are formatted", {

  dte <- seq(as.Date("2018-01-01"), as.Date("2018-02-01"), by = 1)
  cv <- colour_values_rgb( dte, n_summaries = 5, format = T)
  expect_true( all( cv$summary_values == c("2018-01-01","2018-01-08","2018-01-16","2018-01-24","2018-02-01") ) )

  psx <- seq(as.POSIXct("2018-01-01 00:00:00", tz = "Australia/Melbourne"),
             as.POSIXct("2018-02-01 00:00:00", tz = "Australia/Melbourne"),
             by = 60 * 60 * 24)
  cv <- colour_values_rgb( psx, n_summaries = 5, format = T)
  expect_true(all(cv$summary_values == c("2017-12-31T13:00:00", "2018-01-08T07:00:00", "2018-01-16T01:00:00",
                                         "2018-01-23T19:00:00", "2018-01-31T13:00:00")))


  psx <- seq(as.POSIXct("2018-01-01 00:00:00", tz = "UTC"),
             as.POSIXct("2018-02-01 00:00:00", tz = "UTC"),
             by = 60 * 60 * 24)
  cv <- colour_values_rgb( psx, n_summaries = 5, format = T)
  expect_true(all(cv$summary_values == c("2018-01-01T00:00:00", "2018-01-08T18:00:00", "2018-01-16T12:00:00",
                                         "2018-01-24T06:00:00", "2018-02-01T00:00:00")))

  lv <- c(T,F,F,T,F)
  cv <- colour_values_rgb(lv, summary = T)
  expect_true( all (cv$summary_values == c("FALSE","TRUE") ) )

  fct <- factor(letters)
  cv <- colour_values_rgb( fct, summary = T )
  expect_true( all( cv$summary_values  == letters ) )

})

test_that("summary rgb values are formatted with palette matrix", {

  df <- data.frame(x = 0:20)
  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)

  cv <- colour_values_rgb( df$x, palette = m, n_summaries = 5)
  expect_true(all(cv$summary_values == c("0.00","5.00","10.00","15.00","20.00")))

})

test_that("n_summaries is the min of 5 or length(x) ", {

  cv <- colour_values_rgb( 1, n_summaries = 5 )
  expect_true( cv$summary_values == "1.00" )

  cv <- colour_values_rgb( 1:50, n_summaries = 500 )
  expect_true( length( cv$summary_values ) == 50 )

  cv <- colour_values_rgb(c("a","b"), summary = T )
  expect_true(all(cv$summary_values == c("a","b")))

})


test_that("summary values contain FF alphas", {

  cv <- colour_values_rgb( 1, n_summaries = 5 )
  expect_true(all( cv$summary_colours == convert_colour("#440154FF")))
  cv <- colour_values_rgb( 1, n_summaries = 5, alpha = 1 )
  expect_true(all(cv$summary_colours == convert_colour("#440154FF")))
  cv <- colour_values_rgb( 1:100, n_summaries = 5 )
  expect_true( all( cv$summary_colours[, 4] == 255 ) )
  cv <- colour_values_rgb( 1:100, n_summaries = 5, alpha = 1:100 )
  expect_true( all( cv$summary_colours[, 4] == 255 ) )
  cv <- colour_values_rgb( 1:100, n_summaries = 100, alpha = 1:100 )
  expect_true( all( cv$summary_colours[, 4] == 255 ) )

  cv <- colour_values_rgb( 1, n_summaries = 5, include_alpha = F )
  expect_true(all(cv$summary_colours == convert_colour("#440154")))
  cv <- colour_values_rgb( 1, n_summaries = 5, alpha = 1, include_alpha = F )
  expect_true(all(cv$summary_colours == convert_colour("#440154")))
  cv <- colour_values_rgb( 1:100, n_summaries = 5, include_alpha = F )
  expect_true( ncol( cv$summary_colours ) == 3 )
  cv <- colour_values_rgb( 1:100, n_summaries = 5, alpha = 1:100, include_alpha = F )
  expect_true( ncol( cv$summary_colours ) == 3 )
  cv <- colour_values_rgb( 1:100, n_summaries = 100, alpha = 1:100, include_alpha = F )
  expect_true( ncol( cv$summary_colours ) == 3 )


  cv <- colour_values_rgb( "a", summary = T)
  expect_true(all(cv$summary_colours == convert_colour( "#440154FF") ) )
  cv <- colour_values_rgb( "a", summary = T, alpha = 1 )
  expect_true(all(cv$summary_colours == convert_colour( "#440154FF") ) )
  cv <- colour_values_rgb( letters, summary = T)
  expect_true( all( cv$summary_colours[, 4] == 255 ) )
  cv <- colour_values_rgb( letters, summary = T, alpha = 1:26)
  expect_true( all( cv$summary_colours[, 4]  == 255 ) )

  cv <- colour_values_rgb( "a", summary = T, include_alpha = F )
  expect_true(all(cv$summary_colours == convert_colour( "#440154") ) )
  cv <- colour_values_rgb( "a", summary = T, alpha = 1, include_alpha = F  )
  expect_true(all(cv$summary_colours == convert_colour("#440154") ) )
  cv <- colour_values_rgb( letters, summary = T, include_alpha = F )
  expect_true( ncol( cv$summary_colours ) == 3 )
  cv <- colour_values_rgb( letters, summary = T, alpha = 1:26, include_alpha = F )
  expect_true( ncol( cv$summary_colours ) == 3 )


  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)
  cv <- colour_values_rgb( "a", summary = T, palette = m)
  expect_true(all( cv$summary_colours == convert_colour( "#FF0000FF") ) )
  cv <- colour_values_rgb( "a", summary = T, alpha = 1, palette = m )
  expect_true(all(cv$summary_colours == convert_colour("#FF0000FF") ) )
  cv <- colour_values_rgb( letters, summary = T, palette = m )
  expect_true( all( cv$summary_colours[, 4] == 255) )
  cv <- colour_values_rgb( letters, summary = T, alpha = 1:26, palette = m )
  expect_true( all( cv$summary_colours[, 4] == 255) )

  m <- grDevices::colorRamp(c("red","green","blue","yellow"))(0:1000/1000)
  cv <- colour_values_rgb( "a", summary = T, palette = m, include_alpha = F)
  expect_true(all(cv$summary_colours == convert_colour("#FF0000") ) )
  cv <- colour_values_rgb( "a", summary = T, alpha = 1, palette = m, include_alpha = F)
  expect_true(all(cv$summary_colours == convert_colour( "#FF0000") ) )
  cv <- colour_values_rgb( letters, summary = T, palette = m, include_alpha = F)
  expect_true( ncol(cv$summary_colours ) == 3 )
  cv <- colour_values_rgb( letters, summary = T, alpha = 1:26, palette = m, include_alpha = F )
  expect_true( ncol( cv$summary_colours ) == 3 )


})
