#define DEBUG
#include	"../include/simple_matrix.h"
#include	"../include/gpf_exceptions.h"
#include    "../include/graph_base.h"
#include	"../include/directed_graph.h"
using namespace std;
using namespace gpf;


int main()
{
	directed_graph dir(5);
	
	directed_graph d;
	
	dir = d;
	
<<<<<<< HEAD
	cout<<dir;
=======
	cout<<d;
	
	cout<<"My modification"<<endl;
>>>>>>> c2889557cd37170c41c92d5d1d65f4ca83d1f5c9
		
	return 0;
	
}







