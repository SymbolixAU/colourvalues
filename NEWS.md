
# v0.3.11

* Added missing `Rcpp::clone()` calls

# v0.3.10

* removed local copy of `cardinal_cubic_b_spline.hpp`

# v0.3.9

* Udpated S3 methods to be consistent

# v0.3.8

* Updated tests to [appease Boost (BH)](https://github.com/SymbolixAU/colourvalues/pull/77)
* Updated Rcpp and BH dependency requirements

# v0.3.7

* fixed gcc-ASAN valgrind error

# v0.3.6

* updated interleave code
* validate `na_colour` hex input [issue70](https://github.com/SymbolixAU/colourvalues/issues/70)
* Bug fixed for `na_colour` when `include_alpha = FALSE` [issue 69](https://github.com/SymbolixAU/colourvalues/issues/69)

# v0.3.5

* return interleaved vectors (C++ only)
* patch for failures on rdevel

# v0.3.4

* removed Boost dates
* running self-contained boost headers
* removed ggplot2 from readme and suggests

# v0.3.3

* updated `cubic_b_spline` to `cardinal_cubic_b_spline` -  [issue61](https://github.com/SymbolixAU/colourvalues/issues/61)

# v0.3.2

* fixed updating-by-reference [issue 60](https://github.com/SymbolixAU/colourvalues/issues/60)
* `get_palette()` gets a `rgb = TRUE` argument [issue 58](https://github.com/SymbolixAU/colourvalues/issues/58)

# v0.3.1

* `get_palette()` for returning 256x3 matrix of colorus
* factor-level order maintained in summary
* lists supported
* Added palette row check function inside .hpp files 
* BH -DBOOST_NO_AUTO_PTR flag

# v0.2.2

* [0,1) alpha values treated as percentage [issue 37](https://github.com/SymbolixAU/colourvalues/issues/37)
* Fixed NAs in character summary values [issue 42](https://github.com/SymbolixAU/colourvalues/issues/42)
* Improved handling of Dates in summary values

# v0.2.1

* `show_colours()` to plot all colour palettes
* added more colour palettes. Use `colour_palettes()` to list them
* fix NA values in summary [issue 39](https://github.com/SymbolixAU/colourvalues/issues/39)
* alpha now accepts fewer than 5 values when using a vector

# v0.2.0

* `alpha` can accept [0,1) values to indicate a percentage
* `format`, `summary`, `n_summaries` arguments for returning summary colours (for use in legends)
* `convert_colours()` function exposed to R to convert between hex-rgb [issue 14](https://github.com/SymbolixAU/colourvalues/issues/14)
* speed improvement for internal hex-to-RGB conversion
* speed improvement for `NumericVector`s [issue 26](https://github.com/SymbolixAU/colourvalues/issues/26)
* updated headers with more `inline` statements
* Added a `NEWS.md` file to track changes to the package.
