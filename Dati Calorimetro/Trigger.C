#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TGraph.h>
void Trigger(){
int n=12900;
int Pmt1[n]; 
int Pmt2[n]; 
int Pmt3[n];
int Pmt4[n]; 
int Pmt5[n];
int Pmt6[n];
int ieve=0;
int num=0;
int a=0;
int b=0;
int c=0;
int d=0;
int e=0;
int f=0;

TH1D* h1 =  new TH1D("h1", "Pmt 1",200 ,10,1200);
 TH1D* h2 =  new TH1D("h2", "Pmt 2",200 ,10,1200);
TH1D* h3 =  new TH1D("h3", "Pmt 3",200 ,10,1200);
TH1D* h4 =  new TH1D("h4", "Pmt 4",200 ,10,1200);
TH1D* h5 =  new TH1D("h5", "Pmt 5",200,10,1200 );
TH1D* h6 =  new TH1D("h6", "Pmt 6", 200 ,10,1200 );
TCanvas* c1= new TCanvas("c1", "PMT", 2000,500);

   ifstream infile;    
  infile.open("3PMT.txt");// file containing numbers in 6 columns 
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


TCanvas* c2= new TCanvas("c2", "EventDisplay", 2000,500);
TH2I *g1= new TH2I("g1","EventDisplay",2,0,2,3,0,3);
for(int ieve=0; ieve<n; ieve++){
  a =  Pmt1[ieve]>30;
  b =  Pmt2[ieve]>30;
  c =  Pmt3[ieve]>30;
  d =  Pmt4[ieve]>30;
  e =  Pmt5[ieve]>130;
  f =  Pmt6[ieve]>30;
  if(a==1 && b==1 && c==1 && d==1){
  h1->Fill(Pmt1[ieve]);
  h2->Fill(Pmt2[ieve]);
  h3->Fill(Pmt3[ieve]);
  h4->Fill(Pmt4[ieve]);
  h5->Fill(Pmt5[ieve]);
  h6->Fill(Pmt6[ieve]);
  }
  /* int A = a || b || c || d || e || f;
  if(A==1){
    g1->SetBinContent(1,1,Pmt5[ieve]);
  g1->SetBinContent(2,1,Pmt6[ieve]);
  g1->SetBinContent(1,2,Pmt3[ieve]);
  g1->SetBinContent(2,2,Pmt4[ieve]);
  g1->SetBinContent(1,3,Pmt1[ieve]);
  g1->SetBinContent(2,3,Pmt2[ieve]);

   c2->cd();
   g1->Draw("COLZ");
   g1->SetStats(0);
   c2->WaitPrimitive();
   c2->Update();
//Aggiorna la canvas e aspetta il colpo di barra per far vedere quello dopo
}*/
 }

  c1->Divide(2,3);
   

  c1->cd(1);
  h1->Draw();
  c1->cd(2);
  h2->Draw();
  c1->cd(3);
  h3->Draw();
  c1->cd(4);
  h4->Draw();
  c1->cd(5);
  h5->Draw();
  c1->cd(6);
  h6->Draw();


 }
