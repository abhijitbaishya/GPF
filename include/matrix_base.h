#ifndef _BASE_MAT
#define _BASE_MAT

/*
   This is the base class from which we will derive our matrix classes
*/
class matrix_base
{
public:
   //This matrix class will be used to represent graphs and since graphs always use
   //squire matrices, there fore only degree is sufficient
   matrix_base(unsigned int degree);

}


#endif
