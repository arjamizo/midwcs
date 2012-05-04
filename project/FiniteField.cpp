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

    if(initiated){
		zechArray = new int[n-2];
		initiated = fillZechArray();
    }

}

FiniteField::~FiniteField(){
	if(initiated){
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

bool FiniteField::fillZechArray(){
	int filled=3, x=1, k, v, q=n-1, zech;
	mem_set(zechArray, 0, n-2);

	for(x=0; !generator[x+1] && x<m-1; ++x);
	zechArray[x] = m;

	for(int y=x; filled < n; ++y){
		if(x != y){
			while(zechArray[y] && ++y);
		}
		zech = getZech(y);

		for(int i=0;; ++i){
			k = absModulo((q-y-1)*(int)pow(2.0, i), q) - 1;

			if(zechArray[k]){
				break;
			}

			v = absModulo((zech-y-1)*(int)pow(2.0, i), q);
			zechArray[k] = v;
			++filled;
		}
		for(int i=1;; ++i){
			k = absModulo((y+1)*(int)pow(2.0, i), q) - 1;

			if(zechArray[k]){
				break;
			}

			v = absModulo(zech*(int)pow(2.0, i), q);
			zechArray[k] = v;
			++filled;
		}
	}
	if(filled != n){
		return false;
	}
	return true;
}
