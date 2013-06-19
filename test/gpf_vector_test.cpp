#define DEBUG
#include	"../include/gpf_vector.h"

using namespace std;
using namespace gpf;

int main()
{
	gpf_vector vec(17);
	
	gpf_vector vec2(4);
	
	vec.push_back(100);
	
	cout<<vec.size()<<" "<<vec2.size()<<endl;
	cout<<vec.capacity()<<" "<<vec2.capacity()<<endl;
	
	//This is our contribution to GPF project
	cout<<"We changed this line of code"<<endl;
	
	return 0;
	
}







