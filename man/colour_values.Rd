% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/colour_values_hex.R
\name{colour_values}
\alias{colour_values}
\alias{color_values}
\alias{colour_values_to_hex.character}
\alias{colour_values_to_hex.logical}
\alias{colour_values_to_hex.factor}
\alias{colour_values_to_hex.Date}
\alias{colour_values_to_hex.POSIXct}
\alias{colour_values_to_hex.POSIXlt}
\title{Colour Values}
\usage{
colour_values(
  x,
  palette = "viridis",
  alpha = 255,
  na_colour = "#808080FF",
  include_alpha = TRUE,
  summary = FALSE,
  n_summaries = 0,
  format = TRUE,
  digits = 2
)

color_values(
  x,
  palette = "viridis",
  alpha = 255,
  na_colour = "#808080FF",
  include_alpha = TRUE,
  summary = FALSE,
  n_summaries = 0,
  format = TRUE,
  digits = 2
)

\method{colour_values_to_hex}{character}(
  x,
  palette,
  alpha,
  na_colour,
  include_alpha,
  summary,
  n_summaries,
  format,
  digits
)

\method{colour_values_to_hex}{logical}(
  x,
  palette,
  alpha,
  na_colour,
  include_alpha,
  summary,
  n_summaries,
  format,
  digits
)

\method{colour_values_to_hex}{factor}(
  x,
  palette,
  alpha,
  na_colour,
  include_alpha,
  summary,
  n_summaries,
  format,
  digits
)

\method{colour_values_to_hex}{Date}(
  x,
  palette,
  alpha,
  na_colour,
  include_alpha,
  summary,
  n_summaries,
  format,
  digits
)

\method{colour_values_to_hex}{POSIXct}(
  x,
  palette,
  alpha,
  na_colour,
  include_alpha,
  summary,
  n_summaries,
  format,
  digits
)

\method{colour_values_to_hex}{POSIXlt}(
  x,
  palette,
  alpha,
  na_colour,
  include_alpha,
  summary,
  n_summaries,
  format,
  digits
)
}
\arguments{
\item{x}{vector of values to map to a colour}

\item{palette}{colour palette. See details and examples}

\item{alpha}{optional. Single value in [0,255] applied to all colours,
or a decimal in [0, 1) (to indicate a percentage, noting 1 is excluded),
or a vector of numeric values the same length as \code{x}.
The numeric vector will be scaled into the range [0,255].
If a matrix palette is supplied this argument is ignored.}

\item{na_colour}{hex string colour to use for NA values in the form \code{#RRGGBBAA}.}

\item{include_alpha}{logical indicating if the returned hex or matrix should include
the alpha values. Defaults to \code{TRUE}.}

\item{summary}{logical indicating if a summary of the colours should be returned as
well as the full colour mapping. This will be the unique elements of \code{x} mapped to the colour.}

\item{n_summaries}{positive integer. If supplied a summary colour palette will be returned
in a list, containing \code{n_summaries} equally spaced values of \code{x} in the range \code{[min(x),max(x)]},
and their associated colours. If a non-numeric \code{x} is used this value is ignored}

\item{format}{logical indicating if the summary values should be formatted.}

\item{digits}{number of decimal places to show in the summary}
}
\description{
maps colours to values, returning a vector of hex strings
}
\details{
The palette can either be
\itemize{
  \item{String - }{use \code{colour_palettes()} to view available palettes}
  \item{Matrix - }{At least 5 rows, and 3 (or 4) columns representing the red, green and blue (and alpha) values}
}

The matrix \code{palette} requires 5 rows because the colours are interpolated using a
cubic b-spline. This method requires 5 values.
}
\examples{

## in-built palettes
colour_values(x = 1:5) ## default is "viridis"
colour_values(x = 1:5, palette = "inferno")
colour_values(x = 1:5, palette = "plasma")
colour_values(x = 1:5, palette = "magma")
colour_values(x = 1:5, palette = "cividis")
colour_values(x = 1:5, palette = "rainbow")

## matrix palette
n <- 100
m <- grDevices::colorRamp(c("red", "green"))( (1:n)/n )
df <- data.frame(a = 10, x = 1:n)
df$col <- colour_values(df$x, palette = m)
barplot(height = df$a, col = df$col, border = NA, space = 0)

## with an alpha column on the palette
n <- 100
m <- grDevices::colorRamp(c("red", "green"))( (1:n)/n )
m <- cbind(m, seq(0, 255, length.out = 100))
df <- data.frame(a = 10, x = 1:n)
df$col <- colour_values(df$x, palette = m)
barplot(height = df$a, col = df$col, border = NA, space = 0)

## single alpha value for all colours
df <- data.frame(a = 10, x = 1:255)
df$col <- colour_values(df$x, alpha = 50)
barplot(height = df$a, col = df$col, border = NA, space = 0)

## vector of alpha values
df <- data.frame(a = 10, x = 1:300, y = rep(c(1:50, 50:1), 3) )
df$col <- colour_values(df$x, alpha = df$y)
barplot(height = df$a, col = df$col, border = NA, space = 0)

## returning a summary palette
colour_values(-10:10, n_summaries = 5)

colour_values(x = runif(20, 0, 1), n_summaries = 3, digits = 2)
colour_values(x = runif(20, 0, 1), n_summaries = 3, digits = 10)

## Formatting output
## default is TRUE
colour_values(
  x = seq(as.Date("2023-01-01"), as.Date("2023-01-31"), by = 1)
  , n_summaries = 5
)
colour_values(
  x = seq(as.Date("2023-01-01"), as.Date("2023-01-31"), by = 1)
  , n_summaries = 5
  , format = FALSE
)

}
\seealso{
colour_values_rgb
}
