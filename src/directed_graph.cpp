#include 	"../include/directed_graph.h"

namespace gpf
{

directed_graph::directed_graph():vertices()
{
	ref_index = 0;	//by default start index is 0
}

directed_graph::directed_graph(unsigned int num_vertices):
				simple_matrix(num_vertices),	//initialize the edges (initially null)
				vertices(num_vertices)			//initialize the vertices (by default lebeled 0,1,2,3,....)
{
	ref_index = 0;
}

bool directed_graph::empty()
{
	return vertices.empty();	//if there are no vertices then the graph is empty
}

//returns true if null graph
bool directed_graph::is_null()
{
	int deg = get_degree();	//get the degree of the edge matrix
	int i , j;
	
	if(deg == 0) return false;
	
	for(i = 0; i< deg ; i++)
		for(j = 0; j < deg ; j++)
			if((*this)[i][j] != 0) return false;
	return true;
	
}

bool directed_graph::is_directed() { return true; }
bool directed_graph::is_undirected() { return false; }

void directed_graph::set_ref_vertex(int lebel)
{
	int i = vertices.index_of(lebel);	//find the index of the vertex
	if(i == -1) throw new exc_invalid_operation();	//illegal : lebel not found
	this->ref_index = i;	//store for future use
}

int directed_graph::num_vertices()
{
	return vertices.size();	//erturns the number of vertices
}

int directed_graph::add_vertex(int lebel)
{
	if(vertices.exists(lebel))	throw new exc_invalid_operation();
	
	vertices.add(lebel);	//add the vertex to vertex set
	
	this->add_degree();		//increase the degree of the graph i.e. add a new column and row for the new vertex
	
	return vertices.size();	//the size of the vertex set is the index of the newly addes vertex
}

void directed_graph::rm_vertex(int lebel)
{
	rm_rowcol(vertices.index_of(lebel));	//erase the row and column corresponding to the vertex lebel
	vertices.rm(lebel);						//delete the vertex from the vertex set
}

bool directed_graph::is_complete()
{
	int deg = get_degree();	//get the degree of the incidence matrix
	for(int i = 0 ; i < deg ; i++)
		for(int j = 0 ; j < deg ; j++)
		{
			if( i == j) continue;	//ignore self loops
			if((*this)[i][j] < 1) return false;
		}
	return true;	//if we did not find a disconnection then return true
}

int directed_graph::distance_to(int lebel)
{
	if(	vertices.size() == 0 ||				//if start_index is out of bounds or there are no vertices 
		ref_index >= vertices.size()) throw new exc_invalid_operation();
	
	int dst_index = vertices.index_of(lebel);
	if(dst_index >= 0) return (*this)[ref_index][dst_index];	//note that distance may be 0 but may not -ve
	else
		return -1;		//no edge was found
}

int directed_graph::distance_from(int lebel)
{
	if(	vertices.size() == 0 ||				//if start_index is out of bounds or there are no vertices 
		ref_index >= vertices.size()) throw new exc_invalid_operation();
		
	int src_index = vertices.index_of(lebel);	//find the index of lebel
	
	if(src_index >= 0) return (*this)[src_index][ref_index];	//return the distance from src to ref
	else return -1;	//else return -1
}

int directed_graph::distance_between(int src_lebel,int dst_lebel)
{
	int src_index,dst_index;
	
	src_index = vertices.index_of(src_lebel);
	dst_index = vertices.index_of(dst_lebel);
	
	if(src_index >= 0 && dst_index >= 0) return (*this)[src_index][dst_index];	//both lebels are valid so return distance
																				//order of index matters in directed graphs
	else return -1;		//else return -1										
}

int directed_graph::num_edges()
{
	int num = 0;
	int deg = this->get_degree();
	
	for(int i = 0 ; i < deg ; i++)
		for(int j = 0 ; j < deg ; j++)
			if((*this)[i][j] >= 0) num++;
			
	return num; //return thr number of edges
}

}

















