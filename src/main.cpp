#include <omp.h>
#include <iostream>
#include "algorithmtype.h"
#include "sortmanager.h"
#include "valuesmanager.h"

using namespace std;

int main(int argc, char* argv[]) {
	int nThreads = 1;                            // Número de threads
	int nSubVector = 1;                          // Número de subvetores
	int maxValue = 100;                          // Valor máximo gerado
	int n = 10;                                  // Número total de elmentos
	int nValuesPerSubVector = n / nSubVector;    // Número de elementos por subvetor
	int* values;                                 // Vetor de elementos

	values = ValuesManager::instance().generateRandom(n, 100);


	cout << "Vetor Original\n";
	ValuesManager::instance().print(values, n);


	SortManager::instance().sort(AlgorithmType::MERGE_SORT, values, n);


	cout << "\nVetor Ordenado\n";
	ValuesManager::instance().print(values, n);
	cout << "\n";

	//	int nthreads, tid;

	//	#pragma omp parallel num_threads(4)
	//	{
	//		#pragma omp for
	//		for(int i = 0; i < 32; i++){
	//			tid = omp_get_thread_num();
	//			printf("Hello World %d from thread = %d\n", i, tid);
	//		}

	//	}

	//	return 0;
}
