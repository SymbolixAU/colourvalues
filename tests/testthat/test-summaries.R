context("summaries")

test_that("NA values are removed from summaries", {

  x <- c(1:5,NA,7:10,NA,12:20)
  cols <- colour_values( x, n_summaries = 5 )
  expect_true( all( !is.na( as.numeric( cols$summary_values ) ) ) )
})
