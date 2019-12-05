//Vogliamo leggere e plottare dei dati

void graph_from_file()
{
	TGraphErrors* g = new TGraphErrors("plateauPMT8_50mv.txt");
	//A seconda del numero hai marker diversi
	g->SetMarkerStyle(7);
	g->SetLineColor(1);
	g->SetTitle("Plateau PMT8-soglia 50mv;tensioni[V];conteggi");
	//Disegnami gli Assi (A), una Linea(L) e i data Points (P)
	g->Draw("AP");
}
