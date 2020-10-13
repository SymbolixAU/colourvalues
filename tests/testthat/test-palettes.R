context("palettes")

test_that("palettes are returned", {

  expect_error(colour_values(1:5, palette = "mypalette"), "unknown palette")

  all_palettes <- color_palettes()
  expect_true( length(all_palettes) == 52 )

  for( palette in all_palettes ) {
    expect_silent( colour_values(1, palette = palette ))
    res <- colourvalues::get_palette( palette )
    expect_true( ncol( res ) == 3 & nrow( res ) == 256 )

    ## And call teh function directly
    res <- eval(parse(text = paste0(palette, "()")))
    expect_true( ncol( res ) == 3 )
  }

  expect_error( colourvalues::get_palette("test"), "not a valid palette" )

  # lns <- readLines("./R/palettes.R")
  # funs <- lns[ grepl("function\\(\\) rcpp_", lns ) ]
  # gsub(" .*", "", funs )

})

test_that("first 4 columns of palette matrix used",{

  dfv <- viridis()
  dfp <- plasma()
  m <- cbind( as.matrix(dfv), 0)
  m <- cbind( m, as.matrix(dfp) )
  expect_warning( colour_values(1:5, palette = m ) )


})

## issue 58
test_that("palettes returned either RGB or hex",{
  pal <- get_palette("viridis")
  expect_true( is.matrix( pal ))
  expect_true( is.numeric( pal ))
  pal <- get_palette("viridis", FALSE)
  expect_false( is.matrix( pal ))
  expect_true( is.character( pal ))
})
