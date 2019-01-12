

## create
# palette.hpp


## update
# palettes.hpp
# palette_utils.hpp
# palettes.cpp
# palettes.R

# NEWS

# palette.hpp template

# pal <- colourvalues::convert_colours(
#   grDevices::heat.colors(n = 256)
# )

n <- 256
cols <- 4
pal_name <- "rainbow_hcl"

pal <- colourvalues::convert_colours(
  #RColorBrewer::brewer.pal(n, pal_name)
  #grDevices::rainbow( n = n )
  #colorRamps::blue2red(n)
  colorspace::rainbow_hcl(n = n)
)

pal_name <- tolower(pal_name)
pal <- pal / 255

### ------------
### palette.hpp
### ------------

save_dir <- "./inst/include/colourvalues/palettes/"

to_matrix <- function(x, cols) {
  m <- matrix(x, ncol = cols, byrow = TRUE)
  #m <- x
  res <- vector( mode = "character", length = n / cols )
  for( i in 1:nrow(m) ) {
    if ( i != nrow(m) ) {
      res[i] <- paste0("    ", paste0(m[i,], collapse = ","), "," , sep = "\n")
    } else {
      res[i] <- paste0("    ", paste0(m[i,], collapse = ","), sep = "\n")
    }
  }
  return( res )
}

red <- to_matrix( pal[, 1], cols)
green <- to_matrix( pal[, 2], cols )
blue <- to_matrix( pal[, 3], cols )


txt <- paste0(
  "#ifndef R_COLOURVALUES_", toupper(pal_name), "_H\n",
  "#define R_COLOURVALUES_", toupper(pal_name), "_H\n",
  "\n",
  "#include <Rcpp.h>\n",
  "using namespace Rcpp;\n",
  "\n",
  "namespace colourvalues {\n",
  "namespace palette {\n",
  "\n",
  "  const Rcpp::NumericVector ", pal_name, "_red = {\n",
  paste0( red, collapse = ""),
  "  };\n",
  "\n",
  "  const Rcpp::NumericVector ", pal_name, "_green = {\n",
  paste0( green, collapse = ""),
  "  };\n",
  "\n",
  "  const Rcpp::NumericVector ", pal_name, "_blue = {\n",
  paste0( blue, collapse = ""),
  "  };\n",
  "\n",
  "const Rcpp::List ", pal_name, " = Rcpp::List::create(\n",
  "  _[\"r\"] = ", pal_name, "_red,\n",
  "  _[\"g\"] = ", pal_name, "_green,\n",
  "  _[\"b\"] = ", pal_name, "_blue\n",
  ");",
  "\n",
  "} // namespace palette\n",
  "} // namepsace colourvalues\n",
  "\n",
  "#endif"
)

fileConn <- file(paste0(save_dir, pal_name,".hpp"))
writeLines(txt, fileConn)
close(fileConn)

### ------
### palettes.hpp
### ------
fileConn <- file("./inst/include/colourvalues/palettes.hpp")
txt <- readLines(con = fileConn)
close(fileConn)

# clipr::write_clip(
#   paste0("#include \"colourvalues/palettes/",pal_name,".hpp\"")
# )

## insert new line before #endif
endline <- which(grepl("#endif", txt))

newVec <- vector("character", length = length(txt) + 1)

newVec[1:(endline-1)] <- txt[1:(endline-1)]
newVec[endline-1] <- paste0("#include \"colourvalues/palettes/",pal_name,".hpp\"\n")
newVec[length(newVec)] <- txt[endline]

#cat( paste0(newVec, collapse = "\n") )

cat(paste0(newVec, collapse = "\n"), file = "./inst/include/colourvalues/palettes.hpp", append = FALSE)



### ------
### palette_utils.hpp
### ------

txt <- paste0(
  "} else if ( palette == \"", pal_name, "\" ) {\n",
  "  red = colourvalues::palette::",pal_name,"_red;\n",
  "  green = colourvalues::palette::",pal_name,"_green;\n",
  "  blue = colourvalues::palette::",pal_name,"_blue;"
)

clipr::write_clip(txt)

### ----------
### palettes.R
### ----------

capitalise <- function(x) {
  x <- strsplit(x, "")[[1]]
  x <- paste0(toupper(x[1]),paste0(x[2:length(x)], collapse = ""))
  return(x)
}

txt <- paste0(
  "\n",
  "#' ", capitalise(pal_name), "\n",
  "#'\n",
  "#' Data Frame of the ", pal_name, " palette\n",
  "#'\n",
  "#' @export\n",
  pal_name, " <- function() rcpp_", pal_name, "()\n"
)

#clipr::write_clip(txt)

cat(txt, file = "./R/palettes.R", append = TRUE)


#### ---------
### palettes.cpp
### -----------

txt <- paste0(
  "\n",
  "// [[Rcpp::export]]\n",
  "  Rcpp::DataFrame rcpp_",pal_name,"() {\n",
  "    return Rcpp::DataFrame::create(\n",
  "   _[\"red\"] = colourvalues::palette::", pal_name, "_red,\n",
  "   _[\"green\"] = colourvalues::palette::", pal_name, "_green,\n",
  "   _[\"blue\"] = colourvalues::palette::", pal_name, "_blue\n",
  ");\n",
"}\n"
)

# clipr::write_clip(txt)

cat(txt, file = "./src/palettes.cpp", append = TRUE)

