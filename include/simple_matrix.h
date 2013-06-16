#ifndef __SIMPLE_MATRIX_
#define __SIMPLE_MATRIX_

#include	"matrix_base.h"

//The graph processing framework namespace
namespace gpf
{
/*
	DESC : 	simple_matrix is the class to model a simple or general squire matrix
			used to represent directed graphs. simple_matrix is not sparse.
*/
class simple_matrix:public matrix_base
{
	private:
		int 	degree;					//The degree of the matrix
		gpf_vector**	mat_rows;		//array of row pointers for ease of shifting
										
	public:
		//The virtual destructor
		virtual ~simple_matrix();
	
		//constructor
		simple_matrix();
		simple_matrix(unsigned int degree);
	
		//dumps the matrix to stdout
		unsigned int 		get_degree		()	{return degree;}
		//returns a gpf_vector object
		gpf_vector& 		operator[]		(int suffix) const;	//Returns a matrix row which also overloads a [] operator	
		void				dump_to_stdout	();
};



}

#endif