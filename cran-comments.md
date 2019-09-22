
## Submission feedback

* fixed reverse-dependency spatialwidget compilation errors
* tested against spatialwidget CRAN release [v0.2.0 7f0e42a](https://github.com/SymbolixAU/spatialwidget/releases/tag/v0.2.0)
  - the error was due to rearranged arguments in C++ functions
  - fixed by providing function overloads with the required arguments

## Release Notes

* Updates v0.2.2 to v0.3
* CRAN Build Notes: Fedora Clang and OSX builds give notes
"installed package size is 6.8Mb"
  - I can't reduce the libs directory as all the compiled source code is required



## Test environments
* local OS X install, R 3.6.0
* ubuntu 14.04 (on travis-ci), R 3.5.0
* win-builder (devel and release)

## R CMD check results

0 errors | 0 warnings | 0 notes
