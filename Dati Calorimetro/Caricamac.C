
#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TCanvas.h>
void Caricamac(){
int Pmt1[1000];// array that can hold 100 numbers for 1st column 
int Pmt2[1000];// array that can hold 100 numbers for 2nd column 
int Pmt3[1000];// array that can hold 100 numbers for 3rd column
int Pmt4[1000];// array that can hold 100 numbers for 1st column 
int Pmt5[1000];// array that can hold 100 numbers for 2nd column 
int Pmt6[1000];// array that can hold 100 numbers for 3rd column
int i;
int num=0;
TH1D* h1 =  new TH1D("h1", "Pmt 1",1000 ,2,2000);
TH1D* h2 =  new TH1D("h2", "Pmt 2",1000 ,2,2000);
TH1D* h3 =  new TH1D("h3", "Pmt 3",1000  ,2,2000);
TH1D* h4 =  new TH1D("h4", "Pmt 4",1000 ,2,2000);
TH1D* h5 =  new TH1D("h5", "Pmt 5",1000  ,2,2000 );
TH1D* h6 =  new TH1D("h6", "Pmt 6", 1000 ,2,2000 );
TCanvas* c1= new TCanvas("c1", "PMT", 20000,5000);
 c1->Divide(2,3);

      
  ifstream infile;    
  infile.open("DatiM1.txt");// file containing numbers in 3 columns 
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

  for(int i=0; i<=999; i++){
      h1->Fill(Pmt1[i]-6);
      h2->Fill(Pmt2[i]-4);
      h3->Fill(Pmt3[i]-5);
      h4->Fill(Pmt4[i]-5);
      h5->Fill(Pmt5[i]-6);
      h6->Fill(Pmt6[i]-7);
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
