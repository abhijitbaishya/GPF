#include "../include/simple_matrix.h"

namespace gpf
{

//The simple_matrix constructor
simple_matrix::simple_matrix(unsigned int degree)
{
	try
	{
		this->degree = degree;	//store the degree
		mat_rows = new matrix_row[degree];		//allocate degree number of rows
		
		for(int i = 0; i < degree ; i++)
			mat_rows[i].resize(degree);	//create degree number of elements in each row
	}
	catch(...)
	{
		throw new exc_alloc_failed();	//rethrow our exception
		this->degree = 0;
	}
}

//The destructor
simple_matrix::~simple_matrix()
{
	if(degree != 0) //we do have something to delete
	{
		delete[] mat_rows;
#ifdef DEBUG
		std::cout<<std::endl<<"simple_matrix::~simple_matrix() >> Freed memory mat_rows[]"<<std::endl;
#endif
	}
}

//The operator[] definition
matrix_row& simple_matrix::operator[](int suffix) const
{
	if(suffix <= (degree -1))
	{
		return mat_rows[suffix];
	} else throw new exc_out_of_bounds(suffix);
}

//this method dumps the matrix formatted to the stdout
void simple_matrix::dump_to_stdout()
{
	std::cout<<std::endl;
	for(int i = 0 ; i < degree ; i++)
		(*this)[i].dump_to_stdout();		//mat[i] is matrix_row again
}

}