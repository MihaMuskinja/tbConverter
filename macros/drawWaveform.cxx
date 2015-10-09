TGraph* drawWaveform(int nwf, const char* filePath="../testWF.root", const char* wfName="waveform1", const char* drawOption="")
{
	TFile* file = new TFile(filePath);
	TTree* t = (TTree*) file->Get("Plane0/Waveforms");
    TBranch* b = t->GetBranch(wfName);

	float wfTemp[10000];
    b->SetAddress(wfTemp);
    int bSize = b->GetEntry(nwf) / sizeof(float);

    float* taxis = new float[bSize];
    float* wf = new float[bSize];
    for(int i=0;i<bSize;i++) {
        taxis[i] = i;
        wf[i] = wfTemp[i];
    }
    TGraph* gr = new TGraph(1024,taxis,wf);
    gr->Draw(drawOption);
    gr->GetYaxis()->SetRangeUser(-0.17,0.03);
    file->Close();
    delete file;
    return gr;
}

TGraph* drawNWaveforms(int N, const char* filePath="../testWF.root", int N2=0, const char* wfName="waveform1"){
    TGraph* gr = new TGraph;
    TGraph* gr2 = new TGraph;
    gr = drawWaveform(N2,filePath,wfName,"");
	for(int i = N2+1;i<N+N2;i++){
	   gr2 = drawWaveform(i,filePath,wfName,"same");
	}

    return gr;
}

TGraph* avgNWaveforms(int N, const char* filePath="../testWF.root", int N2=0, const char* wfName="waveform1")
{
    TFile* file = new TFile(filePath);
    TTree* t = (TTree*) file->Get("Plane0/Waveforms");
    TBranch* b = t->GetBranch(wfName);

    int Nwfs = 0;

    float wfTemp[10000];
    b->SetAddress(wfTemp);
    int bSize = b->GetEntry(N2) / sizeof(float);

    float* taxis = new float[bSize];
    float* wf = new float[bSize];

    for(int i=0;i<bSize;i++) {
        taxis[i] = i;
        wf[i] = wfTemp[i]/((float)N);
    }
    Nwfs++;

    for(int nwf=N2+1; nwf<N+N2; nwf++) {
        b->GetEntry(nwf);
        for(int i=0;i<bSize;i++) {
            wf[i] = wf[i] + wfTemp[i]/((float)N);
        }
        Nwfs++;
    }
    TGraph* gr = new TGraph(1024,taxis,wf);
    gr->Draw();

    cout << "number of averaged waveforms: " << Nwfs << endl;

    file->Close();
    delete file;

    return gr;
}