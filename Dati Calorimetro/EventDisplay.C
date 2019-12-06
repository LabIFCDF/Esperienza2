#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TGraph.h>
void EventDisplay(){
int n=20;
int Pmt1[n]; 
int Pmt2[n]; 
int Pmt3[n];
int Pmt4[n]; 
int Pmt5[n];
int Pmt6[n];
int i=0;
int num=0;

   ifstream infile;    
  infile.open("DatiDisplay.txt");// file containing numbers in 6 columns 
     if(infile.fail()) // checks to see if file opended 
    { 
      cout << "error" << endl;
    } 

 while(!infile.eof()) // reads file to end of *file*, not line
      { 
         infile >> Pmt1[num];
         infile >> Pmt2[num]; 
         infile >> Pmt3[num]; 
	 infile >> Pmt4[num]; 
         infile >> Pmt5[num]; 
         infile >> Pmt6[num]; 


         ++num; // go to the next number
      } 
  infile.close();

TCanvas* c1= new TCanvas("c1", "PMT", 2000,500);
TH2I *g1= new TH2I("g1","EventDisplay",2,0,2,3,0,3);
 for(int ieve=0; ieve<n; ieve++){
   g1->AddBinContent(1,Pmt6[i]);
   g1->AddBinContent(2,Pmt5[i]);
   g1->AddBinContent(3,Pmt4[i]);
   g1->AddBinContent(4,Pmt3[i]);
   g1->AddBinContent(5,Pmt2[i]);
   g1->AddBinContent(6,Pmt1[i]);
   c1->cd();
   g1->Draw("COLZ");
   gPad->WaitPrimitive();
//Aggiorna la canvas e aspetta il colpo di barra per far vedere quello dopo
 }
 }
