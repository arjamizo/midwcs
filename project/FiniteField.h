#ifndef FINITEFIELD_H_
#define FINITEFIELD_H_

#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <iostream>

using namespace std;

extern "C"{
	int bin_to_dec(int *tab, int n);
}

class FiniteField {
private:
    const int p; //base
    const int m; //length
    const int n; //field size, p^m
    int **elements;
    int *generator, *zechArray, *index;
    bool initiated;

    string intArrayToStr(int *ar);
    int binToDec(int *ar);

    //fills array with Zech's logarithms, returns true if complete
    bool fillZechArray();

    //returns absolute value of modulo
    inline int absModulo(int v, int q)const{ int r = v%q; return (r<0 ? r+q : r); }

public:
    //initiates elements
    FiniteField(int p, int m, int *a0, int *generator);
    ~FiniteField();

    //fills elements table with values evaluated from formula s_{j+3}=s_{j}+s_{j+1}
    //return true if complete, unless false
    bool generate(int *a0);

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

    //return true if elements generated properly, unless false
    inline bool isInitiated()const{ return initiated; }

    //returns index of result
    int xorElements(int x, int y);

    //returns Zech(x)
    int getZech(int x);
};

#endif /* FINITEFIELD_H_*/
