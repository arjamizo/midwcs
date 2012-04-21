#include "functions.h"

string generatorToStr(FiniteField *ff){
	stringstream ss;

	ss.width(6);
	ss << "gen=[";
	ss << ff->genToStr() << "]" << endl;
	return ss.str();
}

string elementsListToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount();

	for(int i=0; i<n; ++i){
		ss.width(4);
	    ss << ff->elementsLabelToStr(i);
	  	ss << "=[" << ff->elementToStr(i) << "]" << endl;
	}
	return ss.str();
}

string mulTabToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount(), k;

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			ss.width(4);
			if(i && j){
				k = 1 + (i+j-2) % (n-1);
			}else{
				k = 0;
			}
			ss << ff->elementsLabelToStr(k);
		}
		ss << endl;
	}
	return ss.str();
}

string addTabToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount(), k, x, y;

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			ss.width(4);
			if(i && j){
				if(i-j){
					x = min(i, j);
					y = max(i, j);
					k = (x + ff->getZech(y-x-1) - 1) % (n-1) + 1;
				}else{
					k = 0;
				}
			}else{
				k = i+j;
			}
			ss << ff->elementsLabelToStr(k);
		}
		ss << endl;
	}

	return ss.str();
}
