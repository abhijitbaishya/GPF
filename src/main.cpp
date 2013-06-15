#define DEBUG
#include	"../include/simple_matrix.h"
#include	"../include/gpf_exceptions.h"
using namespace std;
using namespace gpf;


int main()
{
	matrix_row row(3);
	
	cout<<"The capacity of the row is :"<<row.capacity()<<endl
		<<"The size of the row is :"<<row.size()<<endl;
	
	row.insert(2,45);
row.insert(2,23);

	
	cout<<"The capacity of the row is :"<<row.capacity()<<endl
		<<"The size of the row is :"<<row.size()<<endl;
	
	row.dump_to_stdout();
	
	return 0;
	
}