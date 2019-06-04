#include <iostream>
#include <string>
#include "sortalgorithmtype.h"
#include "sortmanager.h"
#include "valuesmanager.h"


using namespace std;



int main(int argc, char* argv[]) {
	int max = 101;                             // Valor máximo gerado
	int n = 10;                                // Número total de elmentos
	bool verbose = false;                      // True para imprimir os vetores. False, caso contrário
	string filePath = "data";                  // Nome do arquivo gerado
	string logFilePath = "hybrid_sort.log";    // Nome do arquivo de log


	for (auto op = 0; op < argc; op++) {
		string option(argv[op]);

		if (option.compare("--verbose") == 0 || option.compare("-v") == 0) {
			verbose = true;
		} else if (option.compare("--file") == 0 || option.compare("-f") == 0) {
			filePath = argv[++op];
		} else if (option.compare("--size") == 0 || option.compare("-n") == 0) {
			n = atoi(argv[++op]);
		} else if (option.compare("--maximum") == 0 || option.compare("-m") == 0) {
			max = atoi(argv[++op]) + 1;
		} else if (option.compare("--log") == 0 || option.compare("-l") == 0) {
			logFilePath = argv[++op];
		}
	}



	int* values;    // Vetor de elementos

	cout << "Generating values............" << flush;
	values = ValuesManager::instance().generateRandom(n, max);
	ValuesManager::instance().save(filePath + "_unordered.txt", values, n);
	cout << "DONE\n" << flush;



	if (verbose) {
		cout << "\nGenerated values\n";
		ValuesManager::instance().print(values, n);
	}


	cout << "Sorting......................" << flush;
	SortManager::instance().sort(SortAlgorithmType::SERIAL_HYBRID, values, n, 2);
	ValuesManager::instance().save(filePath + "_ordered.txt", values, n);
	cout << "DONE\n" << flush;



	if (verbose) {
		cout << "\nOrdered values\n";
		ValuesManager::instance().print(values, n);
		cout << "\n";
	}



	//	int nthreads, tid;

	//	#pragma omp parallel num_threads(4)
	//	{
	//		#pragma omp for
	//		for(int i = 0; i < 32; i++){
	//			tid = omp_get_thread_num();
	//			printf("Hello World %d from thread = %d\n", i, tid);
	//		}

	//	}

	return 0;
}
