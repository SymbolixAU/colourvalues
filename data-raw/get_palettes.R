

fileConn <- file("./inst/include/colourvalues/palettes.hpp")
txt <- readLines(con = fileConn)
close(fileConn)

txt <- txt[4:(length(txt)-1)]
txt <- gsub("\\.hpp\"","",basename(txt))
txt <- txt[ txt != "" ]

dput( txt )


### viridis
v_sequential <- txt[1:5]

## RColorBrewer
rcb_sequential <- txt[6:23]
rcb_diverging <- txt[24:32]

## grDevices
gr_sequential <- txt[38:46]

## colorspace
cs_diverging <- txt[47:48]
cs_sequential <- txt[49:52]

df <- data.frame(
  name = c(v_sequential, rcb_sequential, rcb_diverging, cs_diverging, cs_sequential, gr_sequential)
  , source = c(
    rep("viridis", length(v_sequential))
    , rep("rcolorbrewer", length(rcb_sequential) + length(rcb_diverging))
    , rep("colorspace", length(cs_diverging) + length(cs_sequential))
    , rep("grdevices", length(gr_sequential))
    )
  , type = c(
    rep("sequential", length(v_sequential))
    , rep("sequential", length(rcb_sequential))
    , rep("diverging", length(rcb_diverging))
    , rep("diverging", length(cs_diverging))
    , rep("sequential", length(cs_sequential))
    , rep("sequential", length(gr_sequential))
  )
)



vir <- txt[1:5]
txt <- sort( txt[6:length(txt)] )
dput( c( vir, txt ) )


## https://github.com/EmilHvitfeldt/r-color-palettes/blob/master/R/list_plotter.R
list_plotter <- function( colours = colour_palettes() ) {
  par(mar = c(0, 0, 0, 0) + 0.1)

  plot(0, 0, type = "n", axes = FALSE, bty = "n", xlab = "", ylab = "",
       xlim = c(0, 1), ylim = c(-length(colours)-1, 0))

  #title(package_name, line = -3)
  for (i in seq_len(length(colours))) {
    #print( colours[i] )
    cols <- colourvalues::colour_values(1:50, palette = colours[i])
    colours_len <- length(cols)
    breaks <- seq(from = 0.075, to = 1, length = colours_len + 1)

    text(0, -i - 0.5, colours[i], cex = (10 / colours_len) + 0.6)  ## 0.6 is min size, ## 10 is max
    rect(xleft = breaks[1:colours_len], xright = breaks[1:colours_len + 1],
         ytop = - 0.15-i, ybottom = -0.8-i,
         col = cols, border = NA)
  }
}

list_plotter()

