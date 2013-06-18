#define DEBUG
#include	"../include/simple_matrix.h"
#include	"../include/gpf_exceptions.h"
#include    "../include/graph_base.h"
#include	"../include/directed_graph.h"
using namespace std;
using namespace gpf;


int main()
{
/*
	directed_graph dir(5);
	
	
	dir.add_vertex	(12);
	dir.rm_vertex	(12);
	
	dir.dump_to_stdout();
	
	cout<<"The number of vertices are : "<<dir.num_vertices()<<endl;
	
	if(!dir.is_complete())
		cout<<"The graph is not a complete graph"<<endl;
	else cout<<"The graph is connected"<<endl;
*//*
	simple_matrix simp(3);
	directed_graph dir(5);
	

	cout<<dir;
	
	
	for(int i = 0 ; i < simp.get_mat_degree() ; i++)
		for(int j = 0; j < simp.get_mat_degree() ; j++ )
			simp[i][j] = 0.89;
	
	cout<<simp;
*/

	gpf_vector vec(5);
	
	gpf_vector vec2(vec);
	
	cout<<vec<<vec2;
	
	cout<<vec.size()<<" "<<vec2.size()<<endl;
	cout<<vec.capacity()<<" "<<vec2.capacity()<<endl;
	
	return 0;
	
}







