context("factors")


test_that("factor order is maintained - hex",{

  ## String Palette
  x <- factor(c("a","b","a"), levels = c("b","a"))
  res <- colour_values(x, summary = T)

  expect_equal( res$summary_values, c("b","a") )
  expect_equal( res$colours, colour_values(c(2,1,2) ))
  expect_equal( res$summary_colours, colour_values( c(1,2) ) )

  x <- factor(c("a","b","a", 1), levels = c("b","a", 1))
  res <- colour_values(x, summary = T)

  expect_equal( res$summary_values, c("b","a","1") )
  expect_equal( res$colours, colour_values(c(2,1,2,3) ))
  expect_equal( res$summary_colours, colour_values( c(1,2,3) ) )

  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = letters[1:4])
  res <- colour_values( df$col, summary = T )

  ## matrix Palette
  x <- factor(c("a","b","a"), levels = c("b","a"))
  m <- as.matrix( colourvalues:::viridis() * 255 )
  res <- colour_values(x, palette = m, summary = T)

  expect_equal( res$summary_values, c("b","a") )
  expect_equal( res$colours, colour_values(c(2,1,2) ))
  expect_equal( res$summary_colours, colour_values( c(1,2) ) )

  x <- factor(c("a","b","a", 1), levels = c("b","a", 1))
  res <- colour_values(x, summary = T)

  expect_equal( res$summary_values, c("b","a","1") )
  expect_equal( res$colours, colour_values(c(2,1,2,3) ))
  expect_equal( res$summary_colours, colour_values( c(1,2,3) ) )

  ## TODO
  ## test using numbers as factors


})


test_that("factor order is maintained - rgb",{

  ## String Palette
  x <- factor(c("a","b","a"), levels = c("b","a"))
  res <- colour_values_rgb(x, summary = T)

  expect_equal( res$summary_values, c("b","a") )
  expect_equal( res$colours, colour_values_rgb(c(2,1,2) ))
  expect_equal( res$summary_colours, colour_values_rgb( c(1,2) ) )

  x <- factor(c("a","b","a", 1), levels = c("b","a", 1))
  res <- colour_values_rgb(x, summary = T)

  expect_equal( res$summary_values, c("b","a","1") )
  expect_equal( res$colours, colour_values_rgb(c(2,1,2,3) ))
  expect_equal( res$summary_colours, colour_values_rgb( c(1,2,3) ) )

  ## matrix Palette
  x <- factor(c("a","b","a"), levels = c("b","a"))
  m <- as.matrix( colourvalues:::viridis() * 255 )
  res <- colour_values_rgb(x, palette = m, summary = T)

  expect_equal( res$summary_values, c("b","a") )
  expect_equal( res$colours, colour_values_rgb(c(2,1,2) ))
  expect_equal( res$summary_colours, colour_values_rgb( c(1,2) ) )

  x <- factor(c("a","b","a", 1), levels = c("b","a", 1))
  res <- colour_values_rgb(x, summary = T)

  expect_equal( res$summary_values, c("b","a","1") )
  expect_equal( res$colours, colour_values_rgb(c(2,1,2,3) ))
  expect_equal( res$summary_colours, colour_values_rgb( c(1,2,3) ) )

})
