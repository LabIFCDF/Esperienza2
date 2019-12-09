#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TGraph.h>
void Caricamac(){
int n=70500;
int Pmt1[n]; 
int Pmt2[n]; 
int Pmt3[n];
int Pmt4[n]; 
int Pmt5[n];
int Pmt6[n];
int i;
int z1=0;
int v1=0;
int num=0;
TH1D* h1 =  new TH1D("h1", "Pmt 1",200 ,2,1200);
TH1D* h2 =  new TH1D("h2", "Pmt 2",200 ,2,1200);
TH1D* h3 =  new TH1D("h3", "Pmt 3",200 ,2,1200);
TH1D* h4 =  new TH1D("h4", "Pmt 4",200 ,2,1200);
TH1D* h5 =  new TH1D("h5", "Pmt 5",200,2,1200 );
TH1D* h6 =  new TH1D("h6", "Pmt 6", 200 ,2,1200 );
TCanvas* c1= new TCanvas("c1", "PMT", 2000,500);



c1->Divide(2,3);

      
  ifstream infile;    
  infile.open("DatiFinali.txt");// file containing numbers in 6 columns 
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

  for(int i=0; i<=n-1; i++){  //Ciclo for per riscalare da eliminare in seguito
    Pmt1[i]=Pmt1[i]-7;
    Pmt2[i]=Pmt2[i]-7;
    Pmt3[i]=Pmt3[i]-7;
    Pmt4[i]=Pmt4[i]-7;
    Pmt5[i]=Pmt5[i]-7;
    Pmt6[i]=Pmt6[i]-7;
  }
TCanvas* c2= new TCanvas("c2", "Pmt1vs2",2000,500);
TH2I *g1 = new TH2I("g1","Pmt1vs2",100,10,1200,100,10,1200);
   for(Int_t ieve =0; ieve<n; ieve++)
     g1->Fill(Pmt1[ieve],Pmt2[ieve]);
  c2->cd();
  g1->Draw("COLZ");
  gPad->SetLogz();
TCanvas* c3= new TCanvas("c3", "Pmt1vs3",2000,500);
TH2I *g2 = new TH2I("g2","Pmt1vs3",100,10,1200,100,10,1200);
   for(Int_t ieve =0; ieve<n; ieve++)
     g2->Fill(Pmt1[ieve],Pmt3[ieve]);
  c3->cd();
  g2->Draw("COLZ");
  gPad->SetLogz();
TCanvas* c4= new TCanvas("c4", "Pmt3vs4",2000,500);
TH2I *g3 = new TH2I("g3","Pmt3vs4",100,10,1200,100,10,1200);
   for(Int_t ieve =0; ieve<n; ieve++)
     g3->Fill(Pmt3[ieve],Pmt4[ieve]);
  c4->cd();
  g3->Draw("COLZ");
  gPad->SetLogz();
TCanvas* c5= new TCanvas("c5", "Pmt2vs4",2000,500);
TH2I *g4 = new TH2I("g4","Pmt2vs4",100,10,1200,100,10,1200);
   for(Int_t ieve =0; ieve<n; ieve++)
     g4->Fill(Pmt2[ieve],Pmt4[ieve]);
  c5->cd();
  g4->Draw("COLZ");
  gPad->SetLogz();
TCanvas* c6= new TCanvas("c6", "Pmt1vs5",2000,500);
TH2I *g5 = new TH2I("g5","Pmt1vs5",100,10,1200,100,10,1200);
   for(Int_t ieve =0; ieve<n; ieve++)
     g5->Fill(Pmt1[ieve],Pmt5[ieve]);
  c6->cd();
  g5->Draw("COLZ");
  gPad->SetLogz();
TCanvas* c7= new TCanvas("c7", "Pmt2vs6",2000,500);
TH2I *g6 = new TH2I("g6","Pmt2vs6",100,10,1200,100,10,1200);
   for(Int_t ieve =0; ieve<n; ieve++)
     g6->Fill(Pmt2[ieve],Pmt6[ieve]);
  c7->cd();
  g6->Draw("COLZ");
  gPad->SetLogz();
TCanvas* c8= new TCanvas("c8", "Pmt5vs6",2000,500);
TH2I *g7 = new TH2I("g7","Pmt5vs6",100,10,1200,100,10,1200);
   for(Int_t ieve =0; ieve<n; ieve++)
     g7->Fill(Pmt5[ieve],Pmt6[ieve]);
  c8->cd();
  g7->Draw("COLZ");
  gPad->SetLogz();
  

  
/*Tutto questo pezzo serve per fare gli scatter plot, che però non ci interssano più perché i TH" sono molto più fighi
c2->Divide(2,3);
c3->Divide(2,2);
TGraph* g1= new TGraph (n,Pmt1,Pmt2);
   c2->cd();
   g1->SetMarkerStyle(1);
   g1->Draw("AP");
TGraph* g2= new TGraph (n,Pmt1,Pmt3);
   g2->SetMarkerStyle(1);
   g2->Draw("AP");
TGraph* g3= new TGraph (n,Pmt1,Pmt4);
   c4->cd();
   g3->SetMarkerStyle(1);
   g3->Draw("AP");
TGraph* g4= new TGraph (n,Pmt1,Pmt5);
   c5->cd();
   g4->SetMarkerStyle(1);
   g4->Draw("AP");
TGraph* g5= new TGraph (n,Pmt1,Pmt6);
   c6->cd();
   g5->SetMarkerStyle(1);
   g5->Draw("AP");

 TGraph* t1= new TGraph (n,Pmt2,Pmt3);
   d1->cd();
   t1->SetMarkerStyle(1);
   t1->Draw("AP");
 TGraph* t2= new TGraph (n,Pmt2,Pmt4);
   d2->cd();
   t2->SetMarkerStyle(1);
   t2->Draw("AP");
 TGraph* t3= new TGraph (n,Pmt2,Pmt5);
   d3->cd();
   t3->SetMarkerStyle(1);
   t3->Draw("AP");
 TGraph* t4= new TGraph (n,Pmt2,Pmt6);
   d4->cd();
   t4->SetMarkerStyle(1);
   t4->Draw("AP");
   */

 
  for(int i=0; i<=n-1; i++){
    h1->Fill(Pmt1[i]);
    h2->Fill(Pmt2[i]);
    h3->Fill(Pmt3[i]);
    h4->Fill(Pmt4[i]);
    h5->Fill(Pmt5[i]);
    h6->Fill(Pmt6[i]);
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


  for (int i=0; i<=n-1; i++){
    if(Pmt1[i]<=9) //fissato baseline+2 per starci larghi
	     {z1++;}
    else v1++;
  }
  printf("%d/" , z1);
  printf("/%d", v1);
  /*eff1= (n-Accettanza*n-v1) / (n-Accettanza*n) */
  
} 
