#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H



class SortAlgorithm {
public:
	SortAlgorithm();

	virtual ~SortAlgorithm();

	virtual void sort(int* values, int n) = 0;
};



#endif    // SORTALGORITHM_H
