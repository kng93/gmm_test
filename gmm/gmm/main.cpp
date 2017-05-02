#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>
#include <fstream>

using namespace cv;
#define NUM_CLUS 5


//#include <opencv2/highgui.hpp>
int dataFromFile(std::string fn, Mat& samples)
{
	std::vector<float> val;
	double raw;

	// Get the data from the file
	std::ifstream dFile(fn);
	if (!dFile.is_open())
		return -1;

	while (dFile >> raw)
		val.push_back(raw);

	dFile.close();

	// Put the data into the matrix
	int num_points = val.size();
	samples = Mat::zeros(num_points, 1, CV_64FC1);
	for (int i = 0; i < num_points; i++)
		samples.at<double>(i) = val[i];

	return 0;
}


int main(int argc, char** argv)
{
	// Get the data from a file
	std::string dataFile("../../setup/gmm.txt"); // by default
	if (argc > 1)
		dataFile = argv[1];

	// Get data
	Mat samples;
	if (dataFromFile(dataFile, samples) < 0)
		return -1; // File didn't read properly

	
	//// Train expectation maximization
	Ptr<ml::EM> mdl = ml::EM::create();
	mdl->setClustersNumber(NUM_CLUS);
	mdl->trainEM(samples);

	// Get + print means
	Mat means = mdl->getMeans();
	std::cout << "Means: " << std::endl;
	for (int i = 0; i < NUM_CLUS; i++)
		std::cout << "\t" << means.at<double>(i) << std::endl;

	// Get + print covariance matrix
	std::vector<Mat> cov;
	for (int i = 0; i < NUM_CLUS; i++)
		cov.push_back(Mat::zeros(1, 1, CV_64FC1));
	mdl->getCovs(cov);
	std::cout << "\n\nSigmas: " << std::endl;
	for (int i = 0; i < NUM_CLUS; i++)
		std::cout << "\t" << cov[i].at<double>(0) << std::endl;

	system("pause");
}
