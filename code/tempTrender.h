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
	

	void readFile(string filePath, string cityName) { //function that reads the datafile and outputs a easy-to-read output file which is used for the remaining files
		
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
					
					usefulData << yearold << ' ' << monthold << ' ' << dayold << ' ' << temptot/n << ' ' << GYold << ' ' << standarddev << ' ' << n << endl;
					
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
	
	void tempPerDay(string cityName, string computeYear){ //this functions reads the temperature of every single day in a year and prints a graph of the data
		
		int yearToCompute = ::atoi(computeYear.c_str());
		string datafileName = "usefulData";
		datafileName.append(cityName);
		datafileName.append(".dat");
		ifstream usefulData(datafileName.c_str()); //depending on what city is input, the program checks the appropriate data file
		
		vector<float> temperatures; // here we declare vectors and variables that will be useful for the plot.
		vector<float> stdevs;
		vector<float> tempError;
		
		
		string year, month, day, temp, line, status, stdev, n; 
				
		while (getline(usefulData, line)){
			
			usefulData >> year >> month >> day >> temp >> status >> stdev >> n; // here all variables are assigned

			int yearnow = ::atoi(year.c_str()); //turns the year into an integer
			float tempno = ::atof(temp.c_str()); //turns the temperature into a float
			float stdevcurrent = ::atof(stdev.c_str());//turns the standard deviation into a float


			if (yearToCompute == yearnow){
				
				temperatures.push_back (tempno);//the temperature of each day during the selected year is stored in a vector here
				stdevs.push_back (stdevcurrent);//the standard deviation of the temperature each day during the selected year is stored here
				
				cout << tempno <<endl;
			}
			
		}
		int nt = temperatures.size(); // here, the temperature of each day is plotted against the day of the year
		
		string cTitle = "Temp per day of year "; //here the title of the graph is made
		cTitle.append(computeYear.c_str());
		cTitle.append(" in ");
		cTitle.append(cityName.c_str());
		
		string saveAsName = "../Results/TempPerDay/temp";
		saveAsName.append(cityName.c_str());
		saveAsName.append(computeYear.c_str());
		saveAsName.append(".png");
		
		
		TCanvas *c1 = new TCanvas("c1",cTitle.c_str(),200,10,700,500);
		Float_t x[nt], y[nt], ex[nt], ey[nt];
		for (Int_t i=0;i<nt;i++) { //fills up arrays containing the values for x,y, ex, ey which are used to graph.
			x[i] = i+1;
			y[i] = temperatures.at(i);
			ex[i] = 0;
			ey[i] = stdevs.at(i);
			
		}
		
		TGraphErrors* gre = new TGraphErrors(nt,x,y,ex,ey);//Creating the graph for error bars
		TGraph* gr = new TGraph(nt,x,y); //and the one for the line
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

	void tempOnDay(string cityFile = "NaN", string cityName = "NaN") { // this function reads the temperature of a single day during all years measured and outputs the temperatures in the histogram

		
		TH1D* dayTemp = new TH1D("Values", "Temperature distribution x; Counts", // used for making a histogram.
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
		
		
		
		ifstream file(cityFile.c_str()); // reading a file
		
		double dummyYear; // year is not used in actual data, however because values from the file are taken in order, it has to be assigned to something. This is also usefull for checking if the code works properly.
		string dummyTime; // same case as for dummyYear.
		int test = 0; // this value is used in a while loop in order to make a nice vector which adjust to the data size.
		int fdd; // day from the file.
		int fmm; // month from the file.
		float temp; // temperature value from the file.
		string line; // used for readfile.

		while (getline(file, line)) { // Processing data
			file >> dummyYear >> fmm >> fdd >> temp; // taking values from file.
		
			if(fmm == month && fdd == day){
				temperature.push_back(temp); // adding chosen value into a vector.
				yearvec.push_back((float) dummyYear); // constructing a vector in parallel for plotting a graph.
				cout << dummyYear << "-" << fmm << "-" << fdd << " " << temperature.at(test) << endl; // output of which data was storred into temperature vector.
				test++;	// increasing test value by 1 for vector construction.		
			}
		}
		
		
		unsigned short ntemp = temperature.size(); // using temperature.size() inside of the for loop doesnt always work propperly, so the length of the for loop was defined outside.
		for(Int_t k = 0; k < ntemp; k++){ // a for loop to fill a histogram.
			dayTemp->Fill(temperature[k]);
		}
		string saveAs();
		// Set ROOT drawing styles
	    gStyle->SetOptStat(1111);
	    gStyle->SetOptFit(1111);

	    // create canvas for temperature values
	    TCanvas* c1 = new TCanvas("c1", "dayTemp canvas", 900, 600);
	    dayTemp->Draw();    
	    dayTemp->SetMinimum(0);
	    dayTemp->SetFillColor(2);


	

		double mean = dayTemp->GetMean(); //The mean of the distribution
		double stdev = dayTemp->GetRMS(); //The standard deviation	
	    //dayTemp->SetAxisRange(0, 20, "Y"); //sets the axis range
	 	
	    dayTemp->SetTitle("Temperature [C]; Temperature [#circC]; Counts" ); //sets the lable of axis
	
		stringstream legendDateTest; // constructs a string for the legend.
		legendDateTest << "Temperature on " << day << "/" << month;
		string legendDate = legendDateTest.str();
	
		stringstream saveAsStream; // construcs a string for the canvas name
		saveAsStream << "../Results/TempOnDay/temp"<< day << "-" << month << cityName<< ".png";
		string saveAsName = saveAsStream.str();
		
		// draw the legend
		
	    TLegend *legend=new TLegend(0.5,0.8,0.2,0.90);
	    legend->SetTextFont(2);
	    legend->SetTextSize(0.03);
 	    legend->AddEntry(dayTemp, legendDate.c_str(), "f");
 	    legend->Draw();  

	  
	    // Save the canvas as a picture
	    c1->SaveAs(saveAsName.c_str());
	    
		file.close();
		
	}
	
	void compareData() { //this function compares results for the other functions between the lund and visby data sets
		
		cout << "Data exists from both sets starting 1961. Which year do you want to compare?" <<endl;
		string computeYear;
		cin >> computeYear;
		int yearToCompute = ::atoi(computeYear.c_str());
		//this should print a graph of the difference in temperature between lund and visby (lundT-visbyT)
		
		string lundFileName = "usefulDataLund.dat"; //defines datafile paths
		string visbyFileName = "usefulDataVisby.dat";
		ifstream UDLund(lundFileName.c_str()); //opens the data files for reading
		ifstream UDVisby(visbyFileName.c_str());
		
		vector<float> lundT; // initializes all the variables and vectors containing relevant data for the plot
		vector<float> visbyT;
		vector<float> diff_T;
		vector<float> stddevs;
		vector<float> stdLund;
		vector<float> stdVisby;
		vector<float> countL;
		vector<float> countV;
		string year, month, day, temp, line, status, stdivs, n;
		
		while (getline(UDLund, line)){
			UDLund >> year >> month >> day >> temp >> status >> stdivs >> n;
			
			int yearnow = ::atoi(year.c_str()); //turns the relevant quantities into integers and floats
			float stddevs = ::atof(stdivs.c_str());
			float ncount = ::atof(n.c_str());
			float tempno = ::atof(temp.c_str()); 

			if (yearToCompute == yearnow){ // records data if the year being read is the desired year
				lundT.push_back (tempno);
				stdLund.push_back(stddevs);
				countL.push_back(ncount);
			}	
		}
		while (getline(UDVisby, line)){ // same as the above code block, but for visby rather than lund
			UDVisby >> year >> month >> day >> temp >> status >> stdivs >> n;
			
			int yearnow = ::atoi(year.c_str()); 
			float stddevs = ::atof(stdivs.c_str());
			float ncount = ::atof(n.c_str());
			float tempno = ::atof(temp.c_str()); 

			if (yearToCompute == yearnow){
				visbyT.push_back (tempno);
				stdVisby.push_back(stddevs);
				countV.push_back(ncount);
			}
		}
			
		int nt = lundT.size(); // the loop of the comparison being made, this is based on the size of the lund vector, meaning that we don't have problems with leap years, etc.
		for (Int_t i = 0; i < nt; i++ ) {
			diff_T.push_back(lundT.at(i)-visbyT.at(i));
			stddevs.push_back( sqrt( stdLund.at(i)*stdLund.at(i)/countL.at(i)  + stdVisby.at(i)*stdVisby.at(i)/countV.at(i) ) );
		}
		string cTitle = "Temperature difference, Lund - Visby [";
		cTitle.append(computeYear.c_str());
		cTitle.append("].");
		
		string saveAsName = "../Results/CompareData/diff_";
		saveAsName.append(computeYear.c_str());
		saveAsName.append(".png");
		TCanvas *c1 = new TCanvas("c1",cTitle.c_str(),200,10,700,500);
		Float_t x[nt], y[nt], ex[nt], ey[nt];
		for (Int_t i=0;i<nt;i++) {
			x[i] = i+1;
			y[i] = diff_T.at(i);
			ex[i] = 0;
			ey[i] = stddevs.at(i);
			cout << x[i] << " || " << y[i] <<endl;
		}
		TGraph* gr = new TGraph(nt,x,y);	
		TGraphErrors* gre = new TGraphErrors(nt,x,y,ex,ey);
		gre->SetLineWidth(4); //setting line width and color
		gre->SetLineColor(kCyan);
		gr->SetLineWidth(2);
		gr->SetLineColor(kBlack);
		
		gre->GetXaxis()->SetTitle("Day of year");
		gre->GetYaxis()->SetTitle("Temperature [^{o}C]");
		gre->GetXaxis()->CenterTitle();
		gre->GetYaxis()->CenterTitle();
		gre->Draw("ALZ");      
		gr->Draw("L");
		
		TLegend *legend=new TLegend(0.67,0.8,0.94,0.9);
		legend->SetTextFont(72);
		legend->SetTextSize(0.03);
		legend->AddEntry(gre,"Temp diff Error", "l");
		legend->AddEntry(gr,"Temp diff Lund-Visby", "l");			
		legend->Draw();
		
		c1->Modified();
		c1->Update();
		c1->SaveAs(saveAsName.c_str());
		UDLund.close();
		UDVisby.close();
	}
		
	private:
	int day;
	int month;
};

#endif








