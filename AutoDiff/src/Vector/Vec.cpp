#include "Vector.hpp"

Vector::Vector (int width) {
    this->array = new Variable[width]; 
    this->width = width;
}

Vector::Vector () {
    this->width = -1;
}