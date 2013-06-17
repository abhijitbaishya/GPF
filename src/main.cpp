#define DEBUG
#include	"../include/simple_matrix.h"
#include	"../include/gpf_exceptions.h"
#include    "../include/graph_base.h"
#include	"../include/directed_base.h"
using namespace std;
using namespace gpf;


int main()
{
	directed_base dir(5);
	
	
	dir.add_vertex(12);
	dir.rm_vertex(12);
	
	dir.dump_to_stdout();
	
	cout<<"The number of vertices are : "<<dir.num_vertices()<<endl;
	
	return 0;
	
}