#include "opencv_gmm.h"
#include "arma_gmm.h"
#include <ctime>

const int NUM_TESTS = 20;


int main(int argc, char** argv)
{
	for (int t = 1; t <= NUM_TESTS; t++)
	{
		std::string REL_PATH = "../../setup/results/c" + std::to_string(NUM_CLUS) + "_t" + std::to_string(t) + "/";
		// Get the data from a file
		std::string dataFile = REL_PATH + "gmm.txt"; // by default
		std::string cvOutFile = REL_PATH + "cv_est_ms.txt"; // by default
		std::string armaOutFile = REL_PATH + "arma_est_ms.txt";; // by default

		// For timing
		std::string timeFile = REL_PATH + "time.txt";
		std::clock_t start;
		double duration;
		std::fstream fs;
		fs.open(timeFile, std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::cout << "Gaussions: " << NUM_CLUS << ", Test: " << t << std::endl;
		std::cout << "===========================================" << std::endl;
		start = std::clock();
		// Actually run opencv
		if (cvRun(dataFile, cvOutFile) < 0)
			std::cout << "Error with OpenCV Code" << std::endl << std::endl;
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "opencv: " << duration << '\n';
		fs << "opencv: " << duration << '\n';

		std::cout << std::endl << std::endl;
		std::cout << "===========================================" << std::endl;
		start = std::clock();
		// Actually run armadillo
		if (armaRun(dataFile, armaOutFile) < 0)
			std::cout << "Error with Arma Code" << std::endl << std::endl;
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "arma: " << duration << '\n';
		fs << "arma: " << duration << '\n';

		fs.close();
	}
	system("pause");
}
