

test_that("list vector types correctly calculated", {

  ## rcpp_vector_type( new_type, existing_type )
  res <- colourvalues:::rcpp_vector_type( 10, 11 );
  expect_true( res == 16 ) ## 11 isn't a valid type

  res <- colourvalues:::rcpp_vector_type( 10, 13 );
  expect_true( res == 13 )

  res <- colourvalues:::rcpp_vector_type( 10, 9 );
  expect_true( res == 10 )

  res <- colourvalues:::rcpp_vector_type( 12, 10 );
  expect_true( res == 16 )

  res <- colourvalues:::rcpp_vector_type( 16, 10 );
  expect_true( res == 16 )

  res <- colourvalues:::rcpp_vector_type( 12, 12 );
  expect_true( res == 16 )

  res <- colourvalues:::rcpp_vector_type( 14, 14 );
  expect_true( res == 14 )

  res <- colourvalues:::rcpp_vector_type( 14, 15 );
  expect_true( res == 16 )

  res <- colourvalues:::rcpp_vector_type( 18, 15 );
  expect_true( res == 16 )

})


test_that("lists work", {

  l <- list(
    x = 1:100
    , y = letters
    , z = list( list( x = letters ) )
    , a = list( list( list( x = list( letters ) ) ) )
  )

  res <- colour_values( l )
  expect_true( all( res[[2]] == res[[3]][[1]][[1]] ) )
  expect_true( all( res[[2]] == res[[4]][[1]][[1]][[1]][[1]] ) )

  x <- c(as.character(1:100), letters)

  expect_true( all( res[[1]] == colourvalues::colour_values(x)[1:100] ) )

})


test_that("lists of various types work",{

  ## logical
  l <- list( c(T,F) )
  expect_true( all( colour_values( l )[[1]] == colour_values( l[[1]] ) ) )
  l <- list( x = c(T, F), y = list(T, F))
  res <- colour_values( l )
  expect_true( all( res[[1]] == colour_values( l[[1]] ) ) )
  expect_true( all( unlist( res[[2]] ) == unlist( colour_values( l[[2]] ) ) ) )

  ## integer
  l <- list(x = 1L:3L, y = list( 3L:5L ) )
  v <- colour_values(c(1L:3L,3L:5L))
  res <- colour_values( l )
  expect_true( all( unlist( res ) == v ) )

  ## numeric
  l <- list(x = 1:3, y = list( 3:5 ) )
  v <- colour_values(c(1:3,3:5))
  res <- colour_values( l )
  expect_true( all( unlist( res ) == v ) )

  ## date
  l <- list( as.Date("2018-01-01"), x = list( as.Date("2018-01-01" ) ) )
  v <- colour_values( c(as.Date("2018-01-01"),as.Date("2018-01-01")))
  expect_true( all( unlist( colour_values( l ) ) == v ) )

  ## posixct
  ## posixlt
  ## character

  ## Multi
  l <- c(T,F,T)
  i <- c(1L:5L)
  n <- c(10:12)
  d <- as.Date("2018-01-01")
  pct <- c(as.POSIXct("2018-01-01"), as.POSIXct("2019-01-01") )
  plt <- c(as.POSIXlt("2018-09-01"), as.POSIXlt("2019-09-01") )
  ch <- letters

  ## logical and integer
  res <- colour_values( list(l, i) )
  exp <- colour_values( c(l, i) )
  expect_true( all( unlist( res ) == exp ) )

  ## logical and character
  res <- colour_values( list(l, y = list(x = list(ch))))
  exp <- colour_values( c(l, ch))
  expect_true( all( unlist( res ) == exp ) )

  ## numeric and char
  res <- colour_values( list( n, list( ch ), x = ch ) )
  exp <- colour_values( c( n, ch, ch ) )
  expect_true( all( unlist( res ) == exp ) )

  ## TODO
  ## - re-implement this test after R 4.0.0 has stabalised
  # ## Posixct and logical
  # res <- colour_values( list( pct, list( x = l ) ) )
  # exp <- colour_values( c( pct, l ) )
  # expect_true( all ( unlist( res ) == exp ) )

  l <- list(1:2, x = list(y = 1:2) )
  res <- colour_values( l )
  expect_true( res[[1]][1] == res[[2]][[1]][1] )
  expect_true( res[[1]][2] == res[[2]][[1]][2] )

})

test_that("list produces summary",{

  l <- list(x = 1:5, y = list( list( z = 2:6 ) ) )
  expect_warning( colour_values( l, summary = T) )

  res <- colour_values( l, n_summaries = 5 )
  expect_true( all( unlist( res$colours ) == colour_values( c(1:5, 2:6 ) ) ) )
  expect_true( all( res$summary_values == c("1.00","2.25","3.50","4.75","6.00") ) )

  res <- colour_values( l, n_summaries = 5, digits = 5 )
  expect_true( all( unlist( res$colours ) == colour_values( c(1:5, 2:6 ) ) ) )
  expect_true( all( res$summary_values == c("1.00000","2.25000","3.50000","4.75000","6.00000") ) )

  expect_warning( colour_values( list(letters),  n_summaries = 4) )

  ## Mix
  l <- list( x = 1, y = "a")
  res <- colour_values( l, summary = T )
  expect_true( all( res$summary_values == c("1","a") ) )

  l <- list( x = as.Date("2018-01-01"), y = as.POSIXct("2018-01-01", tz = "GMT"))
  res <- colour_values( l, n_summaries = 3 )
  expect_true( all( res$summary_values == c("17532","1514764800")))
})


test_that("lists return rgb values", {


  l <- list(1:2, x = list(y = 1:2) )
  res <- colour_values_rgb( l )
  expect_equal( res[[1]], res[[2]][[1]] )

  l <- list(1:2, letters)
  res <- colour_values_rgb( l )
  exp <- colour_values_rgb( c(1:2, letters) )
  expect_equal( rbind( res[[1]], res[[2]] ), exp )

})


