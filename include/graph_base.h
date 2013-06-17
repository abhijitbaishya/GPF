#ifndef __GRAPH_BASE_
#define __GRAPH_BASE_

#include "gpf_vector.h"

//graph processing framework namespace
namespace gpf
{

/**
	Used to store the vertex set. Note that vertex set doesnot allows duplicate data.
*/
class vertex_set
{
	private:
		gpf_vector	lebels;	//a list of lebels
	public:
	//The constructor
		vertex_set();
		vertex_set(unsigned int num_vertex);
	//insert a new vertex with lebel : returns false if the lebel already exists
		bool 	add 		(int lebel);
	//delete a vertex and returns false if lebel was not found
		bool	rm			(int lebel);
	//returns the index of the lebeled vertex or -1 if not exist
		int 	index_of	(int lebel);
	//retuns the lebel of index-th vertex
		int 	lebel_of	(int index);
	//change the lebel of a vertex
		bool 	set_lebel	(int index, int lebel);
	//returns true if a lebel exists
		bool	exists		(int lebel);
	//returns if the set is empty
		bool	empty		();
	//size returns the size of the vertex set
		int 	size		();
	
};


/**
 *	It is a pure interface from which we will derive the directed_graph and undirected_graph
 *	subclasses.
 */
class graph_base
{
	public:
	//Boolean properties
		virtual bool empty			()  = 0;	//unusable
		virtual bool is_null		()	= 0;	//completely disconnected i.e. no edges
		//virtual bool is_complete	() 	= 0;
		virtual bool is_directed	() 	= 0;
		virtual bool is_undirected	() 	= 0;
		//virtual bool is_connected	()  = 0;	//whether the graph is connected
		
		virtual int num_vertices	() = 0;
		//virtual int num_edges		() = 0;
		
		/*
		The edge related functions are graph type dependent so dont include them here
		virtual bool is_edge		(int lebel) = 0;	//if an edge exists between ref vertex and lebel
		virtual bool is_edge		(int l1,int l2) = 0; //if an edge exists between l1 and l2
		*/
		
	//Start vertex is required for some algorithms
		virtual void set_ref_vertex	(int lebel) = 0;
	//returns the distance of index-th vertex's distance from ref vertex
		//virtual int  distance_to		(int index) = 0;
	//returns the distance from ref vertex to index-th vertex
		//virtual int  distance_from		(int index) = 0;
	//returns the distance between two vertices
		//virtual int  distance_between	(int src_index,int dst_index) = 0;
	//returns the number of adjacent vertex of the ref vertex
		//virtual void num_adjacent		()			= 0;
	//returns the number of adjacent vertex of the index-th vertex
		//virtual int  num_adjacent		(int index) = 0;
	//returns the index of the closest vertex from ref vertex
		//virtual int  closest			()			= 0;
	//returns the index of the closest vertex from the index-th vertex;
		//virtual int  closest			(int index) = 0;
	//adds a new vertex to the graph and returns its index
		//*virtual int  add_vertex			(int lebel)			= 0;
	//removes a vertex from the graph
		//*virtual void rm_vertex			(int lebel)			= 0;
	//adds an edge from ref to lebel
		//virtual void add_edge			(int lebel) = 0;
	//adds a new edge from src to dst
		//virtual void add_edge			(int src,int dst)  =0;
	//removes an edge from ref to lebel from the graph
		//virtual void rm_edge			(int lebel)  = 0;
	//removes an edge from src to dst
		//virtual void rm_edge			(int src,int dst)  = 0;
	//returns the array of adjacent vertex of the ref vertex
		//virtual int* get_adjacency		() = 0;
	//returns the adjacent vertex of the given vertex
		//virtual int* get_adjacency		(int index) = 0;
};


}







#endif