#include <iostream>
#include "tempTrender.h"

using namespace std;

tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
}

void junkfunc() {
	string datafile = "../datasets/smhi-opendata_Visby.csv"; //a relative path to the visby data file in the directory tree.
	tempTrender visbyTempData = tempTrender("../datasets/smhi-opendata_Visby.csv"); // we create a new instance of the object tempTrender for the visby data.
	visbyTempData.readFile(datafile); //we call the readFile data function to first create a usefulData file, which improves formatting.
	//Since this function takes a long time for large data sets, we could have the user be prompted to call this function.
}
