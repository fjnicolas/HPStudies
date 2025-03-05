void MacroG4BNBGeo(){
    std::cout<<"MacroPlotTargetGeo"<<std::endl;
}

struct Binning{
    int nBinsZ;
    int nBinsXY;
    double minZ;
    double maxZ;
    double minXY;
    double maxXY;
};

void PlotTargetGeo(std::string filename, int maxEntries=0, bool debug=0, std::string treename="prihp"){

    TFile *f = new TFile(filename.c_str());
    TTree *tree = (TTree*)f->Get(treename.c_str());
    int nEntries = (maxEntries==0) ? tree->GetEntries() : maxEntries;

    tree->Print();
    Float_t vtx[3];
    std::string *mat = new std::string;
    int nmult;
    Int_t pdg[1000];
    Float_t mom[1000][3];
    tree->SetBranchAddress("vtx", vtx);
    tree->SetBranchAddress("mat", &mat);
    tree->SetBranchAddress("nmult", &nmult);
    tree->SetBranchAddress("pdg", &pdg);
    tree->SetBranchAddress("mom", &mom);


    // Material list
    std::unordered_set<std::string> materials;
    std::vector<std::string> materialList = {"All", "ALUMINIUM", "BERILLIUM", "AIRMATERIAL", "STEEL", "Concrete"};

    // Binning for materials
    std::map<std::string, Binning> binningMap{
        {"All",         {100, 600, -100, 10000, -200, 200}},
        {"ALUMINIUM",   {100, 600, -100, 10000, -200, 200}},
        {"BERILLIUM",   {100, 600, -100, 6000, -25, 25}},
        {"AIRMATERIAL", {100, 600, -100, 10000, -200, 200}},
        {"STEEL",       {100, 600, -100, 10000, -200, 200}},
        {"Concrete",    {100, 600, -100, 60000, -200, 200}}
    };

    // Histograms
    std::map<std::string, TH2F*> hZXMap;
    std::map<std::string, TH2F*> hXYMap;
    for(std::string material : materialList){
        Binning binning = binningMap[material];
        int nBinsZ = binning.nBinsZ;
        int nBinsXY = binning.nBinsXY;
        double minZ = binning.minZ;
        double maxZ = binning.maxZ;
        double minXY = binning.minXY;
        double maxXY = binning.maxXY;

        hZXMap[material] = new TH2F(("hZX"+material).c_str(),(material+";Z [mm]; X [mm]").c_str(), nBinsZ, minZ, maxZ, nBinsXY, minXY, maxXY);
        hXYMap[material] = new TH2F(("hXY"+material).c_str(),(material+"; X [mm]; Y [mm]").c_str(), nBinsXY, minXY, maxXY, nBinsXY, minXY, maxXY);

        // no stats
        hZXMap[material]->SetStats(0);
        hXYMap[material]->SetStats(0);
    }


    for (int i = 0; i < nEntries; i++){
        tree->GetEntry(i);

        // Fill histograms
        hZXMap["All"]->Fill(vtx[2], vtx[0]);
        hXYMap["All"]->Fill(vtx[0], vtx[1]);

        bool found = false;
        for (std::string material : materialList){
            if (*mat == material){
                hZXMap[material]->Fill(vtx[2], vtx[0]);
                hXYMap[material]->Fill(vtx[0], vtx[1]);
                found = true;
                break;
            }
        }


        materials.insert(*mat);

        if (debug){
            tree->Show(i);
            std::cout<<"Entry "<<i<<std::endl;
            std::cout<<"Vtx: "<<vtx[0]<<" "<<vtx[1]<<" "<<vtx[2]<<std::endl;
            std::cout<<"Material: "<<*mat<<std::endl;
            std::cout<<"Number of particles: "<<nmult<<std::endl;
            for (int j = 0; j < nmult; j++){
                std::cout<<"PDG: "<<pdg[j]<<std::endl;
                std::cout<<"Mom: "<<mom[j][0]<<" "<<mom[j][1]<<" "<<mom[j][2]<<std::endl;
            }
        }
    }

    std::cout<<"Materials: ";
    for (auto mat : materials){
        std::cout<<mat<<" ";
    }

    
    // Plot histograms
    // create plot directory
    std::string plotDir = "_plots_geo";
    std::string cmd = "mkdir -p "+plotDir;
    system(cmd.c_str());
    for (std::string material : materialList){
        TCanvas *c1 = new TCanvas(("c1"+material).c_str(), ("c1"+material).c_str(), 0, 0, 1200, 600);
        // 4 pads
        TPad *pad1 = new TPad("pad1", "pad1", 0., 0., 0.5, 1.);
        TPad *pad2 = new TPad("pad2", "pad2", 0.5, 0., 1., 1.);
       
        pad1->Draw();
        pad2->Draw();

        pad1->cd();
        hZXMap[material]->Draw("colz");

        pad2->cd();
        hXYMap[material]->Draw("colz");

        c1->cd();
        c1->Update();
        c1->SaveAs((plotDir+material+".pdf").c_str());

    }    



}