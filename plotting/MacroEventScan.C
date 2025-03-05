
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

void MacroEventScan(std::string filename="proton_8_Be_FTFP_BERT_1.root"){

    std::string treename = "hAinfoTree";
    // TChain
    TChain* evts  = new TChain("hAinfoTree");
    // Add input file to chain
    std::cout<<"Adding ntuple at : "<<filename<<std::endl;
    evts->Add(filename.c_str());
    int nEntries = evts->GetEntries();
    // Define variables and set branches
    HPTuple*  hAinfo  = new HPTuple;
    evts->SetBranchAddress("hAinfo",&hAinfo);
    
    // Loop
    for(long int jentry=0;jentry<nEntries;jentry++){
        std::cout<<"\n Entry "<<jentry<<std::endl;
        evts->GetEntry(jentry);
    
        std::cout<<"  - Number of particles: "<<hAinfo->prodpart.size()<<std::endl;
        std::cout<<"  - Total final energy: "<<GetTotalFinalEnergy(hAinfo)<<std::endl;
        std::cout<<"  - Particles in event -"<<std::endl;

        for (auto const& part : hAinfo->prodpart){
            std::cout<<"    PDG: "<<part.pdg<<std::endl;
            std::cout<<"    Mass: "<<GetInvariantMass(part)<<std::endl;
            std::cout<<"    E: "<<part.mom[3]<<std::endl;
            std::cout<<"    Vtx: "<<part.vtx[0]<<" "<<part.vtx[1]<<" "<<part.vtx[2]<<std::endl;
            std::cout<<"    Mom: "<<part.mom[0]<<" "<<part.mom[1]<<" "<<part.mom[2]<<std::endl;
            std::cout<<"    xf: "<<part.xf<<std::endl;
            std::cout<<"    pt: "<<part.pt<<std::endl;
            std::cout<<"    ff: "<<part.ff<<std::endl;
            std::cout<<std::endl;
        }

        bool continueLoop = true;
        std::cout<<"Continue? (0/1)"<<std::endl;
        std::cin>>continueLoop;
        if (!continueLoop) break;
        
    }

    return;

}