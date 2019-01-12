context("summaries")

test_that("NA values are removed from summaries", {

  ## Numeric
  x <- c(1:5,NA,7:10,NA,12:20)
  cols <- colour_values( x, n_summaries = 5 )
  expect_true( all( !is.na( as.numeric( cols$summary_values ) ) ) )

  ## Character
  x <- c("a","b",NA_character_, "d", "e","f","g")
  cols <- color_values( x, summary = T)
  expect_true( all( !is.na( cols$summary_values ) ) )
  expect_true( length( cols$summary_colours ) == length( cols$summary_values ) )
})



