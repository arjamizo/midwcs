#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "FiniteField.h"

string startHtml();

string endHtml();

string startTable();

string endTable();

string startTr();

string endTr();

string startTd();

string endTd();

string startTh();

string endTh();

string br();

string hr();

string h3(string txt);

string generatorToStr(FiniteField *ff);

string elementsListToStr(FiniteField *ff);

string mulTabToStr(FiniteField *ff);

string addTabToStr(FiniteField *ff);

string zechTabToStr(FiniteField *ff);

#endif /* FUNCTIONS_H_ */
