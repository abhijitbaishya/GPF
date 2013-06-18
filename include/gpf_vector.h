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
	//actual row pointer
		float*			row_ptr;
	//number of elements currently present
		int 			num_elements;
	//capacity of the vector
		int 			_capacity;


	public:
	//the destructor
		virtual ~gpf_vector		();
	//deafault constructor : creates an empty row
		gpf_vector				();
	//The copy constructor
		gpf_vector				(const gpf_vector& copy);
	//The constructor default size increment is 16 units
		gpf_vector				(int num_elements);
	
	public:
	//member functions
	
	//remove an elements from pos position
		void 			rm					(int pos);
	//returns no of elements in this row (may be usefull for sparse matrix)
		int 			size				();
	//returns the index if val is found otherwise returns -1
		int 			find				(float val);
	//returns true if the array is empty
		bool			empty				();
	//resize the array (here size is no of elements)
		void			resize				(int new_size);
	//insert an element
		void 			insert				(int pos,float val);
	//removes an elements from the back of the row
		float 			pop_back			();
	//returns the capacity value
		int 			capacity			();
	//adds an element at the end of the row
		void			push_back			(int val);
	//dumps the row to stdout
		void			dump_to_stdout		();
		
	//overloaded operators
	
	//returns an element from the gpf_vector given an index it also handles bound checking
		float& 			operator[]			(int suffix) throw (exc_out_of_bounds*);
	//The assignment operator : assigning a vector will overwrite the original one
		gpf_vector&		operator=			(const gpf_vector& row);
	//inserter overloaded
	friend std::ostream& operator<<(std::ostream& out, gpf_vector& vec);
};

//inserter overloaded
std::ostream& operator<<(std::ostream& out, gpf_vector& vec);

}
#endif