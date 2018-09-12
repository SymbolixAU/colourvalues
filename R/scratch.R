#
# ## TODO(Why are these plots different, why is m2 different to m, why are there negatives?)
# ## matrix palette
# alpha <- c(0, 100, 150, 200, 255)
# m <- cbind( grDevices::colorRamp(c("red","green","blue"))(0:9/9), alpha )
# m2 <- colour_values(1:10, palette = m, return = "rgb")
# ## m2 is the interpolated palette; we are not using m[1:10,] as the palette for the values
# df <- data.frame(a = 10, x = 1:10)
# df$col <- colour_values(df$x, palette = m)
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# ## TODO - default alpha to 255
# df <- data.frame(a = 10, x = 1:10)
# df$col <- colour_values(df$x, palette = m[,1:3])
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# df <- data.frame(a = 10, x = 1:5)
# df2 <- data.frame(a = 10, x = 1:5)
#
# ## plot using the raw palette
# df$col <- colour_values(df$x, palette = m)
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# df2$col <- colour_values(df2$x, palette = m2[,1:3])
# barplot(height = df2$a, col = df2$col, border = NA, space = 0)
# ## they are different because 'm' gets interpolated, then 'm2' gets interpolated
# ## and since they are different to start with, the plots are different
#
# ## TODO
# ## matrix with an alpha-column. The alpha column needs to be interpolated along wtih
# ## the RGB values
# df <- data.frame(a = 10, x = 1:20)
# m <- matrix(c(rep(100, 4*25)), ncol = 4)
# df$col <- colour_values(df$x, palette = m)  ## TODO
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# df <- data.frame(a = 10, x = 1:20)
#
# alpha <- seq(0,255,length.out = 10)
# m <- cbind( grDevices::colorRamp(c("red","green","blue"))(0:9/9), alpha )
#
# df$col <- colour_values(df$x, palette = m)
# ## THIS IS THE ERROR
# barplot(height = df$a, col = df$col, border = NA, space = 0)
# ## ths plot ^^ and this plot vv should be the same (without alpha)
#
# df <- data.frame(a = 10, x = 1:20)
#
# m <- grDevices::colorRamp(c("red","green","blue"))(0:9/9) ## point of error == 12
#
# df$col <- colour_values(df$x, palette = m)
# ## THIS IS THE ERROR
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# m <- grDevices::colorRamp( RColorBrewer::brewer.pal(8, name = "YlOrRd") )(0:255/255)
# df$col <- colour_values(df$x, palette = m)
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# m <- grDevices::colorRamp(c("red","green","blue"))(0:255/255) ## point of error == 12
# df$col <- colour_values(df$x, palette = m)
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
#
#
# ## TODO: another error?
# ## maybe from my (255 - r :: r + 255) stuff
# df <- data.frame(a = 10, x = 1:20)
# m <- grDevices::colorRamp(c("red","green"))(0:9/9)
# df$col <- colour_values(df$x, palette = m)
# ## THIS IS THE ERROR
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
#
# ## another error
# ## red is 255 for ALL values, so it gets scaled to 0, not 1...
# ## but, need to ensure if all values are 0, they remain 0...
# ##
# m <- grDevices::colorRamp(c("yellow","red"))(0:255/255)
# df <- data.frame(a = 10, x = 1:20)
# df$col <- colour_values(df$x, palette = m)
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# # df <- data.frame(a = 10, x = 1:20)
# # m <- matrix(c(rep(100, 4*25)), ncol = 4)
# # df2$col <- colour_values(df2$x, palette = m)
# #
# # barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# # df <- data.frame(a = 10, x = 1:2)
# # df$col <- colour_values(df$x, palette = "viridis")
# # barplot(height = df$a, col = df$col, border = NA, space = 0)
# #
# # n <- 2
# # df <- data.frame(a = 10, x = 1:n)
# # df$col <- scales::col_numeric(viridisLite::viridis(2), domain = df$x)(df$x)
# # barplot(height = df$a, col = df$col, border = NA, space = 0)
#
#
# # df <- data.frame(a = 10, x = 1:10)
# # df$col <- mapview:::zcolColors(df$x)
# # barplot(height = df$a, col = df$col, border = NA, space = 0)
# #
# # df$col <- RcppViridis::color_values(df$x)
# # barplot(height = df$a, col = df$col, border = NA, space = 0)
# #
# # df <- data.frame(a = 10, x = c(1:5,NA,7,NA,9,10))
# # df$col2 = mapview:::zcolColors(df$x, na.color = "#00FF00")
# # barplot(height = df$a, col = df$col2, border = NA, space = 0)
# #
# # df$col2 <- RcppViridis::colour_values(df$x, na_colour = "")
# # barplot(height = df$a, col = df$col2, border = NA, space = 0)
# #
# #
# # mapview:::zcolColors(df$x, na.color = "#00FF00")
# # substr(RcppViridis::colour_values(df$x, na_colour = "#00FF00"), 1,7)
#
#
#
# # library(mapview)
# #
# # df <- data.frame(a = 10, x = 1:250)
# # df$col <- mapview:::zcolColors(df$x, at = seq(0, 250, 50))
# # barplot(height = df$a, col = df$col, border = NA, space = 0)
# #
# # table(df$col)
# # #21908C #3B528B #440154 #5DC863 #FDE725
# # 50      50      50      50      50
