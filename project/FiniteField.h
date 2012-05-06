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
	int abs_modulo(long int x, long int q);
	int add_elements(int x, int y, int *zech, int n);
	int	bin_to_dec(int *src, int n);
	int fill_zech_array(int *zech, int n, int m, int *index, int **elements, int *gen);
	int generate(int *a0, int *gen, int **elements, int *index, int n, int m);
	int get_zech(int *zech, int at, int m, int *index, int **elements);
	void mem_set(int *dst, int x, int n);
	void mem_cpy(int *dst, int *src, int n);
	int mul_elements(int x, int y, int n);
	int powa(long int x, int y);
	int xor_elements(int *x, int *y, int m, int *index);
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
    inline int binToDec(int *ar){ return bin_to_dec(ar, m); }

    //fills array with Zech's logarithms, returns true if complete
    inline bool fillZechArray(){ return fill_zech_array(zechArray, n, m, index, elements, generator); }

    //returns absolute value of modulo
    inline int absModulo(int x, int q){ return abs_modulo(x, q); }

public:
    //initiates elements
    FiniteField(int p, int m, int *a0, int *generator);
    ~FiniteField();

    //fills elements table with values evaluated from formula s_{j+3}=s_{j}+s_{j+1}
    //return true if complete, unless false
    inline bool generate(int *a0){ return ::generate(a0, generator, elements, index, n, m); }

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
    inline int xorElements(int x, int y){ return xor_elements(elements[x], elements[y], m, index); }

    //return index of result
    inline int addElements(int x, int y){ return add_elements(x, y, zechArray, n); }

    //return index of result
    inline int mulElements(int x, int y){ return mul_elements(x, y, n); }

    //returns Zech(x)
    inline int getZech(int x){ return get_zech(zechArray, x, m, index, elements); }
};

#endif /* FINITEFIELD_H_*/

