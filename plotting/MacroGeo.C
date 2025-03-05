
class ProdPart{

 public:
  Int_t pdg;
  Double_t vtx[3]; //Initial position of the track
  Double_t mom[4]; //4-momentum. P[maxPart][3] is the energy
  Double_t xf; 
  Double_t pt; 
  Bool_t ff;
  
};

class HPTuple{

 public:
    std::vector<ProdPart> prodpart;
  
};


double GetInvariantMass(ProdPart part1){
    if(part1.pdg == 22) return 0;
    else{
        double E2 = pow(part1.mom[3],2);
        double P2 = pow(part1.mom[0],2) + pow(part1.mom[1],2) + pow(part1.mom[2],2);
        double mass = sqrt(E2 - P2);
        return mass;
    }
}

double GetTotalFinalEnergy(HPTuple* hAinfo){
    double totalEnergy = 0;
    for (auto const& part : hAinfo->prodpart){
        totalEnergy += part.mom[3];
    }
    return totalEnergy;
}

void MacroGeo(){
    std::cout<<"MacroPlotTargetGeo"<<std::endl;
}

void PlotTargetGeo(std::string filename="proton_8_Be_FTFP_BERT_1.root", int maxEntries=0, bool debug=0, std::string treename="hAinfoTree"){

   
    // TChain
    TChain* evts  = new TChain("hAinfoTree");
    // Add input file to chain
    std::cout<<"Adding ntuple at : "<<filename<<std::endl;
    evts->Add(filename.c_str());
    int nEntries = (maxEntries==0) ? evts->GetEntries() : maxEntries;
    // Define variables and set branches
    HPTuple*  hAinfo  = new HPTuple;
    evts->SetBranchAddress("hAinfo",&hAinfo);

    int nBins = 100;
    double minZ = -4, maxZ = 4;
    double minX = -2e-2, maxX = 2e-2;
    double minY = -2e-2, maxY = 2e-2;

    TH2F *hZX = new TH2F("hZX","Z vs X; Z [mm]; X [mm]", nBins, minZ, maxZ, nBins, minX, maxX);
    TH2F *hXY = new TH2F("hXY","X vs Y; X [mm]; Y [mm]", nBins, minX, maxX, nBins, minY, maxY);
    TH1F *hNPart = new TH1F("hNPart",";# particles; # interactions", 40, 0, 40);
    
    // Loop
    for(long int jentry=0;jentry<nEntries;jentry++){
        std::cout<<"\n Entry "<<jentry<<std::endl;
        evts->GetEntry(jentry);

        for (auto const& part : hAinfo->prodpart){
            hZX->Fill(part.vtx[2], part.vtx[0]);
            hXY->Fill(part.vtx[0], part.vtx[1]);
        }
        hNPart->Fill(hAinfo->prodpart.size());

        
        
        if(debug || hAinfo->prodpart.size()<=3){
            std::cout<<"Number of particles: "<<hAinfo->prodpart.size()<<std::endl;
            std::cout<<"Total final energy: "<<GetTotalFinalEnergy(hAinfo)<<std::endl;
            for (auto const& part : hAinfo->prodpart){
                std::cout<<" - Particles in event -"<<std::endl;
                std::cout<<"  PDG: "<<part.pdg<<std::endl;
                std::cout<<"  Mass: "<<GetInvariantMass(part)<<std::endl;
                std::cout<<"  Vtx: "<<part.vtx[0]<<" "<<part.vtx[1]<<" "<<part.vtx[2]<<std::endl;
                std::cout<<"  Mom: "<<part.mom[0]<<" "<<part.mom[1]<<" "<<part.mom[2]<<" "<<part.mom[3]<<std::endl;
                std::cout<<"  xf: "<<part.xf<<std::endl;
                std::cout<<"  pt: "<<part.pt<<std::endl;
                std::cout<<"  ff: "<<part.ff<<std::endl;
            }
        }
    }

    TCanvas *c1 = new TCanvas("c1", "c1", 100, 100, 1300, 1000);
    // 4 pads
    TPad *pad1 = new TPad("pad1", "pad1", 0., 0., 0.5, 0.5);
    TPad *pad2 = new TPad("pad2", "pad2", 0.5, 0., 1., 0.5);
    TPad *pad3 = new TPad("pad3", "pad3", 0., 0.5, 0.5, 1.);
    TPad *pad4 = new TPad("pad4", "pad4", 0.5, 0.5, 1., 1.);

    pad1->Draw();
    pad2->Draw();
    pad3->Draw();
    pad4->Draw();

    pad1->cd();
    hZX->Draw("colz");

    pad2->cd();
    hXY->Draw("colz");

    pad3->cd();
    hNPart->Draw();
    // log
    gPad->SetLogy();

    c1->Update();
    c1->WaitPrimitive();

    





}