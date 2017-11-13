#include "tempTrender.h"
#include <string>
#include <fstream>
#include <limits>
#include <vector>
using namespace std;
//Root libraries
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

void fileread() {
	string visbyDatafilePath = "../datasets/smhi-opendata_Visby.csv"; //a relative path to the visby data file in the directory tree.
	string lundDatafilePath = "../datasets/smhi-opendata_Lund.csv"; //to lund
	tempTrender visbyTempData = tempTrender(visbyDatafilePath); // we create a new instance of the object tempTrender for the visby data.
	tempTrender lundTempData = tempTrender(lundDatafilePath);
	createfile:
	cout << "---fileread()---"<<endl;
	cout << "Do you want to create new useful data file paths for any of the two cities we analyze? [y]/[n]"<<endl;
	string userInput;
	cin >> userInput;
	 //we call the readFile data function to first create a usefulData file, which improves formatting.
	if (userInput == "y") {  //we ask the user if they want to create new data files for lund or visby. 
		cout << "Which of the two cities would you like? Lund [l], or Visby [v]? " <<endl;
		string cityInput;
		cin >> cityInput;
		if (cityInput == "l") {
			lundTempData.readFile(lundDatafilePath,"Lund");
			goto createfile;
		}	
		else if (cityInput == "v") {
			visbyTempData.readFile(visbyDatafilePath,"Visby");
			goto createfile;
		}
	}
	else {cout << "very well. " <<endl;}
}

void yearmean(){
	tempTrender visbyTempData = tempTrender("usefulDataVisby.dat"); // we create a new instance of the object tempTrender for the visby data.
	tempTrender lundTempData = tempTrender("usefulDataLund.dat");
	checkafile:
	 //we call the readFile data function to first create a usefulData file, which improves formatting.
	cout << "Plot average temperature of each day during the chosen year" <<endl;
	cout << "Which of the two cities would you like to do this for? Lund [l], or Visby [v]. " <<endl;
	string cityInput;
	cin >> cityInput;
	cout << "Which year would you like to investigate?" << endl;
	string yearchecked;
	cin >> yearchecked;
	if (cityInput == "l") {
		lundTempData.tempPerDay("Lund", yearchecked);
	}	
	else if (cityInput == "v") {
		visbyTempData.tempPerDay("Visby", yearchecked);
		}
	
	else {cout << "Invalid city." <<endl;
	}
}

void temperatureOnDay(){// calls the tempOnDay function in tempTrender.h
	string VisbyFile = "usefulDataVisby.dat" ;
	string LundFile = "usefulDataLund.dat" ;
	string cityFile;
	string cityName;
	string userInput;
	
	tempTrender daytemp = tempTrender(cityFile);
	cout << "Plotting the average temperatures measured for a given day"<<endl;
	cout << "Would you like to check Lund (l) or Visby (v) data? Enter any other imput in order to quit." << endl;
	cin >> userInput;
	
	if (userInput == "v") { 
		cityFile = VisbyFile;
		cityName = "Visby";
			daytemp.tempOnDay(cityFile,cityName);
	}
	else if (userInput == "l") {
			cityFile = LundFile;
			cityName = "Lund";
			daytemp.tempOnDay(cityFile,cityName);
	}
	else {cout << "very well. " <<endl;}

}

void compareData(){//calls compareData in tempTrender.h
	cout << "Comparing data between the two given data sets." <<endl;
	tempTrender visbyTempData = tempTrender("usefulDataVisby.dat");
	visbyTempData.compareData();
}

void project() {
	string pathToFile = "/home/courseuser/git_project/datasets/smhi-opendata_Visby.csv"; // Only use if you're Albin! Put the path to your data file here
	string pathToVisby = "../datasets/smhi-opendata_Visby.csv"; // Now contains the relative path, works in console, not sure how it will react in code
	
	fileread(); //A full demonstration of our code!
	yearmean();
	temperatureOnDay();
	compareData();
	
}
