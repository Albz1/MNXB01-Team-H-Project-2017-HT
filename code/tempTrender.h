#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <fstream>
#include <sstream>
//Root libraries
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

using namespace std;



class tempTrender {
	public:
	tempTrender(string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	void readFile(string filePath) {
		ifstream file(filePath.c_str());
		ofstream usefulData("usefulData.dat");
		string line;
		cout << "processing..."<<endl;
		while (getline(file, line)) {
			
			string yyyy, mm, dd, time, temp, GY;
			string monthrest, dayrest, timerest, temprest, guyrest;
			
			//separates year
			stringstream yearstream(line);
			getline(yearstream, yyyy, '-');
			yearstream >>monthrest;
			
			//separates month
			stringstream monthstream(monthrest);
			getline(monthstream,mm,'-');
			monthstream >> dayrest;
			
			//separates day
			stringstream daystream(dayrest);
			getline(daystream,dd,';');
			daystream >> timerest;
			
			//separates time
			stringstream timestream(timerest);
			getline(timestream,time,';');
			timestream >> temprest;
			
			//separates temp
			stringstream tempstream(temprest);
			getline(tempstream, temp, ';');		
			tempstream >> GY;				
			
			//separates G/Y value
			
			
			cout << yyyy << ' ' << mm << ' ' << dd << ' ' << time << ' ' << temp << ' ' << GY << endl;
			usefulData << yyyy << ' ' << mm << ' ' << dd << ' ' << time << ' ' << temp << ' ' << GY << endl;
			
			//

		}
		cout << "done" <<endl;
		file.close();
		usefulData.close();
	}
	void tempPerDay(int yearToCompute){ //Make a histogram of the average temperature of each day of the year

	}
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

	private:
	unsigned short day;
	unsigned short month;
};

#endif
