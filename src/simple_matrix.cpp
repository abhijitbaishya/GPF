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
			std::cout<<"Deleting matrix row number "<<i<<std::endl;
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
	gpf_vector** temp = 0;	//temporary pointer
	
	for(int i = 0 ; i < degree ; i++)
	{
		(*this)[i].push_back(0);	//add a column of zeroes to the matrix
	}	

	temp =(gpf_vector**) malloc(sizeof(gpf_vector*)*(degree+1));  //allocate space for our new matrix (with one more row)
	
	for(int i = 0 ; i < degree ; i++) temp[i] = mat_rows[i];	  //copy previous matrix rows
	
	free(mat_rows);		//free previous matrix

	temp[degree] = new gpf_vector(degree + 1);	//create the last row

	mat_rows = temp;	//update the pointer
    degree++;			//update degree
}

void simple_matrix::rm_rowcol(int index)
{
	if(index >= degree) throw new exc_out_of_bounds(index);	//throw array index out of range
	
	delete mat_rows[index];		//delete the memory associated with the array
	
	for(int i = index ; i < degree - 1 ; i++ )	//shift the array
		mat_rows[i] = mat_rows[i+1];
		
	for(int i = 0 ; i < degree ; i++ )
		mat_rows[i]->rm(index);			//remove column entries
	
	degree--;	//since now one row and one column is removed reduce the degree value
}

}















