#define rec_cxx
#include "rec.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <cmath>
void rec::Loop()
{
//   In a ROOT session, you can do:
//      root> .L rec.C
//      root> rec t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

   if (fChain == 0) return;
   
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   double charge_w0[5000] = {0};
   double charge_w1[5000] = {0};
   double charge_w2[5000] = {0};
   double charge_w3[5000] = {0};
   double charge_w4[5000] = {0};
   double charge_w5[5000] = {0};
   double charge_w6[5000] = {0};
   double charge_w7[5000] = {0};
   double media_w6 = 0;
   double var_w6 = 0;
   double media_w7 = 0;
   double var_w7 = 0;
   TCanvas* c1 = new TCanvas("c1", "Tutti i PMT", 2000, 500);
   c1->Divide(2,3);
   TH1F* h0 = new TH1F("h1", "PMT1", 150, -4.0, 0);
   TH1F* h1 = new TH1F("h2", "PMT2", 150, -4.0, 0);
   TH1F* h2 = new TH1F("h3", "PMT3", 150, -4.0, 0);
   TH1F* h3 = new TH1F("h4", "PMT4", 150, -4.0, 0);
   TH1F* h4 = new TH1F("h5", "PMT5", 150, -4.0, 0);
   TH1F* h5 = new TH1F("h6", "PMT6", 150, -4.0, 0);
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
   	GetEntry(jentry);
	Long64_t ientry = LoadTree(jentry);
	
	for (Long64_t j = 0; j < 1024; j++) 
	{
		
      		charge_w0[jentry] += w0[j];
      		charge_w1[jentry] += w1[j];
      		charge_w2[jentry] += w2[j];
      		charge_w3[jentry] += w3[j];
      		charge_w4[jentry] += w4[j];
      		charge_w5[jentry] += w5[j];
      		charge_w6[jentry] += w6[j];
      		charge_w7[jentry] += w7[j];
        }
        //SOMMO BASELINE CALCOLATA SOTTO
        //COMMENTARE QUANDO SI ACQUISISCONO NUOVI DATI
      	charge_w0[jentry] += 2;
      	charge_w1[jentry] += 2;
      	charge_w2[jentry] += 2;
      	charge_w3[jentry] += 2;
      	charge_w4[jentry] += 2;
      	charge_w5[jentry] += 2;
      	charge_w6[jentry] += 2;
      	charge_w7[jentry] += 2;
    	
    	    
   }
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
   	//printf("%lf;", charge_w0[jentry]);
   	h0->Fill(charge_w0[jentry]);
   }
   c1->cd(1);
   h0->Draw();
   printf("\n");
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
    	//printf("%lf;", charge_w1[jentry]);
    	h1->Fill(charge_w1[jentry]);
   }
   c1->cd(2);
   h1->Draw();
   printf("\n");
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
    	//printf("%lf;", charge_w2[jentry]);
    	h2->Fill(charge_w2[jentry]);
   }
   c1->cd(3);
   h2->Draw();
   printf("\n");
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
    	//printf("%lf;", charge_w3[jentry]);
    	h3->Fill(charge_w3[jentry]);
   }
   c1->cd(4);
   h3->Draw();   
   printf("\n");
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
   	//printf("%lf;", charge_w4[jentry]);
   	h4->Fill(charge_w4[jentry]);
   }
   c1->cd(5);
   h4->Draw();   
   printf("\n");
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
    	//printf("%lf;", charge_w5[jentry]);
    	h5->Fill(charge_w5[jentry]);
   }
   c1->cd(6);
   h5->Draw();   
   printf("\n");
   /*
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
    	printf("%lf;", charge_w6[jentry]);
   }
   printf("\n");
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
    	printf("%lf;", charge_w7[jentry]);
   }
   printf("\n");*/

   
   //media e varianza rumore, commentare se si studia un altro dataset
   //file da 5000 dati usiamo -1.73 -0.13 -0.13=-2
   
  /* for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
   	media_w6 += charge_w6[jentry];
   	media_w7 += charge_w7[jentry];
   }

   media_w6 = media_w6/nentries;
   media_w7 = media_w7/nentries;
   printf("La media del rumore nel canale 6 è:%lf\n", media_w6);
   printf("La media del rumore nel canale 7 è:%lf\n", media_w7);
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
   	var_w6 += pow(charge_w6[jentry]-media_w6, 2);
   	var_w7 += pow(charge_w7[jentry]-media_w7, 2);
   	
   }
   var_w6=var_w6/(nentries-1);
   var_w7=var_w7/(nentries-1);
   printf("La var del rumore nel canale 6 è:%lf\n", sqrt(var_w6));
   printf("La var del rumore nel canale 7 è:%lf\n", sqrt(var_w7));
   printf("\n");*/
   
   //file da 5000-> sommo 2 a tutti i segnali
   
   
   
   
   
 			
   
}
