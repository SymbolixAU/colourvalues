

## Release Notes

* Patches v0.3 to v0.3.1
  - valgrind issues https://cran.r-project.org/web/checks/check_results_colourvalues.html
  - suggests a memory leak in inst/include/alpha/alpha.hpp , line 63, where it returns a vector
  - I was unable to reproduce this using valgrind, but I have put an explicit check for an empty vector to handle this possible error.
  
  
* CRAN Build Notes: Fedora Clang and OSX builds give notes
"installed package size is 6.8Mb"
  - I can't reduce the libs directory as all the compiled source code is required


## Test environments

* local OS X install, R 3.6.1 and R 3.6.0
* ubuntu 14.04 (on travis-ci), R 3.5.0
* win-builder (devel and release)

## R CMD check results

0 errors | 0 warnings | 0 notes
