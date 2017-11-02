<<<<<<< HEAD
// include C++ STL headers 
#include <iostream>
#include <fstream>

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object 


=======
>>>>>>> 524ab4bed4a2441c5f2385906dd2ec4313892daf
void rootlogon() {
	
/*	  // create histogram that we will fill with random values
	TH1D* hTemp = new TH1D("hTemp", "ROOT func generated Temperature distribution; x; Counts", 
			100, -49, 50);
			
	string helpString;
	ifstream file( "phi_dist.dat"); //need to be specified
	
	while(file >> helpString >> eventNo){
			
		// create canvas for hPhi
	TCanvas* c1 = new TCanvas("c1", "Phi", 900, 600);
	hPhi->SetMinimum(0);
	hPhi->Draw();		
	  // Save the canvas as a picture
	c1->SaveAs("Temp_rootfunc.jpg"); */
			
  gStyle->SetOptStat(0); //Let's make our plots look a bit better. Get rid of the stat box
  gStyle->SetOptTitle(0); //Get rid of the title (good plots use legends instead)
  gStyle->SetTitleSize(0.05, "x"); //Use bigger text on the axes
  gStyle->SetTitleSize(0.05, "y");
  gStyle->SetLabelSize(0.05, "x"); //Use bigger labels too
  gStyle->SetLabelSize(0.05, "y");
  gStyle->SetPadTopMargin(0.05); //Change the margins to fit our new sizes
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.16);
  
  gROOT->ProcessLine(".L tempTrender.cpp+"); //Load the classes that we want to use automatically - Convenient!
  gROOT->ProcessLine(".L project.cpp+"); //The + means to recompile only if it changed sine last time
  //Now you can type project() to invoke the function defined in project
  //You can also create and invoke functions in a temptrender manually by doing e.g. tempTrender t(pathToFile); t.hotCold();
}
