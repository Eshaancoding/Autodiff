#include <iostream>
#include <vector>
#include <assert.h>
#include "coreEquation.h"
using namespace std;
class Matrix {
public:
    int height;
    int width;
    Variable *array; 
    // src/operationsMat.cpp
    Matrix (const int height, const int width); 
    // src/operationsMat.cpp
    void operator= (initializer_list<Variable> ar);
    void operator= (initializer_list<double> ar); 
}; 