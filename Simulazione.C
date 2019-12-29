//CONTROLLO DEL TRIGGER
//Dato un evento (x,y,theta,phi) sullo scintillatore superiore, restituisce 0 se esso non triggera, 1 se esso triggera
//Si basa sul programma "sguincio" che ho scritto prima di tutti gli altri

int Trigger(double x, double y, double theta, double phi){
  int A1,A2,A3,A4; 
  int PHI1,PHI2,PHI3,PHI4;
  int THETA1,THETA2,THETA3,THETA4;
  double A = 40.0; /*lato corto TRIGGER*/
  double B = 51.5; /*lato lungo TRIGGER*/
  int T;
  double phi1, phi2, phi3, phi4;
  double theta1, theta2, theta3, theta4;
  double s = TMath::Sin(phi), c = TMath::Cos(phi);
  phi1 = TMath::ATan((A-y)/(B-x));
  phi2 = M_PI - TMath::ATan((A-y)/(x));
  phi3 = M_PI + TMath::ATan((y)/(x));
  phi4 = 2*M_PI - TMath::ATan((y)/(B-x));
  theta1 = TMath::ATan((B-x)/(c*A));
  theta2 = TMath::ATan((A-y)/(s*A));
  theta3 = -1*TMath::ATan((x)/(c*A));
  theta4 = -1*TMath::ATan((y)/(s*A));

  PHI1 = ((phi>= 0) && (phi <= phi1)) || ((phi >= phi4)&&(phi<= 2*M_PI));
  PHI2 = ((phi > phi1) && (phi <= phi2));
  PHI3 = ((phi > phi2) && (phi <= phi3));
  PHI4 = ((phi > phi3) && (phi <= phi4));
  THETA1 = ((theta <= theta1)&&(theta >=0));
  THETA2 = ((theta <= theta2)&& theta >=0);
  THETA3 = ((theta <= theta3)&&(theta>=0));
  THETA4 = ((theta <= theta4)&&(theta>=0));

  A1 = PHI1*THETA1;
  A2 = PHI2*THETA2;
  A3 = PHI3*THETA3;
  A4 = PHI4*THETA4;
  
  T = A1 || A2 || A3 || A4;
  return T;
}

//NUMERO DI FOTOELETTRONI: CASO BASE SENZA ACCETTANZA E SOLO DA SOPRA
//Calcola il numero di fotoelettroni prodotti dal passaggio di una MIP in un critallo qualunque in funzione del punto (x,y,theta,phi) sulla faccia superiore
//Gli eventi possono uscire da sotto o da laterale
//Calcola N_pe e ritorna tale valore.

double sguincio(double x, double y, double theta, double phi){
  double C = 4.26687;
  double phi1,phi2,phi3,phi4;
  double theta1,theta2,theta3,theta4;
  int PHI1,PHI2,PHI3,PHI4;
  int THETA1, THETA2, THETA3, THETA4;
  int S, S1, S2, S3, S4;
  int A1, A2, A3, A4;
  double L, s = TMath::Sin(phi), c = TMath::Cos(phi), z = TMath::Sin(theta),k = TMath::Cos(theta), a = 10.5, b = 37;
  
  phi1 = TMath::ATan((a-y)/(b-x));
  phi2 = M_PI - TMath::ATan((a-y)/(x));
  phi3 = M_PI + TMath::ATan((y)/(x));
  phi4 = 2*M_PI - TMath::ATan((y)/(b-x));
  theta1 = TMath::ATan((b-x)/(c*a));
  theta2 = TMath::ATan((a-y)/(s*a));
  theta3 = -1*TMath::ATan((x)/(c*a));
  theta4 = -1*TMath::ATan((y)/(s*a));

  PHI1 = ((phi>= 0) && (phi <= phi1)) || ((phi >= phi4)&&(phi<= 2*M_PI));
  PHI2 = ((phi > phi1) && (phi <= phi2));
  PHI3 = ((phi > phi2) && (phi <= phi3));
  PHI4 = ((phi > phi3) && (phi <= phi4));
  THETA1 = ((theta <= theta1)&&(theta >=0));
  THETA2 = ((theta <= theta2)&& theta >=0);
  THETA3 = ((theta <= theta3)&&(theta>=0));
  THETA4 = ((theta <= theta4)&&(theta>=0));

  A1 = PHI1*THETA1;
  A2 = PHI2*THETA2;
  A3 = PHI3*THETA3;
  A4 = PHI4*THETA4;
  
  S = A1 || A2 || A3 || A4;
  if (S == 1){
    //cout << "non sguincio" << endl;
    L = a/(k);
  }
  if (S == 0){
    //cout << "sguincio" << endl;
    if (PHI1 == 1 && A1==0) L = (b-x)/(z*c); 
    if (PHI2 == 1 && A2==0) L = (a-y)/(z*s);
    if (PHI3 == 1 && A3==0) L = -1*(x)/(z*c); 
    if (PHI4 == 1 && A4==0) L = -1*(y)/(z*s); 
    }
  if (L > 39.8685){
    cout << "-------------------------------------------------------------------------------------------------------"<< endl;
    cout << L << endl;
    cout << PHI1 << "\t" << PHI2 << "\t" << PHI3 << "\t"  << PHI4 << "\t" << endl;
    cout << (b-x)/(c*z) << "\t" << (a-y)/(s*z) << "\t" << -1*(x)/(c*z) << "\t"  << -1*(y)/(s*z) << "\t" << endl;
    cout << x << "\t" << y <<  endl;
    cout << "-------------------------------------------------------------------------------------------------------"<< endl;
  }
  return L*C;
}

//NUMERO DI FOTOELETTRONI
//Calcola il numero di fotoelettroni dovuti al passaggio di una MIP nel cristallo, in funzione del punto (x,y,theta,phi)
// PMT seleziona il PMT che si vuole controllare
// TRIGGER = 1 seleziona gli eventi triggeranti
// ss = 1: SOPRA-SOPRA
// sl = 1: SOPRA-LATERALE
// ll = 1: LATERALE LATERALE
// ritorna il numero di fotoelettroni

double Montecarlo(double x, double y, double theta, double phi, int PMT, int TRIGGER, int ss, int sl, int ll){
  //Definizione variabili
  double a = 10.5; /*lato di base di singolo PMT*/
  double b = 37; /*lato lungo di singolo PMT*/
  double a0 = 7, b0 = 5; /*posizionamento pmt*/
  double X = b0,Y,Z;
  double A = 40; /*lato corto TRIGGER*/
  double B = 51.5; /*lato lungo TRIGGER*/
  double C = 4.26687;
  double N_pe;
  double PhiSS_1, PhiSS_2, PhiSS_3, PhiSS_4, LSS_xy,thetaSSMax;
  int ASS1, ASS2, ASS3, ASS4, ThetaSS, ZonaSopra, SS;
  double theta1, theta2, theta3, theta4, phi21, phi22, phi41, phi42, phi51, phi52,phi71, phi72; 
  double thetas11, thetas21, thetas31, thetas41;
  double thetas12, thetas22, thetas32, thetas42; 
  double phi1L1, phi1L2, phi6L1, phi6L2, phi8L1, phi8L2, phi3L1, phi3L2; 
  double phi1l1, phi1l2, phi6l1, phi6l2, phi8l1, phi8l2, phi3l1, phi3l2; 
  int PMT4, PMT5, PMT2, PMT7; 
  int PMT1L, PMT1l, PMT6L, PMT6l, PMT8L, PMT8l, PMT3L, PMT3l; 
  int Sopra, Zona1, Zona2, Zona3, Zona4, Zona5, Zona6, Zona7, Zona8; 
  int Theta1,Theta2,Theta3,Theta4, Phi1L,Phi3L,Phi6L,Phi8L, Phi1l, Phi3l,Phi6l,Phi8l,Phi2,Phi4, Phi5, Phi7;
  int Sopra1L,Sopra1l,Sopra2,Sopra4,Sopra5,Sopra7,Sopra3L,Sopra3l,Sopra6L,Sopra6l,Sopra8L,Sopra8l, SopraLaterale, LateraleLaterale;
  int i = 0;
  double colpito =0, trigger =0;
  double t = TMath::Tan(theta), c = TMath::Cos(phi), s = TMath::Sin(phi);
  int PHISL11, PHISL12, PHISL13, PHISL21, PHISL22, PHISL23, PHISL31, PHISL32, PHISL33, PHISL34, PHISL35, PHISL36, PHISL37, PHISL41,PHISL42,PHISL43,PHISL44,PHISL45,PHISL46,PHISL47;
  int PHISL111, PHISL112, PHISL113, PHISL114, PHISL211, PHISL212, PHISL213, PHISL214;
  int Colpito;
  //Localizzo il cristallo
  if(PMT == 1){
    Y = a0;
    Z = 0;
  }
  if(PMT == 2){
    Y = a0 + a;
    Z = 0;
  }
  if(PMT == 3){
    Y = a0;
    Z = a;
  }
  if(PMT == 4){
    Y = a0 + a;
    Z = a;
  }
  if(PMT == 5){
    Y = a0;
    Z = 2*a;
  }
  if(PMT == 6){
    Y = a0 + a;
    Z = 2*a;
  }
      //SOPRA DA SOPRA
      //verifico se sono sopra sopra
      PhiSS_1 = TMath::ATan((Y+a-y)/(X+b-x));
      PhiSS_2 = M_PI - TMath::ATan((a-y+Y)/(x-X));
      PhiSS_3 = M_PI + TMath::ATan((y-Y)/(x-X));
      PhiSS_4 = 2*M_PI - TMath::ATan((y-Y)/(X+b-x));
      ASS1 = (phi >= PhiSS_4 && phi <= 2*M_PI) || (phi >= 0 && phi <= PhiSS_1);
      ASS2 =(phi >= PhiSS_1 && phi <= PhiSS_2);
      ASS3 = (phi >= PhiSS_2 && phi <= PhiSS_3); 
      ASS4 = (phi >= PhiSS_3  && phi <= PhiSS_4);
      LSS_xy = ((X+b-x)/(TMath::Cos(phi)))*ASS1 + ((Y+a-y)/(TMath::Sin(phi)))*ASS2 -(((x-X)/(TMath::Cos(phi))))*ASS3 -(((y-Y)/(TMath::Sin(phi))))*ASS4;
      thetaSSMax = TMath::ATan((LSS_xy)/(Z));
      ThetaSS = theta <= thetaSSMax;
      ZonaSopra = ((x >= X) && (x <= X + b)) && ((y >= Y) && (y <= Y + a));
      SS = ZonaSopra*ThetaSS;
      if (SS == 1){// se colpisco sopra da sopra è esattamente il caso di sguincio (traslato);
	   double t = TMath::Tan(theta), c = TMath::Cos(phi), s = TMath::Sin(phi);
	   N_pe = ss*sguincio (x - X + Z*t*c, y - Y + Z*t*s , theta, phi);
	   if (N_pe < 0) return -3; // flag nel caso qualcosa andasse storto
      }
      //COLPISCO DA LATERALE
      /*verifico in quale zona laterale è l'evento*/
      Zona1 = (x < X) && (y < Y);
      Zona2 = (x < X) && ((y > Y) && (y < Y +a));
      Zona3 = (x < X) && (y > Y  + a);
      Zona4 = ((x > X) && (x < X+b)) && (y < Y);
      Zona5 = ((x > X) && (x < X+b)) && (y > Y+a);
      Zona6 = (x > X + b) && (y < Y);
      Zona7 = (x > X + b) && ((y > Y) && (y < Y +a));
      Zona8 = (x > X + b) && (y > Y + a);
      /*angoli limite vari ed eventuali (li mortacci loro....)*/
      phi1L1 = TMath::ATan((Y-y)/(X+b-x));
      phi1L2 = phi1l1 = TMath::ATan((Y-y)/(X-x));
      phi1l2 = TMath::ATan((Y+a-y)/(X-x));
      phi21 = TMath::ATan(((Y+a)-y)/(X-x));
      phi22 = 2*M_PI - TMath::ATan((y-Y)/(X-x));
      phi3l1 = 2*M_PI - TMath::ATan((y-Y)/(X-x));
      phi3l2 =  phi3L1 = 2*M_PI - TMath::ATan((y-(Y+a))/(X-x));
      phi3L2 = 2*M_PI - TMath::ATan((y-(Y+a))/(X+b-x));
      phi41 = TMath::ATan((Y-y)/(X+b-x));
      phi42 = M_PI - TMath::ATan((Y-y)/(x-X));
      phi51 = M_PI + TMath::ATan((y-(Y+a))/(x-X));
      phi52 = 2*M_PI -TMath::ATan((y-(Y+a))/(X+b-x));
      phi6l1 = M_PI - TMath::ATan((Y+a-y)/(x-(X+b)));
      phi6l2 = phi6L1 = M_PI - TMath::ATan((Y-y)/(x-(X+b)));
      phi6L2 = M_PI -  TMath::ATan((Y-y)/(x-X));
      phi71 = M_PI - TMath::ATan((Y+a-y)/(x-(X+b)));
      phi72 = M_PI + TMath::ATan((y-Y)/(x-(X+b)));
      phi8L1 = M_PI + TMath::ATan((y-(Y+a))/(x-X));
      phi8L2 = phi8l1 = M_PI + TMath::ATan((y-(Y+a))/(x-(X+b)));
      phi8l2 = M_PI + TMath::ATan((y-Y)/(x-(X+b)));
      
      theta3 = TMath::ATan((Y-y)/((Z+a)*s));
      theta4 = -1*TMath::ATan((y-(Y+a))/((Z+a)*s));
      theta1 = TMath::ATan((X-x)/((Z+a)*c));
      theta2 = -1*TMath::ATan((x-(X+b))/((Z+a)*c));
      
      thetas11 = TMath::ATan((X-x)/(Z*c));
      thetas21 = TMath::ATan((X+b-x)/(Z*c));
      thetas31 = TMath::ATan((Y-y)/(Z*s));
      thetas41 = TMath::ATan((Y+a-y)/(Z*s));
      
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

      PHISL11 = ((phi >= 0) && (phi < TMath::ATan((Y+a-y)/(X+b-x)))) || ((phi > 2*M_PI - TMath::ATan((Y-y)/(X-x))) && (phi < 2*M_PI));
      PHISL12 = (phi > TMath::ATan((Y+a-y)/(X+b-x))) && (phi < phi21);
      PHISL13 = (phi > phi22) && (phi < 2*M_PI - TMath::ATan((Y-y)/(X+b-x)));
      PHISL21 = (phi > phi71) && (phi < M_PI - TMath::ATan((Y+a-y)/(x-X)));
      PHISL22 = (phi > M_PI - TMath::ATan((Y+a-y)/(x-X))) && (phi < M_PI + TMath::ATan((y-Y)/(x-X)));
      PHISL23 = (phi > M_PI + TMath::ATan((y-Y)/(x-X))) && (phi < phi72);
      PHISL31 = (phi > phi1L1) && (phi < TMath::ATan((Y+a-y)/(X+b-x)));
      PHISL32 = (phi > TMath::ATan((Y+a-y)/(X+b-x))) && (phi < phi1l2);
      PHISL33 = (phi > phi41) && (phi < TMath::ATan((Y+a-y)/(X+b-x)));
      PHISL34 = (phi > TMath::ATan((Y+a-y)/(X+b-x))) && (phi < M_PI - TMath::ATan((Y+a-y)/(x-X)));
      PHISL35 = (phi > M_PI - TMath::ATan((Y+a-y)/(x-X))) && (phi < phi42);
      PHISL36 = (phi > phi6L1) && (phi < TMath::ATan((Y+a-y)/(x-X)));
      PHISL37 = (phi > TMath::ATan((Y+a-y)/(x-X))) && (phi < phi6L2);
      PHISL41 = (phi > phi3L1) && (phi < 2*M_PI - TMath::ATan((y-Y)/(X+b-x)));
      PHISL42 = (phi > 2*M_PI - TMath::ATan((y-Y)/(X+b-x))) && (phi < phi3L2);
      PHISL43 = (phi > phi51) && (phi < M_PI + TMath::ATan((y-Y)/(x-X)));
      PHISL44 = (phi > M_PI + TMath::ATan((y-Y)/(x-X))) && (phi < 2*M_PI - TMath::ATan((y-Y)/(X+b-x)));
      PHISL45 = (phi > 2*M_PI - TMath::ATan((y-Y)/(X+b-x))) && (phi < phi52);
      PHISL46 = (phi > phi8L1) && (phi < TMath::ATan((y-Y)/(x-X)));
      PHISL47 = (phi > TMath::ATan((y-Y)/(x-X))) && (phi < phi8L2);
      PHISL111 = (phi > phi1l1) && (phi < TMath::ATan((Y+a-y)/(X+b-x)));
      PHISL112 = (phi > TMath::ATan((Y+a-y)/(X+b-x))) && (phi < phi1l2);
      PHISL113 = (phi > phi3l1) && (phi < 2*M_PI - TMath::ATan((y-Y)/(X+b-x)));
      PHISL114 = (phi > 2*M_PI - TMath::ATan((y-Y)/(X+b-x))) && (phi < phi3l2);
      PHISL211 = (phi > phi6l1) && (phi < M_PI -TMath::ATan((Y+a-y)/(x-X)));
      PHISL212 = (phi > M_PI -TMath::ATan((Y+a-y)/(x-X))) && (phi < phi6l2);
      PHISL213 = (phi > phi8l1) && (phi < M_PI + TMath::ATan((y-Y)/(x-X)));
      PHISL214 = (phi > M_PI + TMath::ATan((y-Y)/(x-X))) && (phi < phi8l2);

      if (Zona1 == 1) {
	if (Phi1l == 1) {
	  if (y > (b/a)*(x-X) + Y){
	    if (PHISL111 == 1) thetas12 = TMath::ATan((X+b-x)/(Z*c));
	    if (PHISL112 == 1) thetas12 = TMath::ATan((Y+a-y)/(Z*s));
	  }
	  else if (y < (b/a)*(x-X) + Y) thetas12 = TMath::ATan((Y+a-y)/(Z*s));
	}
	if (Phi1L == 1) {
	  if (PHISL31 == 1) thetas32 = TMath::ATan((X+b-x)/(Z*c));
	  if (PHISL32 == 1) thetas32 = TMath::ATan((Y+a-y)/(Z*s));
	}
      }
      if (Zona2 == 1){
	if (PHISL11 == 1) thetas12 = TMath::ATan((X+b-x)/(Z*c));
	if (PHISL12 == 1) thetas12 = TMath::ATan((Y+a-y)/(Z*s));
	if (PHISL13 == 1) thetas12 = TMath::ATan((Y-y)/(Z*s));				 
      }
      if (Zona3 == 1){
        if (Phi3l == 1) {
	  if (y < -(b/a)*(x-X) + Y + a){
	    if (PHISL114 == 1) thetas12 = TMath::ATan((X+b-x)/(Z*c));
	    if (PHISL113 == 1) thetas12 = TMath::ATan((Y-y)/(Z*s));
	  }
	  else if (y > -(b/a)*(x-X) + Y + a) thetas12 = TMath::ATan((Y-y)/(Z*s));
	}
	if (Phi3L == 1){
	  if (PHISL41 == 1) thetas42 = TMath::ATan((Y-y)/(Z*s));
	  if (PHISL42 == 1) thetas42 = TMath::ATan((X+b-x)/(Z*c));
	}
      }

      if (Zona4 == 1){
	if (PHISL33 == 1) thetas32 = TMath::ATan((X+b-x)/(Z*c));
	if (PHISL34 == 1) thetas32 = TMath::ATan((Y+a-y)/(Z*s));
	if (PHISL35 == 1) thetas32 = TMath::ATan((X-x)/(Z*c));
      }

      if (Zona5 == 1){
        if (PHISL43 == 1) thetas42 = TMath::ATan((X-x)/(Z*c));
	if (PHISL44 == 1) thetas42 = TMath::ATan((Y-y)/(Z*s));
	if (PHISL45 == 1) thetas42 = TMath::ATan((X+b-x)/(Z*c));
      }
	
      if (Zona6 == 1){
        if (Phi6l == 1){
	  if (y > -(b/a)*(x-X) + Y+a){
	    if (PHISL211) thetas22 = TMath::ATan((Y+a-y)/(Z*s));
	    if (PHISL212) thetas22 = TMath::ATan((X-x)/(Z*c));
	  }
	  else if (y < -(b/a)*(x-X) + Y+a) thetas22 = TMath::ATan((Y+a-y)/(Z*s));
	}
	if (Phi6L == 1){
	  if (PHISL37 == 1) thetas32 = TMath::ATan((Y+a-y)/(Z*s));
	  if (PHISL36 == 1) thetas32 = TMath::ATan((X-x)/(Z*c));
	}
      }
      if (Zona7 == 1){
	if (PHISL21 == 1) thetas22 = TMath::ATan((Y+a-y)/(Z*s));
	 if (PHISL22 == 1) thetas22 = TMath::ATan((X-x)/(Z*c));
	 if (PHISL23 == 1) thetas22 = TMath::ATan((Y-y)/(Z*s));  
      }
      if (Zona8 == 1){
	if (Phi8l == 1){
	  if (y < (b/a)*(x-X) +Y) {
	    if (PHISL213) thetas22 = TMath::ATan((X-x)/(Z*c));
	    if (PHISL214) thetas22 = TMath::ATan((Y-y)/(Z*s));
	  }
	  else if (y > (b/a)*(x-X) +Y) thetas22 = TMath::ATan((Y-y)/(Z*s));
	}
	 if (Phi8L == 1){
	   if (PHISL46 == 1) thetas42 = TMath::ATan((X-x)/(Z*c));
	   if (PHISL47 == 1) thetas42 = TMath::ATan((Y-y)/(Z*s));
	 }
      }
	 
      //da che zona laterale colpisco sopra?
      //sopra-laterale
      Sopra1L = Zona1 && ((theta >= thetas31) && (theta <= thetas32)) && Phi1L;
      Sopra1l = Zona1 && ((theta >= thetas11) && (theta <= thetas12)) && Phi1l;
      Sopra2 = Zona2 && ((theta >= thetas11) && (theta <= thetas12)) && Phi2;
      Sopra3L = Zona3 && ((theta >= thetas41) && (theta <= thetas42)) && Phi3L;
      Sopra3l = Zona3 && ((theta >= thetas11) && (theta <= thetas12)) && Phi3l;
      Sopra4 = Zona4 && ((theta >= thetas31) && (theta <= thetas32)) && Phi4;
      Sopra5 = Zona5 && ((theta >= thetas41) && (theta <= thetas42)) && Phi5;
      Sopra6L = Zona6 && ((theta >= thetas31) && (theta <= thetas32)) && Phi6L;
      Sopra6l = Zona6 && ((theta >= thetas21) && (theta <= thetas22)) && Phi6l;
      Sopra7 = Zona7 && ((theta >= thetas21) && (theta <= thetas22)) && Phi7;
      Sopra8L = Zona8 && ((theta >= thetas41) && (theta <= thetas42)) && Phi8L;
      Sopra8l = Zona8 && ((theta >= thetas21) && (theta <= thetas22)) && Phi8l;
	 
      Theta1 = (theta > theta1) && (theta < thetas11);
      Theta2 = (theta > theta2) && (theta < thetas21);
      Theta3 = (theta > theta3) && (theta < thetas31);
      Theta4 = (theta > theta4) && (theta < thetas41);
      //laterale-laterale
      PMT4 = Zona4 && Theta3 && Phi4;
      PMT5 = Zona5 && Theta4 && Phi5;
      PMT2 = Zona2 && Theta1 && Phi2;
      PMT7 = Zona7 && Theta2 && Phi7;
      PMT1L = Zona1 && Theta3 && Phi1L;
      PMT1l = Zona1 && Theta1 && Phi1l;
      PMT6L = Zona6 && Theta3 && Phi6L;
      PMT6l = Zona6 && Theta2 && Phi6l;
      PMT8L = Zona8 && Theta4 && Phi8L;
      PMT8l = Zona8 && Theta2 && Phi8l;
      PMT3L = Zona3 && Theta4 && Phi3L;
      PMT3l = Zona3 && Theta1 && Phi3l;
      
      
      SopraLaterale = Sopra1L || Sopra5 || Sopra6L || Sopra3L || Sopra4 || Sopra8L ||Sopra1l || Sopra2 || Sopra3l || Sopra6l || Sopra7 || Sopra8l*(1-SS);
      LateraleLaterale =  PMT3L || PMT4 || PMT8L || PMT1l || PMT2 || PMT3l || PMT6l || PMT7 || PMT8l || PMT1L || PMT5 || PMT6L;
      
      //SOPRA DA LATERALE
      if (SopraLaterale == 1){
	colpito ++;
	N_pe = sl*sguincio(x - X + Z*t*c , y - Y + Z*t*s , theta , phi);
	if (N_pe < 0) return -5; // flag nel caso qualcosa andasse storto
      }      
      //LATERALE DA LATERALE
      if (LateraleLaterale == 1){
	N_pe = ll*sguincio((x - X + (Z+a)*t*c), (y - Y + (Z+a)*t*s) , theta ,M_PI + phi);
	if (N_pe < 0) return -20; // flag nel caso qualcosa andasse storto
    }
      
      Colpito = LateraleLaterale + SopraLaterale + SS ;
      if (Colpito == 0) return 0; // se Colpito = 0 vuol dire che non si è colpito il cristallo
      return N_pe;
  }

// SIMULAZIONE DELL'ESPERIMENTO
// genera N eventi muonici fissando x, y, theta, phi, sullo scintillatore superiore:
// se l'evento triggera verifica quale PMT colpisce e calcola il numero di fotoelettroni atteso;
// genera l'istogramma di N_pe e calcola l'accettanza di ciascun PMT e la restituisce. Disegna l'istogramma e le coordinate (x,y) di ciascun cristallo.
// N è il numero di eventi triggeranti che si vogliono generare.
// Limite è il limite superiore dell'istogramma.
// Tr è il trigger: se Tr = 1 allora si scelgono gli eventi triggeranti. Se Tr = 0 quelli non triggeranti.
// rum implementa il taglio sul rumore.
// grafico = 1: visualizzazione grafico
//  ss = 1: visualizzazione eventi SOPRA-SOPRA
//  sl = 1: visualizzazione eventi SOPRA-LATERALE
//  ll = 1: visualizzazione eventi LATERALE-LATERALE 


double* Simulazione (int N, int Limite, int Tr, int grafico, int rum, int ss, int sl, int ll){
  double x,y,z,phi,theta;
  double A = 40.0, B = 51.5, trigger = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, N1, N2, N3, N4, N5, N6;
  int T, i =0;
  TF1* distribuzioneZeta = new TF1("distribuzioneZeta", "[0]*x*x", 0,1);
  double* ArrayAccettanza = (double*) malloc (6*sizeof(double)); 
  distribuzioneZeta->SetParameter(0,3);
  TH1D* h1 = new TH1D("h1", "1; N_{pe}", sqrt(N),-5*rum + 1*(1-rum), Limite);
  TH1D* h2 = new TH1D("h2", "2; N_{pe}", sqrt(N),-5*rum + 1*(1-rum), Limite);
  TH1D* h3 = new TH1D("h3", "3; N_{pe}", sqrt(N),-5*rum + 1*(1-rum), Limite);
  TH1D* h4 = new TH1D("h4", "4; N_{pe}", sqrt(N),-5*rum + 1*(1-rum), Limite);
  TH1D* h5 = new TH1D("h5", "5; N_{pe}", sqrt(N),-5*rum + 1*(1-rum), Limite);
  TH1D* h6 = new TH1D("h6", "6; N_{pe}", sqrt(N),-5*rum + 1*(1-rum), Limite);
  TGraph* g1 = new TGraph();
  TGraph* g2 = new TGraph();
  TGraph* g3 = new TGraph();
  TGraph* g4 = new TGraph();
  TGraph* g5 = new TGraph();
  TGraph* g6 = new TGraph();
  
  while (i != N){
    x = gRandom->Uniform(0,B);
    y = gRandom->Uniform(0,A);
    z = distribuzioneZeta->GetRandom(0,1);
    phi = gRandom->Uniform(0,2*M_PI);
    theta = TMath::ACos(z);
    T = Trigger(x,y,theta,phi);
    if (T == 1){
      i++;
      N1 = Montecarlo( x,  y,  theta,  phi,  1,  Tr, ss, sl, ll);
      N2 = Montecarlo( x,  y,  theta,  phi,  2,  Tr, ss, sl, ll);
      N3 = Montecarlo( x,  y,  theta,  phi,  3,  Tr, ss, sl, ll);
      N4 = Montecarlo( x,  y,  theta,  phi,  4,  Tr, ss, sl, ll);
      N5 = Montecarlo( x,  y,  theta,  phi,  5,  Tr, ss, sl, ll);
      N6 = Montecarlo( x,  y,  theta,  phi,  6,  Tr, ss, sl, ll);
      h1-> Fill(N1);
      h2-> Fill(N2);
      h3-> Fill(N3);
      h4-> Fill(N4);
      h5-> Fill(N5);
      h6-> Fill(N6);
      if (N1 > 0) {g1->SetPoint(i,x,y); c1++;}
      if (N2 > 0) {g2->SetPoint(i,x,y); c2++;}
      if (N3 > 0) {g3->SetPoint(i,x,y); c3++;}
      if (N4 > 0) {g4->SetPoint(i,x,y); c4++;}
      if (N5 > 0) {g5->SetPoint(i,x,y); c5++;}
      if (N6 > 0) {g6->SetPoint(i,x,y); c6++;}
    }
  }

  if (grafico == 1){
  TCanvas* c = new TCanvas("c","Distribuzione Fotoelettroni");
  c->Divide(2,3);
  TCanvas* d = new TCanvas("d","Eevent Display");
  d->Divide(2,3);
  c->cd(1);
  h1->Draw();
  gPad->SetLogy();
  c->cd(2);
  h2->Draw();
  gPad->SetLogy();
  c->cd(3);
  h3->Draw();
  gPad->SetLogy();
  c->cd(4);
  h4->Draw();
  gPad->SetLogy();
  c->cd(5);
  h5->Draw();
  gPad->SetLogy();
  c->cd(6);
  h6->Draw();
  gPad->SetLogy();

  d->cd(1);
  g1->Draw();
  g1->SetLineColor(0);
  g1->SetTitle("1");
  g1->SetMaximum(51.5);
  g1->SetMinimum(0);
  d->cd(2);
  g2->Draw();
  g2->SetLineColor(0);
  g2->SetTitle("2");
  g2->SetMaximum(51.5);
  g2->SetMinimum(0);
  d->cd(3);
  g3->Draw();
  g3->SetLineColor(0);
  g3->SetMaximum(51.5);
  g3->SetMinimum(0);
  g3->SetTitle("3");
  d->cd(4);
  g4->Draw();
  g4->SetLineColor(0);
  g4->SetTitle("4");
  g4->SetMaximum(51.5);
  g4->SetMinimum(0);
  d->cd(5);
  g5->Draw();
  g5->SetLineColor(0);
  g5->SetTitle("5");
  g5->SetMaximum(51.5);
  g5->SetMinimum(0);
  d->cd(6);
  g6->Draw();
  g6->SetLineColor(0);
  g6->SetTitle("6");
  g6->SetMaximum(51.5);
  g6->SetMinimum(0);
  }

  ArrayAccettanza[0] = c1/N;
  ArrayAccettanza[1] = c2/N;
  ArrayAccettanza[2] = c3/N;
  ArrayAccettanza[3] = c4/N;
  ArrayAccettanza[4] = c5/N;
  ArrayAccettanza[5] = c6/N;
  
  return ArrayAccettanza;
}


//DISTRIBUZIONE ACCETTANZE
// esegue M volte l'algoritmo di simulazione Simulazione(), eseguito ogni volta su N eventi, e produce l'istogramma del risultato per ciascun cristallo
// N: numero di eventi per ogni iterazione
// M: numero di iterazioni
// Tr = 1: selezione eventi triggeranti
// ss = 1: selezione eventi SOPRA-SOPRA
// sl = 1: selezione eventi SOPRA-LATERALE
// ll = 1: selezione eventi LATERALE-LATERALE

void IstogrammiAccettanze (int N, int M, int Tr, int ss, int sl, int ll){
  TH1D* h1 = new TH1D("h1", "1; A_1", 500, 0, 1);
  TH1D* h2 = new TH1D("h2", "2; A_2", 500, 0, 1);
  TH1D* h3 = new TH1D("h3", "3; A_3", 500, 0, 1);
  TH1D* h4 = new TH1D("h4", "4; A_4", 500, 0, 1);
  TH1D* h5 = new TH1D("h5", "5; A_5", 500, 0, 1);
  TH1D* h6 = new TH1D("h6", "6; A_6", 500, 0, 1);
  TCanvas* c = new TCanvas ("c", "Istogramma accettanze geometriche");
  c->Divide(2,3);
  double A1,A2,A3,A4,A5,A6;
  double dA1, dA2, dA3, dA4, dA5, dA6;
  double* Accettanze;
  for (int i = 0; i < M; i++){
	Accettanze = Simulazione (N, 100, Tr, 0, 1,  ss,  sl,  ll);
	A1 = Accettanze[0];
	A2 = Accettanze[1];
	A3 = Accettanze[2];
	A4 = Accettanze[3];
	A5 = Accettanze[4];
	A6 = Accettanze[5];
	h1->Fill(A1);
	h2->Fill(A2);
	h3->Fill(A3);
	h4->Fill(A4);
	h5->Fill(A5);
	h6->Fill(A6);
  }
  c->cd(1);
  h1->Draw();
  A1 = h1->GetMean();
  dA1 = h1->GetStdDev();
  c->cd(2);
  h2->Draw();
  A2 = h2->GetMean();
  dA2 = h2->GetStdDev();
  c->cd(3);
  h3->Draw();
  A3 = h3->GetMean();
  dA3 = h3->GetStdDev();
  c->cd(4);
  h4->Draw();
  A4 = h4->GetMean();
  dA4 = h4->GetStdDev();
  c->cd(5);
  h5->Draw();
  A5 = h5->GetMean();
  dA5 = h5->GetStdDev();
  c->cd(6);
  h6->Draw();
  A6 = h6->GetMean();
  dA6 = h6->GetStdDev();
  cout << "---------------------------------------------------------------" << endl;
  cout << "--------------------- CALCOLO ACCETTANZE -----------------------" << endl;
  cout << "---------------------------------------------------------------" << endl;
  cout << "A1 = " << A1 << endl;
  cout << "dA1 = " << dA1 << endl;
  cout << "---------------------------------------------------------------" << endl;
  cout << "A2 = " << A2 << endl;
  cout << "dA2 = " << dA2 << endl;
  cout << "---------------------------------------------------------------" << endl;
  cout << "A3 = " << A3 << endl;
  cout << "dA3 = " << dA3 << endl;
  cout << "---------------------------------------------------------------" << endl;
  cout << "A4 = " << A4 << endl;
  cout << "dA4 = " << dA4 << endl;
  cout << "---------------------------------------------------------------" << endl;
  cout << "A5 = " << A5 << endl;
  cout << "dA5 = " << dA5 << endl;
  cout << "---------------------------------------------------------------" << endl;
  cout << "A6 = " << A6 << endl;
  cout << "dA6 = " << dA6 << endl;
  cout << "---------------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------" << endl;
  return;
}
