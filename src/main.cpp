#include <iostream>
#include <string>
#include "datamanipulator.h"

using namespace std;




int main() {
    int n = 10;
    int max = 100;
    int* input = nullptr;
    int* output = nullptr;
    string filePath = "/home/rafaelssantos/teste.txt";

    cout << "Generating values .............";
    input = DataManipulator::instance().generateRandom(n, max);
    cout << "Done\n";
    cout << "Saving values .................";
    DataManipulator::instance().save(filePath, input, n);
    cout << "Done\n";

    cout << "Reading values ................";
    output = DataManipulator::instance().read(filePath, &n);
    cout << "Done\n";


    cout << "\n\nINPUT:  ";
    DataManipulator::instance().print(input, n);
    cout << "\nOUTPUT: ";
    DataManipulator::instance().print(output, n);

    delete[] output;
    input = nullptr;
    delete[] input;
    input = nullptr;

    cin.get();
    return 0;
}
