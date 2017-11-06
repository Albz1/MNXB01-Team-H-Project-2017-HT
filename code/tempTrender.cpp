#include <iostream>
#include "tempTrender.h"
#include <vector>

using namespace std;

tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
}

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
	cout << "Do you want to find the mean temperatures during a single year? [y]/[n]"<<endl;
	string userInput;
	cin >> userInput;
	 //we call the readFile data function to first create a usefulData file, which improves formatting.
	if (userInput == "y") {  //we ask the user if they want to create new data files for lund or visby. 
		cout << "Which of the two cities would you like to do this for? Lund [l], or Visby [v]. " <<endl;
		string cityInput;
		cin >> cityInput;
		cout << "Which year would you like to investigate?" << endl;
		int yearchecked;
		cin >> yearchecked;
		if (cityInput == "l") {
			lundTempData.tempPerDay("Lund", yearchecked);
			goto checkafile;
		}	
		else if (cityInput == "v") {
			visbyTempData.tempPerDay("Visby", yearchecked);
			goto checkafile;
		}
	}
	else {cout << "very well. " <<endl;
	}
}
void compareData(){
	tempTrender visbyTempData = tempTrender("usefulDataVisby.dat");
	visbyTempData.compareData();
}

void temperatureOnDay(){
	string cityFile = "usefulDataVisby.dat" ;
	/*
	string userInput;

	cout << "Would you like to check Lund (l) or Visby (v) data?" << endl;
	if (userInput == "v") { 
		cityFile = "usefulDataVisby.dat";
	}
	else if (userInput == "l") {
			cityFile = "usefulDataLund.dat";
	}
	else {cout << "very well. " <<endl;}
	*/
	tempTrender daytemp = tempTrender(cityFile);
	daytemp.tempOnDay(cityFile);
	


}

void GYcomparison(){
	string cityFile = "usefulDataVisby.dat" ;
	
	tempTrender Variance(cityFile);
	Variance.GY_comparison(cityFile);
}
void compareData(){
	tempTrender visbyTempData = tempTrender("usefulDataVisby.dat");
	visbyTempData.compareData();
} 




