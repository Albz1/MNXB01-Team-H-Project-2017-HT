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


void TestHistogram( Int_t nEntries, Int_t Measurement ) {
	
	  // create histogram that we will fill with random values
	TH1D* hTemp = new TH1D("hTemp", "ROOT func generated Temperature distribution; x; Counts", 
			100, -20, 20);
			
/*	string helpString;
	ifstream file( "phi_dist.dat"); //need to be specified
	
	while(file >> helpString >> eventNo){ */
	
	 // Define the function we want to generate
    TF1* fTemp = new TF1("fTemp", "[0]", -20, 20); //Just to have the temperature input be some function rng values
	
	Double_t SumT =0;
	Double_t VecTemp[nEntries];
	fTemp->SetParameter(0,Measurement);
	for (Int_t nt = 0; nt < nEntries; nt++){
			//Fill the array
			Int_t Measurement;
	       VecTemp[nt] = fTemp->GetRandom();
	       cout << nt << " : " << VecTemp[nt] << endl; 
	       
	       SumT += VecTemp[nt]; 
	 } 
	Double_t AverageT = SumT/nEntries;
	Double_t SumDiff = 0;
	
	for(Int_t i = 0; i< nEntries; i++){
		Double_t Diff = (VecTemp[i] - AverageT)*(VecTemp[i] - AverageT);
		SumDiff += Diff;
	}
	Double_t Variance = SumDiff/nEntries;

		
//		cout << VecTemp[i] << endl; //Prints the same as above
	for(Int_t k = 0; k < nEntries; k++){
			hTemp->Fill(VecTemp[k]);
//			hTemp->SetBinError(k, sqrt(Variance));	
		} 
		

  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // create canvas for hPhi
  TCanvas* c1 = new TCanvas("c1", "hTemp canvas", 900, 600);
  hTemp->SetMinimum(0);
  hTemp->Draw();
  hTemp->SetAxisRange(0, 20, "Y"); //sets the axis range
  hTemp->SetTitle("Temperature [C]; Hello; Bye" ); //sets the lable of axis
  
  
  // Save the canvas as a picture
  c1->SaveAs("Temp_rootfunc.jpg");
}

/* void Histogram_2D( ){
	
   TCanvas *c1 = new TCanvas("c1", "c1",900,900);
   gStyle->SetOptStat(0);
   
   // Create the three pads
   TPad *center_pad = new TPad("center_pad", "center_pad",0.0,0.0,0.6,0.6);
   center_pad->Draw();

   right_pad = new TPad("right_pad", "right_pad",0.55,0.0,1.0,0.6);
   right_pad->Draw();

   top_pad = new TPad("top_pad", "top_pad",0.0,0.55,0.6,1.0);
   top_pad->Draw(); 

   // Create, fill and project a 2D histogram.
   TH2F *h2 = new TH2F("h2","",40,-4,4,40,-20,20);
   Float_t px, py;
   for (Int_t i = 0; i < 25000; i++) {
      gRandom->Rannor(px,py);
      h2->Fill(px,5*py);
   }
   TH1D * projh2X = h2->ProjectionX();
   TH1D * projh2Y = h2->ProjectionY();

   // Drawing
   center_pad->cd();
   gStyle->SetPalette(1);
   h2->Draw("COL");

   top_pad->cd();
   projh2X->SetFillColor(kBlue+1);
   projh2X->Draw("bar");

   right_pad->cd();
   projh2Y->SetFillColor(kBlue-2);
   projh2Y->Draw("hbar");
   
   c1->cd();
   TLatex *t = new TLatex();
   t->SetTextFont(42);
   t->SetTextSize(0.02);
   t->DrawLatex(0.6,0.88,"This example demonstrate how to display");
   t->DrawLatex(0.6,0.85,"a histogram and its two projections."); 
}*/

 
