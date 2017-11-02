#include "tempTrender.h"
#include <string>
#include <fstream>
#include <vector>
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
	
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);

}
