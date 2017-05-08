#include "opencv_gmm.h"
#include "arma_gmm.h"

#define NUM_CLUS 5


int main(int argc, char** argv)
{
	// Get the data from a file
	std::string dataFile("../../setup/gmm.txt"); // by default
	std::string cvOutFile("../../setup/cv_est_ms.txt"); // by default
	std::string armaOutFile("../../setup/arma_est_ms.txt"); // by default
	if (argc > 3)
	{
		dataFile = argv[1];
		cvOutFile = argv[2];
		armaOutFile = argv[2];
	}

	std::cout << "===========================================" << std::endl;
	if (cvRun(dataFile, cvOutFile) < 0)
		std::cout << "Error with OpenCV Code" << std::endl << std::endl;

	std::cout << std::endl << std::endl;
	std::cout <<"===========================================" << std::endl;
	// Armadillo
	if (armaRun(dataFile, armaOutFile) < 0)
		std::cout << "Error with Arma Code" << std::endl << std::endl;

	system("pause");
}
