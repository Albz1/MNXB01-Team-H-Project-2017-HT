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
	

	void readFile(string filePath, string cityName) { 
		
		vector<float> temperatures;
		
		
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
			tempstream >> guyrest;				
			
			//separates G/Y value
			stringstream guystream(guyrest);
			getline(guystream, GY, ';');	
			guystream >> restrest;
			
			float tempno = ::atof(temp.c_str()); //turns the temperature into a float

			cout << yyyy << ' ' << mm << ' ' << dd << ' ' << time << ' ' << tempno << ' ' << GY << endl; //outputs the result into the console / copies the result into the usefulData file.
		
			
			if (dayold != "0"){ // this makes sure that the average temperature and standard deviation of each day is saved in the "useful data" file
				
				if (dayold != dd){
					int size = temperatures.size();
					double StandardDiv =0.;
					for (int i = 0; i<size; i++){
						StandardDiv += (temperatures.at(i) - temptot/n) * (temperatures.at(i) - temptot/n);// here, standard deviation is calculated
					}
					double standarddev = sqrt(StandardDiv/n);
					
					usefulData << yearold << ' ' << monthold << ' ' << dayold << ' ' << temptot/n << ' ' << GYold << ' ' << standarddev << endl;
					
					temptot=0; // here, all sums, counters, and vectors are reset, so that they do not interfere with other data
					n=0;
					standarddev = 0;
					while (!temperatures.empty()){
						temperatures.pop_back();
					}
					
				}
			}
			
			n++; // here we have counters, vectors and sums all being added, this is all necessary for the above loop which records the average temperature each day
			dayold = dd;
			monthold = mm;
			yearold = yyyy;
			GYold = GY;
			timeold = time;
			temptot += tempno;
			temperatures.push_back (tempno);
		}
		cout << "done" <<endl;
		file.close();
		usefulData.close();
	}
	
	void tempPerDay(string cityName, string computeYear){ //FUNCTION COMPLETE.
		
		int yearToCompute = ::atoi(computeYear.c_str());
		string datafileName = "usefulData";
		datafileName.append(cityName);
		datafileName.append(".dat");
		ifstream usefulData(datafileName.c_str()); //we can have custom city name input! :D
		
		vector<float> temperatures;
		vector<float> stdevs;
		vector<float> tempError;
		
		
		string year, month, day, temp, line, status, stdev;
		
		while (getline(usefulData, line)){
			
			usefulData >> year >> month >> day >> temp >> status >> stdev;

			int yearnow = ::atoi(year.c_str()); //turns the year into an integer
			float tempno = ::atof(temp.c_str()); //turns the temperature into a float
			float stdevcurrent = ::atof(stdev.c_str());//turns the standard deviation into a float


			if (yearToCompute == yearnow){
				
				temperatures.push_back (tempno);//the temperature of each day during the selected year is stored in a vector here
				stdevs.push_back (stdevcurrent);//the standard deviation of the temperature each day during the selected year is stored here
				
				cout << tempno <<endl;
			}
			
		}
		int n = temperatures.size(); // here, the temperature of each day is plotted against the day of the year
		
		string cTitle = "Temp per day of year ";
		cTitle.append(computeYear.c_str());
		cTitle.append(" in ");
		cTitle.append(cityName.c_str());
		
		string saveAsName = "../Results/TempPerDay/temp";
		saveAsName.append(cityName.c_str());
		saveAsName.append(computeYear.c_str());
		saveAsName.append(".png");
		
		
		TCanvas *c1 = new TCanvas("c1",cTitle.c_str(),200,10,700,500);
		Float_t x[n], y[n], ex[n], ey[n];
		for (Int_t i=0;i<n;i++) { //fills up arrays containing the values for x,y, ex, ey which are used to graph.
			x[i] = i+1;
			y[i] = temperatures.at(i);
			ex[i] = 0;
			ey[i] = stdevs.at(i);
			
		}
		
		TGraphErrors* gre = new TGraphErrors(n,x,y,ex,ey);//Creating the graph for error bars
		TGraph* gr = new TGraph(n,x,y); //and the one for the line
		gre->SetLineWidth(4); //setting line width and color
		gre->SetLineColor(kCyan);
		gr->SetLineWidth(2);
		gr->SetLineColor(kBlack);
		
		gre->GetXaxis()->SetTitle("Day of year");
		gre->GetYaxis()->SetTitle("Temperature [^{o}C]");
		gre->GetXaxis()->CenterTitle();
		gre->GetYaxis()->CenterTitle();
		gre->Draw("ALZ"); //draw the error bars below the line, do not draw the ends of the error bars (Z).
		gr->Draw("L");
		
		TLegend *legend=new TLegend(0.67,0.8,0.94,0.9);
	    legend->SetTextFont(72);
	    legend->SetTextSize(0.03);
 	    legend->AddEntry(gre,"Measurement Error", "l");
 	    legend->AddEntry(gr,"Measurement", "l");
 	    legend->Draw();

		c1->Update();
		
		c1->SaveAs(saveAsName.c_str());
		usefulData.close();
	}

	void tempOnDay(string cityFile = "NaN", string cityName = "NaN") { // shows every year temperature of a chosen year.
		//cout << "Using file: " << cityFile << endl;
		
		 TH1D* fTemp = new TH1D("fTemp", "Temperature distribution x; Counts", // used for making a histogram.
			150, -20, 40);
		
		vector<double> temperature;
		vector<double> yearvec;
		float floatInput; // using this variable in case of imput being a float.
		
		cout << "Choose a month." << endl;
		cin >> floatInput; // using a dummy value in case the imput is not an integer.
		
		while(!floatInput){ // This was done by marcus
			cout << "This is not a valid input!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			cin >> floatInput;
		}
		
		month = static_cast<unsigned short>(floatInput); // This turns a float into an unsigned short.
		

		
		while (month < 1 || month > 12 ) { // this while loop makes sure that entered month is a valid choise, that is, it checks if chosen month is between 1 and 12.
			cout << "Month " << month << " does not exist, please choose a month between 1 and 12." << endl;
			cout << "Please choose another month" << endl;
			cin >> floatInput;
			
			while(!floatInput){ // makes sure that the imput is not someting like a string.
				cout << "This is not a valid input! Please choose a month between 1 and 12." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cin >> floatInput;
		}
			
			month = static_cast<unsigned short>(floatInput);
		}
		
		
		cout << "Choose a day." << endl; // This and other two if statements check if the imput of a day is valid for chosen month. It is generally not a good idea to hard-code numbers into the code, however this was an easy solution to a problem which does not depend on any other code, so it should be fine.
		float dayInput;
		cin >> dayInput;
		
		while(!dayInput){ // makes sure that the imput is not someting like a string.
					cout << "This is not a valid input! Day should be an integer." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> dayInput;
		}
		day = static_cast<unsigned short>(dayInput);
		
		// next 3 statements make sure that entered date exists in a data file
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
			while ( day < 1 || day > 31 ){
				cout << "Day " << day << " is not valid for month " << month << ". Please choose a day between 1 and 31." << endl;
				cin >> floatInput;
				
				while(!floatInput){ // makes sure that the imput is not someting like a string.
					cout << "This is not a valid input! Please choose a day between 1 and 31." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					
					cin >> floatInput;
		}
				
				
				day = static_cast<unsigned short>(floatInput);
			}
		}
		if (month == 4|| month == 6 || month == 9 || month == 11){
			while ( day < 1 || day > 30 ){
				cout << "Day " << day << " is not valid for month " << month << ". Please choose a day between 1 and 30." << endl;
				cin >> floatInput;
				
				while(!floatInput){ // makes sure that the imput is not someting like a string.
					cout << "This is not a valid input! Please choose a day between 1 and 30." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					
					cin >> floatInput;
		}
				
				day = static_cast<unsigned short>(floatInput);
			}
		}
		if (month == 2){
			while ( day < 1 || day > 29 ){
				cout << "Day " << day << " is not valid for month " << month << ". Please choose a day between 1 and 29." << endl;
				cin >> floatInput;
				
				while(!floatInput){ // makes sure that the imput is not someting like a string.
					cout << "This is not a valid input! Please choose a day between 1 and 29." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					
					cin >> floatInput;
		}
				
				day = static_cast<unsigned short>(floatInput);
			}
		}
		
		
		
		// Untill this part the code makes sure that the user imput is valid.
		
		
		
		ifstream file(cityFile.c_str());
		
		double dummyYear; // year is not used in actual data, however because values from the file are taken in order, it has to be assigned to something. This is also usefull for checking if the code works properly.
		string dummyTime; // same case as for dummyYear.
		int test = 0; // this value is used in a while loop in order to make a nice vector which adjust to the data size.
		int fdd; // day from the file.
		int fmm; // month from the file.
		float temp; // temperature value from the file.
		string line; // used for readfile.

		while (getline(file, line)) {
			file >> dummyYear >> fmm >> fdd >> temp; // taking values from file.
		
			if(fmm == month && fdd == day){
				temperature.push_back(temp); // adding chosen value into a vector.
				yearvec.push_back((float) dummyYear); // constructing a vector in parallel for plotting a graph.
				cout << dummyYear << "-" << fmm << "-" << fdd << " " << temperature.at(test) << endl; // output of which data was storred into temperature vector.
				test++;	// increasing test value by 1 for vector construction.		
			}
		}
		
		TF1* dayTemp = new TF1("fTemp", "[0]", -20, 40);
		
		unsigned short ntemp = temperature.size(); // using temperature.size() inside of the for loop doesnt always work propperly, so the length of the for loop was defined outside.
		for(Int_t k = 0; k < ntemp; k++){ // a for loop to fill a histogram.
			fTemp->Fill(temperature[k]);
		}
		string saveAs();
		// Set ROOT drawing styles
	    gStyle->SetOptStat(1111);
	    gStyle->SetOptFit(1111);

	    // create canvas for hPhi
	    TCanvas* c1 = new TCanvas("c1", "fTemp canvas", 900, 600);
	    fTemp->SetMinimum(0);
	    fTemp->Draw();
	    fTemp->SetFillColor(2);
	
	/*
		double mean = fTemp->GetMean(); //The mean of the distribution
		double stdev = fTemp->GetRMS(); //The standard deviation	
	    //fTemp->SetAxisRange(0, 20, "Y"); //sets the axis range
	 	*/
	 	
	    fTemp->SetTitle("Temperature [C]; Temperature [#circC]; Counts" ); //sets the lable of axis

	
		stringstream legendDateTest;
		legendDateTest << "Temperature on " << day << "/" << month;
		string legendDate = legendDateTest.str();
	
		stringstream saveAsStream;
		saveAsStream << "../Results/TempOnDay/temp"<< day << "-" << month << cityName<< ".png";
		string saveAsName = saveAsStream.str();
		// draw the legend
	    TLegend *legend=new TLegend(0.9,0.8,0.65,0.90);
	    legend->SetTextFont(2);
	    legend->SetTextSize(0.03);
 	    legend->AddEntry(fTemp, legendDate.c_str(), "f");
 	    legend->Draw();

	  
	  
	    // Save the canvas as a picture
	    c1->SaveAs(saveAsName.c_str());
	    
		file.close();
	}
	
	
	
	
	
	void GY_comparison(string cityFile = "NaN") { //was not able to do the Y/G comparison since we don't include them in the "usefulData" file
		cout << "Using file: " << cityFile << endl;
		vector<double> temperatureY;
		vector<double> temperatureG;
		double year;
		cout << "Choose a year." << endl;
		cin >> year;
		
		ifstream file(cityFile.c_str());
		
		double fYear;
		string dummyTime;
		int test = 0;
		int dummyday; // day from the file
		int dummymonth; // month from the file
		float temp; // temperature value
		string GY;
		string line;
		
		while (getline(file, line)) {
			file >> fYear >> dummymonth >> dummyday >> temp;
		
			if(fYear == year){ //&& GY == 'Y' dummymonth == 12
				temperatureY.push_back(temp);
//				dayvec.push_back((float) dummyday);
				cout << fYear << "-" << dummymonth << "-" << dummyday << " " << temperatureY.at(test) << endl;
				test++;				
			}
			
/*			else if (fYear == year && dummymonth == 03){
				temperatureG.push_back(temp);
//				dayvec.push_back((float) dummyday);
				cout << fYear << "-" << dummymonth << "-" << dummyday << " " << temperatureG.at(test) << endl;
				test++;	
			}*/
			
		}
		cout << "\n" << "The warmest measured temperature was " << *max_element(temperatureY.begin(), temperatureY.end()) << " Degrees" << endl;
		cout << "While the coldest temperature was " << *min_element(temperatureY.begin(), temperatureY.end()) << " Degrees" << endl;
		
	}
	
	void compareData() { //Should compare results for the other functions between the lund and visby data sets
		cout << "Pick a function [yearmean], [tempOnDay], [GYcomp], [SDofmonth]"<<endl; //I will default this to temperature during a year.
		string usrChoice = "yearmean";
		
		if (usrChoice == "yearmean") {
			cout << "Data exists from both sets starting 1961. Which year do you want to compare?" <<endl;
			int yearToCompute;
			cin >> yearToCompute;
			//this should print a graph of the difference in temperature between lund and visby (lundT-visbyT)
			
			string lundFileName = "usefulDataLund.dat"; //defines datafile paths
			string visbyFileName = "usefulDataVisby.dat";
			ifstream UDLund(lundFileName.c_str()); //opens the data files for reading
			ifstream UDVisby(visbyFileName.c_str());
			
			vector<float> lundT;
			vector<float> visbyT;
			vector<float> diff_T;
			string year, month, day, temp, line, status;
			
			while (getline(UDLund, line)){
				UDLund >> year >> month >> day >> temp >> status;
				
				int yearnow = ::atoi(year.c_str()); //turns the year into an integer

				float tempno = ::atof(temp.c_str()); //turns the temperature into a float

				if (yearToCompute == yearnow){
					lundT.push_back (tempno);
				}	
			}
			while (getline(UDVisby, line)){
				UDVisby >> year >> month >> day >> temp >> status;
				
				int yearnow = ::atoi(year.c_str()); //turns the year into an integer

				float tempno = ::atof(temp.c_str()); //turns the temperature into a float

				if (yearToCompute == yearnow){
					visbyT.push_back (tempno);
				}
			}
			int n = lundT.size();
			for (Int_t i = 0; i < n; i++ ) {
				diff_T.push_back(lundT.at(i)-visbyT.at(i));
			}
			
			TCanvas *c1 = new TCanvas("c1","Temperature comparison between Lund and Visby",200,10,700,500);
			Float_t x[n], y[n];
			for (Int_t i=0;i<n;i++) {
				x[i] = i+1;
				y[i] = diff_T.at(i);
				cout << x[i] << " || " << y[i] <<endl;
			}
			TGraph* gr = new TGraph(n,x,y);	
			gr->Draw("AL");
			c1->Modified();
			c1->Update();
			
			UDLund.close();
			UDVisby.close();
		}
	} 

	//I don't think we're using these...
	private:
	unsigned short day;
	unsigned short month; 
};

#endif








