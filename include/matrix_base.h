#ifndef _BASE_MAT
#define _BASE_MAT

//Graph Processor Framework
namespace gpf
{
/*
   This is the abstract base class from which we will derive our matrix classes
*/
class matrix_base
{
private:
	int**     	buffer;	//int buffer to store the matrix 
						//(array of array can be used to store sparse matrix also)
	int			degree;	//to store the degree of the matrix
public:
   //to free up the buffer
   virtual ~matrix_base();
   
   //This matrix class will be used to represent graphs and since graphs always use
   //squire matrices, there fore only degree is sufficient
   matrix_base(unsigned int degree);

public:
	//operators are implemented by the derived classes
   virtual matrix_base operator+	(matrix_base& operand) = 0;
   virtual matrix_base operator-	(matrix_base& operand) = 0;
   virtual matrix_base operator*	(matrix_base& operand) = 0;
   virtual int*		   operator[]	(int suffix) = 0;			//suffix operator will return the address of the row (which is integer array)
};


}	//end of namespace
#endif
