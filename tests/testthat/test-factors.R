context("factors")


test_that("factor order is maintained - hex",{

  ## String Palette
  x <- factor(c("a","b","a"), levels = c("b","a"))
  res <- colour_values(x, summary = T)

  expect_equal( res$summary_values, c("b","a") )
  expect_equal( res$colours, colour_values(c(2,1,2) ))
  expect_equal( res$summary_colours, colour_values( c(2,1) ) ) ## not sure why...

  x <- factor(c("a","b","a", 1), levels = c("b","a", 1))
  res <- colour_values(x, summary = T)

  expect_equal( res$summary_values, c("b","a","1") )
  expect_equal( res$colours, colour_values(c(2,1,2,3) ))
  expect_equal( res$summary_colours, colour_values( c(3,2,1) ) ) ## not sure why...

  ## matrix Palette
  x <- factor(c("a","b","a"), levels = c("b","a"))
  m <- as.matrix( colourvalues:::viridis() * 255 )
  res <- colour_values(x, palette = m, summary = T)

  expect_equal( res$summary_values, c("b","a") )
  expect_equal( res$colours, colour_values(c(2,1,2) ))
  expect_equal( res$summary_colours, colour_values( c(2,1) ) ) ## not sure why...

  x <- factor(c("a","b","a", 1), levels = c("b","a", 1))
  res <- colour_values(x, summary = T)

  expect_equal( res$summary_values, c("b","a","1") )
  expect_equal( res$colours, colour_values(c(2,1,2,3) ))
  expect_equal( res$summary_colours, colour_values( c(3,2,1) ) ) ## not sure why...

})


test_that("factor order is maintained - rgb",{

  ## String Palette
  x <- factor(c("a","b","a"), levels = c("b","a"))
  res <- colour_values_rgb(x, summary = T)

  expect_equal( res$summary_values, c("b","a") )
  expect_equal( res$colours, colour_values_rgb(c(2,1,2) ))
  expect_equal( res$summary_colours, colour_values_rgb( c(2,1) ) ) ## not sure why...

  x <- factor(c("a","b","a", 1), levels = c("b","a", 1))
  res <- colour_values_rgb(x, summary = T)

  expect_equal( res$summary_values, c("b","a","1") )
  expect_equal( res$colours, colour_values_rgb(c(2,1,2,3) ))
  expect_equal( res$summary_colours, colour_values_rgb( c(3,2,1) ) ) ## not sure why...

  ## matrix Palette
  x <- factor(c("a","b","a"), levels = c("b","a"))
  m <- as.matrix( colourvalues:::viridis() * 255 )
  res <- colour_values_rgb(x, palette = m, summary = T)

  expect_equal( res$summary_values, c("b","a") )
  expect_equal( res$colours, colour_values_rgb(c(2,1,2) ))
  expect_equal( res$summary_colours, colour_values_rgb( c(2,1) ) ) ## not sure why...

  x <- factor(c("a","b","a", 1), levels = c("b","a", 1))
  res <- colour_values_rgb(x, summary = T)

  expect_equal( res$summary_values, c("b","a","1") )
  expect_equal( res$colours, colour_values_rgb(c(2,1,2,3) ))
  expect_equal( res$summary_colours, colour_values_rgb( c(3,2,1) ) ) ## not sure why...

})
