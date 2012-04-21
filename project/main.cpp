 #include <iostream>
#include <iterator>
#include "functions.h"

using namespace std;

int main(){
    const int M=5;
    const int P=2;

    int a0[] = {1, 0, 0, 0, 0, 0};
    int gen[] = {1, 0, 1, 0, 0, 1}; //=0*x^2 + 1*x + 1*1

    FiniteField *ff = new FiniteField(P,M, &a0[0], &gen[0]);

    if(ff->isInitiated()){
		cout << "\nGenerator:\n" << generatorToStr(ff);
		cout << "\nElement's list:\n" << elementsListToStr(ff);
		cout << "\nMultiplication tab:\n" << mulTabToStr(ff);
		cout << "\nAddition tab:\n" << addTabToStr(ff);
    }else{
    	cout << "Wrong generator!" << endl;
    }

    delete ff;
    return 0;
}
