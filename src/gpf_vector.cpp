#include "../include/gpf_vector.h"


namespace gpf
{

gpf_vector::gpf_vector()
{
	row_ptr 		= NULL;
	num_elements 	= 0;	//it is okay to have 0 elements in a row
}
//The constructor for gpf_vector
gpf_vector::gpf_vector(unsigned int num_elements)
{
	if(num_elements != 0)
	try
	{
		this->_capacity = (												//round capacity to boundary 16
							num_elements % 16 ? 
							num_elements - (num_elements % 16) + 16 : 
							num_elements
						 );
		
		this->row_ptr = (int*) malloc ( sizeof(int) * this->_capacity );				//allocate capacity no of integers
		memset(this->row_ptr,0, sizeof(int) * num_elements);	//zero initialize the whole memory

		this->num_elements = num_elements;						//update the number of elements: note that num_elements <= capacity
	}
	catch(...)
	{
		row_ptr 		= NULL;
		num_elements 	= 0;
		this->_capacity  = 0;
		throw new exc_alloc_failed();	//throw our own exception
	} 
	else if(num_elements == 0)
		{
			row_ptr 		= NULL;
			num_elements 	= 0;	//it is okay to have 0 elements in a row
			this->_capacity  = 0;
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
gpf_vector::gpf_vector(gpf_vector& row)
{
	std::cout<<"Copy ctor invoked"<<std::endl;
	if(row.num_elements != 0)
	try{
		this->row_ptr = new int[row.num_elements];	//allocate same number of elements as row
	   }
	catch(...) 
	{
		throw exc_alloc_failed();
	}
	
	for(int i = 0; i < row.num_elements ; i++ )
		row_ptr[i] = row[i];	//copy all elements
	this->num_elements = row.num_elements;	//copy other states
}

gpf_vector&	gpf_vector::operator=(gpf_vector& row)
{
#ifdef DEBUG
	std::cout<<"assignment operator invoked"<<std::endl;
#endif
	if(row.num_elements != 0)
	try
	{
		this->resize(row.num_elements);			//resize this array to fit row
		this->num_elements = row.num_elements;	//copy number of elements
		this->_capacity = row._capacity;		//copy capacity value
	}
	catch(...) 
	{
		throw new exc_alloc_failed();
	}
	
	memcpy(this->row_ptr,row.row_ptr,row._capacity);	//copy the entire memory in one shot
		
	return *this;
}

int& gpf_vector::operator[] (int suffix) throw (exc_out_of_bounds*)
{
	if(suffix <= (num_elements-1)) //if we are within bounds
	{
		return row_ptr[suffix];
	}
	else throw  new exc_out_of_bounds(suffix);		//throw a out of bounds exception
}


//returns number of elements
unsigned int gpf_vector::size()
{
	return num_elements;
}

void gpf_vector::dump_to_stdout()
{
	if(num_elements == 0) { std::cout<<"<EMPTY>"<<std::endl; return; }
	
	for(int i = 0; i < num_elements ; i++)
		std::cout<<row_ptr[i]<<" ";
	std::cout<<std::endl;
}

void gpf_vector::insert(int pos,int val)
{
	if(pos >= num_elements) throw new exc_out_of_bounds(pos);	//array index out of bound
	
	this->num_elements ++;	//new element may be added
	
	//first decide if we have to expand the memory
	if(_capacity == num_elements)			//the array is full
	{
		try{
			this->_capacity = (				//so recalcute the required _capacity
							num_elements % 16 ? 
							num_elements - (num_elements % 16) + 16 : 
							num_elements
						 );
			realloc(this->row_ptr, sizeof(int) * this->_capacity);	//grow the size of the array
		}
		catch(...) //catch anything
		{
			num_elements--;	//insertion was failed
			throw new exc_alloc_failed();	//throw our own exception
		}
		
	}

	for(int i = num_elements - 2 ; i >= pos; i--)
		this->row_ptr[i+1] = this->row_ptr[i];	//shift the entire array to the right starting from pos position
		
	this->row_ptr[pos] = val;	//assign the value to pos-th element
}

void gpf_vector::rm(int pos)
{
	int re_calc;
	if(pos >= num_elements) throw new exc_out_of_bounds(pos);	//array index out of bound
	
	if(num_elements <= 16) 
	{	
		for(int i = pos + 1 ; i < num_elements ; i++)
			this->row_ptr[i-1] = this->row_ptr[i];	//shift the array to left
		
			num_elements--;
		
		return;
	}	//array size is less than one paragraph so just decrement the number of elements
	
	try
	{
		for(int i = pos ; i < num_elements-2 ; i++)
			this->row_ptr[i] = this->row_ptr[i+1];	//shift the array to left
		
		this->num_elements--;		//decrement the element count
		
		re_calc = (												//recalculate the space required
					num_elements % 16 ? 
					num_elements - (num_elements % 16) + 16 : 
					num_elements
				 );
				 
		if(re_calc < this->_capacity)			//if recalculated value is less than the _capacity
		{
			realloc(this->row_ptr,re_calc);	//shrink the array
			this->_capacity = re_calc;		//update the capacity value
		}
	}
	catch(...) //catch anything
	{
		throw new exc_alloc_failed();	//allocation failed
	}
}

void gpf_vector::resize(int new_size)
{
	if(new_size < 0 ) throw new exc_invalid_operation();
	if(new_size == 0) {free(this->row_ptr);this->row_ptr = NULL;}	//special cases
	
	int recalc =   (												//calculate the aligned space required
						new_size % 16 ? 
						new_size - (new_size % 16) + 16 : 
						new_size
					);
					
	if(recalc != this->_capacity)	//if the calculated space does not equal the _capacity
	{
		try
		{
			if(this->row_ptr != NULL)	//already allocated 
			{
				realloc(this->row_ptr, sizeof(int) * recalc);	//resize the array
				this->_capacity = recalc;		//update the capacity value
			}
			else		//if not created yet
			{
				this->row_ptr = (int*) malloc(sizeof(int) * recalc);
				this->_capacity = recalc;	//update the capacity value
			}
				
			this->num_elements = new_size;					//update the number of elements
		}
		catch(...)
		{
			throw new exc_alloc_failed();	//throw our exception
		}
	}
}

int gpf_vector::capacity()
{
	return this->_capacity;
}

void gpf_vector::push_back(int val)
{
	num_elements++;			//increment the number of elements
	int re_calc = (												//recalculate the space required
					num_elements % 16 ? 
					num_elements - (num_elements % 16) + 16 : 
					num_elements
				  );
	
	if(re_calc > _capacity)
	{
		try
		{
			if(this->row_ptr == NULL)	//not allocated yet
			{
				this->row_ptr = (int*) malloc(sizeof(int) * re_calc);	//allocate the array
				this->_capacity = re_calc;		//update the capacity value
			}
			else
			{
				realloc(this->row_ptr , sizeof(int) * re_calc);	//expand the array
				this->_capacity = re_calc;		//update the capacity
			}
		}
		catch(...)
		{
			throw new exc_alloc_failed();	//throw an allocation failed exception
		}
	}
	this->row_ptr[num_elements-1] = val;	//append the value to the end of the array
}

bool gpf_vector::empty()
{
	return (this->num_elements == 0);
}

int gpf_vector::pop_back()
{
	int ret;
	
	if(num_elements == 0) throw new exc_invalid_operation();		//nothing to pop
	if(num_elements <= 16) return this->row_ptr[num_elements--];	//no need to resize
	
	ret = this->row_ptr[num_elements--];	//store return value
	this->resize(num_elements);				//may shrink
	return ret;								//return
}

int gpf_vector::find(int val)
{
	for(int i = 0 ; i < this->size() ; i++)
		if(row_ptr[i] == val) return i;		//if data found return index
	return -1;
}


}


