#define DEBUG
#include	"../include/simple_matrix.h"
using namespace std;
using namespace gpf;


int main()
{
	simple_matrix simp(3);
	
	
	for(int i = 0 ; i < simp.get_mat_degree() ; i++)
		for(int j = 0; j < simp.get_mat_degree() ; j++ )
			simp[i][j] = 0.89;
	
	cout<<simp;
	
}







