#ifndef __DIRECTED_BASE__
#define __DIRECTED_BASE__
#include 	"simple_matrix.h"
#include	"graph_base.h"

namespace gpf
{

class directed_graph:public graph_base,public simple_matrix
{
	//the iterator class can access the private members
	friend class dfs_iterator;
	friend class bfs_iterator;
	
	private:
		vertex_set	vertices;	//set of vertices
		int 		ref_index;	//used to store the reference vertex index (may be used for some algorithms)
	public:
	//The destructor
		~directed_graph();
	//The constructor
	//the default constriuctor
		directed_graph();
	//constructor with number of vertices
		directed_graph(int num_vertices);
	//copy constructor
		directed_graph(const directed_graph& copy);
	
	//see the graph_base class for description
		bool empty			() const;		//the graph is unusable
		bool is_null		() const;		//completely disconnected i.e. no edges (may be useful)
		bool is_directed	() const;		//is the graph a directed graph
		bool is_complete	() const;		//is the graph a complete graph
		bool is_undirected	() const;		//is the graph an undirected graph
		
		int  num_vertices			() const;				//returns the number of vertices of the graph
		int  num_edges				() const;
		
		void set_ref_vertex			(int lebel);	//sets the reference vertex
		int  add_vertex				(int lebel);	//adds a new vertex to the graph
		void rm_vertex				(int lebel);	//removes a vertex from the graph
		
	//clear will empty this graph object
		void clear				();
	//returns the distance of index-th vertex's distance from ref vertex
		int  distance_to		(int lebel) const;
	//returns the distance from ref vertex to index-th vertex
		int  distance_from		(int lebel) const;
	//distance between two vertex
		int  distance_between	(int src_lebel,int dst_lebel) const;
		
	//returns the lebel of vertex with maximum in degree (lowest index if there are collisions), returns -1 if null graph
		int  max_indegree	();
	//returns the lebel of the vertex with minimum in degree (lowest index if there are collision)
		int  min_indegree	();
	//returns the lebel of vertex with maximum out degree (lowest index if there are collision)
		int  max_outdegree	();
	//returns the lebel of the vertex with maximum out (lowest index if there are collision)
		int  min_outdegree	();
	//returns the in degree of the vertex	
		int  indegree_of		(int lebel);
	//returns the out degree of the vertex
		int  outdegree_of	(int lebel);
		
	//assignment operator overloaded returns a persistant copy
		directed_graph&	operator=(const directed_graph& graph);
		
	private:
		//override the operator[] privately to prevent the user from using [] on directed_graph objects and instead
		//use manualy calling respective edge functions (but friend functions can still use this)
		gpf_vector&	operator[](int suffix) const;
		
		//inserter overloaded operator to output simple_graph object using << operator
		friend	std::ostream&	operator<<(std::ostream& out,directed_graph& graph);
		//input operator overloaded
		friend  std::istream& operator>>(std::istream& in, directed_graph& graph);
};

//The declaration for inserter operator overloaded function
std::ostream&	operator<<(std::ostream& out,directed_graph& graph);
//input operator overloaded
std::istream& operator>>(std::istream& in, directed_graph& graph);

}
#endif