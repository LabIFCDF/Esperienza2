
#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TGraph.h>
void Caricamac(){
int n=20000;
int Pmt1[n]; 
int Pmt2[n]; 
int Pmt3[n];
int Pmt4[n]; 
int Pmt5[n];
int Pmt6[n];
int i;
int num=0;
TH1D* h1 =  new TH1D("h1", "Pmt 1",50 ,2,450);
TH1D* h2 =  new TH1D("h2", "Pmt 2",100 ,2,480);
TH1D* h3 =  new TH1D("h3", "Pmt 3",50 ,2,400);
TH1D* h4 =  new TH1D("h4", "Pmt 4",50 ,2,600);
TH1D* h5 =  new TH1D("h5", "Pmt 5",50,2,420 );
TH1D* h6 =  new TH1D("h6", "Pmt 6", 100 ,2,450 );
TCanvas* c1= new TCanvas("c1", "PMT", 2000,500);
TCanvas* c2= new TCanvas("c2", "Pmt1vsAll",2000,500);
TCanvas * c3= new TCanvas("c3", "Pmt2vsAll",2000,500);
 c2->Divide(2,3);
 c3->Divide(2,2);
 c1->Divide(2,3);

      
  ifstream infile;    
  infile.open("DatiM.txt");// file containing numbers in 3 columns 
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
  
   TGraph* g1= new TGraph (n,Pmt1,Pmt2);
 c2->cd(1);
 g1->Draw("AP");
   TGraph* g2= new TGraph (n,Pmt1,Pmt3);
 c2->cd(2);
 g2->Draw("AP");
    TGraph* g3= new TGraph (n,Pmt1,Pmt4);
 c2->cd(3);
 g3->Draw("AP");
    TGraph* g4= new TGraph (n,Pmt1,Pmt5);
 c2->cd(4);
 g4->Draw("AP");
    TGraph* g5= new TGraph (n,Pmt1,Pmt6);
 c2->cd(5);
 g5->Draw("AP");

 TGraph* t1= new TGraph (n,Pmt2,Pmt3);
 c3->cd(1);
 t1->Draw("AP");
 TGraph* t2= new TGraph (n,Pmt2,Pmt4);
 c3->cd(2);
 t2->Draw("AP");
 TGraph* t3= new TGraph (n,Pmt2,Pmt5);
 c3->cd(3);
 t3->Draw("AP");
 TGraph* t4= new TGraph (n,Pmt2,Pmt6);
 c3->cd(4);
 t4->Draw("AP");


 
  for(int i=0; i<=n-1; i++){
    h1->Fill(Pmt1[i]-6);
    h2->Fill((Pmt2[i]-4)/2.5);
    h3->Fill((Pmt3[i]-5)/3);
    h4->Fill((Pmt4[i]-5)/2);
    h5->Fill((Pmt5[i]-6)/2.9);
    h6->Fill((Pmt6[i]-7)*1.2);
  }
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
