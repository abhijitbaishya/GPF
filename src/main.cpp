#define DEBUG
#include	"../include/simple_matrix.h"
#include	"../include/gpf_exceptions.h"
#include    "../include/graph_base.h"
#include	"../include/directed_base.h"
using namespace std;
using namespace gpf;


int main()
{
	directed_base dir;
	
	dir.dump_to_stdout();
	
	cout<<"The graph is : "<<dir.is_null()<<"And : "<<dir.empty()<<endl;
	
	return 0;
	
}