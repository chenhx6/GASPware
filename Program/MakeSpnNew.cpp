
void MakeSpnNew()
{
	TString FileInName;
	cout <<" Input input file name" << endl;;
	cin >> FileInName;
	TString HistogramName;
	cout <<" Input the name of histogram" << endl;
	cin >> HistogramName;
	// Open file and get histrgam
//	TFile *ipf = new TFile("./Clover_g-g_matrix.root");
	TFile *ipf = new TFile(FileInName.Data());
//	TH2D *hggAll = (TH2D*)gROOT->FindObject("hggAll");
	TH2D *hggAll = (TH2D*)gROOT->FindObject(HistogramName.Data());
	// Get Bin number
    Int_t BinMax = hggAll->GetNbinsX();
	Int_t BytesPerChannel = 4; //bytes per channel 
    Int_t zmat[2000][2000] = {0};  // if Break here, ulimit -s 51200 in terminal
	// Get Count of each bin
    for(Int_t iy=1; iy <= BinMax; iy++)
    {
        for(Int_t ix=1; ix <= BinMax; ix++)
       	{
        	zmat[ix-1][iy-1] = (Int_t)hggAll->GetBinContent(ix, iy);
    	}
    }
	//Output  *.spn file
    FILE *fout;
    fout = fopen("out.spn", "wb+");
    for(Int_t zi=0; zi<BinMax; zi++)
    	fwrite(zmat[zi], BytesPerChannel, BinMax, fout);
    fclose(fout);
	std::cout << "Xbins and Ybins are " << BinMax << "   " << BinMax << std::endl;
	std::cout << BytesPerChannel << " bytes per channel." << std::endl;
}
