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
	this->mat_rows = NULL;
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
	}
}

//the copy constructor
simple_matrix::simple_matrix(const simple_matrix& copy)
{
	try
	{
	//store the degree for future reference
		this->degree = copy.degree;
	//allocate degree number of row pointers
		mat_rows = (gpf_vector**)malloc( sizeof(gpf_vector*) * degree);
		
		for(int i = 0; i < degree ; i++)
		{
		//allocate the rows
			this->mat_rows[i] = new gpf_vector();
		//copy values from input matrix rows this this objects rows
			(*mat_rows[i]) = (*copy.mat_rows[i]);
		}		
	}
	catch(...)
	{
	//something went wrong so rethrow our exception
		throw new exc_alloc_failed();
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
	if(this->mat_rows) free(this->mat_rows);
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
	//index cannot be negative
	if(index < 0) throw new exc_invalid_operation();
	//throw array index out of range
	if(index >= degree) throw new exc_out_of_bounds(index);
	//delete the memory associated with the array
	delete mat_rows[index];
	
	//shift the array : to fill the gap due to a row being deleted
	for(int i = index ; i < degree - 1 ; i++ )
		mat_rows[i] = mat_rows[i+1];
	//remove column entries from each row
	for(int i = 0 ; i < degree ; i++ )
		mat_rows[i]->rm(index);
	//since now one row and one column is removed reduce the degree value
	degree--;
}
//deletes the last row and column of the matrix
void simple_matrix::rm_degree()
{
	//delete the last row and column
	this->rm_rowcol(this->degree - 1);
}

bool simple_matrix::empty() const
{
	return (this->degree == 0);
}

simple_matrix& simple_matrix::operator=(const simple_matrix& mat)
{
	gpf_vector**	temp = NULL;
	//if the input matrix is empty
	if(mat.degree == 0 )
	{
	//delete each individual rows
		for(int  i = 0 ; i < degree ; i++)
			delete this->mat_rows[i];
	//free the container
		free(this->mat_rows);
	//important for destructor
		this->mat_rows = 0;
	//make degree = 0 
		this->degree = 0;
	//we are done
	return (*this);
	}
	
	//if this object is empty but input matrix is non empty
	if(this->degree == 0)
	{
		try
		{
		//store the degree for future reference
			this->degree = mat.degree;
		//allocate degree number of row pointers
			mat_rows = (gpf_vector**)malloc( sizeof(gpf_vector*) * degree);
		
			for(int i = 0; i < degree ; i++)
			{
			//allocate the rows
				this->mat_rows[i] = new gpf_vector();
			//copy values from input matrix rows this this objects rows
				(*mat_rows[i]) = (*mat.mat_rows[i]);
			}		
		}
		catch(...)
		{
		//something went wrong so rethrow our exception
			throw new exc_alloc_failed();
			this->degree = 0;
		}
	}
	//This matrix is non empty, input matrix is non empty and both have same degree
	else if(this->degree == mat.degree)
	{
		//just copy all the rows to this matrix making use of gpf_vector::operator=
		for(int i = 0 ; i < degree ; i ++)
			(*mat_rows[i]) = (*mat.mat_rows[i]);
	}
	//if this object is non empty and input matrix is also non empty and this matrix is smaller
	else if(this->degree < mat.degree)
	{
		//allocate large enough array to hold same number of row pointers as input matrix
		temp = (gpf_vector**)malloc(sizeof(gpf_vector*) * mat.degree);
		
		//in-case allocation failed
		if(temp == NULL) throw new exc_alloc_failed();
		
		//copy the old data into the bigger array
		for(int i = degree - 1 ; i >= 0 ; i--)
			temp[i] = this->mat_rows[i];
		
		//free the old matrix
		//( old array is surely created because we checked for 
		//empty matrix in previous if block )
		free(this->mat_rows);
		this->mat_rows = NULL;	//good habit
		
		//append extra arrays at the end
		for(int i = degree ; i < mat.degree ; i++)
			temp[i] = new gpf_vector();	//empty vectors are created faster
		
		//now copy all the rows of input matrix making use of operator= of gpf_vector class
		for(int i = 0 ; i < mat.degree ; i++)
			(*temp[i]) = (*mat.mat_rows[i]);
		
		//update the original pointer
		this->mat_rows = temp;
		
		//update degree
		this->degree = mat.degree;
	}
	//if input matrix is non empty, our matrix is non empty and this->degree > mat.degree
	else
	{
		//allocate a smaller array of row pointers
		gpf_vector** temp = (gpf_vector**) malloc ( sizeof(gpf_vector*) * (this->degree - mat.degree) );
		
		//copy original entries to shrinked array
		for(int  i = mat.degree - 1 ; i >= 0 ; i--)
			temp[i] = this->mat_rows[i];	
		
		//delete extra rows from the original array
		for(int i = mat.degree ; i < this->degree ; i++)
			delete this->mat_rows[i];
			
		//delete the original array
		free(this->mat_rows);
		this->mat_rows = NULL;
		
		//update the original pointer
		this->mat_rows = temp;
		
		//update the degree
		this->degree = mat.degree;
		
		//now that this object has same no of rows as that of the input matrix
		//we can copy from input matrix all the arrays
		for(int i = 0 ; i < this->degree ; i++)
			(*mat_rows[i]) = (*mat.mat_rows[i]);
			
	}
	
//We are done now
	return (*this);	
}

void simple_matrix::clear()
{
	//if already empty then just return
	if(this->empty()) return;
	
	//else free all memory
	for(int i = 0 ; i < degree ; i++)
		delete this->mat_rows[i];
		
	free(this->mat_rows);
	this->mat_rows = NULL;
	
	//make the degree of this matrix 0
	this->degree = 0;
}

}















