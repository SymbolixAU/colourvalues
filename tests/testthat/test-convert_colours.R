context("convert")

test_that("various hex string formats converted RGBA", {
  expect_equal(convert_colour("#FFFFFFFF"), matrix(c(rep(255,4)),ncol = 4))
  expect_equal(convert_colour("#FFFFFF"), matrix(c(rep(255,3)),ncol = 3))
  expect_equal(convert_colour("#FFFF"), matrix(c(rep(255,4)),ncol = 4))
  expect_equal(convert_colour("#FFF"), matrix(c(rep(255,3)),ncol = 3))

  expect_error(convert_colour("FFFFFFFF"), "unknown hex string, expecting # symbol")
  expect_error(convert_colour("#F"), "Unsupported hex string")
  expect_error(convert_colour("#FF"), "Unsupported hex string")
  expect_error(convert_colour("#FFFFF"), "Unsupported hex string")
  expect_error(convert_colour("#FFFFFFF"), "Unsupported hex string")
})

test_that("hex strings correctly converted to RGB(A) matrices", {

  expect_equal(convert_colour("#FFAA00"), matrix(c(255,170,0),ncol=3))
  expect_equal(convert_colour("#FFAA00FF"), matrix(c(255,170,0,255),ncol=4))
  ## element with and wihtout ALPHA
  expect_equal(convert_colour(c("#FFAA00","#FFAA00AA")), matrix(c(255,170,0,255,255,170,0,170),ncol=4,byrow=T))

  expect_equal(convert_colour("#FA0"), matrix(c(255,170,0), ncol =3 ))
  expect_equal(convert_colour("#FA0F"), matrix(c(255,170,0,255),ncol=4))
  ## element with and wihtout ALPHA
  expect_equal(convert_colour(c("#FA0","#FA0A")), matrix(c(255,170,0,255,255,170,0,170),ncol=4,byrow=T))
  expect_equal(convert_colour(c("#FA0A","#FFAA00AA")), matrix(c(255,170,0,170,255,170,0,170),ncol=4,byrow=T))
  expect_equal(convert_colour(c("#FA0","#FFAA00AA")), matrix(c(255,170,0,255,255,170,0,170),ncol=4,byrow=T))

})
