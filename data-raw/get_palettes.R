

fileConn <- file("./inst/include/colourvalues/palettes.hpp")
txt <- readLines(con = fileConn)
close(fileConn)

txt <- txt[4:(length(txt)-1)]
txt <- gsub("\\.hpp\"","",basename(txt))
txt <- txt[ txt != "" ]

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

