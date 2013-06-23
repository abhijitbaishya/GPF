#include 	"../include/directed_graph.h"
#include	<stdio.h>


namespace gpf
{
std::istream& operator>>(std::istream& in, directed_graph& graph)
{
	int num_vertex;
	int temp_lebel;
	
	//first of all clear the previous contrnts
	graph.clear();

	std::cout<<std::endl<<"[GPATH INPUT :]"<<std::endl
			 <<"Number of vertices : ";
	in>>num_vertex;
	
	for(int i = 0 ; i < num_vertex ; i++)
	{	
		//try to get
		while(1)
		{
			try
			{
			//prompt users
				std::cout<<"Enter the lebel for "<<i<<"-th vertex :";
			//store the temp_lebel
				in>>temp_lebel;
			//try to add the vertex to the graph
				graph.add_vertex(temp_lebel);
			//if everything goes well break
				break;
			}catch(...)
			{
			//something went wrong so alert user
				std::cout<<"The lebel already exists, try again!"<<std::endl;
			//we did not break here so while loop will not terminate here
			}
		}
	}
	std::cout<<std::endl<<"Enter the adjacency matrix :"<<std::endl<<std::endl;
	
	for(int  i = 0 ; i < num_vertex ; i++)
		for(int j = 0 ; j < num_vertex ; j++)
			in>>graph[i][j];
			
	std::cout<<"[END OF INPUT]"<<std::endl<<std::endl;
	return in;
}
std::ostream&	operator<<(std::ostream& out,directed_graph& graph)
{
	char num_digit[10];
	
	if(graph.empty()) { out<<std::endl<<"<EMPTY>"<<std::endl; return out; }

	//get the degree of the graph
	int deg = graph.get_mat_degree();
	
	int max_lebel = 0, max_edge = 0, max_val;
	
	for(int i = 0 ; i < graph.vertices.size() ; i++)
		if(graph.vertices.lebel_of(i) > max_lebel) max_lebel = graph.vertices.lebel_of(i);
	
	for(int i = 0 ; i < deg ; i++)
		for(int j = 0 ; j < deg ; j++)
			if(graph[i][j] > max_edge) max_edge = graph[i][j];
			
	max_val = max_lebel > max_edge ? max_lebel : max_edge;
	
	sprintf(num_digit,"%f",max_val);
	
	int space = 1+strlen(num_digit);
	
	
	out<<std::endl;
	out<<'+';
	for(int i = 0 ; i <= deg ; i++)
		for(int k = space ; k >= 0 ; k--)
				(k == 0) ? out<<'+' : out<<'-';
				
	out<<std::endl<<'|';
	
	out.fill(' ');
	out.width(space);
	out<<'#';
	out<<'|';
	
	
	for(int i = 0 ; i < deg ; i++)
	{
		out.fill(' ');
		out.width(space);
		out<<graph.vertices.lebel_of(i);
		out<<'|';
	}
	out<<std::endl<<'+';
	for(int i = 0 ; i <= deg ; i++)
		for(int k = space ; k >= 0 ; k--)
				(k == 0) ? out<<'+' : out<<'-';
				
	out<<std::endl;
	
	for(int i = 0 ; i < deg ; i++)
	{
		out<<'|';
		out.fill(' ');
		out.width(space);
		out<<graph.vertices.lebel_of(i);
		out<<'|';
		for(int j = 0 ; j < deg ; j++)
		{
			out.fill(' ');
			out.width(space);
			out<<graph[i][j];
			out<<'|';
		}
		out<<std::endl<<'+';
		for(int i = 0 ; i <= deg ; i++)
			for(int k = space ; k >= 0 ; k--)
				(k == 0) ? out<<'+' : out<<'-';
				
		out<<std::endl;
	}
	return out;
}

directed_graph::~directed_graph()
{
	
}

directed_graph::directed_graph():vertices(0)
{
	ref_index = 0;	//by default start index is 0
}

directed_graph::directed_graph(int num_vertices):
				simple_matrix(num_vertices),	//initialize the edges (initially null)
				vertices(num_vertices)			//initialize the vertices (by default lebeled 0,1,2,3,....)
{
	ref_index = 0;
}

directed_graph::directed_graph(const directed_graph& copy)
{
	//copy the vertices
	this->vertices = copy.vertices;
}

bool directed_graph::empty() const
{
	//return false is vertices as well as edges are empty
	return vertices.empty() && simple_matrix::empty();
}

//returns true if null graph
bool directed_graph::is_null() const
{
	int deg = get_mat_degree();	//get the degree of the edge matrix
	int i , j;
	
	if(deg == 0) return false;
	
	for(i = 0; i< deg ; i++)
		for(j = 0; j < deg ; j++)
			if((*this)[i][j] != 0) return false;
	return true;
	
}

bool directed_graph::is_directed() const { return true; }
bool directed_graph::is_undirected() const { return false; }

void directed_graph::set_ref_vertex(int lebel)
{
	int i = vertices.index_of(lebel);	//find the index of the vertex
	if(i == -1) throw new exc_invalid_operation();	//illegal : lebel not found
	this->ref_index = i;	//store for future use
}

int directed_graph::num_vertices() const
{
	return vertices.size();	//erturns the number of vertices
}

bool directed_graph::is_complete() const
{
	int deg = get_mat_degree();	//get the degree of the incidence matrix
	for(int i = 0 ; i < deg ; i++)
		for(int j = 0 ; j < deg ; j++)
		{
			if( i == j) continue;	//ignore self loops
			if((*this)[i][j] < 1) return false;
		}
	return true;	//if we did not find a disconnection then return true
}

int directed_graph::distance_to(int lebel) const
{
	if(	vertices.size() == 0 ||				//if start_index is out of bounds or there are no vertices 
		ref_index >= vertices.size()) throw new exc_invalid_operation();
	
	int dst_index = vertices.index_of(lebel);
	if(dst_index >= 0) return (*this)[ref_index][dst_index];	//note that distance may be 0 but may not -ve
	else
		return -1;		//no edge was found
}

int directed_graph::distance_from(int lebel) const
{
	if(	vertices.size() == 0 ||				//if start_index is out of bounds or there are no vertices 
		ref_index >= vertices.size()) throw new exc_invalid_operation();
		
	int src_index = vertices.index_of(lebel);	//find the index of lebel
	
	if(src_index >= 0) return (*this)[src_index][ref_index];	//return the distance from src to ref
	else return -1;	//else return -1
}

int directed_graph::distance_between(int src_lebel,int dst_lebel) const
{
	int src_index,dst_index;
	
	src_index = vertices.index_of(src_lebel);
	dst_index = vertices.index_of(dst_lebel);
	
	if(src_index >= 0 && dst_index >= 0) return (*this)[src_index][dst_index];	//both lebels are valid so return distance
																				//order of index matters in directed graphs
	else return -1;		//else return -1										
}

int directed_graph::num_edges() const
{
	int num = 0;
	int deg = this->get_mat_degree();
	
	for(int i = 0 ; i < deg ; i++)
		for(int j = 0 ; j < deg ; j++)
			if((*this)[i][j] >= 0) num++;
			
	return num; //return thr number of edges
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

gpf_vector& directed_graph::operator[] (int suffix) const
{
	return simple_matrix::operator[](suffix);
}

directed_graph& directed_graph::operator=(const directed_graph& graph)
{
	//degree of this graph
	int this_deg = this->get_mat_degree();
	//degree of the input graph
	int src_deg  = graph.get_mat_degree();

	
	//if the input graph is empty
	if(graph.empty())
	{
	//clear this graph
		this->clear();
	//return this object
		return (*this);
	}
	
	//clear this object
	this->clear();
	
	//copy the vertex set
	this->vertices = graph.vertices;

	//make this graph large enough to accomodate input graph
	for(int i = 0 ; i < src_deg ; i++)
		this->add_degree();
	
	//now copy each row from the input graph
	for(int i = 0 ; i < src_deg ; i++)
		(*this)[i] = graph[i];
	
	return (*this);
}

void directed_graph::clear()
{
//IMPORTANT : first edges should be released because some function uses vertex_set size in simple_matrix class
	simple_matrix::clear();
//now clear the vertices
	this->vertices.clear();
}

int directed_graph::max_indegree()
{
	int max = 0 , temp = 0 , index = -1;
	int deg = this->get_mat_degree();
	
	//search from extream righ column
	for( int colm = deg -1 ; colm >= 0 ; colm++)
	{
		temp = 0;	//to hold the no of incomming connections
		for( int row = 0 ; row < deg ; row++)
		{
			//ignore all sel loops
			if(row == colm) continue; 
			//increment temp if there is a connection from j to i (incomming)
			//notice column is fixed for this loop because our matrix is row major ().
			temp += ((*this)[row][colm] > 0 ) ? 1 : 0;
		}
		//if temp (incomming) is greater than the previous max store the corresponding index else do nothing
		index = temp > max ? colm : index;
		//update the new max (number of incomming connections)
		max	  = temp > max ? temp : max;
	}
	
	return (index == -1 ? index : vertices.lebel_of(index));
}

int directed_graph::min_indegree()
{
	int min = 0 , temp = 0 , index = -1;
	int deg = this->get_mat_degree();
	
	//search from extream righ column
	for( int colm = deg -1 ; colm >= 0 ; colm++)
	{
		temp = 0;	//to hold the no of incomming connections
		for( int row = 0 ; row < deg ; row++)
		{
			//ignore all sel loops
			if(row == colm) continue; 
			//increment temp if there is a connection from j to i (incomming)
			//notice column is fixed for this loop because our matrix is row major ().
			temp += ((*this)[row][colm] > 0 ) ? 1 : 0;
		}
		//if temp (incomming) is greater than the previous min store the corresponding index else do nothing
		index = temp < min ? colm : index;
		//update the new min (number of incomming connections)
		min	  = temp < min ? temp : min;
	}
	
	return (index == -1 ? index : vertices.lebel_of(index));
}

int directed_graph::max_outdegree()
{
	int max = 0 , temp = 0 , index = -1;
	int deg = this->get_mat_degree();
	
	//search from bottom row
	for( int row = deg -1 ; row >= 0 ; row++)
	{
		temp = 0;	//to hold the no of incomming connections
		for( int colm = 0 ; colm < deg ; colm++)
		{
			//ignore all sel loops
			if(row == colm) continue; 
			//increment temp if there is a connection from j to i (incomming)
			//notice column is fixed for this loop because our matrix is row major ().
			temp += ((*this)[row][colm] > 0 ) ? 1 : 0;
		}
		//if temp (incomming) is greater than the previous max store the corresponding index else do nothing
		index = temp > max ? row : index;
		//update the new max (number of incomming connections)
		max	  = temp > max ? temp : max;
	}
	
	return (index == -1 ? index : vertices.lebel_of(index));
}

int directed_graph::min_outdegree()
{
	int min = 0 , temp = 0 , index = -1;
	int deg = this->get_mat_degree();
	
	//search from bottom row
	for( int row = deg -1 ; row >= 0 ; row++)
	{
		temp = 0;	//to hold the no of incomming connections
		for( int colm = 0 ; colm < deg ; colm++)
		{
			//ignore all sel loops
			if(row == colm) continue; 
			//increment temp if there is a connection from j to i (incomming)
			//notice column is fixed for this loop because our matrix is row major ().
			temp += ((*this)[row][colm] > 0 ) ? 1 : 0;
		}
		//if temp (incomming) is greater than the previous min store the corresponding index else do nothing
		index = temp < min ? row : index;
		//update the new min (number of incomming connections)
		min	  = temp < min ? temp : min;
	}
	
	return (index == -1 ? index : vertices.lebel_of(index));
}

int directed_graph::indegree_of(int lebel)
{
	//get the degree of this matrix
	int deg   = this->get_mat_degree();
	//find the index of this lebel
	int index = vertices.index_of(lebel);
	//return val
	int ret = 0;
	
	if(index == -1) return -1;
	
	//increment ret if we found an incomming connection
	for(int i = 0 ; i < deg ; i++)
		ret += (*this)[i][index] > 0 ? 1 : 0;
	
	return ret;
}

int directed_graph::outdegree_of(int lebel)
{
	//get the degree of this matrix
	int deg   = this->get_mat_degree();
	//find the index of this lebel
	int index = vertices.index_of(lebel);
	//return val
	int ret = 0;
	
	//the lebel was not found
	if(index == -1) return -1;
	
	//increment ret if we found an outgoing connection
	for(int i = 0 ; i < deg ; i++)
		ret += (*this)[index][i] > 0 ? 1 : 0;
	
	return ret;
}


}

















