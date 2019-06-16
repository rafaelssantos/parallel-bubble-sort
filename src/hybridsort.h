#ifndef HYBRIDSORT_H
#define HYBRIDSORT_H



class HybridSort {
public:
	HybridSort();

	virtual ~HybridSort();

	void sort(int* values, int n, int maxDepth);

	void sortParallel(int* values, int n, int maxDepth, int nThreads);
};

#endif    // HYBRIDSORT_H
