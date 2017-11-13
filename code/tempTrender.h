#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <numeric> //added this. Marcus
#include <limits>

//Root libraries
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TGraph.h> //Graph object
#include <TGraphErrors.h> //Graph object
#include <TLegend.h> //Graph object
#include <TColor.h> //Colors for graphs!
#include <TApplication.h>
using namespace std;



class tempTrender {
	public:
	tempTrender(string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	

	void readFile(string filePath, string cityName); //function that reads the datafile and outputs a easy-to-read output file which is used for the remaining files

	void tempPerDay(string cityName, string computeYear); //this functions reads the temperature of every single day in a year and prints a graph of the data		

	void tempOnDay(string cityFile = "NaN", string cityName = "NaN"); // this function reads the temperature of a single day during all years measured and outputs the temperatures in the histogram

	void compareData(); //this function compares results for the other functions between the lund and visby data sets

		
	private:
};

#endif








