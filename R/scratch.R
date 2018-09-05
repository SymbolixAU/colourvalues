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
#
# x <- c(1, NA, NaN, Inf, 2)
# colour_variables(x)
#
# x <- c(1, NA)
# colour_variables(x)
#
# x <- c(NA)
# colour_variables(x)
#
# x <- c(NA_integer_)
# colour_variables(x)
#
# x <- c(NA_character_, 1)
# myFactor(x)
#
# x <- c("a","b")
# myFactor(x)
# colour_variables(x)
#
# x <- c(NA, "a","b", 1, NA_character_)
#
# myFactor(x)
# colour_variables(x)
#
# factor(NA_character_)
# sort(c(NA_character_, "a"))
#
# colour_variables(c(1,2))
#
# colour_variables(c("a","b"))
# colour_variables(c("zzzz", "djfkldsjflkds"))
# colour_variables(c("djfkldsjflkds", "zzzz"))
# ## these two should be equal?
#
# ## TODO
# colour_variables(as.Date(c("2018-01-01","2018-01-01","2018-01-02") ) )
# colour_variables( factor(c(1,2,3,1,2,3)) )
#
