#include <iostream>
#include "vectormanipulator.h"

using namespace std;




int main() {
    int n = 10;
    int max = 100;
    int* vector = nullptr;

    vector = VectorManipulator::instance().generateRandom(n, max);

    VectorManipulator::instance().print(vector, n);
    delete[] vector;
    vector = nullptr;

    cin.get();
    return 0;
}
