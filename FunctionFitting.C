#include<TRandom2.h>
#include<iostream>
#include<fstream>
using namespace std;

void FunctionFitting()
{
   TRandom2 r;
   std::fstream outfile;
   TH1F* h1 = new TH1F("h1","Gaussian random numbers",100,-5,5);
   TCanvas *c1 = new TCanvas("c", "A new canvas", 900,900);
   
  outfile.open("FittingFunction.dat",std::fstream::out | std::fstream::app);
 {
   for(int i =0;i<1000000;i++)
   {
     x = r.Gaus(0.0,1.0);
     h1->Fill(x);
     outfile << x << endl;
     cout<< x << endl;
   }
 }
outfile.close();

   //Double_t norm = h1->GetEntries(); // Method 1
   //h1->Scale(1/norm);

  // Double_t scale = h1->GetXaxis()->GetBinWidth(1)/(h1->GetIntegral());
  // h1->Scale(scale);                // Method 2

   // Double_t norm = 1.0;           // Method 3
   // Double_t scale = norm/(h1->Integral());
  // h1->Scale(scale); 
     h1->Draw();
   cout<< "Mean" << h1->GetMean() << endl;
   cout<< "RMS" << h1->GetRMS() << endl;
   cout << "Nbins" << h1->GetNbinsX() << endl;
   
// Gaussian Fitting 
   Double_t fitf(Double_t *x, Double_t *par)
   {
      Double_t arg = 0;
      if (par[2] != 0) arg = (x[0] - par[1])/par[2];
      Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
      return fitval;
   }


      Float_t Pi = 3.142857143;
      Float_t PI =  sqrt(2*Pi);
      TF1 *fit = new TF1("fit",fitf,-5,5,3);
      fit->SetParameters(1/(PI*h1->GetRMS()),h1->GetMean(),h1->GetRMS());
      fit->SetParNames("Constant","Mean_value","Sigma");
      h1->Fit("fit");
      gStyle->SetOptFit(11111);
      Double_t chi2 =0.0 ;
      chi2 = (fit->GetChisquare())/(fit->GetNDF());
      cout << "Chi2/NDF = " << chi2  << endl;
     // Double_t Integral = 10*fit->Integral(-5,5);  // Integral of fit function 
     // cout<< "Old" << Integral <<  endl;
     // Double_t Integral_new = h1->Integral(1, h1->GetNbinsX(), "width");  // multiplying total no of entries with the bin width
     // cout <<"New ="<< Integral_new << endl;
     

}
