 #include <iostream>
#include <iterator>
#include "FiniteField.h"
using namespace std;

//Tu byłem, Paweł

int main()
{
    const int M=3;
    const int P=2;
    int a0[]={1,0,0};
    int gen[]={1,1,0}; //=0*x^2 + 1*x + 1*1

    std::cout<<"a0=["; std::copy(a0,a0+3, std::ostream_iterator<int>(std::cout, ",")); std::cout<<"]\n";
    std::cout<<"gen=["; std::copy(gen,gen+3, std::ostream_iterator<int>(std::cout, ",")); std::cout<<"]\n";

    //memcpy(gen, a0, M*sizeof(int));
    FiniteField n(P,M, &a0[0], &gen[0]);
    cout<<"0="<<n.genToStr()<<endl;
    for(int i=0; i<8; ++i)
        cout << "a^"<<i<< "=[" << n.elementToStr(i) << "]" << endl;
    return 0;
}
