#ifndef HYBRIDSORT_H
#define HYBRIDSORT_H



class HybridSort {
public:
	HybridSort();

	virtual ~HybridSort();

	void sort(int* values, int n, int mergeMaxRecDepth);

	void sortParallel(int* values, int n, int mergeMaxRecDepth, int npForBubble);
};

#endif    // HYBRIDSORT_H
