
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

And in a **c++** source file so you can `#include` the API header

``` cpp
#include "colourvalues/api.hpp"
// [[Rcpp::depends(colourvalues)]]
```

And call

``` cpp
// return hex colours
colourvalues::api::colour_values_hex()

// return RGP matrix
colourvalues::api::colour_values_rgb()
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
# Warning in if (grepl("colorspace|colourspace", colours)) {: the condition
# has length > 1 and only the first element will be used
# Warning in if (grepl("colorramp|colourramp", colours)) {: the condition has
# length > 1 and only the first element will be used
#  [1] "viridis"  "cividis"  "magma"    "inferno"  "plasma"   "ylorrd"  
#  [7] "ylorbr"   "ylgnbu"   "ylgn"     "reds"     "rdpu"     "purples" 
# [13] "purd"     "pubugn"   "pubu"     "orrd"     "oranges"  "greys"   
# [19] "greens"   "gnbu"     "bupu"     "bugn"     "blues"    "spectral"
# [25] "rdylgn"   "rdylbu"   "rdgy"     "rdbu"     "puor"     "prgn"    
# [31] "piyg"     "brbg"     "terrain"  "topo"     "heat"     "cm"      
# [37] "rainbow"
```

And you can use `show_colours()` to view them all. Here’s what some of
them look like

``` r
show_colours( colours = colour_palettes(c("viridis", "colorspace")))
# Warning in if (grepl("colorspace|colourspace", colours)) {: the condition
# has length > 1 and only the first element will be used
# Warning in if (grepl("colorramp|colourramp", colours)) {: the condition has
# length > 1 and only the first element will be used
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
#  [1] "#66CC5DFF" "#32658EFF" "#31678EFF" "#5EC962FF" "#FDE725FF"
#  [6] "#24878EFF" "#56C666FF" "#3B528BFF" "#52C569FF" "#440154FF"
# 
# $summary_values
# [1] "-1.55" "0.17"  "1.88" 
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
#  [1] "#1FA088FF" "#41BE72FF" "#482072FF" "#1FA088FF" "#228B8DFF"
#  [6] "#FDE725FF" "#1F958BFF" "#2F6B8EFF" "#FDE725FF" "#24AA83FF"
# [11] "#471164FF" "#1F958BFF" "#39558CFF" "#1FA088FF" "#26808EFF"
# [16] "#57C766FF" "#8AD647FF" "#34608DFF" "#30B47CFF" "#1FA088FF"
# [21] "#26808EFF" "#440154FF" "#440154FF" "#E2E418FF" "#3F4989FF"
# [26] "#6FCF58FF" "#471164FF" "#FDE725FF" "#34608DFF" "#482072FF"
# [31] "#228B8DFF" "#2B768EFF" "#3F4989FF" "#A7DB34FF" "#2B768EFF"
# [36] "#C5E022FF" "#433C84FF" "#39558CFF" "#A7DB34FF" "#41BE72FF"
# [41] "#1FA088FF" "#26808EFF" "#472E7CFF" "#24AA83FF" "#26808EFF"
# [46] "#1F958BFF" "#41BE72FF" "#2B768EFF" "#440154FF" "#57C766FF"
# 
# $summary_values
#  [1] "a" "b" "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q"
# [18] "r" "s" "t" "v" "x" "y" "z"
# 
# $summary_colours
#  [1] "#440154FF" "#471164FF" "#482072FF" "#472E7CFF" "#433C84FF"
#  [6] "#3F4989FF" "#39558CFF" "#34608DFF" "#2F6B8EFF" "#2B768EFF"
# [11] "#26808EFF" "#228B8DFF" "#1F958BFF" "#1FA088FF" "#24AA83FF"
# [16] "#30B47CFF" "#41BE72FF" "#57C766FF" "#6FCF58FF" "#8AD647FF"
# [21] "#A7DB34FF" "#C5E022FF" "#E2E418FF" "#FDE725FF"
```

### I see you support lists, but how does it work?

Basically, it’s the same as un-listing the list to create a vector of
all the values, then colouring them.

So if your list contains different types, it will coerce all values to
the same type and colour them.

But it returns a list of the same structure.

For example,

``` r

l <- list( x = 1:5, y = list(z = letters[1:5] ) )
colour_values( l )
# [[1]]
# [1] "#440154FF" "#482878FF" "#3E4A89FF" "#31688EFF" "#26838EFF"
# 
# [[2]]
# [[2]][[1]]
# [1] "#1F9D89FF" "#35B779FF" "#6CCE59FF" "#B4DD2CFF" "#FDE725FF"

x <- c( 1:5, letters[1:5] )
colour_values( x )
#  [1] "#440154FF" "#482878FF" "#3E4A89FF" "#31688EFF" "#26838EFF"
#  [6] "#1F9D89FF" "#35B779FF" "#6CCE59FF" "#B4DD2CFF" "#FDE725FF"
```

What it doesn’t do is treat each list element independently. For this
you would use

``` r
lapply( l, colour_values ) 
# $x
# [1] "#440154FF" "#3B528BFF" "#21908CFF" "#5DC963FF" "#FDE725FF"
# 
# $y
# $y[[1]]
# [1] "#440154FF" "#3B528BFF" "#21908CFF" "#5DC963FF" "#FDE725FF"
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
#  colourvalues 3.325935 3.512659 4.169802 4.417923 4.589773 4.849371    25
#        scales 6.254049 8.290376 8.260139 8.629479 8.766626 9.236977    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-20-1.png" width="100%" height="400" />

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
#  colourvalues 375.0049 393.5553 398.7031 397.6235 405.7669 417.9495    25
#        scales 639.1727 655.2213 686.7740 669.7334 696.7927 882.1402    25

autoplot(m)
# Coordinate system already present. Adding new coordinate system, which will replace the existing one.
```

<img src="man/figures/README-unnamed-chunk-21-1.png" width="100%" height="400" />
