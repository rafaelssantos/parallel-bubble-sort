#ifndef DATAMANIPULATOR_H
#define DATAMANIPULATOR_H

#include <string>


class DataManipulator {
public:
    static DataManipulator& instance();

    int* generateUniform(int n, int max);

    int* generatePoisson(int n, float mean);

    int* generateRandom(int n, int max);

    void print(const int* values, int n);

    void save(std::string filePath, int* values, int n);

    int* read(std::string filePath, int* n);


private:
    DataManipulator();

    ~DataManipulator();
};

#endif // DATAMANIPULATOR_H
