#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <armadillo>

#define NUM_CLUS 5

int armaDataFromFile(std::string fn, arma::mat& samples)
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
	samples = arma::mat(1, num_points, arma::fill::zeros);
	for (int i = 0; i < num_points; i++)
		samples(i) = val[i];

	return 0;
}

//TODO: MAKE SURE THIS WORKS
//int armaOutputData(std::string fn, arma::Base<double, arma::mat> means, arma::mat weights, arma::Base<double, arma::mat> cov)
int armaOutputData(std::string fn, arma::mat means, arma::mat weights, arma::mat cov)
{
	
	std::fstream fs;
	fs.open(fn, std::fstream::in | std::fstream::out | std::fstream::trunc);

	// Mean
	std::cout << "MEANS" << std::endl;
	fs << "MEANS\n";
	for (int i = 0; i < NUM_CLUS; i++)
	{
		std::cout << "\t" << means(i) << std::endl;
		fs << "\t" << means(i) << std::endl;
	}

	// Sigma
	std::cout << "\n\nSIGMAS " << std::endl;
	fs << "\n\nSIGMAS\n";
	for (int i = 0; i < NUM_CLUS; i++)
	{
		std::cout << "\t" << cov(i) << std::endl;
		fs << "\t" << cov(i) << std::endl;
	}

	// Weights
	std::cout << "\n\nWEIGHTS " << std::endl;
	fs << "\n\nWEIGHTS\n";
	for (int i = 0; i < NUM_CLUS; i++)
	{
		std::cout << "\t" << weights(i) << std::endl;
		fs << "\t" << weights(i) << std::endl;
	}

	fs.close();
	return 0;
}

int armaRun(std::string dataFile, std::string outFile)
{
	arma::gmm_diag model;
	arma::mat armaSamples;
	if (armaDataFromFile(dataFile, armaSamples) < 0)
		return -1; // File didn't read properly

	bool status = model.learn(armaSamples, NUM_CLUS, arma::maha_dist, arma::random_subset, 10, 5, 1e-10, false);
	if (status == false)
		std::cout << "learning failed" << std::endl;

	armaOutputData(outFile, model.means, model.hefts, model.dcovs);

	return 0;
}