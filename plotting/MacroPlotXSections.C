struct XSecPlot {
    std::string name;
    std::string label;
    int pdg;
    int isElastic;
    std::string material;
    int width;
};

struct XSecModel {
    std::string name;
    std::string filename;
    int color;
    int style;
};

int fInelasticLineWidth = 3;
int fElasticLineWidth = 1;

// Path to the xsec files
const std::string xsecFilesParentPath = ((std::string) getenv("G4ANADIR")) + "/datasets/";

const std::vector<XSecModel> xsecModels = {
    {"FTFP_BERT+BooNE", xsecFilesParentPath+"nubeam_xsecs.root", kRed+1, kSolid},
    {"FTFP_BERT", xsecFilesParentPath+"nubeam_xsecs_notBooNE.root", kAzure, kDashed}
};


std::vector<XSecPlot> xsecPlots = {
    {"InelasticCrossSections/ine_xsec_prt_be", "Ine p-Be", 2212, 0, "Be", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_prt_al", "Ine p-Al", 2212, 0,  "Al", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_prt_al", "Ine p-Al", 2212, 0,  "Al", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_neu_be", "Ine n-Be", 2112, 0,  "Be", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_neu_al", "Ine n-Al", 2112, 0,  "Al", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_pip_be", "Ine #pi^{+}-Be", 211, 0, "Be", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_pip_al", "Ine #pi^{+}-Al", 211, 0, "Al", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_pim_be", "Ine #pi^{-}-Be", -211, 0, "Be", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_pim_al", "Ine #pi^{-}-Al", -211, 0, "Al", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_kap_be", "Ine K^{+}-Be", 321, 0, "Be", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_kap_al", "Ine K^{+}-Al", 321, 0, "Al", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_kam_be", "Ine K^{-}-Be", -321, 0, "Be", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_kam_al", "Ine K^{-}-Al", -321, 0, "Al", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_k0l_be", "Ine K^{0}_{L}-Be", 130, 0, "Be", fInelasticLineWidth},
    {"InelasticCrossSections/ine_xsec_k0l_al", "Ine K^{0}_{L}-Al", 130, 0, "Al", fInelasticLineWidth},
    {"ElasticCrossSections/ela_xsec_prt_be", "El p-Be", 2212, 1, "Be", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_prt_al", "El p-Al", 2212, 1, "Al", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_neu_be", "El n-Be", 2112, 1, "Be", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_neu_al", "El n-Al", 2112, 1, "Al", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_pip_be", "El #pi^{+}-Be", 211, 1, "Be", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_pip_al", "El #pi^{+}-Al", 211, 1, "Al", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_pim_be", "El #pi^{-}-Be", -211, 1, "Be", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_pim_al", "El #pi^{-}-Al", -211, 1, "Al", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_kap_be", "El K^{+}-Be", 321, 1, "Be", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_kap_al", "El K^{+}-Al", 321, 1, "Al", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_kam_be", "El K^{-}-Be", -321, 1, "Be", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_kam_al", "El K^{-}-Al", -321, 1, "Al", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_k0l_be", "El K^{0}_{L}-Be", 130, 1, "Be", fElasticLineWidth},
    {"ElasticCrossSections/ela_xsec_k0l_al", "El K^{0}_{L}-Al", 130, 1, "Al", fElasticLineWidth}       
};



void PlotXSec(int pdg, std::string material, double maxP, int plotElastic, TLegend *legend = nullptr){

    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.15);


    TH1D *hFrame = new TH1D("hFrame", ";Momentum [GeV/c];#sigma [mb];", 100, 0, maxP);
    hFrame->SetStats(0);
    hFrame->Draw("hist E");
    hFrame->GetYaxis()->SetTitleOffset(1.2);
    double minY = 1e9;
    double maxY = -1e9;
    
    if (legend == nullptr) legend = new TLegend(0.5, 0.6, 0.9, 0.9);
    
    for (auto const& model : xsecModels){
        
        TFile *f = new TFile(model.filename.c_str());
        if (!f->IsOpen()){
            std::cout<<"Error opening file "<<model.filename<<std::endl;
            continue;
        }

        for (auto const& xsecPlot : xsecPlots){
            
            if (xsecPlot.pdg != pdg) continue;
            if (xsecPlot.material != material) continue;
            if (plotElastic != -1 && xsecPlot.isElastic != plotElastic) continue;

            std::cout<<"Plotting "<<xsecPlot.name<<" for "<<model.name<<std::endl;

            TH1D *h = (TH1D*)f->Get(xsecPlot.name.c_str());
            h->SetLineColor(model.color + xsecPlot.width);
            h->SetLineWidth(xsecPlot.width);
            h->SetLineStyle(model.style);
            h->Draw("l0 same");

            if (h->GetMinimum() < minY) minY = h->GetMinimum();
            if (h->GetMaximum() > maxY) maxY = h->GetMaximum();

            legend->AddEntry(h, Form("%s", (xsecPlot.label + " " + model.name).c_str()), "l");

        }
    }
    double width = maxY - minY;
    hFrame->GetYaxis()->SetRangeUser(std::max(minY - 0.1*width, 0.0), maxY + 0.1*width);
    legend->Draw();
}


void MacroPlotXSections(){
    std::cout<<"MacroPlotXSections"<<std::endl;
}

void PlotAllXSecs(double maxP=10.){

    // Plotting
    TCanvas *c1 = new TCanvas("c1", "c1", 100, 100, 1300, 1000);
    c1->Divide(2, 2);

    // Plot protons
    c1->cd(1);
    PlotXSec(2212, "Be", maxP, -1);

    c1->cd(2);
    PlotXSec(2112, "Be", maxP, -1);

    c1->cd(3);
    PlotXSec(211, "Be", maxP, -1);

    c1->cd(4);
    PlotXSec(-211, "Be", maxP, -1);

    // remove previous directory and create new one
    system("rm -rf _plots_xsec");
    system("mkdir _plots_xsec");
    c1->SaveAs("_plots_xsec/xsec_all.pdf");
    
}

void PlotNucleonQEXsections(double maxP=10., int nBins = 30){

    // Open pn QE file
    ifstream filePN(xsecFilesParentPath + "pnQEDataset.txt");
    if (!filePN.is_open()){
        std::cout<<"Error opening file pnQEDataset.txt"<<std::endl;
        return;
    }

    // Open pp QE file
    ifstream filePP( xsecFilesParentPath + "ppQEDataset.txt");
    if (!filePP.is_open()){
        std::cout<<"Error opening file ppQEDataset.txt"<<std::endl;
        return;
    }

    TH1D *hFrame = new TH1D("hFrame", ";Momentum [GeV/c];#sigma [mb];", nBins, 0, maxP);
    hFrame->SetStats(0);
    hFrame->Draw("hist E");
    hFrame->GetYaxis()->SetTitleOffset(1.2);
    double minY = 1e9;
    double maxY = -1e9;

    double energy, xsec;
    TH1D *hPNQE = new TH1D("hPNQE", ";Momentum [GeV/c];#sigma [mb];", nBins, 0, maxP);
    // Read pn file while not end of file
    while(!filePN.eof()){
        filePN >> energy >> xsec;
        hPNQE->SetBinContent(hPNQE->FindBin(energy), xsec);
        if (xsec < minY) minY = xsec;
        if (xsec > maxY) maxY = xsec;
    }

    TH1D *hPPQE = new TH1D("hPPQE", ";Momentum [GeV/c];#sigma [mb];", nBins, 0, maxP);
    // Read pp file while not end of file
    while(!filePP.eof()){
        filePP >> energy >> xsec;
        hPPQE->SetBinContent(hPPQE->FindBin(energy), xsec);
        if (xsec < minY) minY = xsec;
        if (xsec > maxY) maxY = xsec;
    }

    // Clone hPPQE to hBe
    TH1D *hBe = (TH1D*)hPPQE->Clone("hBe");
    // Scale hBe with Belletini factor
    double factor = 1.6 * std::pow(9, 1./3.);
    for (int i = 1; i <= hBe->GetNbinsX(); i++){
        double y = hBe->GetBinContent(i) * factor;
        hBe->SetBinContent(i, y);
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }


    hPNQE->SetMarkerStyle(20);
    hPNQE->SetMarkerColor(kRed);
    hPPQE->SetMarkerStyle(21);
    hPPQE->SetMarkerColor(kBlue);

    hBe->SetLineColor(kBlack);
    hBe->SetLineWidth(2);


    hPNQE->SetStats(0);
    hPPQE->SetStats(0);
    hFrame->GetYaxis()->SetRangeUser(minY - 0.1*(maxY - minY), maxY + 0.1*(maxY - minY));
    hFrame->Draw("");
    hPPQE->Draw("hist p same");
    hBe->Draw("hist l same");
    TLegend *legend = new TLegend(0.5, 0.6, 0.9, 0.9);
    legend->AddEntry(hPPQE, "pp El", "p");
    legend->AddEntry(hBe, "p-Be QE", "l");
    legend->Draw();

    return;
}


void PlotAllQEXSecs(double maxP=10.){

    // Plotting
    TCanvas *c1 = new TCanvas("c1", "c1", 100, 100, 1300, 1000);
    c1->Divide(2, 2);

    // Plot protons
    c1->cd(1);
    PlotNucleonQEXsections(maxP);


    return;

}

TH1D GetQEBelletini(double maxP=30, int nBins=20){

    // Open pp QE file
    ifstream filePP( xsecFilesParentPath + "ppQEDataset.txt");
    if (!filePP.is_open()){
        std::cout<<"Error opening file ppQEDataset.txt"<<std::endl;
    }

    TH1D hPPQE("hPPQE", ";Momentum [GeV/c];#sigma [mb];", nBins, 0, maxP);
    // Read pp file while not end of file
    double energy, xsec;
    while(!filePP.eof()){
        filePP >> energy >> xsec;
        hPPQE.SetBinContent(hPPQE.FindBin(energy), xsec);
    }

    // Scale hBe with Belletini factor
    double factor = 1.6 * std::pow(9, 1./3.);
    for (int i = 1; i <= hPPQE.GetNbinsX(); i++){
        double y = hPPQE.GetBinContent(i) * factor;
        hPPQE.SetBinContent(i, y);
    }


    return hPPQE;
}
