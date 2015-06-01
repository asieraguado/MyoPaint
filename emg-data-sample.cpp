// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.

// This sample illustrates how to use EMG data. EMG streaming is only supported for one Myo at a time.

#include <array>
#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include "randomforest.h"

#include <myo/myo.hpp>

#define WINDOW_SIZE 40/5

class DataCollector : public myo::DeviceListener {
public:
    DataCollector(std::string gesture_name)
    {
		gestname = gesture_name;
		classifier.createFromFile("randomtree_mmv.txt");
		initialize();
    }

	void initialize() {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < windowsize; j++)
				samplewindow[i][j] = 0;
		windowpos = 0;
	}

    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp)
    {
        // We've lost a Myo.
        // Let's clean up some leftover state.
		initialize();
    }

    // onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
    {
        for (int i = 0; i < 8; i++) {
            samplewindow[i][windowpos] = (int)emg[i];
//			std::cout << samplewindow[i][windowpos] << " ";
        }
		windowpos = (windowpos + 1) % windowsize;
    }

    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.

    // We define this function to print the current values that were updated by the on...() functions above.
    void print()
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

	int median(std::array<int, WINDOW_SIZE> v) {
		std::sort(v.begin(), v.end());
		return v[(v.end() - v.begin()) / 2];
	}

	int mean(std::array<int, WINDOW_SIZE> v) {
		int sum = 0;
		for (int i = 0; i < v.size(); i++) {
			sum += v[i];
		}
		return sum / v.size();
	}

	int variance(std::array<int, WINDOW_SIZE> v) {
		int mean = 0, sum = 0;
		for (int i = 0; i < v.size(); i++) {
			mean += v[i];
			sum += v[i] * v[i];
		}
		return (sum / v.size()) - (mean / v.size()) * (mean / v.size());
	}

	void printGesture()
	{
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

		std::cout << classifier.classify(dataset) << std::endl;
	}

    // The values of this array is set by onEmgData() above.
	std::array<std::array<int, WINDOW_SIZE>, 8> samplewindow;
	int windowpos;
	int windowsize = WINDOW_SIZE;
    // std::array<int8_t, 8> emgSamples;
	std::string gestname;
	randomforest classifier;
};

int main(int argc, char** argv)
{
    // We catch any exceptions that might occur below -- see the catch statement for more details.
    try {

    // First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
    // publishing your application. The Hub provides access to one or more Myos.
    myo::Hub hub("com.example.emg-data-sample");

    std::cout << "Attempting to find a Myo..." << std::endl;

    // Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
    // immediately.
    // waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
    // if that fails, the function will return a null pointer.
    myo::Myo* myo = hub.waitForMyo(10000);

    // If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
    if (!myo) {
        throw std::runtime_error("Unable to find a Myo!");
    }

    // We've found a Myo.
    std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

    // Next we enable EMG streaming on the found Myo.
    myo->setStreamEmg(myo::Myo::streamEmgEnabled);

	// Get the gesture name
	std::string gesture;
	std::cin >> gesture;

    // Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
    DataCollector collector(gesture);

    // Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
    // Hub::run() to send events to all registered device listeners.
    hub.addListener(&collector);
	int n = 500;
    // Finally we enter our main loop.
    while (1) {
        // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
        // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
        hub.run(50);
		collector.printGesture();
        // After processing events, we call the print() member function we defined above to print out the values we've
        // obtained from any events that have occurred.
		if (n == 0) break;
		n--;
    }

    // If a standard exception occurred, we print out its message and exit.
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
}
