#define DEBUG
#include	"../include/simple_matrix.h"
using namespace std;
using namespace gpf;


int main()
{
	simple_matrix simp(10);
	simple_matrix s(20);
	
	simp = s;
	
	cout<<simp<<endl;

	return 0;
}







