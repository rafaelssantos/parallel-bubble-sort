#include <iostream>
#include <string>
#include "logger.h"
#include "sortalgorithmtype.h"
#include "sortmanager.h"
#include "valuesmanager.h"

using namespace std;



int main(int argc, char* argv[]) {
	int max = 101;                                      // Valor máximo gerado
	int n = 10;                                         // Número total de elmentos
	bool verbose = false;                               // True para imprimir os vetores. False, caso contrário
	string filePath = "data";                           // Nome do arquivo gerado
	string logFilePath = "parallel-hybrid-sort.log";    // Nome do arquivo de log


	/******************************* Opções ***************************************/
	/******************************************************************************/

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
		} else if (option.compare("--log-enable") == 0 || option.compare("-L") == 0) {
			Logger::instance().setEnable(true);
		} else if (option.compare("--times") == 0 || option.compare("-t") == 0) {
			Logger::instance().setTimes(atoi(argv[++op]));
		} else if (option.compare("--help") == 0 || option.compare("-h") == 0) {
			cout << "[OPTION] = description\n";
			cout << "[--file] or       [-f] = Base data (in and out) file name\n";
			cout << "[--log-enable] or [-L] = Log enable\n";
			cout << "[--log] or        [-l] = Log file name\n";
			cout << "[--maximum] or    [-m] = Max value that can be generated\n";
			cout << "[--size] or       [-n] = Number of values\n";
			cout << "[--times] or      [-t] = Number of executions\n";
			cout << "[--verbose] or    [-v] = Display (or not) values\n";
			return 0;
		}
	}


	/******************************* Processamento ********************************/
	/******************************************************************************/

	int* generatedValues;    // Vetor de elementos
	int* orderedValues;      // Vetor de elementos ordenados

	cout << "Generating values............" << flush;
	generatedValues = ValuesManager::instance().generateRandom(n, max);
	ValuesManager::instance().save(filePath + "_unordered.txt", generatedValues, n);
	cout << "DONE\n" << flush;


	if (verbose) {
		cout << "\nGenerated values\n";
		ValuesManager::instance().print(generatedValues, n);
	}

	orderedValues = new int[n];

	if (Logger::instance().isEnable()) {
		while (Logger::instance().hasRepeatToExec()) {
			ValuesManager::instance().copy(orderedValues, generatedValues, n);
			cout << "Sorting......................" << flush;
			SortManager::instance().sort(SortAlgorithmType::SERIAL_HYBRID, orderedValues, n, 2);
			ValuesManager::instance().save(filePath + "_ordered.txt", orderedValues, n);
			cout << "DONE\n" << flush;
		}
	}

	else {
		ValuesManager::instance().copy(orderedValues, generatedValues, n);
		cout << "Sorting......................" << flush;
		SortManager::instance().sort(SortAlgorithmType::SERIAL_HYBRID, orderedValues, n, 2);
		ValuesManager::instance().save(filePath + "_ordered.txt", orderedValues, n);
		cout << "DONE\n" << flush;
	}



	if (verbose) {
		cout << "\nOrdered values\n";
		ValuesManager::instance().print(generatedValues, n);
		cout << "\n";
	}

	if (Logger::instance().isEnable()) {
		Logger::instance().save(logFilePath);
	}

	delete[] generatedValues;
	delete[] orderedValues;
	generatedValues = nullptr;
	orderedValues = nullptr;


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
