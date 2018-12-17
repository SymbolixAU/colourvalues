

## create
# palette.hpp


## update
# palettes.hpp
# palette_utils.hpp
# palettes.cpp
# palettes.R

# NEWS

# palette.hpp template

pal <- colourvalues::convert_colours(
  grDevices::topo.colors(n = 256)
)
pal <- pal / 255
pal_name <- "topo"

### ------------
### palette.hpp
### ------------

save_dir <- "./inst/include/colourvalues/palettes/"

format_vector <- function(x) {
  m <- matrix(x, ncol = 4, byrow = TRUE)
  res <- vector( mode = "character", length = 256 / 4)
  for( i in 1:nrow(m) ) {
    if ( i != nrow(m) ) {
      res[i] <- paste0("    ", paste0(m[i,], collapse = ","), "," , sep = "\n")
    } else {
      res[i] <- paste0("    ", paste0(m[i,], collapse = ","), sep = "\n")
    }
  }
  return( res )
}

red <- format_vector( pal[, 1] )
green <- format_vector( pal[, 2] )
blue <- format_vector( pal[, 3] )

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

clipr::write_clip(
  paste0("#include \"colourvalues/palettes/",pal_name,".hpp\"")
)



### ------
### palette_utils.hpp
### ------

txt <- paste0(
  "} else if ( palette == \"", pal_name, "\" ) {\n",
  "  red = colourvalues::palette::",pal_name,"_red;\n",
  "  green = colourvalues::palette::",pal_name,"_green;\n",
  "  blue = colourvalues::palette::",pal_name,"_blue;\n"
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
  "#' ", capitalise(pal_name), "\n",
  "#'\n",
  "#' Data Frame of the ", pal_name, " palette\n",
  "#'\n",
  "#' @export\n",
  pal_name, " <- function() rcpp_", pal_name, "()"
)

clipr::write_clip(txt)

#### ---------
### palettes.cpp
### -----------

txt <- paste0(
  "// [[Rcpp::export]]\n",
  "  Rcpp::DataFrame rcpp_",pal_name,"() {\n",
  "    return Rcpp::DataFrame::create(\n",
  "   _[\"red\"] = colourvalues::palette::", pal_name, "_red,\n",
  "   _[\"green\"] = colourvalues::palette::", pal_name, "_green,\n",
  "   _[\"blue\"] = colourvalues::palette::", pal_name, "_blue\n",
  ");\n",
"}"
)

clipr::write_clip(txt)

