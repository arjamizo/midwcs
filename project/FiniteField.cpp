#include "FiniteField.h"


FiniteField::FiniteField(int p, int m, int *a0, int *generator) :
	p(p), m(m), n((int)pow((double)p, m)) {

	index = new int[n];

	this->generator = new int[m];
	memcpy(this->generator, generator, m*sizeof(int));

    elements = new int*[n];
    for(int i=0; i<n; ++i)
        elements[i] = new int[m];

    initiated = generate(a0);

    zechArray = new int[n-2];
    fillZechArray();
}

FiniteField::~FiniteField(){
	delete[] zechArray;

    for(int i=0; i<n; ++i){
        delete[] elements[i];
    }
    delete[] elements;
    delete[] generator;
    delete[] index;
}

bool FiniteField::generate(int *a0) {
	int num;
	memset(index, 0, n*sizeof(int));
	index[0] = 0;

  	memset(elements[0], 0, m*sizeof(int));
    memcpy(elements[1], a0, m*sizeof(int));
    index[binToDec(a0)] = 1;

    for(int i=2; i<n; ++i) {
        memcpy(elements[i], elements[i-1]+1, (m-1)*sizeof(int));
        int sum=0;
        for(int j=0; j<m; ++j) {
                sum += generator[j] * elements[i-1][j];
        }
        elements[i][m-1] = sum % 2;

        num = binToDec(elements[i]);
        if(index[num]){
        	return false;
        }else{
        	index[num] = i;
        }
    }
    return true;
}

string FiniteField::intArrayToStr(int *ar){
    stringstream ss;
    for(int j=0; j<m; ++j)
        ss << ar[j] << " ";
    return ss.str();
}

int FiniteField::binToDec(int *ar){
	int result=0;
	int  base=1;

	for(int i=0; i<m; ++i){
		result += base*ar[i];
		base *= p;
	}
	return result;
}

string FiniteField::elementsLabelToStr(int i){
	stringstream ss;
	if(i > 1){
		ss << "a";
		if(i > 2){
			ss << i-1;
		}
	}else{
		ss << i;
	}
	return ss.str();
}

void FiniteField::fillZechArray(){
	int filled=3, x=1, k, v, q=n-1, zech;
	memset(zechArray, 0, (n-2)*sizeof(int));

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
}

int FiniteField::getZech(int x){
	if(zechArray[x]){
		return zechArray[x];
	}

	return xorElements(1, 2+x)-1;
}

int FiniteField::xorElements(int x, int y){
	int result=0, base=1;

	for(int i=0; i<m; ++i){
		result += base*(elements[x][i] xor elements[y][i]);
		base *= 2;
	}
	return index[result];
}
