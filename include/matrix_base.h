#ifndef _BASE_MAT
#define _BASE_MAT
#include	<iostream>
#include	<memory.h>
#include	"../include/gpf_exceptions.h"
#include    "../include/gpf_vector.h"

//Graph Processor Framework
namespace gpf
{
/**
   DESC : 	matrix_base is the interface for both simple_matrix and sparse_matrix to 
			model directed and undirected graphs respectively. simple_matrix and sparse_matrix
			are declared in there respective headers named as their class names.
			
			Since it is an interface, it does not have an implementation.
*/
class matrix_base
{
	public:
		virtual void				clear				() = 0;							//makes the matrix empty
		virtual bool				empty				() const = 0;					//matrix is unusable i.e. does not have anything
		virtual int 				get_mat_degree		() const = 0;					//returns the degree of the matrix(both simple and sparse matrix has a degree)
		virtual gpf_vector& 		operator[]			(int suffix) const = 0;	//Returns a matrix row which also overloads a [] operator
};


}	//end of namespace
#endif











