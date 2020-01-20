#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>

void Caricamac(){
int n=12900;
int Pmt1[n]; 
int Pmt2[n]; 
int Pmt3[n];
int Pmt4[n]; 
int Pmt5[n];
int Pmt6[n];
int i;
int num=0;
TH1D* h1 =  new TH1D("h1", "Pmt 1",200 ,0,1200);
TH1D* h2 =  new TH1D("h2", "Pmt 2",200 ,0,1200);
TH1D* h3 =  new TH1D("h3", "Pmt 3",200 ,0,1200);
TH1D* h4 =  new TH1D("h4", "Pmt 4",200 ,0,1200);
TH1D* h5 =  new TH1D("h5", "Pmt 5",200,0,1200 );
TH1D* h6 =  new TH1D("h6", "Pmt 6", 200 ,0,1200 );
TCanvas* c1= new TCanvas("c1", "PMT", 2000,500);






//Legge il file e crea 6 array di punti che rappresentano le misure prese dal camac su ogni singolo canale nell'intero rate di acquisizione    
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


  //Ciclo for per eliminare la baseline + 2 sigma
  for(int i=0; i<=n-1; i++){ 
    Pmt1[i]=Pmt1[i]-9;
    Pmt2[i]=Pmt2[i]-9;
    Pmt3[i]=Pmt3[i]-9;
    Pmt4[i]=Pmt4[i]-9;
    Pmt5[i]=Pmt5[i]-9;
    Pmt6[i]=Pmt6[i]-9;
  }


  //Parte riferita ai plot di correlazione

  

TCanvas* c2= new TCanvas("c2", "Pmt1vs2",2000,500);
TH2I *g1 = new TH2I("g1","Pmt1vs2",50,10,400,50,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g1->Fill(Pmt1[ieve],Pmt2[ieve]);
  c2->cd();
  g1->Draw("COLZ");
  g1->SetStats(0);
  gPad->SetLogz();
TCanvas* c3= new TCanvas("c3", "Pmt1vs3",2000,500);
TH2I *g2 = new TH2I("g2","Pmt1vs3",50,10,400,50,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g2->Fill(Pmt1[ieve],Pmt3[ieve]);
  c3->cd();
  g2->Draw("COLZ");
  g2->SetStats(0);
  gPad->SetLogz();
TCanvas* c4= new TCanvas("c4", "Pmt3vs4",2000,500);
TH2I *g3 = new TH2I("g3","Pmt3vs4",50,10,400,50,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g3->Fill(Pmt3[ieve],Pmt4[ieve]);
  c4->cd();
  g3->Draw("COLZ");
  g3->SetStats(0);
  gPad->SetLogz();
TCanvas* c5= new TCanvas("c5", "Pmt2vs4",2000,500);
TH2I *g4 = new TH2I("g4","Pmt2vs4",50,10,400,50,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g4->Fill(Pmt2[ieve],Pmt4[ieve]);
  c5->cd();
  g4->Draw("COLZ");
  g4->SetStats(0);
  gPad->SetLogz();
TCanvas* c6= new TCanvas("c6", "Pmt1vs5",2000,500);
TH2I *g5 = new TH2I("g5","Pmt1vs5",50,10,400,50,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g5->Fill(Pmt1[ieve],Pmt5[ieve]);
  c6->cd();
  g5->Draw("COLZ");
  g5->SetStats(0);
  gPad->SetLogz();
TCanvas* c7= new TCanvas("c7", "Pmt2vs6",2000,500);
TH2I *g6 = new TH2I("g6","Pmt2vs6",50,10,400,50,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g6->Fill(Pmt2[ieve],Pmt6[ieve]);
  c7->cd();
  g6->Draw("COLZ");
  g6->SetStats(0);
  gPad->SetLogz();
TCanvas* c8= new TCanvas("c8", "Pmt5vs6",2000,500);
TH2I *g7 = new TH2I("g7","Pmt5vs6",50,10,400,50,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g7->Fill(Pmt5[ieve],Pmt6[ieve]);
  c8->cd();
  g7->Draw("COLZ");
  g7->SetStats(0);
  gPad->SetLogz();

TCanvas* c9= new TCanvas("c9", "Pmt1vs4",2000,500);
TH2I *g8 = new TH2I("g8","Pmt1vs4",50,10,400,50,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g8->Fill(Pmt1[ieve],Pmt4[ieve]);
  c9->cd();
  g8->Draw("COLZ");
  g8->SetStats(0);
  gPad->SetLogz();

TCanvas* c10= new TCanvas("c10", "Pmt4vs5",2000,500);
TH2I *g9 = new TH2I("g9","Pmt4vs5",50,10,400,50 ,10,400);
   for(Int_t ieve =0; ieve<n; ieve++)
     g9->Fill(Pmt1[ieve],Pmt4[ieve]);
  c10->cd();
  g9->Draw("COLZ");
  g9->SetStats(0);
  gPad->SetLogz();





  
  //Commentato il TH3I per i grafici di correlazione a 3
  /*TCanvas* c9= new TCanvas("c9", "Pmt1vs3vs5",2000,500);
TH3I *g8 = new TH3I("g8","Pmt1vs3vs5",100,10,400,100,10,400,100,10,400);
 for(Int_t ieve =0; ieve<n; ieve++)
    g8->Fill(Pmt1[ieve],Pmt3[ieve],Pmt5[ieve]);
  c9->cd();
  g8->Draw("BOX2Z");*/
  //Commentato il Graph2D per vedere i picchi di elettrone
  /*TCanvas* c10= new TCanvas("c10", "Pmt1vs3vs5",2000,500);
 TGraph2D *g9= new TGraph2D(n,Pmt1,Pmt3,Pmt5);
 c10->cd();
 g9->Draw("surf1");*/
  


//Parte per gli instogrammi di carica
  
 c1->Divide(2,3);
 /*for(int i=0; i<=n-1; i++){
    h1->Fill(Pmt1[i]);
    h2->Fill(Pmt2[i]);
    h3->Fill(Pmt3[i]);
    h4->Fill(Pmt4[i]);
    h5->Fill(Pmt5[i]);
    h6->Fill(Pmt6[i]);
    }*/
 
//Parte da usare se voglio fare i
 int a=0;
 int b=0;
 int c=0;
 int d=0;
 int e=0;
 int f=0;
 int a1=0;
 int b1=0;
 int r1=0;
 int d1=0;
 int e1=0;
 int f1=0;
 int s1=0;
 int s2=0;
 int s3=0;
 int s4=0;
 int t3=0;
 int t4=0;
 int t5=0;
 int t6=0;
 int m1=53;
 int m2=82;
 int m3=84;
 int m4=42;
 int m5=63;
 int m6=41;
 int dev1=106;
 int dev2=138;
 int dev3=101;
 int dev4=66;
 int dev5=74;
 int dev6=46;
 /* for(int ieve=0; ieve<n; ieve++){
  a =  Pmt1[ieve]>m1;
  b =  Pmt2[ieve]>m2;
  c =  Pmt3[ieve]>m3;
  d =  Pmt4[ieve]>m4;
  e =  Pmt5[ieve]>m5;
  f =  Pmt6[ieve]>m6;
  a1 =  Pmt1[ieve]>(m1 + 2*dev1);
  b1 =  Pmt2[ieve]>(m2 + 2*dev2);
  r1 =  Pmt3[ieve]>(m3 + 2*dev3);
  d1 =  Pmt4[ieve]>(m4 + 2*dev4);
  e1 =  Pmt5[ieve]>(m5 + 2*dev5);
  f1 =  Pmt6[ieve]>(m6 + 2*dev6);
  s1= Pmt1[ieve]> (m1 + dev1);
  s2= Pmt2[ieve]> (m2 + dev2);
  s3= Pmt3[ieve]> (m3 + dev3);
  s4= Pmt4[ieve]> (m4 + dev4);
  t3= Pmt3[ieve]> (m3 + dev3);
  t4= Pmt4[ieve]> (m4 + dev4);
  t5= Pmt5[ieve]> (m5 + dev5);
  t6= Pmt6[ieve]> (m6 + dev6);
  if((s1==1 && s2==1 && s3==1 && s4==1)||(t3==1 && t4==1 && t5==1 && t6==1)||(a==1 && b==1 && c==1 && d==1 && e==1 && f==1)||(a1==1)) h1->Fill(Pmt1[ieve]);
   if((s1==1 && s2==1 && s3==1 && s4==1)||(t3==1 && t4==1 && t5==1 && t6==1)||(a==1 && b==1 && c==1 && d==1 && e==1 && f==1)||(b1==1))h2->Fill(Pmt2[ieve]);
   if((s1==1 && s2==1 && s3==1 && s4==1)||(t3==1 && t4==1 && t5==1 && t6==1)||(a==1 && b==1 && c==1 && d==1 && e==1 && f==1)||(r1==1))h3->Fill(Pmt3[ieve]);
   if((s1==1 && s2==1 && s3==1 && s4==1)||(t3==1 && t4==1 && t5==1 && t6==1)||(a==1 && b==1 && c==1 && d==1 && e==1 && f==1)||(d1==1))h4->Fill(Pmt4[ieve]);
   if((s1==1 && s2==1 && s3==1 && s4==1)||(t3==1 && t4==1 && t5==1 && t6==1)||(a==1 && b==1 && c==1 && d==1 && e==1 && f==1)||(e1==1))h5->Fill(Pmt5[ieve]);
   if((s1==1 && s2==1 && s3==1 && s4==1)||(t3==1 && t4==1 && t5==1 && t6==1)||(a==1 && b==1 && c==1 && d==1 && e==1 && f==1)||(f1==1))h6->Fill(Pmt6[ieve]);
   }*/

 for(int ieve=0; ieve<n; ieve++){
   if(Pmt1[ieve]>9) h1->Fill(Pmt1[ieve]);
   if(Pmt2[ieve]>9) h2->Fill(Pmt2[ieve]);
   if(Pmt3[ieve]>9) h3->Fill(Pmt3[ieve]);
   if(Pmt4[ieve]>9) h4->Fill(Pmt4[ieve]);
   if(Pmt5[ieve]>9) h5->Fill(Pmt5[ieve]);
   if(Pmt6[ieve]>9) h6->Fill(Pmt6[ieve]);}
  c1->cd(1);
  h1->Draw();
  gPad->SetLogy();
  h1->SetStats(0);
  c1->cd(2);
  h2->Draw();
  h2->SetStats(0);
  gPad->SetLogy();
  c1->cd(3);
  h3->Draw();
  h3->SetStats(0);
  gPad->SetLogy();
  c1->cd(4);
  h4->Draw();
  h4->SetStats(0);
  gPad->SetLogy();
  c1->cd(5);
  h5->Draw();
  h5->SetStats(0);
  gPad->SetLogy();
  c1->cd(6);
  h6->Draw();
  h6->SetStats(0);
  gPad->SetLogy();

double z1=0;
double v1=0;
double Accettanza1=0.2870;
double eff1=0;
  for (int i=0; i<=n-1; i++){
    if(Pmt1[i]<=0) 
	     {z1++;}
    else v1++;
  }
  eff1= (n-Accettanza1*n-v1) / (n-Accettanza1*n);
   cout<<eff1<<endl;
double z2=0;
double v2=0;
double Accettanza2=0.2741;
double eff2=0;
  for (int i=0; i<=n-1; i++){
    if(Pmt2[i]<=0) 
	     {z2++;}
    else v2++;
  }
  eff2= (n-Accettanza2*n-v1) / (n-Accettanza2*n);
   cout<<eff2<<endl; 
double z3=0;
double v3=0;
double Accettanza3=0.3112;
double eff3=0;
  for (int i=0; i<=n-1; i++){
    if(Pmt3[i]<=0) 
	     {z3++;}
    else v3++;
  }
  eff3= (n-Accettanza3*n-v1) / (n-Accettanza3*n);
   cout<<eff3<<endl; 
double z4=0;
double v4=0;
double Accettanza4=0.367;
double eff4=0;
  for (int i=0; i<=n-1; i++){
    if(Pmt4[i]<=0)
	     {z4++;}
    else v4++;
  }
  eff4= (n-Accettanza4*n-v1) / (n-Accettanza4*n);
   cout<<eff4<<endl;
double z5=0;
double v5=0;
double Accettanza5=0.299;
double eff5=0;
  for (int i=0; i<=n-1; i++){
    if(Pmt5[i]<=0) 
	     {z5++;}
    else v5++;
  }
  eff5= (n-Accettanza5*n-v1) / (n-Accettanza5*n);
   cout<<eff5<<endl;
double z6=0;
double v6=0;
double Accettanza6=0.340;
double eff6=0;
  for (int i=0; i<=n-1; i++){
    if(Pmt6[i]<=0)
	     {z6++;}
    else v6++;
  }
  eff6= (n-Accettanza6*n-v1) / (n-Accettanza6*n);
   cout<<eff6<<endl;
  } 
