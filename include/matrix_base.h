#ifndef _BASE_MAT
#define _BASE_MAT

/*
   This is the abstract base class from which we will derive our matrix classes
*/
class matrix_base
{
private:
	int**     	buffer;	//buffer to store the matrix 
						//(array of array can be used to store sparse matrix also)
	int			degree;	//to store the degree of the matrix
public:
   //This matrix class will be used to represent graphs and since graphs always use
   //squire matrices, there fore only degree is sufficient
   matrix_base(unsigned int degree);

public:
	//operators are implemented by the derived classes
   virtual matrix_base operator+(matrix_base& operand) = 0;
   virtual matrix_base operator-(matrix_base& operand) = 0;
   virtual matrix_base operator*(matrix_base& operand) = 0;
}


#endif
