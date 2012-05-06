#include "FiniteField.h"


FiniteField::FiniteField(int p, int m, int *a0, int *generator) :
	p(p), m(m), n((int)pow((double)p, m)) {

	index = new int[n];

	this->generator = new int[m];
	mem_cpy(this->generator, generator, m);

    elements = new int*[n];
    for(int i=0; i<n; ++i)
        elements[i] = new int[m];

    initiated = generate(a0);

    if(initiated && n>2){
		zechArray = new int[n-2];
		initiated = fillZechArray();
    }else{
    	zechArray = 0;
    }

}

FiniteField::~FiniteField(){
	if(zechArray){
		delete[] zechArray;
	}

    for(int i=0; i<n; ++i){
        delete[] elements[i];
    }
    delete[] elements;
    delete[] generator;
    delete[] index;
}

string FiniteField::intArrayToStr(int *ar){
    stringstream ss;
    for(int j=0; j<m; ++j)
        ss << ar[j] << " ";
    return ss.str();
}

string FiniteField::elementsLabelToStr(int i){
	stringstream ss;
	if(i > 1){
		ss << "a<sup>";
		if(i > 2){
			ss << i-1;
		}
		ss<<"</sup>";
	}else{
		ss << i;
	}
	return ss.str();
}

