#include "FiniteField.h"

FiniteField::FiniteField(int p, int m, int *a0, int *generator) :
	p(p), m(m), n((int)pow((double)p, m)), generator(generator) {

    elements = new int*[n];
    for(int i=0; i<n; ++i)
        elements[i] = new int[m];

    generate(a0,generator);
}

FiniteField::~FiniteField(){
    for(int i=0; i<n; ++i){
        delete elements[i];
    }
    delete elements;
}

void FiniteField::generate(int *a0, int *generator) {
  	memset(elements[0], 0, m*sizeof(int));
    memcpy(elements[1], a0, m*sizeof(int));

    for(int i=2; i<n; ++i) {
        memcpy(elements[i], elements[i-1]+1, (m-1)*sizeof(int));
        int sum=0;
        for(int j=0; j<m; ++j) {
                sum+=generator[j]*elements[i-1][j];
        }
        elements[i][m-1] = sum % 2;
    }
}

string FiniteField::intArrayToStr(int *ar){
    stringstream ss;
    for(int j=0; j<m; ++j)
        ss << ar[j] << " ";
    return ss.str();
}

string FiniteField::elementsLabelToStr(int i){
	stringstream ss;
	if(i){
		ss << "a^" << i-1;
	}else{
		ss << i;
	}
	return ss.str();
}
