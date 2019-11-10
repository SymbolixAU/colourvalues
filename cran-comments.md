

## Release Notes

* Updates v0.3 to v0.3.1
  - patches for valgrind issues https://cran.r-project.org/web/checks/check_results_colourvalues.html and invalid write size error.
  
  
* CRAN Build Notes: Fedora Clang and OSX builds give notes
"installed package size is 6.8Mb"
  - I can't reduce the libs directory as all the compiled source code is required


## Test environments

* local OS X install, R 3.6.1 and R 3.6.0
* ubuntu 14.04 (on travis-ci), R 3.5.0
* win-builder (devel and release)

## R CMD check results

0 errors | 0 warnings | 0 notes
