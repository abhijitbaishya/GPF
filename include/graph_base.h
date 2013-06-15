#ifndef __GRAPH_BASE_
#define __GRAPH_BASE_

//graph processing framework namespace
namespace gpf
{

/**
 *	It is a pure interface from which we will derive the directed_graph and undirected_graph
 *	subclasses.
 */
class graph_base
{
	public:
	//Boolean properties
		virtual bool is_null		()	= 0;
		virtual bool is_complete	() 	= 0;
		virtual bool is_directed	() 	= 0;
		virtual bool is_undircted	() 	= 0;
		virtual bool is_connected	()  = 0;
	
	//Start vertex is required for some algorithms
		virtual void set_start_vertex	(int index) = 0;
	//returns the distance of index-th vertex's distance from start vertex
		virtual int  distance_to		(int index) = 0;
	//returns the distance from start vertex to index-th vertex
		virtual int  distance_from		(int index) = 0;
	//returns the distance between two vertices
		virtual int  distance_between	(int src_index,int dst_index) = 0;
	//returns the number of adjacent vertex of the start vertex
		virtual void num_adjacent		()			= 0;
	//returns the number of adjacent vertex of the index-th vertex
		virtual int  num_adjacent		(int index) = 0;
	//returns the index of the closest vertex from start vertex
		virtual int  closest			()			= 0;
	//returns the index of the closest vertex from the index-th vertex;
		virtual int  closest			(int index) = 0;
	//adds a new vertex to the graph and returns its index
		virtual int  add_vertex			()			= 0;
	//adds a new edge between two vertices
		virtual void add_edge			(int src_index,int dst_index)  =0;
	//returns the array of adjacent vertex of the start vertex
		virtual int* get_adjacency		() = 0;
	//returns the adjacent vertex of the given vertex
		virtual int* get_adjacency		(int index) = 0;
}


}







#endif