#define DEBUG
#include	"../include/gpf_vector.h"

using namespace std;
using namespace gpf;

int main()
{
	gpf_vector vec(5);
	
	gpf_vector vec2(vec);
	
	cout<<vec<<vec2;
	
	cout<<vec.size()<<" "<<vec2.size()<<endl;
	cout<<vec.capacity()<<" "<<vec2.capacity()<<endl;
	
	return 0;
	
}







