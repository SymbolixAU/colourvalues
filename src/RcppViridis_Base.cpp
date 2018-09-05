#include <Rcpp.h>
#include <algorithm>
using namespace Rcpp;

Rcpp::NumericVector m_diff(Rcpp::NumericVector x) {
	int n = x.size() - 1;
	Rcpp::NumericVector difference(n);
	int i = 0;
	for (i = 0; i < n; i++) {
		difference[i] = x[i+1] - x[i];
	}
	return difference;
}

Rcpp::NumericVector m_range(Rcpp::NumericVector x) {
	Rcpp::NumericVector rng(2);
	rng[0] = min(na_omit(x));
	rng[1] = max(na_omit(x));
	return rng;
}


// Always rescales to (0, 1)
Rcpp::NumericVector m_rescale( Rcpp::NumericVector x ) {
	int n = x.size();
	Rcpp::NumericVector rescaled(n);
	Rcpp::NumericVector rng = m_range(x);
	Rcpp::NumericVector diff_from = m_diff(rng); // should only be one value!

	double this_diff = std::max(1.0, diff_from[0]);  // TODO(is this right? what am I doing?)

	int i = 0;

	for (i = 0; i < n; i++) {
		rescaled[i] = (x[i] - rng[0]) / this_diff;
	}
	return rescaled;
}

