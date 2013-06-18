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
	
	cout<<dir<<endl;
		
	return 0;
	
}







