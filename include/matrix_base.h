#ifndef _BASE_MAT
#define _BASE_MAT
#include	<iostream>
#include	<memory.h>
#include	"../include/gpf_exceptions.h"

//Graph Processor Framework
namespace gpf
{

/*
	 int array does not suppot bound checking that is why we created a special array class
	 matrix_row which will serve as the rows of a matrix_base class.
*/
class matrix_row
{
	private:
		//member variables
		int*			row_ptr;			//actual row pointer
		unsigned int 	num_elements;		//number of elements
		unsigned int 	_capacity;			//capacity
	public:
		//constructors and destructors
		virtual ~matrix_row		();								//The destructor
		matrix_row				(unsigned int num_elements);	//The constructor default size increment is 16 bytes or a paragraph
								 
		matrix_row				(matrix_row& copy);				//The copy constructor
		matrix_row				();								//creates empty row
	
	
	public:
		//member functions
		int  			operator[]			(int suffix) throw (exc_out_of_bounds*);	//returns an element from the matrix_row given an index
																						//it also handles bound checking
		matrix_row		operator=			(matrix_row& row);							//The assignment operator
		void			dump_to_stdout		();											//dumps the row to stdout
		unsigned int 	size				();											//returns no of elements in this row (may be usefull for sparse matrix)
		void			resize				(int new_size);								//resize the array (here size is no of elements)
		void 			insert				(int pos,int val);							//insert an element
		void 			rm					(int pos);									//remove an elements frompos position
		int 			capacity			();											//returns the capacity value
		void			push_back			(int val);									//adds an element at the end of the row
		int 			pos_back			();											//removes an elements from the back of the row
};





/*
   DESC : 	matrix_base is the interface for both simple_matrix and sparse_matrix to 
			model directed and undirected graphs respectively. simple_matrix and sparse_matrix
			are declared in there respective headers named as their class names.
			
			Since it is an interface, it does not have an implementation.
*/
class matrix_base
{
	public:
		virtual void				dump_to_stdout	() = 0;					//prints the matrix to stdout
		virtual unsigned int 		get_degree		() = 0;					//returns the degree of the matrix(both simple and sparse matrix has a degree)
		virtual matrix_row& 		operator[]		(int suffix) const = 0;	//Returns a matrix row which also overloads a [] operator
};


}	//end of namespace
#endif











