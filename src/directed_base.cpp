#include 	"../include/directed_base.h"

namespace gpf
{

directed_base::directed_base():vertices()
{
}

directed_base::directed_base(unsigned int num_vertices):
				simple_matrix(num_vertices),	//initialize the edges (initially null)
				vertices(num_vertices)			//initialize the vertices (by default lebeled 0,1,2,3,....)
{
	
}

bool directed_base::empty()
{
	return vertices.empty();	//if there are no vertices then the graph is empty
}

//returns true if null graph
bool directed_base::is_null()
{
	int deg = get_degree();	//get the degree of the edge matrix
	int i , j;
	
	if(deg == 0) return false;
	
	for(i = 0; i< deg ; i++)
		for(j = 0; j < deg ; j++)
			if((*this)[i][j] != 0) return false;
	return true;
	
}




}