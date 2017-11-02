#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

//Root libraries
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TGraph.h> //Graph object
#include <TApplication.h> //Helps draw graph instantly!

using namespace std;



class tempTrender {
	public:
	tempTrender(string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	

	void readFile(string filePath, string cityName) { 
		ifstream file(filePath.c_str());
		string datafileName = "usefulData";
		datafileName.append(cityName);
		datafileName.append(".dat");
		ofstream usefulData(datafileName.c_str()); //we create a file which contains the raw data for easier data processing. This will not have redundant text or comments, the formatting has been remade to
		//only include spaces for partitions. This is done because we can process files with this formatting very quickly, so the other functions will run smoothly!
		string line;
		cout << "processing..."<<endl;
		while (getline(file, line)) { //this processes the first few lines until the formatting definition. This means that these lines won't be written into the usefulData.dat file.
			if (line == "Datum;Tid (UTC);Lufttemperatur;Kvalitet;;Tidsutsnitt:" ) {
				break;
			}
		}
		//usefulData << "Datum Tid (UTC) Lufttemperatur Kvalitet" <<endl; //but we do still want the formatting line, I guess. so I add it here.
		string dayold = "0", monthold = "0", yearold = "0", GYold = "0", timeold = "0";
		float temptot = 0;
		int n = 0;
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
			tempstream >> GY;				
			
			//separates G/Y value
			
			
			cout << yyyy << ' ' << mm << ' ' << dd << ' ' << time << ' ' << temp << ' ' << GY << endl;
			usefulData << yyyy << ' ' << mm << ' ' << dd << ' ' << time << ' ' << temp << ' ' << GY << endl;
			
			tempstream >> guyrest;				
			
			//separates G/Y value
			stringstream guystream(guyrest);
			getline(guystream, GY, ';');		
			guystream >> restrest;
			
			float tempno = ::atof(temp.c_str()); //turns the temperature into a float
			
			
			cout << yyyy << ' ' << mm << ' ' << dd << ' ' << time << ' ' << tempno << ' ' << GY << endl; //outputs the result into the console / copies the result into the usefulData file.
			
			if (dayold != "0"){
				
				if (dayold != dd){
					
					usefulData << yearold << ' ' << monthold << ' ' << dayold << ' ' << temptot/n << ' ' << GYold << endl;
					temptot=0;
					n=0;
				}
			}
			
			n++;
			dayold = dd;
			monthold = mm;
			yearold = yyyy;
			GYold = GY;
			timeold = time;
			temptot += tempno;
		}
		cout << "done" <<endl;
		file.close();
		usefulData.close();
	}
	
	void tempPerDay(string cityName, int yearToCompute){ //Make a histogram of the average temperature of each day of the year || Still need to work on the plot window...
		
		TApplication *canvas = new TApplication("App",0,0);
		string datafileName = "usefulData";
		datafileName.append(cityName);
		datafileName.append(".dat");
		ifstream usefulData(datafileName.c_str());
		
		vector<float> temperatures;
		
		
		string year, month, day, temp, line, status;
		
		while (getline(usefulData, line)){
			
			usefulData >> year >> month >> day >> temp >> status;

			int yearnow = ::atoi(year.c_str()); //turns the year into an integer

			float tempno = ::atof(temp.c_str()); //turns the temperature into a float


			if (yearToCompute == yearnow){
				
				//cout << year << " " << month << " " << day << " " << temp << " " << status << endl;
				temperatures.push_back (tempno);
				cout << tempno<<endl;
			}
			
		}
		int n = temperatures.size();
		TCanvas *c1 = new TCanvas("c1","Temperature of given year for each day",200,10,700,500);
		Float_t x[n], y[n];
		for (Int_t i=0;i<n;i++) {
			x[i] = i+1;
			y[i] = temperatures.at(i);
		}
		TGraph* gr = new TGraph(n,x,y);	
		gr->Draw("AL");
		c1->Modified();
		c1->Update();

		usefulData.close();
	}
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year


	void tempOnDay(string cityFile = "NaN") {
		cout << "Using file: " << cityFile << endl;
		
		vector<double> temperature;
		vector<double> yearvec;
		cout << "Choose a month." << endl;
		cin >> month;
		cout << "Choose a day." << endl;
		cin >> day;
		
		ifstream file(cityFile.c_str());
		
		double dummyYear;
		string dummyTime;
		int test = 0;
		int fdd; // day from the file
		int fmm; // month from the file
		float temp; // temperature value
		string line;

		while (getline(file, line)) {
			file >> dummyYear >> fmm >> fdd >> temp;
		
			if(fmm == month && fdd == day){
				temperature.push_back(temp);
				yearvec.push_back((float) dummyYear);
				cout << dummyYear << "-" << fmm << "-" << fdd << " " << temperature.at(test) << endl;
				test++;				
			}
		}
		int n = temperature.size();
		TCanvas *c1 = new TCanvas("c1","Temperature of given day for each year",200,10,700,500);
		Float_t x[n], y[n];
		for (Int_t i=0;i<n;i++) {
			x[i] = yearvec.at(i);
			y[i] = temperature.at(i);
		}
		TGraph* gr = new TGraph(n,x,y);	
		gr->Draw("AL");
		c1->Modified();
		c1->Update();
		
		file.close();
	}
	//I don't think we're using these...
	private:
	unsigned short day;
	unsigned short month;
};

#endif








