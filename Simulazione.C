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


double Montecarlo(double x, double y, double theta, double phi, int PMT, int TRIGGER){
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
	   N_pe = sguincio (x - X + Z*t*c, y - Y + Z*t*s , theta, phi);
	   if (N_pe < 0) return -3;
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
      phi22 = 2*M_PI - TMath::ATan((Y-y)/(X-x));
      phi3l1 = 2*M_PI - TMath::ATan((y-Y)/(X-x));
      phi3l2 =  phi3L1 = 2*M_PI - TMath::ATan((y-(Y+a))/(X-x));
      phi3L2 = 2*M_PI - TMath::ATan((y-(Y+a))/(X+b-x));
      phi41 = TMath::ATan((Y-y)/(X+b-x));
      phi42 = M_PI - TMath::ATan((Y-y)/(X-x));
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

      PHISL11 = ((phi > 0) && (phi < TMath::ATan((Y+a-y)/(X+b-x)))) || ((phi > 2*M_PI - TMath::ATan((Y-y)/(X-x))) && (phi < 2*M_PI));
      PHISL12 = (phi > TMath::ATan((Y+a-y)/(X+b-x))) && (phi < phi21);
      PHISL13 = (phi > phi21) && (phi < 2*M_PI - TMath::ATan((Y-y)/(X-x)));
      PHISL21 = (phi > phi71) && (phi < M_PI - TMath::ATan((Y+a-y)/(x-X)));
      PHISL22 = (phi > M_PI - TMath::ATan((Y+a-y)/(x-X))) && (phi < M_PI + TMath::ATan((y-Y)/(x-X)));
      PHISL23 = (phi > M_PI + TMath::ATan((y-Y)/(x-X))) && (phi < phi72);
      PHISL31 = (phi > phi1L1) && (phi < TMath::ATan((Y+a-y)/(X+b-x)));
      PHISL32 = (phi > TMath::ATan((Y+a-y)/(X+b-x))) && (phi < phi1l2);
      PHISL33 = (phi > phi1L1) && (phi < TMath::ATan((Y+a-y)/(X+b-x)));
      PHISL34 = (phi > TMath::ATan((Y+a-y)/(X+b-x))) && (phi < M_PI - TMath::ATan((Y+a-y)/(x-X)));
      PHISL35 = (phi > M_PI - TMath::ATan((Y+a-y)/(x-X))) && (phi < M_PI - TMath::ATan((Y-y)/(x-X)));
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
	    if (PHISL211) thetas22 = TMath::ATan((Y+a-y)/(Z*c));
	    if (PHISL212) thetas22 = TMath::ATan((X-x)/(Z*c));
	  }
	  else if (y < -(b/a)*(x-X) + Y+a) thetas22 = TMath::ATan((Y+a-y)/(Z*c));
	}
	if (Phi6L == 1){
	  if (PHISL36 == 1) thetas32 = TMath::ATan((Y+a-y)/(Z*s));
	  if (PHISL37 == 1) thetas32 = TMath::ATan((X-x)/(Z*c));
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

      //cout << SopraLaterale << LateraleLaterale << endl;
      //SOPRA DA LATERALE
      if (SopraLaterale == 1){
	colpito ++;
	N_pe = sguincio(x - X + Z*t*c , y - Y + Z*t*s , theta , phi);
	if (N_pe < 0) return -19;
      }      
      //LATERALE DA LATERALE
      if (LateraleLaterale == 1){
	N_pe = sguincio((x - X + (Z+a)*t*c), (y - Y + (Z+a)*t*s) , theta ,phi);
	if (N_pe < 0) return -20;
    }
      if (LateraleLaterale || SopraLaterale || SS == 0) return 0;
      return N_pe;
  }
void Simulazione (int N, int Limite, int Tr, int rum){
  double x,y,z,phi,theta;
  double A = 40.0, B = 51.5, trigger = 0, N1,N2,N3,N4,N5,N6;
  int T, i =0;
  TF1* distribuzioneZeta = new TF1("distribuzioneZeta", "[0]*x*x", 0,1);
  distribuzioneZeta->SetParameter(0,3);
  TH1D* h1 = new TH1D("h1", "1; N_{pe}", 250,-5*rum + 1*(1-rum), Limite);
  TH1D* h2 = new TH1D("h2", "2; N_{pe}", 250,-5*rum + 1*(1-rum), Limite);
  TH1D* h3 = new TH1D("h3", "3; N_{pe}", 250,-5*rum + 1*(1-rum), Limite);
  TH1D* h4 = new TH1D("h4", "4; N_{pe}", 250,-5*rum + 1*(1-rum), Limite);
  TH1D* h5 = new TH1D("h5", "5; N_{pe}", 250,-5*rum + 1*(1-rum), Limite);
  TH1D* h6 = new TH1D("h6", "6; N_{pe}", 250,-5*rum + 1*(1-rum), Limite);
  TCanvas* c = new TCanvas();
  c->Divide(2,3);
  while (i != N){
    x = gRandom->Uniform(0,B);
    y = gRandom->Uniform(0,A);
    z = distribuzioneZeta->GetRandom(0,1);
    phi = gRandom->Uniform(0,2*M_PI);
    theta = TMath::ACos(z);
    T = Trigger(x,y,theta,phi);
    if (T == 1){
      i++;
      N1 = Montecarlo( x,  y,  theta,  phi,  1,  Tr);
      N2 = Montecarlo( x,  y,  theta,  phi,  2,  Tr);
      N3 = Montecarlo( x,  y,  theta,  phi,  3,  Tr);
      N4 = Montecarlo( x,  y,  theta,  phi,  4,  Tr);
      N5 = Montecarlo( x,  y,  theta,  phi,  5,  Tr);
      N6 = Montecarlo( x,  y,  theta,  phi,  6,  Tr);
      h1-> Fill(N1);
      h2-> Fill(N2);
      h3-> Fill(N3);
      h4-> Fill(N4);
      h5-> Fill(N5);
      h6-> Fill(N6);
    }
  }
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
  return;
}
