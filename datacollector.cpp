#include "datacollector.h"
#include <string>

DataCollector::DataCollector()
{
	gestname = "";
	initialize();
}

DataCollector::DataCollector(std::string gesture_name)
{
	gestname = gesture_name;
	initialize();
}

void DataCollector::initialize() {
	windowsize = WINDOW_SIZE;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < windowsize; j++)
			samplewindow[i][j] = 0;
	windowpos = 0;
}

// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
void DataCollector::onUnpair(myo::Myo* myo, uint64_t timestamp)
{
	// We've lost a Myo.
	// Let's clean up some leftover state.
	initialize();
}

// onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
void DataCollector::onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
{
	for (int i = 0; i < 8; i++) {
		samplewindow[i][windowpos] = (int)emg[i];
		//			std::cout << samplewindow[i][windowpos] << " ";
	}
	windowpos = (windowpos + 1) % windowsize;
}


// Print current statistical data (mean, median, variance) to file 'statdata'
void DataCollector::print()
{
	// Print to file
	std::ofstream datafile;
	datafile.open("statdata", std::ios::app);
	datafile << gestname << " ";
	for (size_t i = 0; i < samplewindow.size(); i++) {
		std::string emgString;
		// Mean
		datafile << mean(samplewindow[i]) << " ";
		// Median
		datafile << median(samplewindow[i]) << " ";
		// Variance
		datafile << variance(samplewindow[i]) << " ";
	}
	datafile << std::endl;
	datafile.close();
}

std::map<std::string, float> DataCollector::getDataset() {
	std::map<std::string, float> dataset;
	for (size_t i = 0; i < samplewindow.size(); i++) {
		char A = 'A' + i;
		std::stringstream ss1, ss2, ss3;
		ss1 << A << "_mean";
		ss2 << A << "_median";
		ss3 << A << "_variance";
		// Mean
		dataset[ss1.str()] = (float)mean(samplewindow[i]);
		// Median
		dataset[ss2.str()] = (float)median(samplewindow[i]);
		// Variance
		dataset[ss3.str()] = (float)variance(samplewindow[i]);
	}
	return dataset;
}

float DataCollector::median(std::array<int, WINDOW_SIZE> v) {
	std::sort(v.begin(), v.end());
	return v[(v.end() - v.begin()) / 2];
}

float DataCollector::mean(std::array<int, WINDOW_SIZE> v) {
	int sum = 0;
	for (int i = 0; i < v.size(); i++) {
		sum += v[i];
	}
	return (float)sum / v.size();
}

float DataCollector::variance(std::array<int, WINDOW_SIZE> v) {
	int mean = 0, sum = 0;
	for (int i = 0; i < v.size(); i++) {
		mean += v[i];
		sum += v[i] * v[i];
	}
	return ((float)sum / v.size()) - ((float)mean / v.size()) * ((float)mean / v.size());
}