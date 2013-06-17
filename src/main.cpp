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
	
	
	dir.add_vertex(12);
	dir.rm_vertex(12);
	
	for(int i = 0 ; i < dir.num_vertices() ; i++)
		for(int j = 0 ; j < dir.num_vertices() ; j++)
			dir[i][j] = 1;
	
	dir.dump_to_stdout();
	
	cout<<"The number of vertices are : "<<dir.num_vertices()<<endl;
	
	if(!dir.is_complete())
		cout<<"The graph is not a complete graph"<<endl;
	else cout<<"The graph is connected"<<endl;
	
	return 0;
	
}