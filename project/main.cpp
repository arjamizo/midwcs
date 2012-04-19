 #include <iostream>
#include <iterator>
#include "FiniteField.h"
using namespace std;

string generateAddTab(){}

int main()
{
    const int M=3;
    const int P=2;
    const int N=8;

    int a0[] = {1, 0, 0};
    int gen[] = {1, 1, 0}; //=0*x^2 + 1*x + 1*1

    std::cout<<"a0=["; std::copy(a0,a0+3, std::ostream_iterator<int>(std::cout, ",")); std::cout<<"]\n";
    std::cout<<"gen=["; std::copy(gen,gen+3, std::ostream_iterator<int>(std::cout, ",")); std::cout<<"]\n\n";

    FiniteField ff(P,M, &a0[0], &gen[0]);

    for(int i=0; i<N; ++i){
    	cout.width(3);
        cout << ff.elementsLabelToStr(i);
    	cout << "=[" << ff.elementToStr(i) << "]" << endl;
    }
    return 0;
}
