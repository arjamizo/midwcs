#include <iostream>
#include <iterator>
#include <fstream>
#include "functions.h"

using namespace std;

int main(){

    int M;
    int P=2;


    for(M=1; M<4; ++M){
		ofstream out("out.html");
		int *a0 = new int[M];
		mem_set(a0, 0, M);
		a0[0] = 1;
		int *gen = new int[M];

		FiniteField *ff = 0;
		for(int i=1; i<powa(P, M) && (!ff || !ff->isInitiated()); ++i){
			if(ff){
				delete ff;
				ff = 0;
			}
			int tmp=i, base;
			for(int j=M-1; j>-1; --j){
				base = (int)pow(2.0, j);
				if(tmp / base){
					gen[j] = 1;
				}else{
					gen[j] = 0;
				}
				tmp %= base;
			}
			ff = new FiniteField(P, M, a0, gen);
		}
		out << startHtml();
		if(ff && ff->isInitiated()){
			out << h3("Generator:") << generatorToStr(ff);
			out << hr() << h3("Zech tab:") << zechTabToStr(ff);
			out << hr() << h3("Element's list:") << elementsListToStr(ff);
			out << hr() << h3("Multiplication tab:") << mulTabToStr(ff);
			out << hr() << h3("Addition tab:") << addTabToStr(ff);
		}else{
			out << "Wrong generator!" << endl;
		}
		out << endHtml();

		if(ff){
			delete ff;
		}
		delete[] a0;
		delete[] gen;

		out.close();
		system("firefox out.html");
    }
    cout << "Success" << endl;
    return 0;
}

