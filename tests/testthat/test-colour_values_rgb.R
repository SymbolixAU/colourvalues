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

  lst <- colour_values_rgb(1:10, n_summaries = 2)
  expect_true(all( lst$summary_values == c(1,10) ) )
  expect_true( all( colour_values_rgb(c(1,10)) == lst$summary_colours ) )
  lst <- colour_values_rgb(-10:10, n_summaries = 5)
  expect_true(all( lst$summary_values == c(-10,-5,0,5,10) ) )
  expect_true( all( colour_values_rgb(c(-10,-5,0,5,10)) == lst$summary_colours ) )


  lst <- colour_values_rgb(letters, summary = T)
  expect_true(all(lst$colours == lst$summary_colours))
  expect_true(all(lst$summary_values == letters))

  lst <- colour_values_rgb(sample(letters, size = 100, replace = T), summary = T)
  expect_true(all(lst$summary_values == letters))
  expect_true(all(lst$summary_colours == colour_values_rgb(letters) ))

})
