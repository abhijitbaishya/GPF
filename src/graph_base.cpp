#include "../include/graph_base.h"

namespace gpf
{
vertex_set::vertex_set():lebels()
{
}

vertex_set::vertex_set(unsigned int num_vertex):lebels(num_vertex)	//initialize the lebels
{
	//by default lebels are ascending numbers from 0
	for(int i = 0; i < num_vertex ; i++)
		lebels[i] = i;
}

int vertex_set::index_of(int lebel) const
{
	if(!exists(lebel)) return -1;	//if lebel doesnot exists then return -1
	
	for(int i = 0; i < lebels.size() ; i++)
		if(lebels[i] == lebel) return i;	//return the matched index
}

int vertex_set::lebel_of(int index) const
{
	if(index >= lebels.size() || (index < 0)) return -1;	//basic validation
	
	return lebels[index];
}

bool vertex_set::exists(int lebel) const
{
	for(int i = 0 ; i < lebels.size() ; i++)	//if lebel already exists then return false
		if(lebels[i] == lebel) return true;
	return false;
}

bool vertex_set::add(int lebel)
{
	for(int i = 0 ; i < lebels.size() ; i++)	//if lebel already exists then return false
		if(lebels[i] == lebel) return false;

	lebels.push_back(lebel);	//else add the vertex and return true
	return true;
}

bool vertex_set::rm(int lebel)
{
	if(!exists(lebel)) return false;	//if lebel does not exist return false
	
	try{
		lebels.rm(index_of(lebel));			//delete the lebel
	} catch(...)
	{
		return false;
	}
	return true;
}

bool vertex_set::set_lebel(int index,int lebel)
{
	if(index >= lebels.size() || index < 0) return false;
	if(exists(lebel)) return false;	//the lebel already exists
	
	lebels[index] = lebel;	//set new lebel
} 

bool vertex_set::empty() const
{
	return lebels.empty();
}

int vertex_set::size() const
{
	return lebels.size();	//returns the size of the vertex array
}

vertex_set& vertex_set::operator=(const vertex_set& copy)
{
	this->lebels = copy.lebels;
	return (*this);
}

void vertex_set::clear()
{
//release all the vertices
	lebels.clear();
}

}



