#include "vectormanipulator.h"

#include <random>
#include <iostream>
#include <fstream>

using namespace std;



VectorManipulator &VectorManipulator::instance() {
    static VectorManipulator instance;

    return instance;
}




int* VectorManipulator::generateUniform(int n, int max) {
    int* vector = nullptr;

    vector = new int[n];
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, max);


    for(auto i = 0; i < n; i++) {
        vector[i] =  distribution(generator);
    }

    return vector;
}




float* VectorManipulator::generateNormal(int n, float max) {
    float* vector = nullptr;

    vector = new float[n];
    default_random_engine generator;
    normal_distribution<float> distribution(0, max);


    for(auto i = 0; i < n; i++) {
        vector[i] =  distribution(generator);
    }

    return vector;
}




int* VectorManipulator::generatePoisson(int n, float mean) {
    int* vector = nullptr;

    vector = new int[n];
    default_random_engine generator;
    poisson_distribution<int> distribution(mean);

    for(auto i = 0; i < n; i++) {
        vector[i] =  distribution(generator);
    }

    return vector;
}



int*VectorManipulator::generateRandom(int n, int max) {
    int* vector = nullptr;

    vector = new int[n];
    random_device generator;


    for(auto i = 0; i < n; i++) {
        vector[i] =  generator() % (max + 1);
    }

    return vector;
}




void VectorManipulator::print(const int* vector, int n) {
    cout << "[";

    for(auto i = 0; i < n - 1; i++){
        cout << vector[i] << ", ";
    }
    cout << vector[n - 1];

    cout << "]";
}




void VectorManipulator::print(const float* vector, int n) {
    cout << "[";

    for(auto i = 0; i < n - 1; i++){
        cout << vector[i] << ", ";
    }
    cout << vector[n - 1];

    cout << "]";
}



void VectorManipulator::save(string filePath, int* vector, int n) {
    ofstream file(filePath);

    for(auto i = 0; i < n - 1; i++){
        file << vector[i] << "\n";
    }
    file << vector[n - 1];

    file.close();
}



void VectorManipulator::save(string filePath, float* vector, int n) {
    ofstream file(filePath);

    for(auto i = 0; i < n - 1; i++){
        file << vector[i] << "\n";
    }
    file << vector[n - 1];


    file.close();
}



VectorManipulator::VectorManipulator() {

}



VectorManipulator::~VectorManipulator() {

}
