#include <opencv2/core.hpp>
#include <iostream>
#include <opencv2/ml.hpp>

using namespace cv;

//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << " Usage: gmm fileWithPoints" << std::endl;
		return -1;
	}

	int k = 3;
	Mat samples;

	// TODO: Get data


	// Train expectation maximization
	Ptr<ml::EM> mdl = ml::EM::create();
	mdl->setClustersNumber(k);
	mdl->trainEM(samples);

	// Get means and covariance matrix
	Mat means = mdl->getMeans();
	std::vector<Mat> cov;
	mdl->getCovs(cov);
}