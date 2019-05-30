#ifndef VECTORMANIPULATOR_H
#define VECTORMANIPULATOR_H


class VectorManipulator {
public:
    static VectorManipulator& instance();

    int* generateUniform(int n, int max);

    float* generateNormal(int n, float max);

    int* generatePoisson(int n, float mean);

    int* generateRandom(int n, int max);

    void print(const int* vector, int n);

    void print(const float* vector, int n);


private:
    VectorManipulator();

    ~VectorManipulator();
};

#endif // VECTORMANIPULATOR_H
