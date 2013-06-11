#ifndef _BASE_MAT
#define _BASE_MAT
#include<iostream>

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
	
	
	public:
		//constructors and destructors
		virtual ~matrix_row		();								//The destructor
		matrix_row				(unsigned int num_elements);	//The constructor
	
	
	public:
		//member functions
		int  operator[]	(int suffix);		//returns an element from the matrix_row given an index
										//it also handles bound checking
		unsigned int get_num_elements();	//returns no of elements in this row (may be usefull for sparse matrix)
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
		virtual unsigned int 	get_degree		() = 0;				//returns the degree of the matrix(both simple and sparse matrix has a degree)
		virtual matrix_row*		get_rows		() = 0;				//returns base address of the rows array
		virtual matrix_row 		operator[]		(int suffix) = 0;	//Returns a matrix row which also overloads a [] operator
};


}	//end of namespace
#endif











