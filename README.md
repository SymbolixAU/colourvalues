
[![Travis-CI Build
Status](https://travis-ci.org/SymbolixAU/RcppViridis.svg?branch=master)](https://travis-ci.org/SymbolixAU/RcppViridis)
[![Coverage
status](https://codecov.io/gh/SymbolixAU/RcppViridis/branch/master/graph/badge.svg)](https://codecov.io/github/SymbolixAU/RcppViridis?branch=master)
[![Github
Stars](https://img.shields.io/github/stars/SymbolixAU/RcppViridis.svg?style=social&label=Github)](https://github.com/SymbolixAU/RcppViridis)

<!-- README.md is generated from README.Rmd. Please edit that file -->

# RcppViridis

### What does it do?

It maps viridis colours to variables, and quickly\!

### How do I install it?

Install the development version from
[GitHub](https://github.com/SymbolixAU/RcppViridis) with:

``` r
# install.packages("devtools")
devtools::install_github("SymbolixAU/RcppViridis")
```

-----

### How can I make use of it in my package?

**Rcpp**

All functions are written in `Rcpp`. I have exposed some of them in
header files so you can `LinkTo` them in your package.

**R**

If you’re not using `Rcpp`, just `Import` this package like you would
any other.

## Do you have any examples?

Of course\!

#### 256 numbers mapped to a colour

``` r
df <- data.frame(a = 10, x = 1:256)
df$col <- colour_variables(df$x, palette = "viridis")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-1-1.png" width="100%" height="200" />

#### 256 numbers on a non-linear scale

``` r
df <- data.frame(a = 10, x = c((1:256)**3))
df$col <- colour_variables(df$x, palette = "viridis")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-2-1.png" width="100%" height="200" />

#### 1000 random numbers

``` r
df <- data.frame(a = 10, x = rnorm(n = 1000))
df$col <- colour_variables(df$x, palette = "inferno")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-3-1.png" width="100%" height="200" />

Eurgh\!

``` r
df <- df[with(df, order(x)), ]
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" height="200" />

That’s better\!

-----

### What’s the performance like?

**1 million numeric values**

``` r
library(microbenchmark)
library(ggplot2)
library(scales)
library(viridisLite)

n <- 1e6
df <- data.frame(x = rnorm(n = n))

m <- microbenchmark(
  RcppViridis = { RcppViridis::colour_variables(x = df$x) },
  scales = { col_numeric(palette = rgb(subset(viridis.map, opt=="D")[, 1:3]), domain = range(df$x))(df$x) },
  times = 25
)
m
# Unit: milliseconds
#         expr      min       lq     mean   median       uq      max neval
#  RcppViridis 167.0503 173.1342 182.9626 176.6451 185.4215 247.2992    25
#       scales 280.6652 302.0834 322.4607 323.1510 334.0339 384.7117    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-5-1.png" width="100%" height="400" />

**1 million characters (26 unique values)**

``` r
library(microbenchmark)
library(ggplot2)
library(scales)
library(viridisLite)

n <- 1e6
x <- sample(x = letters, size = n, replace = TRUE)
df <- data.frame(x = x)

m <- microbenchmark(
  RcppViridis = { x <- RcppViridis::colour_variables(x = df$x) },
  scales = { y <- col_factor(palette = rgb(subset(viridis.map, opt=="D")[, 1:3]), domain = unique(df$x))(df$x) },
  times = 25
)
m
# Unit: milliseconds
#         expr      min       lq     mean   median       uq      max neval
#  RcppViridis 164.1425 168.6360 173.6380 174.0330 176.3976 187.7963    25
#       scales 293.7640 304.5998 326.4161 312.2175 360.0056 373.3169    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-6-1.png" width="100%" height="400" />
