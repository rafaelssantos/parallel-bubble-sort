#include <iostream>
#include "vectormanipulator.h"

using namespace std;




int main() {
    int n = 10;
    int max = 100;
    int* vector = nullptr;

    cout << "Generating vector.............";
    vector = VectorManipulator::instance().generateRandom(n, max);
    cout << "OK\n";

    cout << "Saving original vector........";
    VectorManipulator::instance().save("/home/rafaelssantos/teste.txt", vector, n);
    cout << "OK\n";

    delete[] vector;
    vector = nullptr;

    cin.get();
    return 0;
}
