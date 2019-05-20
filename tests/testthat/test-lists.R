

test_that("list vector types correctly calculated", {

  ## vector_type( new_type, existing_type )
  res <- colourvalues:::vector_type( 10, 11 );
  expect_true( res == 16 ) ## 11 isn't a valid type

  res <- colourvalues:::vector_type( 10, 13 );
  expect_true( res == 13 )

  res <- colourvalues:::vector_type( 10, 9 );
  expect_true( res == 10 )

  res <- colourvalues:::vector_type( 12, 10 );
  expect_true( res == 16 )

  res <- colourvalues:::vector_type( 16, 10 );
  expect_true( res == 16 )

  res <- colourvalues:::vector_type( 12, 12 );
  expect_true( res == 16 )

  res <- colourvalues:::vector_type( 14, 14 );
  expect_true( res == 14 )

  res <- colourvalues:::vector_type( 14, 15 );
  expect_true( res == 16 )

  res <- colourvalues:::vector_type( 18, 15 );
  expect_true( res == 16 )

})


test_that("lists work", {

  l <- list(
    x = 1:100
    , y = letters
    , z = list( list( x = letters ) )
    , a = list( list( list( x = list( letters ) ) ) )
  )

  res <- colourvalues:::colour_list( l )
  expect_true( all( res[[2]] == res[[3]][[1]][[1]] ) )
  expect_true( all( res[[2]] == res[[4]][[1]][[1]][[1]][[1]] ) )

  x <- c(as.character(1:100), letters)

  expect_true( all( res[[1]] == colourvalues::colour_values(x)[1:100] ) )

})
