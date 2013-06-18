#ifndef __SIMPLE_MATRIX_
#define __SIMPLE_MATRIX_

#include	"matrix_base.h"

//The graph processing framework namespace
namespace gpf
{
/**
	DESC : 	simple_matrix is the class to model a simple or general squire matrix
			used to represent directed graphs. simple_matrix is not sparse.
*/
class simple_matrix:public matrix_base
{
	private:
	//The degree of the matrix
		int 			degree;
	//array of row pointers for ease of rearranging rows
		gpf_vector**	mat_rows;
										
	public:
	//The virtual destructor
		virtual ~simple_matrix();
	
	//constructors
	//creates an empty matrix
		simple_matrix();
	//creates a matrix with degree rows and columns
		simple_matrix(int degree);
	//The copy constructor
		simple_matrix(const simple_matrix& copy);
	
	//dumps the matrix to stdout
		int 				get_mat_degree		()	{return degree;}
	//returns true if the matrix is not yet created
		bool				empty			();
	//returns a gpf_vector object
	//Returns a matrix row which also overloads a [] operator
		gpf_vector& 		operator[]		(int suffix) const;
	//assignment operator
		simple_matrix& 		operator=		(const simple_matrix& mat);
	protected:
	//rm_degree function deletes the last column and the last row
		void				rm_degree		();
	//adds a new null column and null row to the matrix (useful for vertex add operation)
		void 				add_degree		();
	//removes a row and a column (reduces the degree of the matrix)
		void 				rm_rowcol		(int index);
	//The inserter overload function for using << operator for output
	friend std::ostream& operator<<(std::ostream& out, simple_matrix& mat);
};

/***
	Inserter operator overloaded for output of simple_matrix object using << operator
*/
std::ostream& operator<<(std::ostream& out, simple_matrix& mat);


}

#endif