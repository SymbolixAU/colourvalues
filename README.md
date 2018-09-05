
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

See for yourself

``` r
library(microbenchmark)
library(ggplot2)
library(scales)

n <- 1e4
df <- data.frame(x = rnorm(n = n))

m <- microbenchmark(
  RcppViridis = { RcppViridis::colour_variables(x = df$x) },
  scales = { scales::col_numeric(palette = viridisLite::viridis(n), domain = unique(df$x))(df$x) },
  times = 25
)
m
# Unit: milliseconds
#         expr        min         lq       mean     median         uq
#  RcppViridis   1.607608   1.718504   1.794033   1.752147   1.817238
#       scales 638.290248 694.100944 723.357659 721.268412 760.871100
#         max neval
#    2.188736    25
#  804.561984    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-5-1.png" width="100%" height="400" />
