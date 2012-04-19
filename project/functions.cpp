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
	int n = ff->getElementCount();

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			ss.width(4);
			ss << ff->elementsLabelToStr((i+j) % n);
		}
		ss << endl;
	}
	return ss.str();
}
