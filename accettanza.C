// Calcolo accettanza geometrica
#include <cmath>
#include <iostream>
void accettanza(int N, int K){/*N è il numero di simulazioni da fare, K è il numero di PMT*/
  //Variabili globali fisiche
  double a = 10.5; /*lato di base di singolo PMT*/
  double b = 37; /*lato lungo di singolo PMT*/
  double a0 = 7, b0 = 7; /*posizionamento pmt*/
  double A = 35; /*lato corto TRIGGER*/
  double B = 50; /*lato lungo TRIGGER*/

  //Dichiarazione variabili ausiliarie TRIGGER
  double x,y,z,theta, phi; /*Variabili da generare*/
  double Phi_1,Phi_2,Phi_3,Phi_4; /*Angoli phi Trigger*/
  double Theta_1, Theta_2, Theta_3, Theta_4; /*Angoli Theta trigger*/
  int A1,A2,A3,A4; /*variabili booleane angolo Phi*/
  int B1,B2,B3,B4; /*variabili booleane angolo Theta*/
  int T; /*variabile booleana trigger*/

  //Dichiarazione variabili ausiliarie PMT
  double theta1, theta2, theta3, theta4, phi21, phi22, phi41, phi42, phi51, phi52,phi71, phi72; /*angoli theta e phi limite*/
  double thetas11, thetas21, thetas31, thetas41; /*angoli limite zona sopra*/
  double thetas12, thetas22, thetas32, thetas42; /*angoli limite zona sopra*/
  double phi1L1, phi1L2, phi6L1, phi6L2, phi8L1, phi8L2, phi3L1, phi3L2; /*angoli sguincio L*/
  double phi1l1, phi1l2, phi6l1, phi6l2, phi8l1, phi8l2, phi3l1, phi3l2; /*angoli sguincio l*/
  
  //variabili booleane PMT
  int PMT4, PMT5, PMT2, PMT7; 
  int PMT1L, PMT1l, PMT6L, PMT6l, PMT8L, PMT8l, PMT3L, PMT3l; 
  int Sopra, Zona1, Zona2, Zona3, Zona4, Zona5, Zona6, Zona7, Zona8, PMT; 
  int Theta1,Theta2,Theta3,Theta4, Phi1L,Phi3L,Phi6L,Phi8L, Phi1l, Phi3l,Phi6l,Phi8l,Phi2,Phi4, Phi5, Phi7;
  //Dichiarazione altre variabili
  double Colpito=0, trigger = 0, Accettanza;/*conta quante volte colpisce il PMT (ovunque, sopra, laterale), quante volte triggero, accettanza*/
  
  //Dichiarazione funzioni di distribuzione
  TF1* distribuzioneZeta = new TF1("distribuzioneZeta", "3*x^2", -1, 1); /*distribuzione di z = costheta*/

  //Definizione grafici e canvas
  TGraph* g1 = new TGraph(); // grafico theta-phi totali
  TGraph* g2 = new TGraph(); // grafico theta-phi totali
  TGraph* g3 = new TGraph(); //grafico xy triggeranti
  TGraph* g4 = new TGraph(); //grafico theta-phi triggeranti
  TGraph* g5 = new TGraph(); //grafico xy colpiscono
  TGraph* g6 = new TGraph(); //grafico theta-phi colpiscono
  TCanvas* c1 = new TCanvas();//canvas punti totali
  c1->Divide(2,3);

  //Controllo preliminare
  if (K != 1 && K != 2 && K != 3 && K != 4 && K != 5 && K != 6){
    cout << "Immettere un numero da 1 a 6." << endl;
    return;
  }
  
  if (K <= 3){
  //Generazione degli eventi, riempimento dei grafici
  for(int i = 0; i< N; i++){
    
    //genero pseudocasualmente le variabili secondo distribuzioni fissate
    x = gRandom->Uniform(0,B); /*posizione x: uniforme tra 0 e B*/
    y = gRandom->Uniform(0,A); /*posizione y: uniforme tra 0 e A*/
    phi = gRandom->Uniform(0, 2*M_PI); /*uniforme tra 0 e 2 pigreco*/
    z = distribuzioneZeta->GetRandom(0,1); /*costheta: distribuito come costheta^2 (dalla scheda)*/
    theta = TMath::ACos(z);/*angolo theta: arcos(z)*/
    
    //riempio grafico degli eventi totali
    g1->SetPoint(i,x,y);
    g2->SetPoint(i,theta,phi);
    
  //TRIGGERO?
    //assegno variabili TRIGGER
    Phi_1 = TMath::ATan((A-y)/(B-x));
    Phi_2 = M_PI/2 + TMath::ATan((x)/(A-y));
    Phi_3 = M_PI + TMath::ATan(y/x);
    Phi_4 = 2*M_PI - TMath::ATan((y)/(b-x));
    Theta_1 = TMath::ATan((A-y)/(3*a));
    Theta_2 = TMath::ATan((y)/(3*a));
    Theta_3 = TMath::ATan((B-x)/(3*a));
    Theta_4 = TMath::ATan((x)/(3*a));
    
    //Setto variabili booleane TRIGGER (copiate dal file sguincio.C)
    A1 = (phi >= Phi_4 && phi <= 2*M_PI) || (phi >= 0 && phi <= Phi_1);/*zona 1*/
    A2 =(phi >= Phi_1 && phi <= Phi_2); /*zona 2*/
    A3 = (phi >= Phi_2 && phi <= Phi_3); /*zona 3*/
    A4 = (phi >= Phi_3  && phi <= Phi_4); /*zona 4*/
    B1 = (theta >=0 && theta <= Theta_4); /*sguincio zona 1*/
    B2 = (theta >=0 && theta <= Theta_1); /*sguincio zona 2*/
    B3 = (theta >=0 && theta <= Theta_3); /*sguincio zona 3*/
    B4 = (theta >=0 && theta <= Theta_2); /*sguincio zona 4*/
    
    //Verifico se triggero
    T = (A1 && B1) || (A2 && B2) || (A3 && B3) || (A4 && B4);
    
    if (T == 1){ /*se triggero posso andare avanti*/
      //riempio grafico punti triggeranti
      g3->SetPoint(i,x,y);
      g4->SetPoint(i,theta,phi);
      trigger ++; /*conto quanto triggero*/

      //setto le varie zone x-y
      Zona1 = (x < b0) && (y < a0);
      Zona2 = (x < b0) && ((y > a0) && (y < a0 +a));
      Zona3 = (x < b0) && (y > a0 + a);
      Zona4 = ((x > b0) && (x < b0+b)) && (y < a0);
      Zona5 = ((x > b0) && (x < b0+b)) && (y > a0+a);
      Zona6 = (x > b0 + b) && (y < a0);
      Zona7 = (x > b0 + b) && ((y > a0) && (y < a0 +a));
      Zona8 = (x > b0 + b) && (y > a0 + a);
      
      //setto i vari angoli limite phi
      phi1L1 = TMath::ATan((a0-y)/((b0+b)-x));
      phi1L2 = phi1l1 = TMath::ATan((a0-y)/(b0-x));
      phi1l2 = TMath::ATan((a0+a-y)/(b0-x));
      phi21 = TMath::ATan(((a0+a)-y)/(b0-x));
      phi22 = 3*M_PI/2 + TMath::ATan((b0-x)/(y-a0));
      phi3l1 = 3*M_PI/2 + TMath::ATan((b0-x)/(y-a0));
      phi3L1 = phi3l2 = 3*M_PI/2 + TMath::ATan((b0-x)/(y-(a0+a)));
      phi3L2 = 3*M_PI/2 + TMath::ATan(((b0+b)-x)/(y-(a0+a)));
      phi41 = TMath::ATan((a0-y)/((b0+b)-x));
      phi42 = M_PI/2 + TMath::ATan((x-b0)/(a0-y));
      phi51 = M_PI + TMath::ATan((y-(a0+a))/(x-b0));
      phi52 = 2*M_PI -TMath::ATan((y-(a0+a))/((b0+b)-x));
      phi6l1 = M_PI/2 + TMath::ATan((x-(b0+b))/((a0+a)-y));
      phi6L1 = phi6l2 = M_PI/2 + TMath::ATan((x-(b0+b))/(a0-y));
      phi6L2 = M_PI/2 + TMath::ATan((x-b0)/(a0-y));
      phi71 = M_PI/2 + TMath::ATan((x-(b0+b))/((a0+a)-y));
      phi72 = M_PI + TMath::ATan((y-a0)/(x-(b0+b)));
      phi8L1 = M_PI + TMath::ATan((y-(a0+a))/(x-b0));
      phi8L2 = phi8l1 = M_PI + TMath::ATan((y-(a0+a))/(x-(b0+b)));
      phi8l2 = M_PI + TMath::ATan((y-a0)/(x-(b0+b)));
      
      //Casi possibili: K =0,1,2,3,4,5,6
      //PMT3
       if(K == 3){
	c1 -> SetTitle ("PMT 3");
	//setto tutte le variabili angolari del PMT3
	//angoli limite theta inferiori
	theta1 = TMath::ATan((a0-y)/(3*a));
	theta2 = TMath::ATan((y-(a0+a))/(3*a));
	theta3 = TMath::ATan((b0-x)/(3*a));
	theta4 = TMath::ATan((x-(b0+b))/(3*a));
	//angoli theta limite superiori
	thetas11 = TMath::ATan((a0-y)/(2*a));
	thetas12 = TMath::ATan((a0+a-y)/(2*a));
	thetas21 = TMath::ATan((y-(a0+a))/(2*a));
	thetas22 = TMath::ATan((y-a0)/(2*a));
	thetas31 = TMath::ATan((b0-x)/(2*a));
	thetas32 = TMath::ATan((b0+b-x)/(2*a));
	thetas41 = TMath::ATan((x-(b0+b))/(2*a));
	thetas42 = TMath::ATan((x-b0)/(2*a));
	//angoli phi limite 
	Phi1L = (phi >= phi1L1) && (phi <= phi1L2);
	Phi1l = (phi >= phi1l1) && (phi <= phi1l2);
	Phi2 = ((phi >= 0) && (phi<= phi21)) || ((phi>= phi22) && (phi<= 2*M_PI));
	Phi3L = (phi >= phi3L1) && (phi <= phi3L2);
	Phi3l = (phi >= phi3l1) && (phi <= phi3l2);
	Phi4 = (phi >= phi41) && (phi <= phi42);
	Phi5 = (phi >= phi51) && (phi <= phi52);
	Phi6L = (phi >= phi6L1) && (phi <= phi6L2);
	Phi6l = (phi >= phi6l1) && (phi <= phi6l2);
	Phi7 = (phi >= phi71) && (phi <= phi72);
	Phi8L = (phi >= phi8L1) && (phi <= phi8L2);
	Phi8l = (phi >= phi8l1) && (phi <= phi8l2);

	//COLPISCO SOPRA DA LATERALE?
	//setto variabili booleane del caso "colpisco sopra da laterale"
	int Sopra1L = Zona1 && ((theta >= thetas11) && (theta <= thetas12)) && Phi1L;
	int Sopra1l = Zona1 && ((theta >= thetas31) && (theta <= thetas32)) && Phi1l;
	int Sopra2 = Zona2 && ((theta >= thetas31) && (theta <= thetas32)) && Phi2;
	int Sopra3L = Zona3 && ((theta >= thetas21) && (theta <= thetas22)) && Phi3L;
	int Sopra3l = Zona3 && ((theta >= thetas31) && (theta <= thetas32)) && Phi3l;
	int Sopra4 = Zona4 && ((theta >= thetas11) && (theta <= thetas12)) && Phi4;
	int Sopra5 = Zona5 && ((theta >= thetas21) && (theta <= thetas22)) && Phi5;
	int Sopra6L = Zona6 && ((theta >= thetas11) && (theta <= thetas12)) && Phi6L;
	int Sopra6l = Zona6 && ((theta >= thetas41) && (theta <= thetas42)) && Phi6l;
	int Sopra7 = Zona7 && ((theta >= thetas41) && (theta <= thetas42)) && Phi7;
	int Sopra8L = Zona8 && ((theta >= thetas21) && (theta <= thetas22)) && Phi8L;
	int Sopra8l = Zona8 && ((theta >= thetas41) && (theta <= thetas42)) && Phi8l;

	//COLPISCO SOPRA DA SOPRA?
	//setto variabili booleane del caso "colpisco direttamente sopra"
	//assegno variabili angolari per le quattro zone della faccia superiore
	Phi_1 = TMath::ATan((a0+a-y)/(b0+b-x));
	Phi_2 = M_PI/2 + TMath::ATan((x-b0)/(a0+a-y));
	Phi_3 = M_PI + TMath::ATan((y-a0)/(x-b0));
	Phi_4 = 2*M_PI - TMath::ATan((y-a0)/(b0+b-x));
	//Setto variabili booleane per le quattro zone della faccia superiore (copiate dal file sguincio.C)
	A1 = (phi >= Phi_4 && phi <= 2*M_PI) || (phi >= 0 && phi <= Phi_1);/*zona 1*/
	A2 =(phi >= Phi_1 && phi <= Phi_2); /*zona 2*/
	A3 = (phi >= Phi_2 && phi <= Phi_3); /*zona 3*/
	A4 = (phi >= Phi_3  && phi <= Phi_4); /*zona 4*/
	
	double ZonaSopra = ((x >= b0) && (x <= b0 + b)) && ((y >= a0) && (y <= a0 + a));
	double L_xy = TMath::Abs(((b0+b-x)/(TMath::Cos(phi))))*A1 + TMath::Abs(((a0+a-y)/(TMath::Sin(phi))))*A2 +TMath::Abs((((x-b0)/(TMath::Cos(phi)))))*A3 +TMath::Abs((((y-a0)/(TMath::Sin(phi)))))*A4;/*serve per fissare la condizione*/
	double thetaSSMax = TMath::ATan((L_xy)/(2*a)); /*in questo caso ci devo mettere 2*a*/
	int ThetaSS = theta <= thetaSSMax;
	int SopraSopra = ZonaSopra && ThetaSS; /*fare figura per capire*/
	Sopra =    Sopra1L || Sopra1l || Sopra2 || Sopra3L || Sopra3l || Sopra4 || Sopra5 || Sopra6L || Sopra6l || Sopra7 || Sopra8L || Sopra8l ||SopraSopra;
	
	//COLPISCO DI LATO?
	//Setto variabili booleane
	Theta1 = (theta > theta1) && (theta < thetas11);
	Theta2 = (theta > theta2) && (theta < thetas21);
	Theta3 = (theta > theta3) && (theta < thetas31);
	Theta4 = (theta > theta4) && (theta < thetas41);
	
	//setto variabili booleane del caso "colpisco di lato", zona per zona
	PMT4 = Zona4 && Theta1 && Phi4;
	PMT5 = Zona5 && Theta2 && Phi5;
	PMT2 = Zona2 && Theta3 && Phi2;
	PMT7 = Zona7 && Theta4 && Phi7;
	PMT1L = Zona1 && Theta1 && Phi1L;
	PMT1l = Zona1 && Theta3 && Phi1l;
	PMT6L = Zona6 && Theta1 && Phi6L;
	PMT6l = Zona6 && Theta4 && Phi6l;
	PMT8L = Zona8 && Theta2 && Phi8L;
	PMT8l = Zona8 && Theta4 && Phi8l;
	PMT3L = Zona3 && Theta2 && Phi3L;
	PMT3l = Zona3 && Theta3 && Phi3l;
	
	//Colpisco il PMT se si verifica l'OR di uno dei casi possibili (sopra o laterale)
	PMT =   PMT4 || PMT5 || PMT2 || PMT7 || PMT1L || PMT1l || PMT6L || PMT6l || PMT8L || PMT8l || PMT3L || PMT3l || Sopra;
	if (PMT == 1) {// Se colpisco, riempio il grafico
	  g5->SetPoint(i,x,y);
	  g6->SetPoint(i,theta,phi);
	  Colpito ++; // ed incremento la variabile colpito
	  }
      }
       //PMT2
      if(K == 2){
	c1 -> SetTitle ("PMT 2");
	//setto tutte le variabili angolari del PMT2
	//angoli limite theta inferiori
	theta1 = TMath::ATan((a0-y)/(2*a));
	theta2 = TMath::ATan((y-(a0+a))/(2*a));
	theta3 = TMath::ATan((b0-x)/(2*a));
	theta4 = TMath::ATan((x-(b0+b))/(2*a));
	//angoli theta limite superiori
	thetas11 = TMath::ATan((a0-y)/(a));
	thetas12 = TMath::ATan((a0+a-y)/(a));
	thetas21 = TMath::ATan((y-(a0+a))/(a));
	thetas22 = TMath::ATan((y-a0)/(a));
	thetas31 = TMath::ATan((b0-x)/(a));
	thetas32 = TMath::ATan((b0+b-x)/(a));
	thetas41 = TMath::ATan((x-(b0+b))/(a));
	thetas42 = TMath::ATan((x-b0)/(a));
	//angoli phi limite 
	Phi1L = (phi >= phi1L1) && (phi <= phi1L2);
	Phi1l = (phi >= phi1l1) && (phi <= phi1l2);
	Phi2 = ((phi >= 0) && (phi<= phi21)) || ((phi>= phi22) && (phi<= 2*M_PI));
	Phi3L = (phi >= phi3L1) && (phi <= phi3L2);
	Phi3l = (phi >= phi3l1) && (phi <= phi3l2);
	Phi4 = (phi >= phi41) && (phi <= phi42);
	Phi5 = (phi >= phi51) && (phi <= phi52);
	Phi6L = (phi >= phi6L1) && (phi <= phi6L2);
	Phi6l = (phi >= phi6l1) && (phi <= phi6l2);
	Phi7 = (phi >= phi71) && (phi <= phi72);
	Phi8L = (phi >= phi8L1) && (phi <= phi8L2);
	Phi8l = (phi >= phi8l1) && (phi <= phi8l2);

	//COLPISCO SOPRA DA LATERALE?
	//setto variabili booleane del caso "colpisco sopra da laterale"
	int Sopra1L = Zona1 && ((theta >= thetas11) && (theta <= thetas12)) && Phi1L;
	int Sopra1l = Zona1 && ((theta >= thetas31) && (theta <= thetas32)) && Phi1l;
	int Sopra2 = Zona2 && ((theta >= thetas31) && (theta <= thetas32)) && Phi2;
	int Sopra3L = Zona3 && ((theta >= thetas21) && (theta <= thetas22)) && Phi3L;
	int Sopra3l = Zona3 && ((theta >= thetas31) && (theta <= thetas32)) && Phi3l;
	int Sopra4 = Zona4 && ((theta >= thetas11) && (theta <= thetas12)) && Phi4;
	int Sopra5 = Zona5 && ((theta >= thetas21) && (theta <= thetas22)) && Phi5;
	int Sopra6L = Zona6 && ((theta >= thetas11) && (theta <= thetas12)) && Phi6L;
	int Sopra6l = Zona6 && ((theta >= thetas41) && (theta <= thetas42)) && Phi6l;
	int Sopra7 = Zona7 && ((theta >= thetas41) && (theta <= thetas42)) && Phi7;
	int Sopra8L = Zona8 && ((theta >= thetas21) && (theta <= thetas22)) && Phi8L;
	int Sopra8l = Zona8 && ((theta >= thetas41) && (theta <= thetas42)) && Phi8l;

	//COLPISCO SOPRA DA SOPRA?
	//setto variabili booleane del caso "colpisco direttamente sopra"
	//assegno variabili angolari per le quattro zone della faccia superiore
	Phi_1 = TMath::ATan((a0+a-y)/(b0+b-x));
	Phi_2 = M_PI/2 + TMath::ATan((x-b0)/(a0+a-y));
	Phi_3 = M_PI + TMath::ATan((y-a0)/(x-b0));
	Phi_4 = 2*M_PI - TMath::ATan((y-a0)/(b0+b-x));
	//Setto variabili booleane per le quattro zone della faccia superiore (copiate dal file sguincio.C)
	A1 = (phi >= Phi_4 && phi <= 2*M_PI) || (phi >= 0 && phi <= Phi_1);/*zona 1*/
	A2 =(phi >= Phi_1 && phi <= Phi_2); /*zona 2*/
	A3 = (phi >= Phi_2 && phi <= Phi_3); /*zona 3*/
	A4 = (phi >= Phi_3  && phi <= Phi_4); /*zona 4*/
	
	double ZonaSopra = ((x >= b0) && (x <= b0 + b)) && ((y >= a0) && (y <= a0 + a));
	double L_xy = TMath::Abs(((b0+b-x)/(TMath::Cos(phi))))*A1 + TMath::Abs(((a0+a-y)/(TMath::Sin(phi))))*A2 +TMath::Abs((((x-b0)/(TMath::Cos(phi)))))*A3 +TMath::Abs((((y-a0)/(TMath::Sin(phi)))))*A4;/*serve per fissare la condizione*/
	double thetaSSMax = TMath::ATan((L_xy)/(a)); /*in questo caso ci devo mettere a*/
	int ThetaSS = theta <= thetaSSMax;
	int SopraSopra = ZonaSopra && ThetaSS; /*fare figura per capire*/
	Sopra =    Sopra1L || Sopra1l || Sopra2 || Sopra3L || Sopra3l || Sopra4 || Sopra5 || Sopra6L || Sopra6l || Sopra7 || Sopra8L || Sopra8l ||SopraSopra;
	
	//COLPISCO DI LATO?
	//Setto variabili booleane
	Theta1 = (theta > theta1) && (theta < thetas11);
	Theta2 = (theta > theta2) && (theta < thetas21);
	Theta3 = (theta > theta3) && (theta < thetas31);
	Theta4 = (theta > theta4) && (theta < thetas41);
	
	//setto variabili booleane del caso "colpisco di lato", zona per zona
	PMT4 = Zona4 && Theta1 && Phi4;
	PMT5 = Zona5 && Theta2 && Phi5;
	PMT2 = Zona2 && Theta3 && Phi2;
	PMT7 = Zona7 && Theta4 && Phi7;
	PMT1L = Zona1 && Theta1 && Phi1L;
	PMT1l = Zona1 && Theta3 && Phi1l;
	PMT6L = Zona6 && Theta1 && Phi6L;
	PMT6l = Zona6 && Theta4 && Phi6l;
	PMT8L = Zona8 && Theta2 && Phi8L;
	PMT8l = Zona8 && Theta4 && Phi8l;
	PMT3L = Zona3 && Theta2 && Phi3L;
	PMT3l = Zona3 && Theta3 && Phi3l;
	
	//Colpisco il PMT se si verifica l'OR di uno dei casi possibili (sopra o laterale)
	PMT =   PMT4 || PMT5 || PMT2 || PMT7 || PMT1L || PMT1l || PMT6L || PMT6l || PMT8L || PMT8l || PMT3L || PMT3l || Sopra;
	if (PMT == 1) {// Se colpisco, riempio il grafico
	  g5->SetPoint(i,x,y);
	  g6->SetPoint(i,theta,phi);
	  Colpito ++; // ed incremento la variabile colpito
	  }
      }
      //PMT1
      if(K == 1){
	c1 -> SetTitle ("PMT 1");
	//setto tutte le variabili angolari del PMT1
	theta1 = TMath::ATan((a0-y)/(a));
	theta2 = TMath::ATan((y-(a0+a))/(a));
	theta3 = TMath::ATan((b0-x)/(a));
	theta4 = TMath::ATan((x-(b0+b))/(a));
	
	//COLPISCO SOPRA?
	//setto le variabili del caso "colpisco direttamente sopra"
	Sopra = ((x >= b0) && (x <= b0 + b)) && ((y >= a0) && (y <= a0 + a));
	
	//COLPISCO DI LATO?
	//Setto variabili booleane
	Theta1 = theta >= theta1;
	Theta2 = theta >= theta2;
	Theta3 = theta >= theta3;
	Theta4 = theta >= theta4;
	Phi1L = (phi >= phi1L1) && (phi <= phi1L2);
	Phi1l = (phi >= phi1l1) && (phi <= phi1l2);
	Phi2 = ((phi >= 0) && (phi<= phi21)) || ((phi>= phi22) && (phi<= 2*M_PI));
	Phi3L = (phi >= phi3L1) && (phi <= phi3L2);
	Phi3l = (phi >= phi3l1) && (phi <= phi3l2);
	Phi4 = (phi >= phi41) && (phi <= phi42);
	Phi5 = (phi >= phi51) && (phi <= phi52);
	Phi6L = (phi >= phi6L1) && (phi <= phi6L2);
	Phi6l = (phi >= phi6l1) && (phi <= phi6l2);
	Phi7 = (phi >= phi71) && (phi <= phi72);
	Phi8L = (phi >= phi8L1) && (phi <= phi8L2);
	Phi8l = (phi >= phi8l1) && (phi <= phi8l2);
	
	//setto variabili booleane del caso "colpisco di lato", zona per zona
	PMT4 = Zona4 && Theta1 && Phi4;
	PMT5 = Zona5 && Theta2 && Phi5;
	PMT2 = Zona2 && Theta3 && Phi2;
	PMT7 = Zona7 && Theta4 && Phi7;
	PMT1L = Zona1 && Theta1 && Phi1L;
	PMT1l = Zona1 && Theta3 && Phi1l;
	PMT6L = Zona6 && Theta1 && Phi6L;
	PMT6l = Zona6 && Theta4 && Phi6l;
	PMT8L = Zona8 && Theta2 && Phi8L;
	PMT8l = Zona8 && Theta4 && Phi8l;
	PMT3L = Zona3 && Theta2 && Phi3L;
	PMT3l = Zona3 && Theta3 && Phi3l;
	
	//Colpisco il PMT se si verifica l'OR di uno dei casi possibili (sopra o laterale)
	PMT = PMT4 || PMT5 || PMT2 || PMT7 || PMT1L || PMT1l || PMT6L || PMT6l || PMT3L || PMT3l || PMT8L || PMT8l || Sopra;
	
	if (PMT == 1) {// Se colpisco, riempio il grafico
	  g5->SetPoint(i,x,y);
	  g6->SetPoint(i,theta,phi);
	  Colpito ++; // ed incremento la variabile colpito
	  }
      }
    } 
  }
 
  //Stampo il risultato
  Accettanza = Colpito / trigger;
  cout << "-------------------------------------------"<< endl;
  cout << "-------------------------------------------"<< endl;
  cout << "PMT " << K << ":" << endl;
  cout << "-------------------------------------------"<< endl;
  cout << "Totali = " << N << endl;
  cout << "Triggerati = " << trigger << endl;
  cout << "Colpiti = " << Colpito << endl;
  cout << "Accettanza PMT = " << Accettanza <<endl;
  cout << "-------------------------------------------"<< endl;
  cout << "-------------------------------------------"<< endl;
  
  //Grafico
  c1 -> cd(1);
  g1->SetTitle("x vs y total; x; y");
  g1->SetLineColor(0);
  g1->Draw();
  
  c1->cd(2);
  g2->SetTitle("#theta vs #varphi total; #theta; #varphi");
  g2->SetLineColor(0);
  g2->Draw();
  
  c1 -> cd(3);
  g3->SetTitle("x vs y triggering; x; y");
  g3->SetLineColor(0);
  g3->Draw();
  
  c1 -> cd(4);
  g4->SetTitle("#theta vs #varphi triggering; #theta; #varphi");
  g4->SetLineColor(0);
  g4->Draw();
  
  c1 -> cd(5);
  g5->SetTitle("x vs y hitting PMT; x; y");
  g5->SetLineColor(0);
  g5->Draw();
  
  c1 -> cd(6);
  g6->SetTitle("#theta vs #varphi hitting PMT; #theta; #varphi");
  g6->SetLineColor(0);
  g6->Draw();
  return;
}

  if (K > 3){
    a0 = a0 +a;
  //Generazione degli eventi, riempimento dei grafici
  for(int i = 0; i< N; i++){
    
    //genero pseudocasualmente le variabili secondo distribuzioni fissate
    x = gRandom->Uniform(0,B); /*posizione x: uniforme tra 0 e B*/
    y = gRandom->Uniform(0,A); /*posizione y: uniforme tra 0 e A*/
    phi = gRandom->Uniform(0, 2*M_PI); /*uniforme tra 0 e 2 pigreco*/
    z = distribuzioneZeta->GetRandom(0,1); /*costheta: distribuito come costheta^2 (dalla scheda)*/
    theta = TMath::ACos(z);/*angolo theta: arcos(z)*/
    
    //riempio grafico degli eventi totali
    g1->SetPoint(i,x,y);
    g2->SetPoint(i,theta,phi);
    
  //TRIGGERO?
    //assegno variabili TRIGGER
    Phi_1 = TMath::ATan((A-y)/(B-x));
    Phi_2 = M_PI/2 + TMath::ATan((x)/(A-y));
    Phi_3 = M_PI + TMath::ATan(y/x);
    Phi_4 = 2*M_PI - TMath::ATan((y)/(b-x));
    Theta_1 = TMath::ATan((A-y)/(3*a));
    Theta_2 = TMath::ATan((y)/(3*a));
    Theta_3 = TMath::ATan((B-x)/(3*a));
    Theta_4 = TMath::ATan((x)/(3*a));
    
    //Setto variabili booleane TRIGGER (copiate dal file sguincio.C)
    A1 = (phi >= Phi_4 && phi <= 2*M_PI) || (phi >= 0 && phi <= Phi_1);/*zona 1*/
    A2 =(phi >= Phi_1 && phi <= Phi_2); /*zona 2*/
    A3 = (phi >= Phi_2 && phi <= Phi_3); /*zona 3*/
    A4 = (phi >= Phi_3  && phi <= Phi_4); /*zona 4*/
    B1 = (theta >=0 && theta <= Theta_4); /*sguincio zona 1*/
    B2 = (theta >=0 && theta <= Theta_1); /*sguincio zona 2*/
    B3 = (theta >=0 && theta <= Theta_3); /*sguincio zona 3*/
    B4 = (theta >=0 && theta <= Theta_2); /*sguincio zona 4*/
    
    //Verifico se triggero
    T = (A1 && B1) || (A2 && B2) || (A3 && B3) || (A4 && B4);
    
    if (T == 1){ /*se triggero posso andare avanti*/
      //riempio grafico punti triggeranti
      g3->SetPoint(i,x,y);
      g4->SetPoint(i,theta,phi);
      trigger ++; /*conto quanto triggero*/

      //setto le varie zone x-y
      Zona1 = (x < b0) && (y < a0);
      Zona2 = (x < b0) && ((y > a0) && (y < a0 +a));
      Zona3 = (x < b0) && (y > a0 + a);
      Zona4 = ((x > b0) && (x < b0+b)) && (y < a0);
      Zona5 = ((x > b0) && (x < b0+b)) && (y > a0+a);
      Zona6 = (x > b0 + b) && (y < a0);
      Zona7 = (x > b0 + b) && ((y > a0) && (y < a0 +a));
      Zona8 = (x > b0 + b) && (y > a0 + a);
      
      //setto i vari angoli limite phi
      phi1L1 = TMath::ATan((a0-y)/((b0+b)-x));
      phi1L2 = phi1l1 = TMath::ATan((a0-y)/(b0-x));
      phi1l2 = TMath::ATan((a0+a-y)/(b0-x));
      phi21 = TMath::ATan(((a0+a)-y)/(b0-x));
      phi22 = 3*M_PI/2 + TMath::ATan((b0-x)/(y-a0));
      phi3l1 = 3*M_PI/2 + TMath::ATan((b0-x)/(y-a0));
      phi3L1 = phi3l2 = 3*M_PI/2 + TMath::ATan((b0-x)/(y-(a0+a)));
      phi3L2 = 3*M_PI/2 + TMath::ATan(((b0+b)-x)/(y-(a0+a)));
      phi41 = TMath::ATan((a0-y)/((b0+b)-x));
      phi42 = M_PI/2 + TMath::ATan((x-b0)/(a0-y));
      phi51 = M_PI + TMath::ATan((y-(a0+a))/(x-b0));
      phi52 = 2*M_PI -TMath::ATan((y-(a0+a))/((b0+b)-x));
      phi6l1 = M_PI/2 + TMath::ATan((x-(b0+b))/((a0+a)-y));
      phi6L1 = phi6l2 = M_PI/2 + TMath::ATan((x-(b0+b))/(a0-y));
      phi6L2 = M_PI/2 + TMath::ATan((x-b0)/(a0-y));
      phi71 = M_PI/2 + TMath::ATan((x-(b0+b))/((a0+a)-y));
      phi72 = M_PI + TMath::ATan((y-a0)/(x-(b0+b)));
      phi8L1 = M_PI + TMath::ATan((y-(a0+a))/(x-b0));
      phi8L2 = phi8l1 = M_PI + TMath::ATan((y-(a0+a))/(x-(b0+b)));
      phi8l2 = M_PI + TMath::ATan((y-a0)/(x-(b0+b)));
      
      //Casi possibili: K =0,1,2,3,4,5,6
      //PMT6
       if(K == 6){
	 c1->SetTitle("PMT 6");
	//setto tutte le variabili angolari del PMT3
	//angoli limite theta inferiori
	theta1 = TMath::ATan((a0-y)/(3*a));
	theta2 = TMath::ATan((y-(a0+a))/(3*a));
	theta3 = TMath::ATan((b0-x)/(3*a));
	theta4 = TMath::ATan((x-(b0+b))/(3*a));
	//angoli theta limite superiori
	thetas11 = TMath::ATan((a0-y)/(2*a));
	thetas12 = TMath::ATan((a0+a-y)/(2*a));
	thetas21 = TMath::ATan((y-(a0+a))/(2*a));
	thetas22 = TMath::ATan((y-a0)/(2*a));
	thetas31 = TMath::ATan((b0-x)/(2*a));
	thetas32 = TMath::ATan((b0+b-x)/(2*a));
	thetas41 = TMath::ATan((x-(b0+b))/(2*a));
	thetas42 = TMath::ATan((x-b0)/(2*a));
	//angoli phi limite 
	Phi1L = (phi >= phi1L1) && (phi <= phi1L2);
	Phi1l = (phi >= phi1l1) && (phi <= phi1l2);
	Phi2 = ((phi >= 0) && (phi<= phi21)) || ((phi>= phi22) && (phi<= 2*M_PI));
	Phi3L = (phi >= phi3L1) && (phi <= phi3L2);
	Phi3l = (phi >= phi3l1) && (phi <= phi3l2);
	Phi4 = (phi >= phi41) && (phi <= phi42);
	Phi5 = (phi >= phi51) && (phi <= phi52);
	Phi6L = (phi >= phi6L1) && (phi <= phi6L2);
	Phi6l = (phi >= phi6l1) && (phi <= phi6l2);
	Phi7 = (phi >= phi71) && (phi <= phi72);
	Phi8L = (phi >= phi8L1) && (phi <= phi8L2);
	Phi8l = (phi >= phi8l1) && (phi <= phi8l2);

	//COLPISCO SOPRA DA LATERALE?
	//setto variabili booleane del caso "colpisco sopra da laterale"
	int Sopra1L = Zona1 && ((theta >= thetas11) && (theta <= thetas12)) && Phi1L;
	int Sopra1l = Zona1 && ((theta >= thetas31) && (theta <= thetas32)) && Phi1l;
	int Sopra2 = Zona2 && ((theta >= thetas31) && (theta <= thetas32)) && Phi2;
	int Sopra3L = Zona3 && ((theta >= thetas21) && (theta <= thetas22)) && Phi3L;
	int Sopra3l = Zona3 && ((theta >= thetas31) && (theta <= thetas32)) && Phi3l;
	int Sopra4 = Zona4 && ((theta >= thetas11) && (theta <= thetas12)) && Phi4;
	int Sopra5 = Zona5 && ((theta >= thetas21) && (theta <= thetas22)) && Phi5;
	int Sopra6L = Zona6 && ((theta >= thetas11) && (theta <= thetas12)) && Phi6L;
	int Sopra6l = Zona6 && ((theta >= thetas41) && (theta <= thetas42)) && Phi6l;
	int Sopra7 = Zona7 && ((theta >= thetas41) && (theta <= thetas42)) && Phi7;
	int Sopra8L = Zona8 && ((theta >= thetas21) && (theta <= thetas22)) && Phi8L;
	int Sopra8l = Zona8 && ((theta >= thetas41) && (theta <= thetas42)) && Phi8l;

	//COLPISCO SOPRA DA SOPRA?
	//setto variabili booleane del caso "colpisco direttamente sopra"
	//assegno variabili angolari per le quattro zone della faccia superiore
	Phi_1 = TMath::ATan((a0+a-y)/(b0+b-x));
	Phi_2 = M_PI/2 + TMath::ATan((x-b0)/(a0+a-y));
	Phi_3 = M_PI + TMath::ATan((y-a0)/(x-b0));
	Phi_4 = 2*M_PI - TMath::ATan((y-a0)/(b0+b-x));
	//Setto variabili booleane per le quattro zone della faccia superiore (copiate dal file sguincio.C)
	A1 = (phi >= Phi_4 && phi <= 2*M_PI) || (phi >= 0 && phi <= Phi_1);/*zona 1*/
	A2 =(phi >= Phi_1 && phi <= Phi_2); /*zona 2*/
	A3 = (phi >= Phi_2 && phi <= Phi_3); /*zona 3*/
	A4 = (phi >= Phi_3  && phi <= Phi_4); /*zona 4*/
	
	double ZonaSopra = ((x >= b0) && (x <= b0 + b)) && ((y >= a0) && (y <= a0 + a));
	double L_xy = TMath::Abs(((b0+b-x)/(TMath::Cos(phi))))*A1 + TMath::Abs(((a0+a-y)/(TMath::Sin(phi))))*A2 +TMath::Abs((((x-b0)/(TMath::Cos(phi)))))*A3 +TMath::Abs((((y-a0)/(TMath::Sin(phi)))))*A4;/*serve per fissare la condizione*/
	double thetaSSMax = TMath::ATan((L_xy)/(2*a)); /*in questo caso ci devo mettere 2*a*/
	int ThetaSS = theta <= thetaSSMax;
	int SopraSopra = ZonaSopra && ThetaSS; /*fare figura per capire*/
	Sopra =    Sopra1L || Sopra1l || Sopra2 || Sopra3L || Sopra3l || Sopra4 || Sopra5 || Sopra6L || Sopra6l || Sopra7 || Sopra8L || Sopra8l ||SopraSopra;
	
	//COLPISCO DI LATO?
	//Setto variabili booleane
	Theta1 = (theta > theta1) && (theta < thetas11);
	Theta2 = (theta > theta2) && (theta < thetas21);
	Theta3 = (theta > theta3) && (theta < thetas31);
	Theta4 = (theta > theta4) && (theta < thetas41);
	
	//setto variabili booleane del caso "colpisco di lato", zona per zona
	PMT4 = Zona4 && Theta1 && Phi4;
	PMT5 = Zona5 && Theta2 && Phi5;
	PMT2 = Zona2 && Theta3 && Phi2;
	PMT7 = Zona7 && Theta4 && Phi7;
	PMT1L = Zona1 && Theta1 && Phi1L;
	PMT1l = Zona1 && Theta3 && Phi1l;
	PMT6L = Zona6 && Theta1 && Phi6L;
	PMT6l = Zona6 && Theta4 && Phi6l;
	PMT8L = Zona8 && Theta2 && Phi8L;
	PMT8l = Zona8 && Theta4 && Phi8l;
	PMT3L = Zona3 && Theta2 && Phi3L;
	PMT3l = Zona3 && Theta3 && Phi3l;
	
	//Colpisco il PMT se si verifica l'OR di uno dei casi possibili (sopra o laterale)
	PMT =   PMT4 || PMT5 || PMT2 || PMT7 || PMT1L || PMT1l || PMT6L || PMT6l || PMT8L || PMT8l || PMT3L || PMT3l || Sopra;
	if (PMT == 1) {// Se colpisco, riempio il grafico
	  g5->SetPoint(i,x,y);
	  g6->SetPoint(i,theta,phi);
	  Colpito ++; // ed incremento la variabile colpito
	  }
      }
       //PMT5
       c1 -> SetTitle("PMT 5");
      if(K == 5){
	//setto tutte le variabili angolari del PMT2
	//angoli limite theta inferiori
	theta1 = TMath::ATan((a0-y)/(2*a));
	theta2 = TMath::ATan((y-(a0+a))/(2*a));
	theta3 = TMath::ATan((b0-x)/(2*a));
	theta4 = TMath::ATan((x-(b0+b))/(2*a));
	//angoli theta limite superiori
	thetas11 = TMath::ATan((a0-y)/(a));
	thetas12 = TMath::ATan((a0+a-y)/(a));
	thetas21 = TMath::ATan((y-(a0+a))/(a));
	thetas22 = TMath::ATan((y-a0)/(a));
	thetas31 = TMath::ATan((b0-x)/(a));
	thetas32 = TMath::ATan((b0+b-x)/(a));
	thetas41 = TMath::ATan((x-(b0+b))/(a));
	thetas42 = TMath::ATan((x-b0)/(a));
	//angoli phi limite 
	Phi1L = (phi >= phi1L1) && (phi <= phi1L2);
	Phi1l = (phi >= phi1l1) && (phi <= phi1l2);
	Phi2 = ((phi >= 0) && (phi<= phi21)) || ((phi>= phi22) && (phi<= 2*M_PI));
	Phi3L = (phi >= phi3L1) && (phi <= phi3L2);
	Phi3l = (phi >= phi3l1) && (phi <= phi3l2);
	Phi4 = (phi >= phi41) && (phi <= phi42);
	Phi5 = (phi >= phi51) && (phi <= phi52);
	Phi6L = (phi >= phi6L1) && (phi <= phi6L2);
	Phi6l = (phi >= phi6l1) && (phi <= phi6l2);
	Phi7 = (phi >= phi71) && (phi <= phi72);
	Phi8L = (phi >= phi8L1) && (phi <= phi8L2);
	Phi8l = (phi >= phi8l1) && (phi <= phi8l2);

	//COLPISCO SOPRA DA LATERALE?
	//setto variabili booleane del caso "colpisco sopra da laterale"
	int Sopra1L = Zona1 && ((theta >= thetas11) && (theta <= thetas12)) && Phi1L;
	int Sopra1l = Zona1 && ((theta >= thetas31) && (theta <= thetas32)) && Phi1l;
	int Sopra2 = Zona2 && ((theta >= thetas31) && (theta <= thetas32)) && Phi2;
	int Sopra3L = Zona3 && ((theta >= thetas21) && (theta <= thetas22)) && Phi3L;
	int Sopra3l = Zona3 && ((theta >= thetas31) && (theta <= thetas32)) && Phi3l;
	int Sopra4 = Zona4 && ((theta >= thetas11) && (theta <= thetas12)) && Phi4;
	int Sopra5 = Zona5 && ((theta >= thetas21) && (theta <= thetas22)) && Phi5;
	int Sopra6L = Zona6 && ((theta >= thetas11) && (theta <= thetas12)) && Phi6L;
	int Sopra6l = Zona6 && ((theta >= thetas41) && (theta <= thetas42)) && Phi6l;
	int Sopra7 = Zona7 && ((theta >= thetas41) && (theta <= thetas42)) && Phi7;
	int Sopra8L = Zona8 && ((theta >= thetas21) && (theta <= thetas22)) && Phi8L;
	int Sopra8l = Zona8 && ((theta >= thetas41) && (theta <= thetas42)) && Phi8l;

	//COLPISCO SOPRA DA SOPRA?
	//setto variabili booleane del caso "colpisco direttamente sopra"
	//assegno variabili angolari per le quattro zone della faccia superiore
	Phi_1 = TMath::ATan((a0+a-y)/(b0+b-x));
	Phi_2 = M_PI/2 + TMath::ATan((x-b0)/(a0+a-y));
	Phi_3 = M_PI + TMath::ATan((y-a0)/(x-b0));
	Phi_4 = 2*M_PI - TMath::ATan((y-a0)/(b0+b-x));
	//Setto variabili booleane per le quattro zone della faccia superiore (copiate dal file sguincio.C)
	A1 = (phi >= Phi_4 && phi <= 2*M_PI) || (phi >= 0 && phi <= Phi_1);/*zona 1*/
	A2 =(phi >= Phi_1 && phi <= Phi_2); /*zona 2*/
	A3 = (phi >= Phi_2 && phi <= Phi_3); /*zona 3*/
	A4 = (phi >= Phi_3  && phi <= Phi_4); /*zona 4*/
	
	double ZonaSopra = ((x >= b0) && (x <= b0 + b)) && ((y >= a0) && (y <= a0 + a));
	double L_xy = TMath::Abs(((b0+b-x)/(TMath::Cos(phi))))*A1 + TMath::Abs(((a0+a-y)/(TMath::Sin(phi))))*A2 +TMath::Abs((((x-b0)/(TMath::Cos(phi)))))*A3 +TMath::Abs((((y-a0)/(TMath::Sin(phi)))))*A4;/*serve per fissare la condizione*/
	double thetaSSMax = TMath::ATan((L_xy)/(a)); /*in questo caso ci devo mettere a*/
	int ThetaSS = theta <= thetaSSMax;
	int SopraSopra = ZonaSopra && ThetaSS; /*fare figura per capire*/
	Sopra =    Sopra1L || Sopra1l || Sopra2 || Sopra3L || Sopra3l || Sopra4 || Sopra5 || Sopra6L || Sopra6l || Sopra7 || Sopra8L || Sopra8l ||SopraSopra;
	
	//COLPISCO DI LATO?
	//Setto variabili booleane
	Theta1 = (theta > theta1) && (theta < thetas11);
	Theta2 = (theta > theta2) && (theta < thetas21);
	Theta3 = (theta > theta3) && (theta < thetas31);
	Theta4 = (theta > theta4) && (theta < thetas41);
	
	//setto variabili booleane del caso "colpisco di lato", zona per zona
	PMT4 = Zona4 && Theta1 && Phi4;
	PMT5 = Zona5 && Theta2 && Phi5;
	PMT2 = Zona2 && Theta3 && Phi2;
	PMT7 = Zona7 && Theta4 && Phi7;
	PMT1L = Zona1 && Theta1 && Phi1L;
	PMT1l = Zona1 && Theta3 && Phi1l;
	PMT6L = Zona6 && Theta1 && Phi6L;
	PMT6l = Zona6 && Theta4 && Phi6l;
	PMT8L = Zona8 && Theta2 && Phi8L;
	PMT8l = Zona8 && Theta4 && Phi8l;
	PMT3L = Zona3 && Theta2 && Phi3L;
	PMT3l = Zona3 && Theta3 && Phi3l;
	
	//Colpisco il PMT se si verifica l'OR di uno dei casi possibili (sopra o laterale)
	PMT =   PMT4 || PMT5 || PMT2 || PMT7 || PMT1L || PMT1l || PMT6L || PMT6l || PMT8L || PMT8l || PMT3L || PMT3l || Sopra;
	if (PMT == 1) {// Se colpisco, riempio il grafico
	  g5->SetPoint(i,x,y);
	  g6->SetPoint(i,theta,phi);
	  Colpito ++; // ed incremento la variabile colpito
	  }
      }
      //PMT4
      if(K == 4){
	c1 -> SetTitle ("PMT 4");
	//setto tutte le variabili angolari del PMT1
	theta1 = TMath::ATan((a0-y)/(a));
	theta2 = TMath::ATan((y-(a0+a))/(a));
	theta3 = TMath::ATan((b0-x)/(a));
	theta4 = TMath::ATan((x-(b0+b))/(a));
	
	//COLPISCO SOPRA?
	//setto le variabili del caso "colpisco direttamente sopra"
	Sopra = ((x >= b0) && (x <= b0 + b)) && ((y >= a0) && (y <= a0 + a));
	
	//COLPISCO DI LATO?
	//Setto variabili booleane
	Theta1 = theta >= theta1;
	Theta2 = theta >= theta2;
	Theta3 = theta >= theta3;
	Theta4 = theta >= theta4;
	Phi1L = (phi >= phi1L1) && (phi <= phi1L2);
	Phi1l = (phi >= phi1l1) && (phi <= phi1l2);
	Phi2 = ((phi >= 0) && (phi<= phi21)) || ((phi>= phi22) && (phi<= 2*M_PI));
	Phi3L = (phi >= phi3L1) && (phi <= phi3L2);
	Phi3l = (phi >= phi3l1) && (phi <= phi3l2);
	Phi4 = (phi >= phi41) && (phi <= phi42);
	Phi5 = (phi >= phi51) && (phi <= phi52);
	Phi6L = (phi >= phi6L1) && (phi <= phi6L2);
	Phi6l = (phi >= phi6l1) && (phi <= phi6l2);
	Phi7 = (phi >= phi71) && (phi <= phi72);
	Phi8L = (phi >= phi8L1) && (phi <= phi8L2);
	Phi8l = (phi >= phi8l1) && (phi <= phi8l2);
	
	//setto variabili booleane del caso "colpisco di lato", zona per zona
	PMT4 = Zona4 && Theta1 && Phi4;
	PMT5 = Zona5 && Theta2 && Phi5;
	PMT2 = Zona2 && Theta3 && Phi2;
	PMT7 = Zona7 && Theta4 && Phi7;
	PMT1L = Zona1 && Theta1 && Phi1L;
	PMT1l = Zona1 && Theta3 && Phi1l;
	PMT6L = Zona6 && Theta1 && Phi6L;
	PMT6l = Zona6 && Theta4 && Phi6l;
	PMT8L = Zona8 && Theta2 && Phi8L;
	PMT8l = Zona8 && Theta4 && Phi8l;
	PMT3L = Zona3 && Theta2 && Phi3L;
	PMT3l = Zona3 && Theta3 && Phi3l;
	
	//Colpisco il PMT se si verifica l'OR di uno dei casi possibili (sopra o laterale)
	PMT = PMT4 || PMT5 || PMT2 || PMT7 || PMT1L || PMT1l || PMT6L || PMT6l || PMT3L || PMT3l || PMT8L || PMT8l || Sopra;
	
	if (PMT == 1) {// Se colpisco, riempio il grafico
	  g5->SetPoint(i,x,y);
	  g6->SetPoint(i,theta,phi);
	  Colpito ++; // ed incremento la variabile colpito
	  }
      }
    } 
  }
 
  //Stampo il risultato
  Accettanza = Colpito / trigger;
  cout << "-------------------------------------------"<< endl;
  cout << "-------------------------------------------"<< endl;
  cout << "PMT " << K << ":" << endl;
  cout << "-------------------------------------------"<< endl;
  cout << "Totali = " << N << endl;
  cout << "Triggerati = " << trigger << endl;
  cout << "Colpiti = " << Colpito << endl;
  cout << "Accettanza PMT = " << Accettanza <<endl;
  cout << "-------------------------------------------"<< endl;
  cout << "-------------------------------------------"<< endl;
  
  //Grafico
  c1 -> cd(1);
  g1->SetTitle("x vs y total; x; y");
  g1->SetLineColor(0);
  g1->Draw();
  
  c1->cd(2);
  g2->SetTitle("#theta vs #varphi total; #theta; #varphi");
  g2->SetLineColor(0);
  g2->Draw();
  
  c1 -> cd(3);
  g3->SetTitle("x vs y triggering; x; y");
  g3->SetLineColor(0);
  g3->Draw();
  
  c1 -> cd(4);
  g4->SetTitle("#theta vs #varphi triggering; #theta; #varphi");
  g4->SetLineColor(0);
  g4->Draw();
  
  c1 -> cd(5);
  g5->SetTitle("x vs y hitting PMT; x; y");
  g5->SetLineColor(0);
  g5->Draw();
  
  c1 -> cd(6);
  g6->SetTitle("#theta vs #varphi hitting PMT; #theta; #varphi");
  g6->SetLineColor(0);
  g6->Draw();
  return;
}
}

void Programma(){
  for (int i = 1; i <= 6; i++) accettanza(1e5, i);
  return;
}
