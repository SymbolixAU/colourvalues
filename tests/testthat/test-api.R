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
  lst_nv <- list(nv)
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


  ## lists get summaries
  res_lst1 <- colourvalues:::rcpp_colour_values_hex(
    x = lst, palette = mat_pal, alpha = 255.0, n_summaries = 5, format = FALSE
  )

  res_lst2 <- colourvalues:::rcpp_colour_values_hex(
    x = list(letters[1:5]), palette = mat_pal, alpha = 255.0, n_summaries = 3, format = FALSE
  )

  res_lst3 <- colourvalues:::rcpp_colour_values_hex(
    x = list(letters[1:5]), palette = mat_pal, alpha = 255.0, n_summaries = 0, format = FALSE
  )

  expect_equal( res_lst1$summary_colours, res_lst2$summary_colours )
  expect_equal( res_lst1$colours, res_lst2$colours )
  expect_equal( res_lst1$colours, res_lst )
  expect_null( res_lst3$summary_values )

  res <- colourvalues:::rcpp_colour_values_hex(
    x = lst_nv, palette = mat_pal, alpha = 255.0, summary = TRUE, format = FALSE
  )

  res2 <- colourvalues:::rcpp_colour_values_hex(
    x = lst_nv, palette = str_pal, alpha = 255.0, n_summaries = 5, format = FALSE
  )

  expect_equal( res, res2 )

  expect_equal(
    res$colours[[1]]
    , colour_values(nv, n_summaries = 5, format = FALSE)$colours
  )

  expect_equal(
    res$summary_values
    , colour_values(nv, n_summaries = 5, format = FALSE)$summary_values
  )

  expect_equal(
    res$summary_colours
    , colour_values(nv, n_summaries = 5, format = FALSE)$summary_colours
  )
})

test_that("interleaved api covered",{

  str_pal <- "viridis"
  mat_pal <- colourvalues::get_palette("viridis")
  int_mat_pal <- matrix( as.integer( mat_pal ), ncol = 4, byrow = TRUE )
  nv_mat_pal <- matrix( as.numeric( as.integer( mat_pal ) ), ncol = 4, byrow = T )
  unk_pal <- list()

  iv <- 1L:5L
  nv <- c(1.1,2.2,3.3,4.4,5.5)
  sv <- letters[1:5]
  lst <- list(1:5)
  lst_nv <- list(nv)
  lst_iv <- list(1L:5L)
  lst_str <- list(letters[1:5])
  fv <- as.factor( iv )
  lv <- c(FALSE, TRUE)

  alpha = 1L

  res1 <- colourvalues:::rcpp_colour_values_rgb_interleaved(
    x = lst_nv
    , palette = nv_mat_pal
    , alpha = alpha
    , repeats = 1
    , total_colours = 5
    , summary = TRUE
  )

  res2 <- colourvalues:::rcpp_colour_values_rgb_interleaved(
    x = lst_str
    , palette = nv_mat_pal
    , alpha = alpha
    , repeats = 1
    , total_colours = 5
    , n_summaries = 5
  )

  expect_equal( res1$colours, res2$colours )
  expect_equal( res1$summary_colours, res2$summary_colours )


  res1 <- colourvalues:::rcpp_colour_values_rgb_interleaved(
    x = lst_nv
    , palette = str_pal
    , alpha = alpha
    , repeats = 1
    , total_colours = 5
    , summary = TRUE
  )

  res2 <- colourvalues:::rcpp_colour_values_rgb_interleaved(
    x = lst_str
    , palette = str_pal
    , alpha = alpha
    , repeats = 1
    , total_colours = 5
    , n_summaries = 5
  )

  res3 <- colourvalues:::rcpp_colour_values_rgb_interleaved(
    x = lst_iv
    , palette = str_pal
    , alpha = alpha
    , repeats = 1
    , total_colours = 5
    , n_summaries = 5
  )

  expect_equal( res1$colours, res2$colours )
  expect_equal( res1$summary_colours, res2$summary_colours )

  expect_equal( res1$colours, res3$colours )
  expect_equal( res1$summary_colours, res3$summary_colours )

})




