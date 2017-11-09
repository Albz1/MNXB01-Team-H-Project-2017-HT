#include <iostream>
#include "tempTrender.h"
#include <vector>

using namespace std;

tempTrender::tempTrender(string filePath) {}

void fileread() {
	string visbyDatafilePath = "../datasets/smhi-opendata_Visby.csv"; //a relative path to the visby data file in the directory tree.
	string lundDatafilePath = "../datasets/smhi-opendata_Lund.csv"; //to lund
	tempTrender visbyTempData = tempTrender(visbyDatafilePath); // we create a new instance of the object tempTrender for the visby data.
	tempTrender lundTempData = tempTrender(lundDatafilePath);
	createfile:
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
	cout << "Which of the two cities would you like to do this for? Lund [l], or Visby [v]. " <<endl;
	string cityInput;
	cin >> cityInput;
	cout << "Which year would you like to investigate?" << endl;
	string yearchecked;
	cin >> yearchecked;
	if (cityInput == "l") {
		lundTempData.tempPerDay("Lund", yearchecked);
		goto checkafile;
	}	
	else if (cityInput == "v") {
		visbyTempData.tempPerDay("Visby", yearchecked);
		goto checkafile;
		}
	
	else {cout << "Invalid city." <<endl;
	}
}

void temperatureOnDay(){// calls the temperatureOnDay function in tempTrender.h
	string VisbyFile = "usefulDataVisby.dat" ;
	string LundFile = "usefulDataLund.dat" ;
	string cityFile;
	string cityName;
	string userInput;
	
	tempTrender daytemp = tempTrender(cityFile);

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
	tempTrender visbyTempData = tempTrender("usefulDataVisby.dat");
	visbyTempData.compareData();
}




