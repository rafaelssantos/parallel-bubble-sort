#ifndef HYBRIDSORT_H
#define HYBRIDSORT_H



class HybridSort {
public:
	HybridSort();

	virtual ~HybridSort();

public:
	void sort(int* values, int n, int maxDepth);
};

#endif    // HYBRIDSORT_H
