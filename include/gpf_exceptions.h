#ifndef _GPF_EXC_
#define _GPF_EXC_

#include	<iostream>
#include	<string>

namespace gpf
{
/*
	General interface for all the GPF exceptions.
*/
class gpf_exception
{
	public:
	virtual std::string what() = 0;
};

/*
	The array out of bounds exception.
*/
class exc_out_of_bounds:public gpf_exception
{
	private:
		int err_index;
	public:
	exc_out_of_bounds(int index)
	{
		err_index = index;
	}
	std::string what()
	{
		return "Array index out of bounds";
	}
	int get_index() {return err_index;}
};

class exc_alloc_failed:public gpf_exception
{
	public:
	std::string what()
	{
		return "Memory allocation failed!\nMay be insufficient memory\n";
	}
};

class exc_invalid_operation:public gpf_exception
{
	public:
	std::string what()
	{
		return "Invalid operation\n";
	}
};

}

#endif









