## Benchmarks

# library(scales)
# library(microbenchmark)
# x <- 1:1e5
# n <- length(x)
# microbenchmark(
#   scales = { x <- scales::col_numeric(viridisLite::viridis(n), domain = x)(x)  },
#   rcpp = { y <- RcppViridis::colour_values(x) },
#   times = 1
# )


# df <- data.frame(a = 10, x = 1:10)
# df$col <- mapview:::zcolColors(df$x)
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
# df$col <- RcppViridis::colour_values(df$x)
# barplot(height = df$a, col = df$col, border = NA, space = 0)
#
#
# df <- data.frame(a = 10, x = c(1:5,NA,7,NA,9,10))
# df$col2 = mapview:::zcolColors(df$x, na.color = "#00FF00")
# barplot(height = df$a, col = df$col2, border = NA, space = 0)
#
# df$col2 <- RcppViridis::colour_values(df$x, na_colour = "#00FF00")
# barplot(height = df$a, col = df$col2, border = NA, space = 0)

#
# library(Rcpp)
#
# cppFunction('Rcpp::IntegerVector myFactor( Rcpp::StringVector x) {
#
#             bool anyNa = any(is_na(x));
#             Rcpp::Rcout << "anyNa? : " << anyNa << std::endl;
#
#             Rcpp::StringVector lvls = sort_unique( x );
#             Rcpp::IntegerVector out = match(x, lvls);
#             //out.attr("levels") = as<CharacterVector>(lvls);
#             //out.attr("class") = "factor";
#
#             // TODO(replace factor value with NA)
#
#             return out;
#             }')
#
# ## is the last level always NA for characters?
#
# x <- c("a",NA, "d","f",NA)
# myFactor( x )
# colour_values( x )
#
# x <- c(1, NA, NaN, Inf, 2)
# colour_values(x)
#
# x <- c(1, NA)
# colour_values(x)
#
# x <- c(NA)
# colour_values(x)
#
# x <- c(NA_integer_)
# colour_values(x)
#
# x <- c(NA_character_, 1)
# myFactor(x)
#
# x <- c("a","b")
# myFactor(x)
# colour_values(x)
#
# x <- c(NA, "a","b", 1, NA_character_)
#
# myFactor(x)
# colour_values(x)
#
# factor(NA_character_)
# sort(c(NA_character_, "a"))
#
# colour_values(c(1,2))
#
# colour_values(c("a","b"))
# colour_values(c("zzzz", "djfkldsjflkds"))
# colour_values(c("djfkldsjflkds", "zzzz"))
# ## these two should be equal?
#
# ## TODO
# colour_values(as.Date(c("2018-01-01","2018-01-01","2018-01-02", NA) ) )
# colour_values( factor(c(1,2,3,1,2,3)) )
#
