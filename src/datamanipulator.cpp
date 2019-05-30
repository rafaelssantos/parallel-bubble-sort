#include "datamanipulator.h"

#include <random>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



DataManipulator &DataManipulator::instance() {
    static DataManipulator instance;

    return instance;
}




int* DataManipulator::generateUniform(int n, int max) {
    int* values = nullptr;

    values = new int[n];
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, max);


    for(auto i = 0; i < n; i++) {
        values[i] =  distribution(generator);
    }

    return values;
}





int* DataManipulator::generatePoisson(int n, float mean) {
    int* values = nullptr;

    values = new int[n];
    default_random_engine generator;
    poisson_distribution<int> distribution(mean);

    for(auto i = 0; i < n; i++) {
        values[i] =  distribution(generator);
    }

    return values;
}



int*DataManipulator::generateRandom(int n, int max) {
    int* values = nullptr;

    values = new int[n];
    random_device generator;


    for(auto i = 0; i < n; i++) {
        values[i] =  generator() % (max + 1);
    }

    return values;
}




void DataManipulator::print(const int* values, int n) {
    cout << "[";

    for(auto i = 0; i < n - 1; i++){
        cout << values[i] << ", ";
    }
    cout << values[n - 1];

    cout << "]";
}




void DataManipulator::save(string filePath, int* values, int n) {
    ofstream file(filePath);

    for(auto i = 0; i < n - 1; i++){
        file << values[i] << "\n";
    }
    file << values[n - 1];

    file.close();
}



int* DataManipulator::read(string filePath, int* n) {
    ifstream file(filePath);
    vector<int> tempValues;
    int value;

    while(file.peek() != EOF){
        file >> value;
        tempValues.push_back(value);
    }

    int* values = new int[tempValues.size()];
    for(auto i = 0u; i < tempValues.size(); i++) {
        values[i] = tempValues[i];
    }
    *n = static_cast<int>(tempValues.size());

    file.close();

    return values;
}




DataManipulator::DataManipulator() {

}



DataManipulator::~DataManipulator() {

}
