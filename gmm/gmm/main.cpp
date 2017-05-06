#include "opencv_gmm.h"
#include "arma_gmm.h"

#define NUM_CLUS 5


int main(int argc, char** argv)
{
	// Get the data from a file
	std::string dataFile("../../setup/gmm.txt"); // by default
	std::string outFile("../../setup/est_ms.txt"); // by default
	if (argc > 2)
	{
		dataFile = argv[1];
		outFile = argv[2];
	}

	if (cvRun(dataFile, outFile) < 0)
		std::cout << "Error with OpenCV Code" << std::endl << std::endl;


	// Armadillo
	if (armaRun(dataFile, outFile) < 0)
		std::cout << "Error with Arma Code" << std::endl << std::endl;

	system("pause");
}
