#include "hybridsort.h"


#include <mpi.h>
#include <cmath>
#include <iostream>

#include "bubblesort.h"
#include "logger.h"
#include "mergesort.h"



HybridSort::HybridSort() {
}





HybridSort::~HybridSort() {
}



void HybridSort::sort(int* values, int n, int maxDepth) {
	int nParts = static_cast<int>(pow(2, maxDepth));
	int nPerPart = n / nParts;

	Logger::instance().start(0);
	Logger::instance().start(1);

	BubbleSort bubble;
	for (auto i = 0; i < nParts; i++) {
		bubble.sort((values + i * nPerPart), nPerPart);
	}
	Logger::instance().stop(1, "Bubble");

	Logger::instance().start(1);
	MergeSort merge;
	merge.partialSort(values, n, maxDepth);
	Logger::instance().stop(1, "Merge");

	Logger::instance().stop(0, "Total");
}



void HybridSort::sortParallel(int* values, int n, int maxDepth, int nThreads) {
	int nPerPart;
	int rank;
	int worldSize;

	//	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

	nPerPart = n / worldSize;
	int localValues[nPerPart];

	BubbleSort bubble;
	//	std::cout << "Here :" << rank << " " << n << " " << nPerPart << "\n";

	MPI_Scatter(values, nPerPart, MPI_INT, localValues, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);
	bubble.sort(localValues, nPerPart);

	MPI_Gather(localValues, nPerPart, MPI_INT, values, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);



	//	MPI_Gather(localValues, nPerPart, MPI_INT, values, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);
	//	MPI_Scatter(values, nPerPart, MPI_INT, localValues, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);


	//	if (rank == 0) {
	//		Logger::instance().start(0);
	//		Logger::instance().start(1);
	//	}




	//	Logger::instance().stop(1, "Bubble");

	//	MergeSort merge;
	//	Logger::instance().start(1);
	//	merge.partialSortParallel(values, n, maxDepth);

	//	Logger::instance().stop(1, "Merge");
	//	Logger::instance().stop(0, "Total");

	if (rank == 0) {
		std::cout << "N =" << n << "\n";
		for (auto i = 0; i < n; i++) {
			std::cout << values[i] << "\n";
		}
	}

	//	delete[] localValues;
}
