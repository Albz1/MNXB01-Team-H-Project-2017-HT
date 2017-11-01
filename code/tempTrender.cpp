#include <iostream>
#include "tempTrender.h"

using namespace std;

tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
}

void junkfunc() {
	string visbyDatafilePath = "../datasets/smhi-opendata_Visby.csv"; //a relative path to the visby data file in the directory tree.
	string lundDatafilePath = "../datasets/smhi-opendata_Lund.csv"; //to lund
	tempTrender visbyTempData = tempTrender(visbyDatafilePath); // we create a new instance of the object tempTrender for the visby data.
	tempTrender lundTempData = tempTrender(lundDatafilePath);
	createfile:
	cout << "do you want to create new useful data file paths for any of the two cities we analyze? [y]/[n]"<<endl;
	string userInput;
	cin >> userInput;
	 //we call the readFile data function to first create a usefulData file, which improves formatting.
	if (userInput == "y") {  //we ask the user if they want to create new data files for lund or visby. 
		cout << "which of the two cities would you like? Lund [l], or Visby [v]. " <<endl;
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
