#include "functions.h"

string startHtml(){
	return string("<html><head>\n"
					"<style type=\"text/css\">\n"
					"\t td, th{ text-align: center; }\n"
					"\t h3{ margin: 5px; }\n"
					"</style>\n"
				  "</head><body>\n");
}

string endHtml(){
	return string("</body></html>");
}

string startTable(){
	return string("\n<table border=1>\n");
}

string endTable(){
	return string("</table>\n");
}

string startTr(){
	return string("<tr>");
}

string endTr(){
	return string("</tr>\n");
}

string startTd(){
	return string("<td>");
}

string endTd(){
	return string("</td>");
}

string startTh(){
	return string("<th>");
}

string endTh(){
	return string("</th>");
}

string br(){
	return string("<br/>");
}

string hr(){
	return string("\n<hr/>\n");
}

string h3(string txt){
	return string("<h3>") + txt + string("</h3>\n");
}

string generatorToStr(FiniteField *ff){
	stringstream ss;

	ss << startTable() << startTr() << startTd();
	ss << ff->genToStr();
	ss << endTd() << endTr() << endTable();
	return ss.str();
}

string elementsListToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount();

	ss << startTable();
	for(int i=0; i<n; ++i){
		ss << startTr();
	    ss << startTh() << ff->elementsLabelToStr(i) << endTh();
	  	ss << startTd() << ff->elementToStr(i) << endTd();
	  	ss << endTr();
	}
	ss << endTable();
	return ss.str();
}

string mulTabToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount(), k;

	ss << startTable() << startTr() << startTh() << endTh();
	for(int i=0; i<n; ++i){
		ss << startTh() << ff->elementsLabelToStr(i) << endTh();
	}
	ss << endTr();
	for(int i=0; i<n; ++i){
		ss << startTr();
		ss << startTh() << ff->elementsLabelToStr(i) << endTh();
		for(int j=0; j<n; ++j){
			if(i && j){
				k = 1 + (i+j-2) % (n-1);
			}else{
				k = 0;
			}
			ss << startTd() << ff->elementsLabelToStr(k) << endTd();
		}
		ss << endTr();
	}
	ss << endTable();
	return ss.str();
}

string addTabToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount();

	ss << startTable() << startTr() << startTh() << endTh();
		for(int i=0; i<n; ++i){
			ss << startTh() << ff->elementsLabelToStr(i) << endTh();
		}
		ss << endTr();
		for(int i=0; i<n; ++i){
			ss << startTr();
			ss << startTh() << ff->elementsLabelToStr(i) << endTh();
		for(int j=0; j<n; ++j){
			ss << startTd() << ff->elementsLabelToStr(ff->addElements(i, j)) << endTd();
		}
		ss << endTr();
	}
	ss << endTable();

	return ss.str();
}

string zechTabToStr(FiniteField *ff){
	stringstream ss;
	int n = ff->getElementCount()-2;

	ss << startTable();
	for(int i=0; i<n; ){
		ss << startTr();
		for(int j=0; j<5 && i<n; ++i, ++j){
			ss << startTd() << ff->getZech(i) << endTd();
		}
		ss << endTr();
	}
	ss << endTable();

	return ss.str();
}
