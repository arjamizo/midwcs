#include <iostream>
#include <iterator>
#include <fstream>
#include "functions.h"

using namespace std;

int main(){
	ofstream out("out.html");

    int M ;
    int P=2;
    cout << "M(1, 8): ";
    cin >> M;

    int *a0 = new int[M];
    memset(a0, 0, M*sizeof(int));
    a0[0] = 1;
    int *gen = new int[M];

    FiniteField *ff = 0;

    for(int i=0; !ff || !ff->isInitiated(); ++i){
    	if(ff){
    		delete ff;
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
    out << "<html><head><style type=\"text/css\">td{ text-align: center; } </style></head><body>" << endl;
    if(ff->isInitiated()){
		out << "<b>Generator:</b><br/>\n" << generatorToStr(ff);
		out << "<br/><hr/>\n<b>Element's list:</b><br/>\n" << elementsListToStr(ff);
		out << "<br/><hr/>\n<b>Multiplication tab:</b><br/>\n" << mulTabToStr(ff);
		out << "<br/><hr/>\n<b>Addition tab:</b><br/>\n" << addTabToStr(ff);
    }else{
    	out << "Wrong generator!" << endl;
    }
    out << "</body></html>";

    delete ff;
    delete[] a0;
    delete[] gen;

    out.close();
    #ifdef _WIN32 || WIN32 || __WIN32 || __WIN32__
    system("firefox out.html");
    #else //maybe unix?
    system("firefox out.html&");
    #endif
    return 0;
}
