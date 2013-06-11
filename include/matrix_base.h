#ifndef _BASE_MAT
#define _BASE_MAT

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
	int*			row_ptr;			//actual row pointer
	unsigned int 	num_elements;		//number of elements
public:
	virtual ~matrix_row();					//The destructor
	matrix_row(unsigned int num_elements);	//The constructor

	matrix_row operator[](int suffix);	//returns an element from the matrix_row given an index
										//it also handles bound checking
}

/*
   DESC : 	matrix_base is the base class for both simple_matrix and sparse_matrix to 
			model directed and undirected graphs respectively. simple_matrix and sparse_matrix
			are declared in there respective headers named as their class names. It encapsulates the common
			functionalities of both types of matrices.
*/
class matrix_base
{
protected:
	matrix_row*	matrix_rows;	//Rows of the matrix
						
	int			degree;	//to store the degree of the matrix
public:
	//to free up the buffer
	virtual ~matrix_base();
	
	unsigned int 	get_degree();		//returns the degree of the matrix(both simple and sparse matrix has a degree)
	matrix_row*		get_rows();			//returns base address of the rows array
public:
	virtual matrix_row operator[](int suffix) = 0;	//Returns a matrix row which also overloads a [] operator
};


}	//end of namespace
#endif
