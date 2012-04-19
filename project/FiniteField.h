#ifndef FINITEFIELD_H_
#define FINITEFIELD_H_

#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
//#todo o profilerze w sprawozdaniu

using namespace std;
class FiniteField {
private:
    const int p; //base
    const int m; //length
    const int n; //field size, p^m
    int **elements;
    int * const generator ; //thats const because generator is just copy of pointer

    string intArrayToStr(int *ar);

public:
    //initiates elements
    FiniteField(int p, int m, int *a0, int *generator);
    ~FiniteField();

    //fills elements table with values evaluated from formula s_{j+3}=s_{j}+s_{j+1}
    void generate(int *a0, int *generator);

    //returns the generator as string
    inline string genToStr(){ return intArrayToStr(generator); }

    //returns the i-th element as string
    inline string elementToStr(int i){ return intArrayToStr(elements[i]); }

    //returns element count
    inline int getElementCount()const { return n; }

    //returns element size
    inline int getElementSize()const { return m; }

    //return the i-th elment's label as string
    string elementsLabelToStr(int i);
};

#endif /* FINITEFIELD_H_*/
