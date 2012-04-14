#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <stdio.h>
//#todo o profilerze w sprawozdaniu

using namespace std;
class FiniteField {
    const int p; //base
    const int m; //length
    const int n; //field size, p^m
    int **elements;
    int * const generator ; //thats const because generator is just copy of pointer
    public:
    /*
    generates table http://google.com/search?q=lab_k2.pdf+"rozszerzonego w postaci wektorowej" page 2
    */
    FiniteField(int p, int m, int *a0, int *generator):p(p),m(m),n((int)pow((double)p,m)),generator(generator) {
        elements=new int*[n];
        for(int i=0; i<n; ++i)
            elements[i]=new int[m];
        for(int i=0; i<n; ++i)
                for(int j=0; j<m; ++j)
                    elements[i][j]=22;
                    ;

        generate(a0,generator);
    }
    ~FiniteField()
    {
        for(int i=0; i<n; ++i)
            delete elements[i];
        delete elements;
    }
    /*
    fills elements table with values evaluated from formula s_{j+3}=s_{j}+s_{j+1}
    */
    void generate(int *a0, int *generator) {
        memcpy(elements[0], a0, m*sizeof(int));
        for(int i=1; i<n; ++i) {
            memcpy(elements[i],elements[i-1]+1,(m-1)*sizeof(int));
            int sum=0;
            for(int j=0; j<m; ++j) {
                    sum+=generator[j]*elements[i-1][j];
            }
            elements[i][m-1]=sum%2;
        }
    }
    private: string intArrayToStr(int *ar)
    {
        stringstream ss;
        for(int j=0; j<m; ++j)
            ss<<ar[j]<<" ";
        return ss.str();
    }
    public:
    /*
        returns the generator as string
    */
    string genToStr() {
        return intArrayToStr(generator);
    }
    /*
        returns the i-th element as string
    */
    string elementToStr(int i) {
        return intArrayToStr(elements[i]);
    }
};
