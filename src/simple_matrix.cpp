#include "../include/simple_matrix.h"
#include	<stdlib.h>
#include	<memory.h>

namespace gpf
{

simple_matrix::simple_matrix()
{
	this->degree = 0;
}

//The simple_matrix constructor
simple_matrix::simple_matrix(unsigned int degree)
{
	try
	{
		this->degree = degree;					//store the degree
		mat_rows = (gpf_vector**)malloc( sizeof(gpf_vector*) * degree);		//allocate degree number of row pointers for ease of shifting
		
		for(int i = 0; i < degree ; i++)
		{
			mat_rows[i] = new gpf_vector(degree);	//allocate the arrays to each pointers
		}
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
		for(int i = 0; i < degree ; i++)
		{
			delete mat_rows[i];	//delete each rows 
		}
		free( mat_rows );			//mat_rows was allocated using malloc so free it
#ifdef DEBUG
		std::cout<<std::endl<<"simple_matrix::~simple_matrix() >> Freed memory mat_rows[]"<<std::endl;
#endif
	}
}

//The operator[] definition
gpf_vector& simple_matrix::operator[](int suffix) const
{
	if(suffix <= (degree -1))
	{
		return *(mat_rows[suffix]);
	} else throw new exc_out_of_bounds(suffix);
}

//this method dumps the matrix formatted to the stdout
void simple_matrix::dump_to_stdout()
{
	if(degree == 0) std::cout<<"<EMPTY>"<<std::endl;
	std::cout<<std::endl;
	for(int i = 0 ; i < degree ; i++)
		(*this)[i].dump_to_stdout();		//mat[i] is gpf_vector again
}

void simple_matrix::add_degree()
{	
	for(int i = 0 ; i < degree ; i++)
	{
		(*this)[i].push_back(0);	//add a column of zeroes to the matrix
	}
	realloc(mat_rows,sizeof(gpf_vector*) * (degree + 1));	//add slot for another row pointer
	mat_rows[degree] = new gpf_vector(degree+1);	//allocate the last row
	degree++;	//increment the degree value at last
}

}















