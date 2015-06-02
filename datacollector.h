#pragma once

// Window size is 10 and we get data every 5ms (EMG works at 200Hz), 
// so a completely different dataset is generated every 50ms
#define WINDOW_SIZE 10

#include <array>
#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>
#include <stdexcept>
#include <string>
#include "randomforest.h"
#include <myo/myo.hpp>

class DataCollector : public myo::DeviceListener {
public:
	DataCollector();
	DataCollector(std::string gesture_name);

	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
	void onUnpair(myo::Myo* myo, uint64_t timestamp);

	// onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
	void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);

	// There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
	// For this example, the functions overridden above are sufficient.

	// We define this function to print the current values that were updated by the on...() functions above.
	void print();

	std::map<std::string, float> getDataset();

private:
	void initialize();

	float median(std::array<int, WINDOW_SIZE> v);
	float mean(std::array<int, WINDOW_SIZE> v);
	float variance(std::array<int, WINDOW_SIZE> v);

	// The values of this array is set by onEmgData() above.
	std::array<std::array<int, WINDOW_SIZE>, 8> samplewindow;
	int windowpos;
	int windowsize;
	// std::array<int8_t, 8> emgSamples;
	std::string gestname;
};