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
		ofstream usefulData("usefulData.dat"); //we create a file which contains the raw data for easier data processing. This will not have redundant text or comments, the formatting has been remade to
		//only include spaces for partitions.
		string line;
		cout << "processing..."<<endl;
		while (getline(file, line)) { //this processes the first few lines until the formatting definition. This means that these lines won't be written into the usefulData.dat file.
			if (line == "Datum;Tid (UTC);Lufttemperatur;Kvalitet;;Tidsutsnitt:" ) {
				break;
			}
		}
		usefulData << "Datum;Tid (UTC);Lufttemperatur;Kvalitet;;Tidsutsnitt:" <<endl; //but we do still want the formatting line, I guess. so I add it here.
		while (getline(file, line)) {
			
			string yyyy, mm, dd, time, temp, GY;
			string monthrest, dayrest, timerest, temprest, guyrest, restrest;
			
			//separates year
			stringstream yearstream(line); //we create a stringstream of the full line and process it so that whatever comes before the first '-'in the line is put into the variable yyyy.
			getline(yearstream, yyyy, '-'); //this little bit of code also removes the -. This basically helps us with formatting the data set for easier readability!
			yearstream >>monthrest; //then we create a rest-string which now starts with the month
			
			//separates month
			stringstream monthstream(monthrest); 	//we successively do this process for each partition. it could possibly have been done in a loop
			getline(monthstream,mm,'-'); 			//but that would complicate it since we wanted to remove both - and ; from the dataset.
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
			tempstream >> guyrest;				
			
			//separates G/Y value
			stringstream guystream(guyrest);
			getline(guystream, GY, ';');		
			guystream >> restrest;
			
			
			cout << yyyy << ' ' << mm << ' ' << dd << ' ' << time << ' ' << temp << ' ' << GY << endl; //outputs the result into the console / copies the result into the usefulData file.
			usefulData << yyyy << ' ' << mm << ' ' << dd << ' ' << time << ' ' << temp << ' ' << GY << endl;
			
			//

		}
		cout << "done" <<endl;
		file.close(); //make sure to close the files in the end!
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
