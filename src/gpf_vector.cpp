#include "../include/gpf_vector.h"


namespace gpf
{

//gpf_vector constructor
gpf_vector::gpf_vector()
{
	//it is okay to have 0 elements in a row
	row_ptr 		= NULL;
	num_elements 	= 0;
	_capacity		= 0;
}

//gpf_vector constructor
gpf_vector::gpf_vector(int num_elements)
{
	//number of elements cannot be negative
	if(num_elements < 0) throw new exc_invalid_operation();
	
	if(num_elements == 0)
	{
		//it is okay to have 0 elements in a row
		row_ptr 		= NULL;
		num_elements 	= 0;
		this->_capacity  = 0;
	}
	if(num_elements != 0)
	try
	{
		//round capacity to 16 units boundary
		this->_capacity = (
							num_elements % 16 ? 
							num_elements - (num_elements % 16) + 16 : 
							num_elements
						 );
		//allocate capacity no. of floats
		this->row_ptr = (float*) malloc ( sizeof(float) * this->_capacity );
		//zero initialize the whole memory
		memset(this->row_ptr,0, sizeof(float) * num_elements);
		//update the number of elements: note that num_elements <= capacity
		this->num_elements = num_elements;
	}
	catch(...)
	{
		//something went wrong : revert to default values
		row_ptr 		= NULL;
		num_elements 	= 0;
		this->_capacity  = 0;
		throw new exc_alloc_failed();	//throw our own exception
	} 
}

//The destructor defination
gpf_vector::~gpf_vector()
{
	if(row_ptr != NULL)	//if this row not assigned to an object or passed to any function delete it
	{
		free(row_ptr);	//call free because we used malloc
		row_ptr = NULL;
#ifdef DEBUG
		std::cout<<std::endl<<"gpf_vector::~gpf_vector() >> Freed memory row_ptr"<<std::endl;
#endif
	}
}


//The copy constructor
gpf_vector::gpf_vector(const gpf_vector& row)
{
#ifdef DEBUG
	std::cout<<"Copy ctor invoked"<<std::endl;
#endif
	gpf_vector& temp = const_cast<gpf_vector&>(row);
	
	//if input array is empty then make this empty too
	if(row.num_elements == 0) { this->resize(0); return;}
	
	//if input is not an empty row
	this->resize(row.num_elements);	//resize this array
	
	//copy all elements
	for(int i = 0; i < row.num_elements ; i++ )
		row_ptr[i] = temp[i];
	
	//copy other states
	this->num_elements = temp.num_elements;
}

gpf_vector&	gpf_vector::operator=(const gpf_vector& row)
{
#ifdef DEBUG
	std::cout<<"Assignment operator invoked!"<<std::endl;
#endif
	if(row.num_elements == 0 ) 
	{
		this->resize(0);	//empty this array also
		return (*this);
	}

	try
	{
		this->resize(row.num_elements);			//resize this array to fit row
	}
	catch(...) 
	{
		throw new exc_alloc_failed();
	}
	
	//copy all the elements
	for(int i = row.num_elements ; i >= 0 ; i--)
		this->row_ptr[i] = row.row_ptr[i];
		
	return *this;
}

float& gpf_vector::operator[] (int suffix) const throw (exc_out_of_bounds*)
{
	//if we are within bounds
	if(suffix <= (num_elements-1))
	{
		return row_ptr[suffix];
	}
	else throw  new exc_out_of_bounds(suffix);	//throw a out of bounds exception
}


//returns number of elements
int gpf_vector::size() const
{
	return num_elements;
}

void gpf_vector::dump_to_stdout() const
{
	if(num_elements == 0) { std::cout<<"<EMPTY>"<<std::endl; return; }
	
	for(int i = 0; i < num_elements ; i++)
		std::cout<<row_ptr[i]<<" ";
	std::cout<<std::endl;
}

void gpf_vector::insert(int pos,float val)
{
	if(pos >= num_elements) throw new exc_out_of_bounds(pos);	//array index out of bound
	
	this->num_elements ++;	//assume new element inserted
	
	//first decide if we have to expand the memory
	if(_capacity == num_elements)	//if the array is full
	{
		try{
			//resize the array to fit an extra element
			this->resize(num_elements);	
		}
		catch(...) //catch anything
		{
			//memory allocation fro extra element was failed
			num_elements--;	
			//throw our own exception
			throw new exc_alloc_failed();	
		}
		
	}
	
	//shift the entire array to the right starting from pos position
	for(int i = num_elements - 2 ; i >= pos; i--)
		this->row_ptr[i+1] = this->row_ptr[i];	
	
	//assign the value to pos-th element
	this->row_ptr[pos] = val;	
}

void gpf_vector::rm(int pos)
{
	int re_calc;
	if(pos >= num_elements) throw new exc_out_of_bounds(pos);	//array index out of bound
	
	if(num_elements <= 16) 
	{	
		//array size is less than one paragraph so just decrement the number of elements
		for(int i = pos + 1 ; i < num_elements ; i++)
			this->row_ptr[i-1] = this->row_ptr[i];	//shift the array to left
		
			num_elements--;
		return;
	}	
	
	try
	{
		for(int i = pos ; i < num_elements-2 ; i++)
			this->row_ptr[i] = this->row_ptr[i+1];	//shift the array to left
		
		this->resize(num_elements - 1);	//resize() will shrink the array
	}
	catch(...) //catch anything
	{
		throw new exc_alloc_failed();	//allocation failed
	}
}

void gpf_vector::resize(int new_size)
{
	//size cannot be negative
	if(new_size < 0 ) throw new exc_invalid_operation();
	//proper way to empty a row
	if(new_size == 0)
	{
		free(this->row_ptr);
		this->row_ptr = NULL;
		this->num_elements = 0;
		this->_capacity = 0;
		return;
	}
	
	//calculate the aligned space required
	int recalc =   (
						new_size % 16 ? 
						new_size - (new_size % 16) + 16 : 
						new_size
					);
	//if the calculated space does not equal the _capacity
	//i.e. if calculated size is either larger or smaller the capacity
	if(recalc != this->_capacity)
	{
		try
		{
			//already allocated 
			if(this->row_ptr != NULL)	
			{
				//resize the array
				realloc(this->row_ptr, sizeof(float) * recalc);
				//update the capacity value
				this->_capacity = recalc;
			}
			else	//if array not created yet
			{
				//allocate the memory
				this->row_ptr = (float*) malloc(sizeof(float) * recalc);
				//update the capacity value
				this->_capacity = recalc;	
			}
		}
		catch(...)
		{
			//something went wrong
			throw new exc_alloc_failed();	
		}
	}
	//update the number of elements outside the if block because if the capacity is bigger control doesnot
	//reaches inside the if block
	this->num_elements = new_size;
}

int gpf_vector::capacity() const
{
	return this->_capacity;
}

void gpf_vector::push_back(int val)
{
	//resize the array to fit one more element
	resize(num_elements + 1);
	//append the value to the end of the array
	this->row_ptr[num_elements-1] = val;
}

bool gpf_vector::empty() const
{
	return (!this->num_elements == 0);
}

float gpf_vector::pop_back()
{
	int ret;
	
	//nothing to pop
	if(num_elements == 0) throw new exc_invalid_operation();
	//no need to resize
	if(num_elements <= 16) return this->row_ptr[num_elements--];
	//store return value
	ret = this->row_ptr[num_elements--];
	//may shrink
	this->resize(num_elements);
	//return
	return ret;
}

int gpf_vector::find(float val) const
{
	for(int i = 0 ; i < this->size() ; i++)
		if(row_ptr[i] == val) return i;	//if data found return index
	return -1;	//else return -1
}

void gpf_vector::clear()
{
//free all memory and recert back to default values 
	if(this->row_ptr != NULL)
	{
		free(this->row_ptr);
		this->row_ptr = NULL;
		
		num_elements 	= 0;
		_capacity 		= 0;
	}
//this function does not causes any exception
}

std::ostream& operator<<(std::ostream& out, gpf_vector& vec)
{
	if(vec.num_elements == 0) { out<<"<EMPTY>"<<std::endl; return out; }
	
	for(int i = 0; i < vec.num_elements ; i++)
		out<<vec.row_ptr[i]<<" ";
	out<<std::endl;
	
	return out;
}

}


