
#' Colour Palettes
#'
#' List the available colour palettes
#'
#' @export
colour_palettes <- function() {
  return(
    c("viridis", "cividis", "magma", "inferno", "plasma", "blue2green",
      "blue2red", "blue2yellow", "blues", "brbg", "bugn", "bupu", "cm",
      "cyan2yellow", "diverge_hcl", "diverge_hsv", "gnbu", "green2red",
      "greens", "greys", "heat", "heat_hcl", "magenta2green", "matlab_like",
      "matlab_like2", "oranges", "orrd", "piyg", "prgn", "pubu", "pubugn",
      "puor", "purd", "purples", "rainbow", "rainbow_hcl", "rdbu",
      "rdgy", "rdpu", "rdylbu", "rdylgn", "reds", "sequential_hcl",
      "spectral", "terrain", "terrain_hcl", "topo", "ygobb", "ylgn",
      "ylgnbu", "ylorbr", "ylorrd")
  )
}

#' Show Colours
#'
#' Plots all the selected colours
#'
#' @param colours vector of colour palettes
#'
#' @export
show_colours <- function( colours = colour_palettes() ) {
  par(mar = c(0, 0, 0, 0) + 0.1)

  plot(0, 0, type = "n", axes = FALSE, bty = "n", xlab = "", ylab = "",
       xlim = c(0, 1), ylim = c(-length(colours)-1, 0))

  for (i in seq_len(length(colours))) {
    cols <- colourvalues::colour_values(1:50, palette = colours[i])
    colours_len <- length(cols)
    breaks <- seq(from = 0.075, to = 1, length = colours_len + 1)

    text(0, -i - 0.5, colours[i], cex = (10 / colours_len) + 0.6)  ## 0.6 is min size, ## 10 is max
    rect(xleft = breaks[1:colours_len], xright = breaks[1:colours_len + 1],
         ytop = - 0.15-i, ybottom = -0.8-i,
         col = cols, border = NA)
  }
}

#' @rdname colour_palettes
#' @export
color_palettes <- colour_palettes

#' Viridis
#'
#' Data frame of the viridis palette
#'
#' @export
viridis <- function() rcpp_viridis()

#' Inferno
#'
#' Data frame of the inferno palette
#'
#' @export
inferno <- function() rcpp_inferno()

#' Plasma
#'
#' Data frame of the plasma palette
#'
#' @export
plasma <- function() rcpp_plasma()

#' Magma
#'
#' Data frame of the magma palette
#'
#' @export
magma <- function() rcpp_magma()

#' Cividis
#'
#' Data frame of the cividis palette
#'
#' @export
cividis <- function() rcpp_cividis()


#' Terrain
#'
#' Data frame of the terrain palette
#'
#' @export
terrain <- function() rcpp_terrain()

#' Topo
#'
#' Data Frame of the topo palette
#'
#' @export
topo <- function() rcpp_topo()

#' Heat
#'
#' Data Frame of the heat palette
#'
#' @export
heat <- function() rcpp_heat()

#' Ylorrd
#'
#' Data Frame of the ylorrd palette
#'
#' @export
ylorrd <- function() rcpp_ylorrd()

#' Ylorbr
#'
#' Data Frame of the ylorbr palette
#'
#' @export
ylorbr <- function() rcpp_ylorbr()

#' Ylgnbu
#'
#' Data Frame of the ylgnbu palette
#'
#' @export
ylgnbu <- function() rcpp_ylgnbu()

#' Ylgn
#'
#' Data Frame of the ylgn palette
#'
#' @export
ylgn <- function() rcpp_ylgn()

#' Reds
#'
#' Data Frame of the reds palette
#'
#' @export
reds <- function() rcpp_reds()

#' Rdpu
#'
#' Data Frame of the rdpu palette
#'
#' @export
rdpu <- function() rcpp_rdpu()

#' Purples
#'
#' Data Frame of the purples palette
#'
#' @export
purples <- function() rcpp_purples()

#' Purd
#'
#' Data Frame of the purd palette
#'
#' @export
purd <- function() rcpp_purd()

#' Pubugn
#'
#' Data Frame of the pubugn palette
#'
#' @export
pubugn <- function() rcpp_pubugn()

#' Pubu
#'
#' Data Frame of the pubu palette
#'
#' @export
pubu <- function() rcpp_pubu()

#' Orrd
#'
#' Data Frame of the orrd palette
#'
#' @export
orrd <- function() rcpp_orrd()

#' Oranges
#'
#' Data Frame of the oranges palette
#'
#' @export
oranges <- function() rcpp_oranges()

#' Greys
#'
#' Data Frame of the greys palette
#'
#' @export
greys <- function() rcpp_greys()

#' Greens
#'
#' Data Frame of the greens palette
#'
#' @export
greens <- function() rcpp_greens()

#' Gnbu
#'
#' Data Frame of the gnbu palette
#'
#' @export
gnbu <- function() rcpp_gnbu()

#' Bupu
#'
#' Data Frame of the bupu palette
#'
#' @export
bupu <- function() rcpp_bupu()

#' Bugn
#'
#' Data Frame of the bugn palette
#'
#' @export
bugn <- function() rcpp_bugn()

#' Blues
#'
#' Data Frame of the blues palette
#'
#' @export
blues <- function() rcpp_blues()

#' Spectral
#'
#' Data Frame of the spectral palette
#'
#' @export
spectral <- function() rcpp_spectral()

#' Rdylgn
#'
#' Data Frame of the rdylgn palette
#'
#' @export
rdylgn <- function() rcpp_rdylgn()

#' Rdylbu
#'
#' Data Frame of the rdylbu palette
#'
#' @export
rdylbu <- function() rcpp_rdylbu()

#' Rdgy
#'
#' Data Frame of the rdgy palette
#'
#' @export
rdgy <- function() rcpp_rdgy()

#' Rdbu
#'
#' Data Frame of the rdbu palette
#'
#' @export
rdbu <- function() rcpp_rdbu()

#' Puor
#'
#' Data Frame of the puor palette
#'
#' @export
puor <- function() rcpp_puor()

#' Prgn
#'
#' Data Frame of the prgn palette
#'
#' @export
prgn <- function() rcpp_prgn()

#' Piyg
#'
#' Data Frame of the piyg palette
#'
#' @export
piyg <- function() rcpp_piyg()

#' Brbg
#'
#' Data Frame of the brbg palette
#'
#' @export
brbg <- function() rcpp_brbg()

#' Cm
#'
#' Data Frame of the cm palette
#'
#' @export
cm <- function() rcpp_cm()
#' Rainbow
#'
#' Data Frame of the rainbow palette
#'
#' @export
rainbow <- function() rcpp_rainbow()
#' Ygobb
#'
#' Data Frame of the ygobb palette
#'
#' @export
ygobb <- function() rcpp_ygobb()

#' Matlab_like2
#'
#' Data Frame of the matlab_like2 palette
#'
#' @export
matlab_like2 <- function() rcpp_matlab_like2()

#' Matlab_like
#'
#' Data Frame of the matlab_like palette
#'
#' @export
matlab_like <- function() rcpp_matlab_like()

#' Magenta2green
#'
#' Data Frame of the magenta2green palette
#'
#' @export
magenta2green <- function() rcpp_magenta2green()

#' Cyan2yellow
#'
#' Data Frame of the cyan2yellow palette
#'
#' @export
cyan2yellow <- function() rcpp_cyan2yellow()

#' Blue2yellow
#'
#' Data Frame of the blue2yellow palette
#'
#' @export
blue2yellow <- function() rcpp_blue2yellow()

#' Green2red
#'
#' Data Frame of the green2red palette
#'
#' @export
green2red <- function() rcpp_green2red()

#' Blue2green
#'
#' Data Frame of the blue2green palette
#'
#' @export
blue2green <- function() rcpp_blue2green()

#' Blue2red
#'
#' Data Frame of the blue2red palette
#'
#' @export
blue2red <- function() rcpp_blue2red()

#' Diverge_hcl
#'
#' Data Frame of the diverge_hcl palette
#'
#' @export
diverge_hcl <- function() rcpp_diverge_hcl()

#' Diverge_hsv
#'
#' Data Frame of the diverge_hsv palette
#'
#' @export
diverge_hsv <- function() rcpp_diverge_hsv()

#' Terrain_hcl
#'
#' Data Frame of the terrain_hcl palette
#'
#' @export
terrain_hcl <- function() rcpp_terrain_hcl()

#' Heat_hcl
#'
#' Data Frame of the heat_hcl palette
#'
#' @export
heat_hcl <- function() rcpp_heat_hcl()

#' Sequential_hcl
#'
#' Data Frame of the sequential_hcl palette
#'
#' @export
sequential_hcl <- function() rcpp_sequential_hcl()

#' Rainbow_hcl
#'
#' Data Frame of the rainbow_hcl palette
#'
#' @export
rainbow_hcl <- function() rcpp_rainbow_hcl()
