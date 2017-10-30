#include "tempTrender.h"
#include <string>
using namespace std;
//Root libraries
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object


void project() {
	string pathToVisby = "../datasets/smhi-opendata_Visby.csv"; // Now contains the relative path, works in console, not sure how it will react in code
	string pathToLund = "../datasets/smhi-opendata_Lund.csv";
	//tempTrender t(pathToFile); //Instantiate your analysis object
	/* USE IF YOU'RE NOT ALBIN
	cout << "Input path to requested datafile, please." << endl;
	cin >> pathToFile;
	*/
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
	
	//Let's try to read the data file!
	/* The structure of the data file is: 
	 * 10 lines of redundant information
	 * YYYY-MM-DD;hh:mm:ss;-T.T;(G/Y) What is G/Y?
	 */
}
