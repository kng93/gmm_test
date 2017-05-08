#pragma once

#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <string>
#include <fstream>

#define NUM_CLUS 4

int cvDataFromFile(std::string fn, cv::Mat& samples)
{
	std::vector<double> val;
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
	samples = cv::Mat::zeros(num_points, 1, CV_64FC1);
	for (int i = 0; i < num_points; i++)
		samples.at<double>(i) = val[i];

	return 0;
}

int cvOutputData(std::string fn, cv::Mat means, cv::Mat weights, std::vector<cv::Mat> cov)
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

int cvRun(std::string dataFile, std::string outFile)
{
	// Get data
	cv::Mat samples;
	if (cvDataFromFile(dataFile, samples) < 0)
		return -1; // File didn't read properly

	
	// Train expectation maximization
	cv::Ptr<cv::ml::EM> mdl = cv::ml::EM::create();
	mdl->setClustersNumber(NUM_CLUS);
	mdl->trainEM(samples);


	// Get means
	cv::Mat means = mdl->getMeans();
	// Get weights
	cv::Mat weights = mdl->getWeights();

	// Get covariance matrix
	std::vector<cv::Mat> cov;
	for (int i = 0; i < NUM_CLUS; i++)
		cov.push_back(cv::Mat::zeros(1, 1, CV_64FC1));
	mdl->getCovs(cov);
	

	// Print out the data (to stdout and to file)
	cvOutputData(outFile, means, weights, cov);

	return 0;
}