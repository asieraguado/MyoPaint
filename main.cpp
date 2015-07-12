// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.
//
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
#include "datacollector.h"
#include "histogram.h"
#include "histGUI.h"
#include <myo/myo.hpp>
#include <Windows.h>

int main(int argc, char** argv)
{
    try {
	// ==== START MYO ====
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
	// =======

	// Get the gesture name
	std::string gesture;
//	std::cin >> gesture;

    // DataCollector is myo::DeviceListener class with utilities for 
    DataCollector collector(gesture);

	// Our own gesture classifier (random forest)
	randomforest classifier;
	classifier.createFromFile("randomforest_AD.txt");

    // Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
    // Hub::run() to send events to all registered device listeners.
    hub.addListener(&collector);

	histogram hist_filter;
	std::string detected_gesture;
	emgdatasampleVisualStudio2013::histGUI^ histogram_gui = gcnew emgdatasampleVisualStudio2013::histGUI();
	histogram_gui->Show();
	int n = 0;
		while (1) {
			histogram_gui->Refresh();
			// In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
			// In this case, we wish to update our display 20 times a second, so we run for 1000/20 milliseconds.
			hub.run(50);
			std::map<std::string, float> current_data = collector.getDataset();
			detected_gesture = classifier.classify(current_data);
			std::cout << detected_gesture << std::endl;

			// Histogram
			hist_filter.add_instant(detected_gesture);
			histogram_gui->updateHist(hist_filter);
			if (n == 10) {
				std::cout << "Filtered gesture: " << std::endl;
				std::cout << hist_filter.peak() << std::endl << std::endl;
				hist_filter.restart();
				n = 0;
			}
			else {
				n++;
			}
		}
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
}
