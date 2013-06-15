#define DEBUG
#include	"../include/simple_matrix.h"
#include	"../include/gpf_exceptions.h"
using namespace std;
using namespace gpf;


int main()
{
	matrix_row row(5);
	
	for(int i=0;i<row.size();i++)
		row[i] = i;
	
	row.dump_to_stdout();
	
	row.rm(2);

	
	row.dump_to_stdout();
	
	return 0;
	
}