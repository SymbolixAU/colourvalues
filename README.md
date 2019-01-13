
[![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/colourvalues)](http://cran.r-project.org/package=colourvalues)
![downloads](http://cranlogs.r-pkg.org/badges/grand-total/colourvalues)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/colourvalues)](http://cran.r-project.org/web/packages/colourvalues/index.html)
[![Travis-CI Build
Status](https://travis-ci.org/SymbolixAU/colourvalues.svg?branch=master)](https://travis-ci.org/SymbolixAU/colourvalues)
[![Coverage
status](https://codecov.io/gh/SymbolixAU/colourvalues/branch/master/graph/badge.svg)](https://codecov.io/github/SymbolixAU/colourvalues?branch=master)
[![Github
Stars](https://img.shields.io/github/stars/SymbolixAU/colourvalues.svg?style=social&label=Github)](https://github.com/SymbolixAU/colourvalues)

<!-- README.md is generated from README.Rmd. Please edit that file -->

# colourvalues

-----

### What does it do?

It maps viridis colours (by default) to values, and quickly\!

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

From CRAN

``` r
install.packages("colourvalues")
```

Or install the development version from
[GitHub](https://github.com/SymbolixAU/colourvalues) with:

``` r
# install.packages("devtools")
devtools::install_github("SymbolixAU/colourvalues")
```

-----

### How can I make use of it in my package?

**Rcpp**

All functions are written in `Rcpp`. I have exposed some of them in
header files so you can “link to” them in your package.

For example, the `LinkingTo` section in `DESCRIPTION` will look
something like

``` yaml
LinkingTo: 
    Rcpp,
    colourvalues
```

And in a **c++** source file so you can `#include` a header and use the
available functions

``` cpp
#include "colourvalues/colours/colours_hex.hpp"
// [[Rcpp::depends(colourvalues)]]
```

**R**

If you’re not using `Rcpp`, just `Import` this package like you would
any other.

## Do you have any examples?

Of course\!

#### 256 numbers mapped to a colour

``` r
bar_plot <- function(df) {
  barplot( height = df[["a"]], col = df[["col"]], border = NA, space = 0, yaxt = 'n')
}
df <- data.frame(a = 10, x = 1:256)
df$col <- colour_values(df$x, palette = "viridis")
bar_plot( df )
```

<img src="man/figures/README-unnamed-chunk-3-1.png" width="100%" height="200" />

#### 5000 numbers on a non-linear scale

``` r
df <- data.frame(a = 10, x = c((1:5000)**3))
df$col <- colour_values(df$x, palette = "viridis")
bar_plot( df )
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" height="200" />

#### 1000 random numbers

``` r
df <- data.frame(a = 10, x = rnorm(n = 1000))
df$col <- colour_values(df$x, palette = "inferno")
bar_plot( df )
```

<img src="man/figures/README-unnamed-chunk-5-1.png" width="100%" height="200" />

Eurgh\!

``` r
df <- df[with(df, order(x)), ]
bar_plot( df )
```

<img src="man/figures/README-unnamed-chunk-6-1.png" width="100%" height="200" />

That’s better\!

-----

## Are there only viridis palettes?

No, you can chose one from

``` r
colour_palettes()
#  [1] "viridis"        "cividis"        "magma"          "inferno"       
#  [5] "plasma"         "ylorrd"         "ylorbr"         "ylgnbu"        
#  [9] "ylgn"           "reds"           "rdpu"           "purples"       
# [13] "purd"           "pubugn"         "pubu"           "orrd"          
# [17] "oranges"        "greys"          "greens"         "gnbu"          
# [21] "bupu"           "bugn"           "blues"          "spectral"      
# [25] "rdylgn"         "rdylbu"         "rdgy"           "rdbu"          
# [29] "puor"           "prgn"           "piyg"           "brbg"          
# [33] "terrain"        "topo"           "heat"           "cm"            
# [37] "rainbow"        "terrain_hcl"    "heat_hcl"       "sequential_hcl"
# [41] "rainbow_hcl"    "diverge_hcl"    "diverge_hsv"    "ygobb"         
# [45] "matlab_like2"   "matlab_like"    "magenta2green"  "cyan2yellow"   
# [49] "blue2yellow"    "green2red"      "blue2green"     "blue2red"
```

And you can use `show_colours()` to view them all. Here’s what some of
them look
like

``` r
show_colours( colours = colour_palettes(c("viridis", "colorspace")))
```

<img src="man/figures/README-unnamed-chunk-8-1.png" width="100%" height="200" />

## Do I have to use the in-built palettes?

No, you can use your own specified as a matrix of red, green and blue
columns in the range \[0,255\]

``` r
n <- 100
m <- grDevices::colorRamp(c("red", "green"))( (1:n)/n )
df <- data.frame(a = 10, x = 1:n)
df$col <- colour_values(df$x, palette = m)
bar_plot( df )
```

<img src="man/figures/README-unnamed-chunk-9-1.png" width="100%" height="200" />

## Do you support ‘alpha’ values

Yep. Either supply a single alpha value for all the colours

``` r
## single alpha value for all colours
df <- data.frame(a = 10, x = 1:255)
df$col <- colour_values(df$x, alpha = 50)
bar_plot( df )
```

<img src="man/figures/README-unnamed-chunk-10-1.png" width="100%" height="200" />

Or use a vector of values the same length as `x`

``` r
df <- data.frame(a = 10, x = 1:300, y = rep(c(1:50, 50:1), 3) )
df$col <- colour_values(df$x, alpha = df$y)
bar_plot( df )
```

<img src="man/figures/README-unnamed-chunk-11-1.png" width="100%" height="200" />

Or include the alpha value as a 4th column in the palette matrix

``` r
n <- 100
m <- grDevices::colorRamp(c("red", "green"))( (1:n)/n )
## alpha values
m <- cbind(m, seq(0, 255, length.out = 100))
df <- data.frame(a = 10, x = 1:n)
df$col <- colour_values(df$x, palette = m)
bar_plot( df )
```

<img src="man/figures/README-unnamed-chunk-12-1.png" width="100%" height="200" />

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

## Can I get a summary of colours to use in a legend?

Yes, for numeric values use the `n_summaries` argument to specify the
number of summary values you’d like

``` r
colour_values(1:10, n_summaries = 3)
# $colours
#  [1] "#440154FF" "#482878FF" "#3E4A89FF" "#31688EFF" "#26838EFF"
#  [6] "#1F9D89FF" "#35B779FF" "#6CCE59FF" "#B4DD2CFF" "#FDE725FF"
# 
# $summary_values
# [1] "1.00"  "5.50"  "10.00"
# 
# $summary_colours
# [1] "#440154FF" "#21908CFF" "#FDE725FF"
```

You can also specify the number of digits you’d like returned in the
summary

``` r
colour_values(rnorm(n = 10), n_summaries = 3, digits = 2)
# $colours
#  [1] "#27AD81FF" "#3F4989FF" "#39568CFF" "#218F8DFF" "#228C8DFF"
#  [6] "#FDE725FF" "#440154FF" "#3F4889FF" "#453681FF" "#26818EFF"
# 
# $summary_values
# [1] "-1.21" "0.71"  "2.62" 
# 
# $summary_colours
# [1] "#440154FF" "#21908CFF" "#FDE725FF"
```

You can also use `format = FALSE` if you don’t want the summary values
formatted.

``` r
dte <- seq(as.Date("2018-01-01"), as.Date("2018-02-01"), by = 1)
colour_values(dte, n_summaries = 3)
# $colours
#  [1] "#440154FF" "#470D60FF" "#48196BFF" "#482474FF" "#472E7CFF"
#  [6] "#453882FF" "#414286FF" "#3E4B8AFF" "#3A548CFF" "#365D8DFF"
# [11] "#32658EFF" "#2E6D8EFF" "#2B758EFF" "#287D8EFF" "#25858EFF"
# [16] "#228C8DFF" "#20948CFF" "#1E9C89FF" "#20A386FF" "#25AB82FF"
# [21] "#2DB27DFF" "#39BA76FF" "#48C16EFF" "#58C765FF" "#6ACD5BFF"
# [26] "#7ED34FFF" "#92D742FF" "#A8DB34FF" "#BEDF26FF" "#D4E21BFF"
# [31] "#E9E41AFF" "#FDE725FF"
# 
# $summary_values
# [1] "2018-01-01" "2018-01-16" "2018-02-01"
# 
# $summary_colours
# [1] "#440154FF" "#21908CFF" "#FDE725FF"

colour_values(dte, n_summaries = 3, format = F)
# $colours
#  [1] "#440154FF" "#470D60FF" "#48196BFF" "#482474FF" "#472E7CFF"
#  [6] "#453882FF" "#414286FF" "#3E4B8AFF" "#3A548CFF" "#365D8DFF"
# [11] "#32658EFF" "#2E6D8EFF" "#2B758EFF" "#287D8EFF" "#25858EFF"
# [16] "#228C8DFF" "#20948CFF" "#1E9C89FF" "#20A386FF" "#25AB82FF"
# [21] "#2DB27DFF" "#39BA76FF" "#48C16EFF" "#58C765FF" "#6ACD5BFF"
# [26] "#7ED34FFF" "#92D742FF" "#A8DB34FF" "#BEDF26FF" "#D4E21BFF"
# [31] "#E9E41AFF" "#FDE725FF"
# 
# $summary_values
# [1] 17532.0 17547.5 17563.0
# 
# $summary_colours
# [1] "#440154FF" "#21908CFF" "#FDE725FF"
```

For categorical values use `summary = TRUE` to return a uniqe set of the
values, and their associated colours

``` r
colour_values(sample(letters, size = 50, replace = T), summary = T)
# $colours
#  [1] "#2F6C8EFF" "#2FB47CFF" "#482575FF" "#2F6C8EFF" "#43BF71FF"
#  [6] "#3B528BFF" "#414487FF" "#2FB47CFF" "#43BF71FF" "#5DC963FF"
# [11] "#5DC963FF" "#2F6C8EFF" "#7AD151FF" "#345F8DFF" "#7AD151FF"
# [16] "#7AD151FF" "#482575FF" "#25848EFF" "#1E9C89FF" "#2A788EFF"
# [21] "#9AD93DFF" "#3B528BFF" "#481466FF" "#7AD151FF" "#22A884FF"
# [26] "#5DC963FF" "#21908CFF" "#FDE725FF" "#21908CFF" "#DDE318FF"
# [31] "#463480FF" "#21908CFF" "#25848EFF" "#2F6C8EFF" "#481466FF"
# [36] "#25848EFF" "#440154FF" "#BCDF27FF" "#345F8DFF" "#25848EFF"
# [41] "#440154FF" "#FDE725FF" "#440154FF" "#43BF71FF" "#1E9C89FF"
# [46] "#22A884FF" "#2F6C8EFF" "#BCDF27FF" "#DDE318FF" "#463480FF"
# 
# $summary_values
#  [1] "a" "b" "c" "e" "f" "g" "h" "i" "j" "k" "m" "o" "p" "q" "r" "s" "t"
# [18] "u" "x" "y" "z"
# 
# $summary_colours
#  [1] "#440154FF" "#481466FF" "#482575FF" "#463480FF" "#414487FF"
#  [6] "#3B528BFF" "#345F8DFF" "#2F6C8EFF" "#2A788EFF" "#25848EFF"
# [11] "#21908CFF" "#1E9C89FF" "#22A884FF" "#2FB47CFF" "#43BF71FF"
# [16] "#5DC963FF" "#7AD151FF" "#9AD93DFF" "#BCDF27FF" "#DDE318FF"
# [21] "#FDE725FF"
```

-----

### What’s the performance like?

**10 million numeric values**

``` r
library(microbenchmark)
library(ggplot2)
library(scales)
library(viridisLite)

n <- 1e7
df <- data.frame(x = rnorm(n = n))

m <- microbenchmark(
  colourvalues = { colourvalues::colour_values(x = df$x) },
  scales = { col_numeric(palette = rgb(subset(viridis.map, opt=="D")[, 1:3]), domain = range(df$x))(df$x) },
  times = 25
)
m
# Unit: seconds
#          expr      min       lq     mean   median       uq      max neval
#  colourvalues 1.617036 1.629365 1.682938 1.645191 1.745641 1.800155    25
#        scales 2.820961 2.916128 3.035900 2.981311 3.140706 3.418156    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-18-1.png" width="100%" height="400" />

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
  colourvalues = { x <- colourvalues::colour_values(x = df$x) },
  scales = { y <- col_factor(palette = rgb(subset(viridis.map, opt=="D")[, 1:3]), domain = unique(df$x))(df$x) },
  times = 25
)
m
# Unit: milliseconds
#          expr      min       lq     mean   median       uq      max neval
#  colourvalues 182.1952 203.5807 206.2559 207.5844 209.7223 245.3349    25
#        scales 329.7487 342.8897 349.5171 345.3121 345.8927 417.3716    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-19-1.png" width="100%" height="400" />
