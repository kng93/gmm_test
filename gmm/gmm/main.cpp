#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <string>
#include <fstream>

using namespace cv;
#define NUM_CLUS 5


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

int outputData(std::string fn, Mat means, Mat weights, std::vector<Mat> cov)
{
	std::fstream fs;
	fs.open(fn, std::fstream::in | std::fstream::out | std::fstream::trunc);

	// Mean
	std::cout << "MEANS" << std::endl;
	fs << "MEANS\n";
	for (int i = 0; i < NUM_CLUS; i++)
	{
		std::cout << "\t" << means.at<double>(i) << std::endl;
		fs << "\t" << means.at<double>(i) << std::endl;
	}

	// Sigma
	std::cout << "\n\nSIGMAS " << std::endl;
	fs << "\n\nSIGMAS\n";
	for (int i = 0; i < NUM_CLUS; i++)
	{
		std::cout << "\t" << cov[i].at<double>(0) << std::endl;
		fs << "\t" << cov[i].at<double>(0) << std::endl;
	}

	// Weights
	std::cout << "\n\nWEIGHTS " << std::endl;
	fs << "\n\nWEIGHTS\n";
	for (int i = 0; i < NUM_CLUS; i++)
	{
		std::cout << "\t" << weights.at<double>(i) << std::endl;
		fs << "\t" << weights.at<double>(i) << std::endl;
	}

	fs.close();
	return 0;
}


int main(int argc, char** argv)
{
	// Get the data from a file
	std::string dataFile("../../setup/gmm.txt"); // by default
	std::string outFile("../../setup/est_ms.txt"); // by default
	if (argc > 1)
		dataFile = argv[1];

	// Get data
	Mat samples;
	if (dataFromFile(dataFile, samples) < 0)
		return -1; // File didn't read properly

	
	// Train expectation maximization
	Ptr<ml::EM> mdl = ml::EM::create();
	mdl->setClustersNumber(NUM_CLUS);
	mdl->trainEM(samples);


	// Get means
	Mat means = mdl->getMeans();
	// Get weights
	Mat weights = mdl->getWeights();

	// Get covariance matrix
	std::vector<Mat> cov;
	for (int i = 0; i < NUM_CLUS; i++)
		cov.push_back(Mat::zeros(1, 1, CV_64FC1));
	mdl->getCovs(cov);
	

	// Print out the data (to stdout and to file)
	outputData(outFile, means, weights, cov);

	system("pause");
}
