#ifndef __DIRECTED_BASE__
#define __DIRECTED_BASE__
#include 	"simple_matrix.h"
#include	"graph_base.h"

namespace gpf
{

class directed_base:public graph_base,public simple_matrix
{
	private:
		vertex_set	vertices;
		int 		ref_index;	//used to store the ref vertex index
	public:
	//The constructor
		directed_base();	//default constriuctor
		directed_base(unsigned int num_vertices);
	
	//see the graph_base class for description
		bool empty			();	//unusable
		bool is_null		();	//completely disconnected i.e. no edges
		bool is_directed	();
		bool is_undirected	();
		
		int  num_vertices		();
		
		//bool is_connected	();	//whether the graph is connected
		
		void set_ref_vertex			(int lebel);
		int  add_vertex				(int lebel);
		//void rm_vertex				(int lebel);
	friend	std::ostream&	operator<<(std::ostream& out,directed_base& graph);
};

}
#endif