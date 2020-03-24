
#ifndef R_COLOURVALUES_LIST
#define R_COLOURVALUES_LIST

#include <Rcpp.h>
#include "colourvalues/format/format.hpp"
//#include "colourvalues/colours/colours_hex.hpp"

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

   inline int vector_type( int new_type, int existing_type ) {

      // can't change from STRSXP
      if( existing_type == 16 ) {
         return existing_type;
      }

      std::vector< int > valid_types{10, 13, 14, 16};
      bool new_is_valid = ( std::find( valid_types.begin(), valid_types.end(), new_type ) != valid_types.end() );
      bool existing_is_valid = ( std::find( valid_types.begin(), valid_types.end(), existing_type ) != valid_types.end() );

      if( new_type == existing_type && new_is_valid ) {
         return existing_type;
      }

      // convert new type up to existing type
      if( new_type < existing_type && existing_is_valid ) {
         return existing_type;
      }

      if( new_type > existing_type && new_is_valid ) {
         return new_type;
      }

      if( new_type > existing_type && !new_is_valid ) {
         return 16;
      }

      if( existing_is_valid ) {
         return existing_type;
      }

      return 16;
   }

   inline Rcpp::List list_size( const Rcpp::List& lst, int& total_size, int& existing_type, std::string& existing_format ) {
      R_xlen_t n = lst.size();
      Rcpp::List res( n ); // create a list to store the size corresponding to each list element
      R_xlen_t i;
      for( i = 0; i < n; i++ ) {
         switch( TYPEOF( lst[i] ) ) {
         case VECSXP: {
            res[ i ] = list_size( lst[i], total_size, existing_type, existing_format );
            break;
         }
         default: {
            int n_elements = Rf_length( lst[i] );
            int new_type = TYPEOF( lst[i] );
            std::string new_format = colourvalues::format::get_format_type( lst[i] );
            //Rcpp::Rcout << "format_type : " << format_type << std::endl;
            if( new_format != existing_format ) {
               existing_format = "character";
            }
            existing_type = vector_type( new_type, existing_type );
            res[i] = n_elements;
            total_size += n_elements;
         }
         }
      }
      return res;
   }

   /*
    * Creates a list of the same dimensions as the original list, but all the elements are now
    * NumericMatrices of rgb colours
    */
   inline Rcpp::List refil_list(
         const Rcpp::List& lst_sizes,
         Rcpp::NumericMatrix& colours,
         int& vector_position
   ) {

      // iterate through the list, if size > 0, fill with that many values from the vector

      size_t n = lst_sizes.size();
      Rcpp::List res( n );
      R_xlen_t i;

      for( i = 0; i < n; i++ ) {
         switch( TYPEOF( lst_sizes[ i ] ) ) {
         case VECSXP: {
            res[ i ] = refil_list( lst_sizes[ i ], colours, vector_position );
            break;
         }
         case INTSXP: {
            Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
            int end_position = vector_position + n_elements[0] - 1;
            //Rcpp::IntegerVector elements = Rcpp::seq( vector_position, end_position );
            Rcpp::Range elements = Rcpp::Range( vector_position, end_position );
            Rcpp::NumericMatrix these_colours = colours( elements, Rcpp::_ );
            res[ i ] = these_colours;
            vector_position = end_position + 1;
            break;
         }
         default: {
            Rcpp::stop("colourvalues - Unknown list element type");
         }
         }
      }
      return res;
   }

   /*
    * Creates a list of the same dimensions as the original list, but all the elements are now
    * StringVectors of hex colours
    */
   inline Rcpp::List refil_list(
         const Rcpp::List& lst_sizes,
         Rcpp::StringVector& colours,
         int& vector_position
   ) {

      // iterate through the list, if size > 0, fill with that many values from the vector

      size_t n = lst_sizes.size();
      Rcpp::List res( n );
      R_xlen_t i;

      for( i = 0; i < n; i++ ) {
         switch( TYPEOF( lst_sizes[ i ] ) ) {
         case VECSXP: {
            res[ i ] = refil_list( lst_sizes[ i ], colours, vector_position );
            break;
         }
         case INTSXP: {
            Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
            int end_position = vector_position + n_elements[0] - 1;
            Rcpp::IntegerVector elements = Rcpp::seq( vector_position, end_position );
            Rcpp::StringVector these_colours = colours[ elements ];
            res[ i ] = these_colours;
            vector_position = end_position + 1;
            break;
         }
         default: {
            Rcpp::stop("colourvalues - Unknown list element type");
         }
         }
      }
      return res;
   }

   /*
    * @param lst - the original input list
    * @param lst_sizes - the dimensions of the list
    * @param colours - vector of values which will go into colour_values_hex()
    */
   inline void unlist_list(
         const Rcpp::List& lst, const Rcpp::List& lst_sizes,
         Rcpp::StringVector& colours, int& list_position
   ) {
      // - iterate through original list
      // - extract each element and insert into 'colours'
      size_t n = lst.size();
      Rcpp::List res( n );
      R_xlen_t i;
      for( i = 0; i < n; i++ ) {
         switch( TYPEOF( lst[i] ) ) {
         case VECSXP: {
            unlist_list( lst[ i ], lst_sizes[ i ], colours, list_position );
            break;
         }
         default: {
            Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
            int end_position = list_position + n_elements[0] - 1;
            Rcpp::IntegerVector elements = Rcpp::seq( list_position, end_position );
            colours[ elements ] = Rcpp::as< Rcpp::StringVector >( lst[ i ] );

            list_position = end_position + 1;
            break;
         }
         }
      }
   }

   inline void unlist_list(
         const Rcpp::List& lst, const Rcpp::List& lst_sizes,
         Rcpp::NumericVector& colours, int& list_position
   ) {
      // - iterate through original list
      // - extract each element and insert into 'colours'
      size_t n = lst.size();
      Rcpp::List res( n );
      R_xlen_t i;
      for( i = 0; i < n; i++ ) {
         switch( TYPEOF( lst[i] ) ) {
         case VECSXP: {
            unlist_list( lst[ i ], lst_sizes[ i ], colours, list_position );
            break;
         }
         default: {
            Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
            int end_position = list_position + n_elements[0] - 1;
            Rcpp::IntegerVector elements = Rcpp::seq( list_position, end_position );
            colours[ elements ] = Rcpp::as< Rcpp::NumericVector >( lst[ i ] );

            list_position = end_position + 1;
            break;
         }
         }
      }
   }

} // list
} // colourvalues

#endif

