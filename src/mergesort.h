#ifndef MERGESORT_H
#define MERGESORT_H


#include "sortalgorithm.h"



class MergeSort : public SortAlgorithm {
public:
	MergeSort();

	virtual ~MergeSort();

	virtual void sort(int* values, int n) override;

protected:
	void virtual merge(int* values, int* tempValues, int begin, int mid, int end);

	void virtual divide(int* values, int* tempValues, int begin, int end);
};

#endif    // MERGESORT_H
