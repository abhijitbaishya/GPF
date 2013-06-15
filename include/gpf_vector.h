#ifndef __GPF_VECTOR__
#define __GPF_VECTOR__

#include	"../include/gpf_exceptions.h"
#include	<stdlib.h>
#include	<memory.h>

namespace gpf
{

/**
 *	 int array does not suppot bound checking that is why we created a special array class
 *	 gpf_vector which will serve as the rows of a matrix_base class. This class is also our dynamic
 *   array solution.
 */
class gpf_vector
{
	private:
	//member variables
		int*			row_ptr;			//actual row pointer
		unsigned int 	num_elements;		//number of elements
		unsigned int 	_capacity;			//capacity
	public:
	//constructors and destructors
		virtual ~gpf_vector		();								//The destructor

		gpf_vector				();								//creates empty row
		gpf_vector				(gpf_vector& copy);				//The copy constructor
		gpf_vector				(unsigned int num_elements);	//The constructor default size increment is 16 bytes or a paragraph	
	
	public:
	//member functions
		void 			rm					(int pos);									//remove an elements from pos position
		unsigned int 	size				();											//returns no of elements in this row (may be usefull for sparse matrix)
		int 			find				(int val);									//returns the index if val is found otherwise returns -1
		bool			empty				();											//returns true if the array is empty
		void			resize				(int new_size);								//resize the array (here size is no of elements)
		void 			insert				(int pos,int val);							//insert an element
		int 			pop_back			();											//removes an elements from the back of the row
		int 			capacity			();											//returns the capacity value
		void			push_back			(int val);									//adds an element at the end of the row
		void			dump_to_stdout		();											//dumps the row to stdout
		
	//overloaded operators
		int&  			operator[]			(int suffix) throw (exc_out_of_bounds*);	//returns an element from the gpf_vector given an index
																						//it also handles bound checking
		gpf_vector&		operator=			(gpf_vector& row);							//The assignment operator
};

}
#endif