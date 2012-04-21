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
	  	ss << "=[" << ff->elementToStr(i) << "]<br/>" << endl;
	}
	return ss.str();
}

string mulTabToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount(), k;

	ss << "<table border=1>" << endl;
	for(int i=0; i<n; ++i){
		ss << "<tr>" << endl;
		for(int j=0; j<n; ++j){
			if(i && j){
				k = 1 + (i+j-2) % (n-1);
			}else{
				k = 0;
			}
			ss << "<td>";
			ss << ff->elementsLabelToStr(k);
			ss << "</td>";
		}
		ss << endl;
		ss << "</tr>" << endl;
	}
	ss << "</table>" << endl;
	return ss.str();
}

string addTabToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount(), k, x, y;

	ss << "<table border=1>" << endl;
	for(int i=0; i<n; ++i){
		ss << "<tr>" << endl;
		for(int j=0; j<n; ++j){
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
			ss << "<td>";
			ss << ff->elementsLabelToStr(k);
			ss << "</td>";
		}
		ss << endl;
		ss << "</tr>" << endl;
	}
	ss << "</table>" << endl;

	return ss.str();
}
