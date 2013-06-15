#define DEBUG
#include	"../include/simple_matrix.h"
#include	"../include/gpf_exceptions.h"
using namespace std;
using namespace gpf;


int main()
{
	simple_matrix simp(5);
	
	simp.dump_to_stdout();
	
	return 0;
	
}