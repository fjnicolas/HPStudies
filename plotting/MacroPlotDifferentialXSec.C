const std::string datasetsParentPath = ((std::string) getenv("G4ANADIR")) + "/datasets/";

void MacroPlotDifferentialXSec(){
    std::cout<<"MacroPlotDifferentialXSec"<<std::endl;
}

std::vector kColors = {kGreen+2, kRed+3, kBlue+4};

TGraphErrors* PlotBellettiniData(std::string filename, double mom){

    std::ifstream file(filename);
    if (!file.is_open()){
        std::cout<<"Error opening file "<<filename<<std::endl;
        return nullptr;
    }

    // format is two coumns: t, xsec
    std::vector<double> t_v, xsec_v;
    double t, xsec;
    while(!file.eof()){
        file >> t >> xsec;
        t_v.push_back(t);
        xsec_v.push_back(xsec);
    }

    // approx: t = p^2 * theta^2
    // get theta for each t
    // change variable dsigma/domega to dsigma/dt
    // dsigma/domega is in cm^2/sr, also need to convert to mb/sr
    // 1mb = 1e-27 cm^2
    double cm2_to_mb = 1./1e-27;
    for( int i = 0; i < t_v.size(); i++){
        double xsec_ = xsec_v[i];
        
        double theta = sqrt( t_v[i] ) / mom;

        xsec_v[i] =  cm2_to_mb * xsec_ * M_PI * sin(theta) / (mom*mom*theta);

        std::cout << "t: " << t_v[i] << " theta: " << theta << " xsec: " << xsec_ << " xsec_new: " << xsec_v[i] << std::endl;
    }

    // plot
    TGraphErrors *g = new TGraphErrors(t_v.size(), &t_v[0], &xsec_v[0], 0, 0);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kAzure);

    return g;
}


TGraphErrors* PlotEMPHATICData(std::string filename, double matScaling = 1.0){
    // Load EMPHATIC data
    ifstream fileEMPHATIC(datasetsParentPath + "EMPHATIC_pC_30GeV.txt");
    if (!fileEMPHATIC.is_open()){
        std::cout<<"Error opening file EMPHATICData_20GeV.txt"<<std::endl;
        return nullptr;
    }

    // Format of the file for each line is range_low range_high xsec
    // Read the file and store the data in a TGraph
    std::vector<double> x, y, yerr;
    double range_low, range_high, xsec, tot_err;
    while(!fileEMPHATIC.eof()){
        double aux;
        fileEMPHATIC >> range_low >> range_high >> xsec >> aux >> aux >> aux >> aux >> tot_err >> aux;
        x.push_back(0.5*(range_low + range_high));
        y.push_back( xsec * matScaling );
        yerr.push_back( tot_err * matScaling );
        std::cout << 0.5*(range_low + range_high) << " " << xsec * matScaling << std::endl;
    }

    TGraphErrors *g = new TGraphErrors(x.size(), &x[0], &y[0], 0, &yerr[0]);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kRed+2);
    g->SetTitle(";p^{2}#theta^{2} [(GeV/c)^{2}];d#sigma/dt (mb/(GeV/c)^{2})");

    return g;

}


TF1* AddQESlopeFitting(std::vector<TH1D*> hV, double range_min, double range_max){
    // Exponential fit
    TF1 *fExp = new TF1("fExp", "[0]*exp(-[1]*x)", range_min, range_max);
    fExp->SetParameters(1e5, 10);
    fExp->SetLineColor(kRed);
    fExp->SetLineStyle(kDashed);
    fExp->SetLineWidth(3);

    TH1F *hSum = new TH1F("hSum", "", hV[0]->GetNbinsX(), hV[0]->GetXaxis()->GetXmin(), hV[0]->GetXaxis()->GetXmax());
    for(int i = 0; i < hV.size(); i++){
        hSum->Add(hV[i]);
    }
    hSum->Fit(fExp, "R");

    return fExp;
}


void PlotRatioDataG4(std::vector<TH1D*> hV, TGraphErrors *grData, std::string label, double min, double max){

    // Make total histogram
    TH1F *hSum = new TH1F("hSum", label.c_str(), hV[0]->GetNbinsX(), hV[0]->GetXaxis()->GetXmin(), hV[0]->GetXaxis()->GetXmax());
    for(int i = 0; i < hV.size(); i++){
        hSum->Add(hV[i]);
    }

    // Data
    TH1* hData = new TH1F("hData", label.c_str(), hSum->GetNbinsX(), hSum->GetXaxis()->GetXmin(), hSum->GetXaxis()->GetXmax());
    for(int i = 0; i < grData->GetN(); i++){
        double x, y, yerr;
        grData->GetPoint(i, x, y);
        yerr = grData->GetErrorY(i);
        std::cout << "x: " << x << " y: " << y << std::endl;
        if(x < min || x > max) continue;
        // get bin
        int bin = hData->FindBin(x);
        hData->SetBinContent(bin, y);
        if(yerr > 0)
            hData->SetBinError(bin, yerr);
        std::cout << "    x: " << x << " y: " << y << " bin: " << bin << std::endl;
    }

    TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9);
    legend->SetHeader(label.c_str());

    // Ratio plot
    TRatioPlot *rp = new TRatioPlot(hData, hSum);
    rp->SetH2DrawOpt("hist");
    rp->SetH1DrawOpt("p");
    rp->SetGraphDrawOpt("p");    
    rp->Draw();

    rp->SetLowBottomMargin(0.55);
    rp->SetLeftMargin(0.15);

    double minY = std::min( hData->GetMinimum(0), hSum->GetMinimum(0) );
    double maxY = std::max( hData->GetMaximum(), hSum->GetMaximum() );
    rp->GetUpperRefYaxis()->SetRangeUser(0.9*minY, 1.1*maxY);

    // marker style first histogram
    hSum->SetLineColor(kRed+2);
    hSum->SetLineWidth(2);
    // marker style second histogram
    hData->SetMarkerStyle(20);
    hData->SetMarkerColor(kAzure);
    rp->SetSeparationMargin(0.001);
    // no stats
    hSum->SetStats(0);
    hData->SetStats(0);

    rp->GetUpperRefYaxis()->SetTitle("d#sigma/dt (mb/(GeV/c)^{2})");
    rp->GetLowerRefYaxis()->SetTitle("Data / G4");
    hSum->GetXaxis()->SetTitle("p^{2}#theta^{2} [(GeV/c)^{2}]");
    hData->GetXaxis()->SetTitle("p^{2}#theta^{2} [(GeV/c)^{2}]");

    rp->GetLowerRefGraph()->SetMarkerStyle(20);
    rp->GetLowerRefGraph()->SetMarkerColor(kBlack);
    rp->GetLowerRefGraph()->SetLineColor(kBlack);
    rp->GetLowerRefGraph()->SetLineWidth(2);
    rp->GetLowerRefGraph()->SetMarkerSize(1.2);

    // Ratio plot limits
    rp->GetLowerRefYaxis()->SetRangeUser(0.01, 2.);
    rp->GetLowYaxis()->SetNdivisions(1005);
    
    // Offsets
    rp->GetLowerRefYaxis()->SetTitleOffset(1.2);
    rp->GetUpperRefYaxis()->SetTitleOffset(1.2);
    rp->GetLowerRefXaxis()->SetTitleOffset(1.2);

    legend->AddEntry(hSum, "G4", "l");
    legend->AddEntry(hData, "Data", "p");
    legend->Draw("same");
;
}


void PlotDifferentialXSec(std::string material, double mom){


    std::string filenameGeant;
    std::string filenameEMPHATIC;
    std::string filenameBellettini;
    double matScaling = 1.;

    if(material == "C"){
        matScaling = 1.0;
        filenameGeant = "DiffXSec_pC_20GeV_FTFP.root";
        filenameEMPHATIC = datasetsParentPath + "EMPHATIC_pC_20GeV.txt";
        filenameBellettini = datasetsParentPath + "/Bellettini_pC_20GeV.txt";
    }
    else if(material == "Be"){
        matScaling = std::pow(0.75, 1./3.);
        filenameGeant = "DiffXSec_pBe_20GeV_FTFP.root";
        filenameEMPHATIC = datasetsParentPath + "EMPHATIC_pC_20GeV.txt";
        filenameBellettini = datasetsParentPath + "Bellettini_pBe_20GeV.txt";
    }

    // Load Geant4 data
    std::vector<string> histNameV = {"QElike", "prodContamination"};
    std::vector<TH1D*> hV;
    //histNameV = {"forw"};
    TFile *f = new TFile(filenameGeant.c_str());
    for(auto histName : histNameV){
        TH1D *h = (TH1D*)f->Get( ("xsec/hxsecA_" + histName).c_str() );
        hV.push_back(h);
    }
    
    std::string canvasName = "p-"+material+"@"+std::to_string( (int) mom)+"GeV";
    TCanvas *c = new TCanvas("c", canvasName.c_str(), 100, 100, 1300, 1000);
    c->cd();
    TPad *pad1 = new TPad("pad1", "pad1", 0., 0., 0.5, 0.5);
    TPad *pad2 = new TPad("pad2", "pad2", 0.5, 0., 1., 0.5);
    TPad *pad3 = new TPad("pad3", "pad3", 0., 0.5, 0.5, 1.);
    TPad *pad4 = new TPad("pad4", "pad4", 0.5, 0.5, 1., 1.);
    pad1->Draw();
    pad2->Draw();
    pad3->Draw();
    pad4->Draw();
   
    pad1->cd();
    // Frame
    double min_t = 0.0;
    double max_t = 0.15;
    int nBins = 100;
    double min_xsec = 20;
    double max_xsec = 5e4;
    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.15);
    TH1D *hFrame = new TH1D("hFrame", ";p^{2}#theta^{2} [(GeV/c)^{2}];d#sigma/dt (mb/(GeV/c)^{2})", 100, 0, 0.15);
    hFrame->GetYaxis()->SetRangeUser(min_xsec, max_xsec);
    hFrame->SetStats(0);
    hFrame->GetXaxis()->SetTitleOffset(1.2);
    hFrame->GetYaxis()->SetTitleOffset(1.2);
    hFrame->Draw("");
    // TLegend
    TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9);
    legend->SetHeader(canvasName.c_str());

    // Fitting
    TF1* qeFit = AddQESlopeFitting(hV, 0.0, 0.15);

    hFrame->Draw();
    THStack *hStack = new THStack("hStack", "");
    for(int i = 0; i < hV.size(); i++){
        hV[i]->SetLineColor(kColors[i]);
        hV[i]->SetLineWidth(2);
        hStack->Add(hV[i]);
        legend->AddEntry(hV[i], histNameV[i].c_str(), "l");
    }   
    hStack->Draw("same");

    
    // EMPHATIC data
    TGraphErrors * grEMPHATIC = PlotEMPHATICData(filenameEMPHATIC, matScaling);
    grEMPHATIC->Draw("p same");
    if(material == "C") legend->AddEntry(grEMPHATIC, "EMPHATIC data", "p");
    else if(material == "Be") legend->AddEntry(grEMPHATIC, "EMPHATIC data (scaled)", "p");

    // Bellettini data
    TGraphErrors * grBellettini = PlotBellettiniData(filenameBellettini, mom);
    grBellettini->Draw("p same");
    legend->AddEntry(grBellettini, "Bellettini data", "p");

    // Draw fit
    qeFit->Draw("same");
    // fit slope, format to 1 decimal
    std::stringstream streamVal;
    streamVal << std::fixed << std::setprecision(1) << qeFit->GetParameter(1);
    std::stringstream streamErr;
    streamErr << std::fixed << std::setprecision(1) << qeFit->GetParError(1);
    std::string fitLabel = "Fit (slope: " + streamVal.str() + " #pm " + streamErr.str() + " mb/(GeV/c)^{2})";
    legend->AddEntry(qeFit, fitLabel.c_str(), "l");

    legend->Draw("same");
    hFrame->Draw("same axis");

    pad2->cd();
    gPad->SetLogy();    
    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.15);
    hFrame->Draw();
    hStack->Draw("same");
    grEMPHATIC->Draw("p same");
    grBellettini->Draw("p same");
    qeFit->Draw("same");
    legend->Draw("same");
    hFrame->Draw("same axis");


    pad3->cd();
    PlotRatioDataG4(hV, grEMPHATIC, "EMPHATIC", 0.05, 0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.15);

    pad4->cd();
    PlotRatioDataG4(hV, grBellettini, "Bellettini", 0.05, 0.15);
    


    c->cd();
    c->Update();
    c->WaitPrimitive();
    c->SaveAs( (canvasName+".pdf").c_str() );

}