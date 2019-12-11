#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TGraph.h>
void EventDisplay(){
int n=50;
int Pmt1[n]; 
int Pmt2[n]; 
int Pmt3[n];
int Pmt4[n]; 
int Pmt5[n];
int Pmt6[n];
int ieve=0;
int num=0;
char a;

   ifstream infile;    
  infile.open("Trigger13.txt");// file containing numbers in 6 columns 
     if(infile.fail()) // checks to see if file opended 
    { 
      cout << "error" << endl;
    } 

 while(!infile.eof()) // reads file to end of *file*, not line
      {  
         infile >> Pmt3[num]; 
	 infile >> Pmt4[num]; 
         infile >> Pmt5[num]; 
         infile >> Pmt6[num]; 


         ++num; // go to the next number
      } 
  infile.close();

TCanvas* c1= new TCanvas("c1", "PMT", 2000,500);
TH2I *g1= new TH2I("g1","EventDisplay",2,0,2,3,0,3);
//TH1I *g1 = new TH1I("g1","EventDisplay",6,0,6);
for(int ieve=0; ieve<n; ieve++){
  if(Pmt6[ieve]<10 && Pmt5[ieve]<10 &&  Pmt4[ieve]<10  &&  Pmt2[ieve]<10);
  else{
  g1->SetBinContent(1,1,Pmt5[ieve]);
  g1->SetBinContent(2,1,Pmt6[ieve]);
  g1->SetBinContent(1,2,0);
  g1->SetBinContent(2,2,Pmt4[ieve]);
  g1->SetBinContent(1,3,0);
  g1->SetBinContent(2,3,Pmt2[ieve]);
   c1->cd();
   g1->Draw("COLZ");
   g1->SetStats(0);
   c1->WaitPrimitive();
   c1->Update();
//Aggiorna la canvas e aspetta il colpo di barra per far vedere quello dopo
 }
 }
 }
