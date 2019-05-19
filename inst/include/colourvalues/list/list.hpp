
#ifndef R_COLOURVALUES_LIST
#define R_COLOURVALUES_LIST

/*colouring a list
#
* - follow: https://stackoverflow.com/questions/30175104/how-to-effectively-combine-a-list-of-numericvectors-into-one-large-numericvector
* - get size of vector
* - get type of each element
* - get overal type
* - create vector of overall type
* - coerce other types to that overall type
* - fill vector
* - pass into colouring function
* - CHECK: the order of values in the vector is maintained from the original list
* - when colour_values returns result, re-form list
*/

namespace colourvalues {
namespace list {

 /*
  * returns a vector the same size as lst, each element is the type of lst[["element"]]
  */
 inline Rcpp::IntegerVector list_types( const Rcpp::List& lst ) {
   std::size_t n = lst.size();
   Rcpp::IntegerVector res( n );
   std::size_t i;
   for( i = 0; i < n; i++ ) {
     // TODO
     // switch on type, andif a list, recurse into this function
     // - need to keep track of different depths and sizes, so we can
     // - build a final vector to store the results of colouring, a
     // - and then rebuild the list at the end
     //
     // - in the switch, only support vector types (and lists), not matrices or data.frames
     res[i] = TYPEOF( lst[i] );
   }
   return res;
 }



  //
  inline void colour_list( const Rcpp::List& lst ) {
     double total_size = 0;

  }

} // list
} // colourvalues

#endif

