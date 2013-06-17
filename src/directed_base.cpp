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

bool directed_base::is_directed() { return true; }
bool directed_base::is_undirected() { return false; }

void directed_base::set_ref_vertex(int lebel)
{
	int i = vertices.index_of(lebel);	//find the index of the vertex
	if(i == -1) throw new exc_invalid_operation();	//illegal : lebel not found
	this->ref_index = i;	//store for future use
}

int directed_base::num_vertices()
{
	return vertices.size();	//erturns the number of vertices
}

int directed_base::add_vertex(int lebel)
{
	if(vertices.exists(lebel))	throw new exc_invalid_operation();
	
	vertices.add(lebel);	//add the vertex to vertex set
	
	this->add_degree();		//increase the degree of the graph i.e. add a new column and row for the new vertex
	
	return vertices.size();	//the size of the vertex set is the index of the newly addes vertex
}

}




