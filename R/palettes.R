#' Get Palette
#'
#' retrieves one of the available palettes
#'
#' @param palette one of the available paletes. See \link{colour_palettes}
#' @param rgb logical indicating if the palette should be returned as an RGB matrix
#' \code{TRUE}, or a vector of hex strings \code{FALSE}
#'
#' @examples
#'
#' get_palette( "viridis" )
#' get_palette( "rainbow" )
#'
#' @return 3 column matrix if \code{rgb = TRUE}, otherwise a 256-length vector.
#'
#' @export
get_palette <- function( palette, rgb = TRUE ) {
  if( !palette %in% colour_palettes() ) stop("not a valid palette")

  pal <- rcpp_get_palette( palette )

  if( !rgb ) {
    return( convert_colour( pal ) )
  }

  return( pal )

}


#' Colour Palettes
#'
#' List the available colour palettes.
#'
#' @param colours vector of source colour palettes to return, one or many of
#' "viridis","rcolorbrewer","grdevices","colorspace","colorramp". NULL will reutrn all palettes.
#'
#' @details
#' The palettes available in \code{colourvalues} have been derived from those in
#' the libraries
#'
#'  * viridis
#'  * RColorBrewer
#'  * grDevices
#'  * colorspaces
#'  * colorRamp
#'
#' @examples
#' colour_palettes()
#' colour_palettes( "viridis" )
#' colour_palettes( colours = c("rcolorbrewer","grdevices") )
#'
#' @export
colour_palettes <- function( colours = NULL ) {
  if( is.null( colours ) ) colours <- c("viridis","rcolorbrewer","grdevices","colorspace","colourspace","colorramp")
  colours <- tolower(colours)

  return(
    c(
      if( "viridis" %in% colours ) { viridis_palettes() }
      , if( "rcolorbrewer" %in% colours ) { c( rcolorbrewer_seq_palettes(), rcolorbrewer_div_palettes() ) }
      , if( "grdevices" %in% colours ) { grdevices_palettes() }
      , if( any( grepl("colorspace|colourspace", colours ) ) ) { c( colorspace_seq_palettes(), colorspace_div_palettes() ) }
      , if( any( grepl("colorramp|colourramp", colours ) ) ) { colorramp_palettes() }
    )
  )
}

viridis_palettes <- function() {
  return(
    c("viridis", "cividis", "magma", "inferno", "plasma")
  )
}

rcolorbrewer_seq_palettes <- function() {
  return(
    c(
      "ylorrd",
      "ylorbr", "ylgnbu", "ylgn", "reds", "rdpu", "purples", "purd",
      "pubugn", "pubu", "orrd", "oranges", "greys", "greens", "gnbu",
      "bupu", "bugn", "blues"
    )
  )
}

rcolorbrewer_div_palettes <- function() {
  return(
    c(
      "spectral", "rdylgn", "rdylbu", "rdgy",
      "rdbu", "puor", "prgn", "piyg", "brbg"
    )
  )
}

grdevices_palettes <- function() {
  return(
    c(
      "terrain", "topo", "heat",
      "cm", "rainbow"
    )
  )
}

colorspace_seq_palettes <- function() {
  return(
    c(
      "terrain_hcl", "heat_hcl", "sequential_hcl",
      "rainbow_hcl"
    )
  )
}

colorspace_div_palettes <- function() {
  return(
    c("diverge_hcl", "diverge_hsv")
    )
}

colorramp_palettes <- function() {
  return(
    c(
      "ygobb", "matlab_like2", "matlab_like", "magenta2green",
      "cyan2yellow", "blue2yellow", "green2red", "blue2green", "blue2red"
    )
  )
}


#' @rdname colour_palettes
#' @export
color_palettes <- colour_palettes


#' Show Colours
#'
#' Plots all the selected colours. See \link{colour_palettes} for avaialble colours.
#'
#' @param colours vector of colour palettes
#'
#' @examples
#'
#' ## view all the colour palettes
#' show_colours()
#'
#' ## view a selection of colour palettes
#' show_colours( colours = colour_palettes( c("viridis", "grdevices") ) )
#'
#'
#'
#' @export
show_colours <- function( colours = colour_palettes() ) {
  ## nocov start
  graphics::par(mar = c(0, 0, 0, 0) + 0.1)

  graphics::plot(0, 0, type = "n", axes = FALSE, bty = "n", xlab = "", ylab = "",
       xlim = c(0, 1), ylim = c(-length(colours)-1, 0))

  for (i in seq_len(length(colours))) {
    cols <- colourvalues::colour_values(1:256, palette = colours[i])
    colours_len <- length(cols)
    breaks <- seq(from = 0.075, to = 1, length = colours_len + 1)

    graphics::text(0, -i - 0.5, colours[i], cex = (10 / colours_len) + 0.6)  ## 0.6 is min size, ## 10 is max
    graphics::rect(xleft = breaks[1:colours_len], xright = breaks[1:colours_len + 1],
         ytop = - 0.15-i, ybottom = -0.8-i,
         col = cols, border = NA)
  }
  ## nocov end
}

#' Viridis
#'
#' Data frame of the viridis palette
#'
viridis <- function() rcpp_viridis()

#' Inferno
#'
#' Data frame of the inferno palette
#'
inferno <- function() rcpp_inferno()

#' Plasma
#'
#' Data frame of the plasma palette
#'
plasma <- function() rcpp_plasma()

#' Magma
#'
#' Data frame of the magma palette
#'
magma <- function() rcpp_magma()

#' Cividis
#'
#' Data frame of the cividis palette
#'
cividis <- function() rcpp_cividis()


#' Terrain
#'
#' Data frame of the terrain palette
#'
terrain <- function() rcpp_terrain()

#' Topo
#'
#' Data Frame of the topo palette
#'
topo <- function() rcpp_topo()

#' Heat
#'
#' Data Frame of the heat palette
#'
heat <- function() rcpp_heat()

#' Ylorrd
#'
#' Data Frame of the ylorrd palette
#'
ylorrd <- function() rcpp_ylorrd()

#' Ylorbr
#'
#' Data Frame of the ylorbr palette
#'
ylorbr <- function() rcpp_ylorbr()

#' Ylgnbu
#'
#' Data Frame of the ylgnbu palette
#'
ylgnbu <- function() rcpp_ylgnbu()

#' Ylgn
#'
#' Data Frame of the ylgn palette
#'
ylgn <- function() rcpp_ylgn()

#' Reds
#'
#' Data Frame of the reds palette
#'
reds <- function() rcpp_reds()

#' Rdpu
#'
#' Data Frame of the rdpu palette
#'
rdpu <- function() rcpp_rdpu()

#' Purples
#'
#' Data Frame of the purples palette
#'
purples <- function() rcpp_purples()

#' Purd
#'
#' Data Frame of the purd palette
#'
purd <- function() rcpp_purd()

#' Pubugn
#'
#' Data Frame of the pubugn palette
#'
pubugn <- function() rcpp_pubugn()

#' Pubu
#'
#' Data Frame of the pubu palette
#'
pubu <- function() rcpp_pubu()

#' Orrd
#'
#' Data Frame of the orrd palette
#'
orrd <- function() rcpp_orrd()

#' Oranges
#'
#' Data Frame of the oranges palette
#'
oranges <- function() rcpp_oranges()

#' Greys
#'
#' Data Frame of the greys palette
#'
greys <- function() rcpp_greys()

#' Greens
#'
#' Data Frame of the greens palette
#'
greens <- function() rcpp_greens()

#' Gnbu
#'
#' Data Frame of the gnbu palette
#'
gnbu <- function() rcpp_gnbu()

#' Bupu
#'
#' Data Frame of the bupu palette
#'
bupu <- function() rcpp_bupu()

#' Bugn
#'
#' Data Frame of the bugn palette
#'
bugn <- function() rcpp_bugn()

#' Blues
#'
#' Data Frame of the blues palette
#'
blues <- function() rcpp_blues()

#' Spectral
#'
#' Data Frame of the spectral palette
#'
spectral <- function() rcpp_spectral()

#' Rdylgn
#'
#' Data Frame of the rdylgn palette
#'
rdylgn <- function() rcpp_rdylgn()

#' Rdylbu
#'
#' Data Frame of the rdylbu palette
#'
rdylbu <- function() rcpp_rdylbu()

#' Rdgy
#'
#' Data Frame of the rdgy palette
#'
rdgy <- function() rcpp_rdgy()

#' Rdbu
#'
#' Data Frame of the rdbu palette
#'
rdbu <- function() rcpp_rdbu()

#' Puor
#'
#' Data Frame of the puor palette
#'
puor <- function() rcpp_puor()

#' Prgn
#'
#' Data Frame of the prgn palette
#'
prgn <- function() rcpp_prgn()

#' Piyg
#'
#' Data Frame of the piyg palette
#'
piyg <- function() rcpp_piyg()

#' Brbg
#'
#' Data Frame of the brbg palette
#'
brbg <- function() rcpp_brbg()

#' Cm
#'
#' Data Frame of the cm palette
#'
cm <- function() rcpp_cm()

#' Rainbow
#'
#' Data Frame of the rainbow palette
#'
rainbow <- function() rcpp_rainbow()

#' Ygobb
#'
#' Data Frame of the ygobb palette
#'
ygobb <- function() rcpp_ygobb()

#' Matlab_like2
#'
#' Data Frame of the matlab_like2 palette
#'
matlab_like2 <- function() rcpp_matlab_like2()

#' Matlab_like
#'
#' Data Frame of the matlab_like palette
#'
matlab_like <- function() rcpp_matlab_like()

#' Magenta2green
#'
#' Data Frame of the magenta2green palette
#'
magenta2green <- function() rcpp_magenta2green()

#' Cyan2yellow
#'
#' Data Frame of the cyan2yellow palette
#'
cyan2yellow <- function() rcpp_cyan2yellow()

#' Blue2yellow
#'
#' Data Frame of the blue2yellow palette
#'
blue2yellow <- function() rcpp_blue2yellow()

#' Green2red
#'
#' Data Frame of the green2red palette
#'
green2red <- function() rcpp_green2red()

#' Blue2green
#'
#' Data Frame of the blue2green palette
#'
blue2green <- function() rcpp_blue2green()

#' Blue2red
#'
#' Data Frame of the blue2red palette
#'
blue2red <- function() rcpp_blue2red()

#' Diverge_hcl
#'
#' Data Frame of the diverge_hcl palette
#'
diverge_hcl <- function() rcpp_diverge_hcl()

#' Diverge_hsv
#'
#' Data Frame of the diverge_hsv palette
#'
diverge_hsv <- function() rcpp_diverge_hsv()

#' Terrain_hcl
#'
#' Data Frame of the terrain_hcl palette
#'
terrain_hcl <- function() rcpp_terrain_hcl()

#' Heat_hcl
#'
#' Data Frame of the heat_hcl palette
#'
heat_hcl <- function() rcpp_heat_hcl()

#' Sequential_hcl
#'
#' Data Frame of the sequential_hcl palette
#'
sequential_hcl <- function() rcpp_sequential_hcl()

#' Rainbow_hcl
#'
#' Data Frame of the rainbow_hcl palette
#'
rainbow_hcl <- function() rcpp_rainbow_hcl()

