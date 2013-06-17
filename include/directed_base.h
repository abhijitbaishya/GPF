#ifndef __DIRECTED_BASE__
#define __DIRECTED_BASE__
#include 	"simple_matrix.h"
#include	"graph_base.h"

namespace gpf
{

class directed_base:public graph_base,public simple_matrix
{
	public:
		vertex_set	vertices;	//set of vertices
		int 		ref_index;	//used to store the reference vertex index (may be used for some algorithms)
	public:
	//The constructor
		directed_base();	//default constriuctor
		directed_base(unsigned int num_vertices);
	
	//see the graph_base class for description
		bool empty			();	//the graph is unusable
		bool is_null		();	//completely disconnected i.e. no edges (may be useful)
		bool is_directed	();
		bool is_undirected	();
		
		int  num_vertices			();				//returns the number of vertices of the graph
		
		void set_ref_vertex			(int lebel);	//sets the reference vertex
		int  add_vertex				(int lebel);	//adds a new vertex to the graph
		void rm_vertex				(int lebel);	//removes a vertex from the graph
		
	friend	std::ostream&	operator<<(std::ostream& out,directed_base& graph);	//later
};

}
#endif