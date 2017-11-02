#include "tempTrender.h"
#include <string>
#include <fstream>
<<<<<<< HEAD
<<<<<<< HEAD
#include <limits>
=======
>>>>>>> 84497f606cdb3e19ae5be378cd1b2a7252194663
=======
#include <vector>
>>>>>>> 524ab4bed4a2441c5f2385906dd2ec4313892daf
using namespace std;
//Root libraries
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object


void project() {
<<<<<<< HEAD
<<<<<<< HEAD
	string pathToFile = "/home/courseuser/git_project/datasets/smhi-opendata_Visby.csv"; // Only use if you're Albin! Put the path to your data file here
	
=======
	string pathToVisby = "../datasets/smhi-opendata_Visby.csv"; // Now contains the relative path, works in console, not sure how it will react in code
	string pathToLund = "../datasets/smhi-opendata_Lund.csv";

>>>>>>> 84497f606cdb3e19ae5be378cd1b2a7252194663
=======
	string pathToVisby = "../datasets/smhi-opendata_Visby.csv"; // Now contains the relative path, works in console, not sure how it will react in code
	string pathToLund = "../datasets/smhi-opendata_Lund.csv";

>>>>>>> 524ab4bed4a2441c5f2385906dd2ec4313892daf
	//tempTrender t(pathToFile); //Instantiate your analysis object
	
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
<<<<<<< HEAD
	
	//Let's try to read the data file!
	/* The structure of the data file is: 
	 * 10 lines of redundant information
	 * YYYY-MM-DD;hh:mm:ss;-T.T;(G/Y) What is G/Y?
	 */
=======
>>>>>>> 524ab4bed4a2441c5f2385906dd2ec4313892daf

}
