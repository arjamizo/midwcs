 #include <iostream>
#include <iterator>
#include "functions.h"

using namespace std;

int main()
{
    const int M=3;
    const int P=2;

    int a0[] = {1, 0, 0};
    int gen[] = {1, 1, 0}; //=0*x^2 + 1*x + 1*1

    FiniteField *ff = new FiniteField(P,M, &a0[0], &gen[0]);

    cout << "\nGenerator:\n" << generatorToStr(ff);
    cout << "\nElement's list:\n" << elementsListToStr(ff);
    cout << "\nMultiplication tab:\n" << mulTabToStr(ff);

    delete ff;
    return 0;
}
