# v0.2.1

* `show_colours()` to plot all colour palettes
* added more colour palettes. Use `colour_palettes()` to list them
* fix NA values in summary [issue 39](https://github.com/SymbolixAU/colourvalues/issues/39)
* alpha now accepts fewer than 5 values when using a vector

# v0.2.0

* `format`, `summary`, `n_summaries` arguments for returning summary colours (for use in legends)
* `convert_colours()` function exposed to R to convert between hex-rgb [issue 14](https://github.com/SymbolixAU/colourvalues/issues/14)
* speed improvement for internal hex-to-RGB conversion
* speed improvement for `NumericVector`s [issue 26](https://github.com/SymbolixAU/colourvalues/issues/26)
* updated headers with more `inline` statements
* Added a `NEWS.md` file to track changes to the package.
