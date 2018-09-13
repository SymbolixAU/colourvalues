
[![Travis-CI Build
Status](https://travis-ci.org/SymbolixAU/RcppViridis.svg?branch=master)](https://travis-ci.org/SymbolixAU/RcppViridis)
[![Coverage
status](https://codecov.io/gh/SymbolixAU/RcppViridis/branch/master/graph/badge.svg)](https://codecov.io/github/SymbolixAU/RcppViridis?branch=master)
[![Github
Stars](https://img.shields.io/github/stars/SymbolixAU/RcppViridis.svg?style=social&label=Github)](https://github.com/SymbolixAU/RcppViridis)

<!-- README.md is generated from README.Rmd. Please edit that file -->

# RcppViridis

-----

### What does it do?

It maps viridis colours to values, and quickly\!

**Note** It does not perform a 1-to-1 mapping of a palette to values. It
interpolates the colours from a given palette.

### Why did you build it?

I’m aware there are other methods for mapping colours to values. And
which do it quick too. But I can never remember them, and I find the
interfaces a bit cumbersome. For example, `scales::col_numeric(palette =
viridisLite::viridis(5), domain = range(1:5))(1:5)`.

I wanted **one** function which will work on **one** argument.

``` r
colour_values(1:5)
# [1] "#440154FF" "#3B528BFF" "#21908CFF" "#5DC963FF" "#FDE725FF"
colour_values(letters[1:5])
# [1] "#440154FF" "#3B528BFF" "#21908CFF" "#5DC963FF" "#FDE725FF"
```

I also want it available at the `src` (C/C++) level for linking to other
packages.

-----

### Why do you spell colour with a ‘u’?

Because it’s correct, and [R tells us
to](http://developer.r-project.org/Rds.html)

> For consistency, aim to use British (rather than American) spelling

But don’t worry, `color_values(1:5)` works as well

-----

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

For example, the `LinkingTo` section in `DESCRIPTION` will look
something like

``` yaml
LinkingTo: 
    Rcpp,
    RcppViridis
```

And in a **c++** source file so you can `#include` a header and use the
available functions

``` cpp
#include "RcppViridis/colours/colours_hex.hpp"
// [[Rcpp::depends(RcppViridis)]]
```

**R**

If you’re not using `Rcpp`, just `Import` this package like you would
any other.

## Do you have any examples?

Of course\!

#### 256 numbers mapped to a colour

``` r
df <- data.frame(a = 10, x = 1:256)
df$col <- colour_values(df$x, palette = "viridis")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-2-1.png" width="100%" height="200" />

#### 5000 numbers on a non-linear scale

``` r
df <- data.frame(a = 10, x = c((1:5000)**3))
df$col <- colour_values(df$x, palette = "viridis")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-3-1.png" width="100%" height="200" />

#### 1000 random numbers

``` r
df <- data.frame(a = 10, x = rnorm(n = 1000))
df$col <- colour_values(df$x, palette = "inferno")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" height="200" />

Eurgh\!

``` r
df <- df[with(df, order(x)), ]
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-5-1.png" width="100%" height="200" />

That’s better\!

-----

## Do I have to use the in-built palettes?

No, you can use your own specified as a matrix of red, green and blue
columns in the range \[0,255\]

``` r
n <- 100
m <- grDevices::colorRamp(c("red", "green"))( (1:n)/n )
df <- data.frame(a = 10, x = 1:n)
df$col <- colour_values(df$x, palette = m)
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-6-1.png" width="100%" height="200" />

## Do you support ‘alpha’ values

Yep. Either supply a single alpha value for all the colours

``` r
## single alpha value for all colours
df <- data.frame(a = 10, x = 1:255)
df$col <- colour_values(df$x, alpha = 50)
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-7-1.png" width="100%" height="200" />

Or use a vector of values the same length as `x`

``` r
df <- data.frame(a = 10, x = 1:300, y = rep(c(1:50, 50:1), 3) )
df$col <- colour_values(df$x, alpha = df$y)
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-8-1.png" width="100%" height="200" />

Or include the alpha value as a 4th column in the palette matrix

``` r
n <- 100
m <- grDevices::colorRamp(c("red", "green"))( (1:n)/n )
## alpha values
m <- cbind(m, seq(0, 255, length.out = 100))
df <- data.frame(a = 10, x = 1:n)
df$col <- colour_values(df$x, palette = m)
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-9-1.png" width="100%" height="200" />

## Some of my plotting functions don’t support alpha, can I exclude it?

Yep. Set `include_alpha = FALSE`

``` r
colour_values(1:5, include_alpha = F)
# [1] "#440154" "#3B528B" "#21908C" "#5DC963" "#FDE725"
colour_values_rgb(1:5, include_alpha = F)
#      [,1] [,2] [,3]
# [1,]   68    1   84
# [2,]   59   82  139
# [3,]   33  144  140
# [4,]   93  201   99
# [5,]  253  231   37
```

-----

### What’s the performance like?

**10 million numeric values**

``` r
library(microbenchmark)
library(ggplot2)
library(scales)
library(viridisLite)
# 
# Attaching package: 'viridisLite'
# The following objects are masked from 'package:RcppViridis':
# 
#     cividis, inferno, magma, plasma, viridis

n <- 1e7
df <- data.frame(x = rnorm(n = n))

m <- microbenchmark(
  RcppViridis = { RcppViridis::colour_values(x = df$x) },
  scales = { col_numeric(palette = rgb(subset(viridis.map, opt=="D")[, 1:3]), domain = range(df$x))(df$x) },
  times = 25
)
m
# Unit: seconds
#         expr      min       lq     mean   median       uq      max neval
#  RcppViridis 1.661479 1.667042 1.685440 1.670131 1.675113 1.877817    25
#       scales 2.881157 2.951867 3.002407 2.987579 3.034468 3.305677    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-11-1.png" width="100%" height="400" />

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
  RcppViridis = { x <- RcppViridis::colour_values(x = df$x) },
  scales = { y <- col_factor(palette = rgb(subset(viridis.map, opt=="D")[, 1:3]), domain = unique(df$x))(df$x) },
  times = 25
)
m
# Unit: milliseconds
#         expr      min       lq     mean   median       uq      max neval
#  RcppViridis 175.5278 180.3672 185.3634 187.5670 190.1344 193.8903    25
#       scales 300.2514 323.6980 340.9838 337.4562 349.3760 427.9255    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-12-1.png" width="100%" height="400" />
