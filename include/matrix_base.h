#ifndef _BASE_MAT
#define _BASE_MAT

//Graph Processor Framework
namespace gpf
{
/*
   DESC : 	matrix_base is the base class for both simple_matrix and sparse_matrix to 
			model directed and undirected graphs respectively. simple_matrix and sparse_matrix
			are declared in there respective headers named as their class names.
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
};


}	//end of namespace
#endif
