{
	ifstream file("test.txt");
	double a[1024];

	for (int i = 0; i < 1024; i++) file >> a[i];
    TH1F *h1 = new TH1F("h1","h1",20,0,2)
	for(int i =0; i < 1024; i++)h1->Fill(a[i])
	h1->Draw()

}