#include "MacroPlotXSections.C"

void MacroPlotXSecIncidentEnergy(){
    std::cout << "MacroPlotXSecIncidentEnergy" << std::endl;
}

//constants:
// NA=6.022e23; // atoms/mol
// cm2_per_mb=1e-27
const double NAval = 6.022e-4;  // NAval = NA * cm2_per_mb
const double dx    = 0.7;       // cm target thickness

void DrawVerticalLine(double x, double ymin, double ymax, int color = kBlack, int style = 2, int width = 2){
    TLine *line = new TLine(x, ymin, x, ymax);
    line->SetLineColor(color);
    line->SetLineStyle(style);
    line->SetLineWidth(width);
    line->Draw();
}

double fNucQELXSec(double* x, double* par){

   //call Regge in G4BNB 
    double pp = x[0]; //mom
    
    double aa = par[0];
    double bb = par[1];
    double cc = par[2];
    double dd = par[3];
    double nn = par[4];
    
    return aa + bb * pow(pp,nn) + cc * pow(log(pp),2) + dd * log(pp);
  }

void QEL(TLegend *leg){

  TF1* outf = new TF1("QelBe_paper",fNucQELXSec,0.145,10,5);

  outf->SetParameter(0, 164.8);
  outf->SetParameter(1, -40.09);
  outf->SetParameter(2,  21.40);
  outf->SetParameter(3, -61.45);
  outf->SetParameter(4,   0.408);

  outf->Draw("same");
  leg->AddEntry(outf,"QE MiniBooNE","l");
}


std::map<int, std::string> fIntType_Mode = {
    //{0, "Elastic-like"},
    {1, "QE-like"},
    {2, "Fragmentation"},
    //{3, "Dissociation"},
    {4, "Prod"}
    , {5, "Other"}
};

std::map<int, std::string> fIntType_Mult = {
    {0, "1p0m"}
    , {1, "2p0m"}
    , {2, ">2p0m"}
    , {3, "NpNm"}
    //, {4, "Other"}
};

//std::map<int, std::string> fIntType = fIntType_Mult; std::string fHistogramName = "hIntTypeMult";
std::map<int, std::string> fIntType = fIntType_Mode; std::string fHistogramName = "hIntType";


const int fNIntType = fIntType.size();

std::map<int, int> fIntTypeColor = {
    {0, kRed-3},
    {1, kAzure-5},
    {2, kGreen+3},
    {3, kOrange-3},
    {4, kViolet-3},
    {5, kCyan-3}
};

std::map<int, int> fIntTypeMarker = {
    {0, 20},
    {1, 21},
    {2, 22},
    {3, 23},
    {4, 20},
    {5, 25}
};

// function to sort vectors based on other vector
void sortVectors(std::vector<double> &v1, std::vector<double> &v2, std::vector<double> &v1_sorted, std::vector<double> &v2_sorted){

    std::vector<std::pair<double, double>> v;
    for (int i = 0; i < v1.size(); i++){
        v.push_back(std::make_pair(v1[i], v2[i]));
    }

    std::sort(v.begin(), v.end());

    v1_sorted.clear();
    v2_sorted.clear();
    for (int i = 0; i < v.size(); i++){
        v1_sorted.push_back(v[i].first);
        v2_sorted.push_back(v[i].second);
    }

    return;

}

void PlotXSectIncidentEnergy(std::string path, std::string label="", double keMax=10.0){

    // Get all ROOT files in the directory
    std::vector<std::string> files;
    for (const auto & entry : std::filesystem::directory_iterator(path)){
        if (entry.path().extension() == ".root"){
            std::cout << "File found: " << entry.path().string() << std::endl;
            files.push_back(entry.path().string());
        }
    }

    // vector to store incident energy
    std::vector<double> incidentP;

    // keMax to momentum
    double momentumMax = sqrt( pow(keMax + 0.938, 2) - 0.938*0.938);

    // vector for total inelastic cross section
    std::vector<double> xsec_total_inelastic;
    std::vector<double> xsec_total_inelastic_error;

    // vectors to store cross sections
    std::map<int, std::vector<double>> xsecByIntType;
    std::map<int, std::vector<double>> xsecByIntTypeError;

    // loop over map
    for(auto const& [key, val] : fIntType){
        xsecByIntType[key] = std::vector<double>();
        xsecByIntTypeError[key] = std::vector<double>();
    }

    for (auto file : files){
 
        // Open the file
        TFile *f = new TFile(file.c_str());
        std::cout << "\nFile opened " << file << std::endl;

        // Analysis general variables
        TVectorD *v = (TVectorD*)f->Get("POT");
        double POT = (*v)[0];
        // get now incident KE
        v = (TVectorD*)f->Get("incidentKE");
        double incidentKE = (*v)[0];
        v = (TVectorD*)f->Get("incidentE");
        double incidentE = (*v)[0];
        v = (TVectorD*)f->Get("incidentMom");
        double incidentMom = (*v)[0];
        v = (TVectorD*)f->Get("A");
        double A = (*v)[0];
        v = (TVectorD*)f->Get("density");
        double dens = (*v)[0];
        v = (TVectorD*)f->Get("sigma_factor");
        double sigma_factor = (*v)[0];
        double sigma_factor_local = A / ( NAval * dens * dx * POT);
        std::cout << "POT: " << POT << std::endl;
        std::cout << "incidentKE: " << incidentKE << std::endl;
        std::cout << "incidentE: " << incidentE << std::endl;
        std::cout << "incidentMom: " << incidentMom << std::endl;
        std::cout << "A: " << A << std::endl;
        std::cout << "dens: " << dens << std::endl;
        std::cout << "sigma_factor: " << sigma_factor << " " << sigma_factor_local << std::endl;

        if(incidentKE > keMax) continue;
        // Read the histograms number of entries
        TH1D *hIntType = (TH1D*)f->Get(fHistogramName.c_str());

        // Get the cross sections
        xsec_total_inelastic.push_back(0);
        incidentP.push_back(incidentMom);
        for (int i = 1; i <= hIntType->GetNbinsX(); i++){

            int intType = hIntType->GetBinCenter(i);
            
            if (fIntType.find(intType) == fIntType.end()){
                std::cout << "intType: " << intType << " not found in fIntType" << std::endl;
                continue;
            }
            
            int nEvents = hIntType->GetBinContent(i);
            double xsec = nEvents * sigma_factor;
            xsecByIntType[i-1].push_back(xsec);
            xsecByIntTypeError[i-1].push_back( sqrt( nEvents ) * sigma_factor);

            xsec_total_inelastic.back() += xsec;
            std::cout << " nEvents: " << nEvents << " xsec: " << xsec << " nEventsErr: " << sqrt(nEvents) << " xsecErr: " << sqrt(nEvents) * sigma_factor << std::endl;
        }
    }

    // Total cross section error
    for (int i = 0; i < xsec_total_inelastic.size(); i++){
        xsec_total_inelastic_error.push_back( 0 );
    }
    
    TCanvas *c = new TCanvas("c", "c", 600, 1000);
    c->cd();
    TPad *pad1 = new TPad("pad1", "pad1", 0., 0., 1., 0.5);
    TPad *pad2 = new TPad("pad2", "pad2", 0., 0.5, 1., 1.);
    pad1->Draw();
    pad2->Draw();

    // bottom margin
    pad1->cd();
    TLegend *legend = new TLegend(0.25, 0.65, 0.65, 0.9);
    gPad->SetBottomMargin(0.15);

    // Plot Geant4 cross sections
    PlotXSec(2212, "Be", momentumMax, 1, legend);
    // Plot QE MiniBooNE
    QEL(legend);
    // Plot Belletini
    TH1D hBelletini = GetQEBelletini(momentumMax, 20);
    hBelletini.SetLineColor(kBlack);
    hBelletini.SetLineWidth(2);
    hBelletini.Draw("hist l same");
    legend->AddEntry(&hBelletini, "QE Belletini", "l");
    

    // Create multi-graph for the cross sections
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle(";Momentum (GeV/c);#sigma (mb)");
    for (auto const& [i, val] : fIntType){

        TGraphErrors *g = new TGraphErrors(incidentP.size(), &incidentP[0], &xsecByIntType[i][0], 0, &xsecByIntTypeError[i][0]);
        g->SetMarkerStyle( fIntTypeMarker[i] );
        g->SetMarkerColor( fIntTypeColor[i] );
        mg->Add(g);
        legend->AddEntry(g, fIntType[i].c_str(), "p");
    }
    // Add total inelastic cross section
    TGraphErrors *gTotal = new TGraphErrors(incidentP.size(), &incidentP[0], &xsec_total_inelastic[0], 0, &xsec_total_inelastic_error[0]);
    gTotal->SetMarkerStyle( 30 );
    gTotal->SetMarkerColor( kBlack );
    mg->Add(gTotal);
    legend->AddEntry(gTotal, "Total inelastic", "p");

    mg->GetXaxis()->SetRangeUser(0, 10);
    mg->Draw("P");
    legend->Draw("same");

    // Get maximum y value of Y axis
    double maxY = mg->GetYaxis()->GetXmax();
    //DrawVerticalLine(8.89, 0, maxY, kRed, 2, 2);
   


    pad2->cd();
    gPad->SetBottomMargin(0.15);

    TMultiGraph *mgFrac = new TMultiGraph();
    TLegend *legendFrac = new TLegend(0.25, 0.65, 0.65, 0.9);
    // Get fraction of each cross section for each channel
    std::cout << "xsec_total_inelastic size: " << xsec_total_inelastic.size() << std::endl;
    for (auto const& [i, val] : fIntType){
        std::vector<double> frac;
        for (int j = 0; j < xsec_total_inelastic.size(); j++){
            frac.push_back(xsecByIntType[i][j] / xsec_total_inelastic[j]);
        }
        std::cout << "frac size: " << frac.size() << " incidentP size: " << incidentP.size() << std::endl;
        TGraph *gFrac = new TGraph(incidentP.size(), &incidentP[0], &frac[0]);
        gFrac->SetMarkerStyle( fIntTypeMarker[i] );
        gFrac->SetMarkerColor( fIntTypeColor[i] );
        mgFrac->Add(gFrac);
        legendFrac->AddEntry(gFrac, fIntType[i].c_str(), "p");
    }

    mgFrac->SetTitle(";Momentum (GeV/c);#sigma/#sigma_{tot}");
    mgFrac->Draw("AP");
    legendFrac->Draw("same");
    
    //DrawVerticalLine(8.89, 0, 1, kRed, 2, 2);
    mgFrac->GetYaxis()->SetRangeUser(0, 1);

    c->cd();
    c->Update();
    c->WaitPrimitive();

    // remove previous plots directory and create a new one
    std::string plotDir = "_plots_xsec_incident_energy/";
    gSystem->mkdir( ("rm -rf "+plotDir).c_str() );
    gSystem->mkdir( plotDir.c_str() );
    c->SaveAs( (plotDir+" XSecIncidentEnergy.pdf").c_str() );

    return;

}





/*// Sort vectors
    std::vector<double> incidentP_sorted;
    std::vector<double> xsec_elastic_sorted;
    std::vector<double> xsec_qe_sorted;
    std::vector<double> xsec_frag_sorted;
    std::vector<double> xsec_dis_sorted;
    std::vector<double> xsec_meson_sorted;
    std::vector<double> xsec_other_sorted;

    std::vector<double> xsec_total_sorted;
    std::vector<double> xsec_inelastic_sorted;

    sortVectors(incidentP, xsec_elastic, incidentP_sorted, xsec_elastic_sorted);
    sortVectors(incidentP, xsec_qe, incidentP_sorted, xsec_qe_sorted);
    sortVectors(incidentP, xsec_frag, incidentP_sorted, xsec_frag_sorted);
    sortVectors(incidentP, xsec_dis, incidentP_sorted, xsec_dis_sorted);
    sortVectors(incidentP, xsec_meson, incidentP_sorted, xsec_meson_sorted);
    sortVectors(incidentP, xsec_other, incidentP_sorted, xsec_other_sorted);

    sortVectors(incidentP, xsec_total, incidentP_sorted, xsec_total_sorted);
    sortVectors(incidentP, xsec_inelastic, incidentP_sorted, xsec_inelastic_sorted);*/