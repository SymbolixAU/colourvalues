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

test_that("convert_color and convert_colours work as per convert_colour", {
  expect_equal(convert_colour("#FA0"), convert_colours("#FA0"))
  expect_equal(convert_colour("#FA0"), convert_color("#FA0"))
  expect_equal(convert_colour("#FA0"), convert_colors("#FA0"))
})

test_that("RGB matrices converted to hex strings", {

  expect_equal(convert_colour(c(255,170,0)),"#FFAA00")
  expect_equal(convert_colour(c(255,170,0,170)),"#FFAA00AA")
  expect_equal(convert_colour(matrix(c(255,170,0), ncol = 3)), "#FFAA00")
  expect_equal(convert_colour(matrix(c(255,170,0,255,170,0), byrow = T,ncol = 3)), c("#FFAA00","#FFAA00"))
  expect_equal(convert_colour(matrix(c(255,170,0,170,255,170,0,170), byrow = T,ncol = 4)), c("#FFAA00AA","#FFAA00AA"))

})

test_that("round trip conversions work", {
  expect_equal(convert_colour(convert_colour("#FAFA09")), "#FAFA09")
  expect_equal(convert_colour(convert_colour(matrix(c(123,211,113,25),ncol = 4))), matrix(c(123,211,113,25),ncol = 4))
})

test_that("invalid matrix & vectors error", {
  expect_error(convert_colour(1:5), "unknown RGB vector")
  expect_error(convert_colour(matrix(c(1,2),ncol = 2)), "unknown RGB matrix")
  expect_error(convert_colour(c("a","b","c")), "unknown hex string, expecting # symbol")
  expect_error(convert_colour(matrix(c("a","b","c"), ncol = 3)))
  expect_error(convert_colour(data.frame(red = 255, green = 170, blue = 0)), "unsupported type")
})
