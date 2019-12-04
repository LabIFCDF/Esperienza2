// Simulazione fotoelettroni prodotti dai  dei muoni che passano nel PMT. Produce un grafico sulla distribuzione del numero di fotoelettroni prodotti dal passaggio di una particella carica, MIP, entro il ccalorimetro Cherenkov
#include <cmath>
#include <iostream>
void sguincio(int N){/*N è il numero di generazioni da fare*/
  //Definizione di variabili globali fisiche
  double alpha= 7.2992*1e-3; /*costante di struttura fine*/
  double a = 10.5; /*lato di base*/
  double b = 37; /*lato lungo*/
  double f = 0.20; /*efficienza quantica*/
  double sin2theta_c = 0.7229916; /*angolo cherenkov*/
  double lambda_min = 350*1e-7; /*estremo inferiore lunghezza d'onda*/
  double lambda_max= 500*1e-7; /*estremo superiore lunghezza d'onda*/
  double RapportoAree = M_PI*pow(1.6,2)/(pow(a,2)); /*Accettanza = rapporto delle aree*/
  double EnMIP = 1.5; /*energia persa da una MIP in MeV/g cm^-2*/
  double Rho = 5.5; /*densità*/
  double N_min; /*numero di soglia dei fotoelettroni cherenkov (verticali)*/
  double n_min; /*numero di soglia dei fotoelettroni (verticali) prodotti dalla perdita di energia*/
  
  //Assegnamento variabili fisiche
  double C1 =  2*M_PI*alpha*sin2theta_c*f*((1/lambda_min)-(1/lambda_max))*RapportoAree; /*costante utile (PDG)*/
  double C2 = f*EnMIP*Rho*RapportoAree; /*costante utile (PDG)*/
  N_min = C1*a; /*PDG*/
  n_min = C2*a;/*dalla scheda dell'esperienza*/
  
  //Dichiarazione di variabili ausiliarie
  int A1,A2,A3,A4; /*variabili booleane che servono per identificare i vari sotto casi (caso non sguincio)*/
  int B1,B2,B3,B4; /*variabili booleane che servono per identificare i vari sotto casi (caso  sguincio)*/
  int A;/*variabile booleana che tiene di conto del caso non sguincio-caso sguincio*/
  double x,y,phi,z,theta; /*variabili necessarie: z è cos(theta)*/
  double phi_1, phi_2, phi_3, phi_4; /*4 angoli phi limite*/
  double theta_1, theta_2, theta_3, theta_4; /*4 angoli theta limite*/
  double s,c,Z; /*variabili ausiliarie che fa comodo nella scrittra della lunghezza sguincio*/
  int n; /*numero di fotoelettroni*/
  
  //Definizione funzioni di distribuzione;
  TF1* distribuzioneZeta = new TF1("distribuzioneZeta", "3*(x^2)", 0, 1);
  TF1* distribuzioneTheta = new TF1 ("distribuzioneTheta", "3*((cos(x))^2)*(sin(x))", 0, M_PI/2);
  
  //Definizione istogramma, grafcici, canvas
  TH1* h = new TH1I ("h", "Distribuzione numero di fotoelettroni attesi (#mu); N; occorrenze",sqrt(N), 0-0.5, 6*N_min + 0.5); /*istogramma della distribuzione*/
  TGraph* g1 = new TGraph();
  TGraph* g2 = new TGraph();
  TCanvas* c1 = new TCanvas();/*canvas dello scatter plot*/
  c1->Divide(2,1);
  TCanvas* c2 = new TCanvas();/*canvas dell'istogramma*/
  
  //Generazione pseudocasuale di N numeri 
  for(int i=0; i<N; i++){
    //genero pseudocasualmente x,y,phi,z,secondo le distribuzioni attese;
    x = gRandom->Uniform(0,b); /*posizione x: uniforme tra 0 e b*/
    y = gRandom->Uniform(0,a); /*posizione y: uniforme tra 0 e a*/
    phi = gRandom->Uniform(0, 2*M_PI); /*uniforme tra 0 e 2 pigreco*/
    z = distribuzioneZeta->GetRandom(0,1); /*costheta: distribuito come costheta^2 (dalla scheda)*/
    theta = TMath::ACos(z);/*angolo theta: arcos(z)*/

    //riempie i grafici di controllo
    g1->SetPoint(i,x,y);
    g2->SetPoint(i,phi,theta);
    
    //definisco angoli limite phi (vedi figura)
    phi_1 = TMath::ATan((a-y)/(b-x));
    phi_2 = M_PI/2 + TMath::ATan((x)/(a-y));
    phi_3 = M_PI + TMath::ATan(y/x);
    phi_4 = 2*M_PI - TMath::ATan((y)/(b-x));
    
    //definisco angoli limite theta (vedi figura)
    theta_1 = TMath::ATan((a-y)/(a));
    theta_2 = TMath::ATan((y)/(a));
    theta_3 = TMath::ATan((b-x)/(a));
    theta_4 = TMath::ATan((x)/(a));

    //setto variabili booleane di controllo per la definizione della larghezza (vedi dichiarazione variabili e testo)
    A1 = (phi >= phi_4 && phi <= 2*M_PI) || (phi >= 0 && phi <= phi_1);/*zona 1*/
    A2 =(phi >= phi_1 && phi <= phi_2); /*zona 2*/
    A3 = (phi >= phi_2 && phi <= phi_3); /*zona 3*/
    A4 = (phi >= phi_3  && phi <= phi_4); /*zona 4*/

    B1 = (theta >=0 && theta <= theta_4); /*sguincio zona 1*/
    B2 = (theta >=0 && theta <= theta_1); /*sguincio zona 2*/
    B3 = (theta >=0 && theta <= theta_3); /*sguincio zona 3*/
    B4 = (theta >=0 && theta <= theta_2); /*sguincio zona 4*/
    
    //definisco variabile booleana complessiva_ se è 0 sguincio, se è 1 non sguincio
    A = (A1 && B1) || (A2 && B2) || (A3 && B3) || (A4 && B4);
    
    //calcolo la larghezza attraversata nei vari casi
    if (A == 1){/*se non sguincio*/
      n = (C1+C2)*(a/z); /*la formula è questa*/
      h->Fill(n); /*riempio l'istogramma*/
    }
    if (A == 0){/*se sguincio*/
      //setto alcune abbreviazioni utili
      c = 1/pow((TMath::Cos(phi)),2);
      s = 1/pow((TMath::Sin(phi)),2);
      Z = pow(z,2)/(1- pow(z,2));
      n = (C1+C2)*((b-x)*sqrt(c + Z)*A1 + (a-y)*sqrt(s+Z)*A2 + x*sqrt(c+z)*A3 + y*sqrt(s+z)*A4);/*la formula è questa*/
      h->Fill(n); /*riempio l'istogramma*/
    }
    
  }


  
  // Grafico controllo su x e y
  c1->cd(1);
  g1->SetMarkerStyle(7);
  g1->SetTitle("x vs y; x; y");
  g1->SetLineColor(0);
  g1->Draw();
  // Grafico controllo su theta e phi
  c1->cd(2);
  g2->SetTitle(" #theta vs #varphi; #varphi ;#theta");
  g2->SetMarkerStyle(7);
  g2->SetLineColor(0);
  g2->Draw();

  // Grafico istogramma
  c2->cd();
  h->Draw();
  return;
}

 
   
