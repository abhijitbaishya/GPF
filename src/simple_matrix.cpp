#include "../include/simple_matrix.h"
#include	<stdlib.h>
#include	<memory.h>

namespace gpf
{

std::ostream& operator<<(std::ostream& out, simple_matrix& mat)
{
	//nothing to print
	if(mat.degree == 0) {out<<std::endl<<"<EMPTY>"<<std::endl; return out;} 
	
	for(int i = 0 ; i < mat.degree ; i++)
	{
		for(int j = 0 ; j < mat.degree ; j++)
		{
			out<<mat[i][j]<<" ";
		}
		out<<std::endl;
	}
	return out;
}


simple_matrix::simple_matrix()
{
	//by default the matrix is empty
	this->degree = 0;
}

//The simple_matrix constructor
simple_matrix::simple_matrix(int degree)
{
	//degree cannot be negative
	if(degree < 0) throw new exc_invalid_operation();
	try
	{
		//store the degree for future reference
		this->degree = degree;
		//allocate degree number of row pointers
		mat_rows = (gpf_vector**)malloc( sizeof(gpf_vector*) * degree);
		
		for(int i = 0; i < degree ; i++)
			mat_rows[i] = new gpf_vector(degree);	//allocate the arrays
	}
	catch(...)
	{
		//something went wrong so rethrow our exception
		throw new exc_alloc_failed();
		this->degree = 0;
	}
}

//The destructor
simple_matrix::~simple_matrix()
{
	//if we do have something to delete
	if(degree != 0)
	{
		//first delete the inner vectors
		for(int i = 0; i < degree ; i++)
		{
			std::cout<<"Deleting matrix row number "<<i<<std::endl;
			delete mat_rows[i];	//delete each rows 
		}
		//then delete the container
		free( mat_rows );
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
		//returns the suffix-th row (gpf_vector)
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

//adds a new row and a new column to the matrix at the extremes
void simple_matrix::add_degree()
{	
	gpf_vector** temp = 0;	//temporary pointer
	
	for(int i = 0 ; i < degree ; i++)
	{
		//add a column of zeroes to the matrix
		(*this)[i].push_back(0);
	}	
	
	//allocate space for our new matrix (with one more row)
	temp =(gpf_vector**) malloc(sizeof(gpf_vector*)*(degree+1)); 
	//copy previous matrix rows
	for(int i = 0 ; i < degree ; i++) temp[i] = mat_rows[i];
	//free previous matrix
	free(mat_rows);
	//create the last row (by default 0 initialized)
	temp[degree] = new gpf_vector(degree + 1);
	//update the pointer
	mat_rows = temp;
	//update degree
    degree++;
}
//removes a row and a column specified by index
void simple_matrix::rm_rowcol(int index)
{
	//throw array index out of range
	if(index >= degree) throw new exc_out_of_bounds(index);
	//delete the memory associated with the array
	delete mat_rows[index];
	
	//shift the array : to fill the gap due to a row being deleted
	for(int i = index ; i < degree - 1 ; i++ )
		mat_rows[i] = mat_rows[i+1];
	//remove column entries
	for(int i = 0 ; i < degree ; i++ )
		mat_rows[i]->rm(index);
	//since now one row and one column is removed reduce the degree value
	degree--;
}

bool simple_matrix::empty()
{
	return (this->degree == 0);
}

}















