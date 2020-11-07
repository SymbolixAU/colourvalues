context("api")

test_that("hex api covered",{

  str_pal <- "viridis"
  mat_pal <- colourvalues::get_palette("viridis")
  int_mat_pal <- matrix( as.integer( mat_pal ), ncol = 4, byrow = TRUE )
  nv_mat_pal <- matrix( as.numeric( as.integer( mat_pal ) ), ncol = 4, byrow = T )
  unk_pal <- list()

  iv <- 1L:5L
  nv <- c(1.1,2.2,3.3,4.4,5.5)
  sv <- letters[1:5]
  lst <- list(1:5)
  fv <- as.factor( iv )
  lv <- c(FALSE, TRUE)

  alpha = 1L

  ## Teting numeric and int palettes reutrn same results
  res1 <- colourvalues:::rcpp_colour_values_hex(
    x = iv, palette = int_mat_pal, alpha = 255.0
  )
  res2 <- colourvalues:::rcpp_colour_values_hex(
    x = iv, palette = nv_mat_pal, alpha = 255.0
  )
  expect_equal( res1, res2 )

  expect_error(
    colourvalues:::rcpp_colour_values_hex(
      x = iv, palette = unk_pal, alpha = 255.0
    )
    , "colourvalues - Unknown palette type"
  )

  res_lst <- colourvalues:::rcpp_colour_values_hex(
    x = lst, palette = mat_pal, alpha = 255.0
  )

  res_iv <- colourvalues:::rcpp_colour_values_hex(
    x = iv, palette = mat_pal, alpha = 255.0
  )

  res_lv <- colourvalues:::rcpp_colour_values_hex(
    x = lv, palette = mat_pal, alpha = 255.0
  )

  expect_equal( res_lst[[1]], res_iv )
  expect_equal( res_lv, colourvalues::colour_values(1:2) )


})
