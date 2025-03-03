#include <iostream>
#include <fstream>
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TVectorD.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include "hptuple.hh"

//Compiling: g++ -o QElEvents QElEvents.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict

using namespace std;

//constants:
// NA=6.022e23; // atoms/mol
// cm2_per_mb=1e-27

const double NAval = 6.022e-4;  //NAval = NA * cm2_per_mb
const double dx    = 0.7;       //cm target thickness
const double pival = 3.14159265;//approx
const double protonMass = 0.938272; //GeV/c^2

// Particle is meson
inline Bool_t isMeson (const int &pdg){
  //mesons have 3 digits in the PDG code
  return abs(pdg)>=100 && abs(pdg)<1000;
}

// Particle is light meson
inline Bool_t isPiMeson (const int &pdg){
  return abs(pdg)==211 || abs(pdg)==111;
}

// Particle is strange meson
inline Bool_t isKMeson (const int &pdg){
  return abs(pdg)==321 || abs(pdg)==130 || abs(pdg)==310;
}


// Particle is nucleon
inline Bool_t isNucleon (const int &pdg){
  return pdg == 2212 || pdg == 2112;
}

//4 cases of QE for studies
const int Ntyp   = 6;
const char* ntyp[Ntyp] = {"ela_like","qel_like","frag_like","disnuc_like","meson_prod", "other"};

const int NtypMult   = 5;
const char* ntypMult[NtypMult] = {"1p0m", "2p0m", ">2p0m", "NpNm", "other"};

// Binning nucleon energies
const int Nbins = 1000;
const double minp = 0.;
const double maxp = 32.;

// Binning multiplicities
const int Nmult = 20;
const double minmult = 0.;
const double maxmult = 20.;



void QElEvents();

void QElEvents(const char* infiles, const char* out_histfile){
    
    // counters
    int nElaEvts  = 0; // 1 nucleon + 1 fragment + 0 mesons
    int nQElEvts  = 0; // 2 nucleons + <= 1 fragment + 0 mesons
    int nProdEvts = 0; // >0 mesons
    int nFragEvts = 0; // >0 nucleons + >1 fragments + 0 mesons
                        // or >2 nucleons + >0 frgaments + 0 mesons
    int nDisNucEvts = 0; // >0 nucleons + 0 fragments + 0 mesons

    int n1p0mEvts = 0; // 1 nucleon + 0 mesons
    int n2p0mEvts = 0; // 2 nucleons + 0 mesons
    int nNpNmEvts = 0; // >2 nucleons + 0 mesons
    int nOtherEvts = 0; // other

    TFile* foutput = new TFile(out_histfile,"RECREATE");

    // Based on interaction type
    // Momentum histograms for leading/other nucleons and mesons 
    TH1D* hlead_nuc[Ntyp];
    TH1D* hoth_nuc[Ntyp];
    TH1D* hlead_meson[Ntyp];
    TH1D* hoth_meson[Ntyp];
    // Multiplicity histograms
    TH1D* hnmult_nuc[Ntyp];
    TH1D* hnmult_meson[Ntyp];
    TH1D* hnmult_pimeson[Ntyp];
    TH1D* hnmult_kmeson[Ntyp];
    TH1D* hnmult_frag[Ntyp];
    for(int i=0;i<Ntyp;i++){
        hlead_nuc[i] = new TH1D(Form("hlead_nuc_%s",ntyp[i]),"",Nbins,minp,maxp);
        hoth_nuc[i]  = new TH1D(Form("hoth_nuc_%s" ,ntyp[i]),"",Nbins,minp,maxp);
        hlead_meson[i] = new TH1D(Form("hlead_meson_%s",ntyp[i]),"",Nbins,minp,maxp);
        hoth_meson[i]  = new TH1D(Form("hoth_meson_%s" ,ntyp[i]),"",Nbins,minp,maxp);

        hnmult_nuc[i] = new TH1D(Form("hnmult_nuc_%s",ntyp[i]),"",Nmult,minmult,maxmult);
        hnmult_meson[i] = new TH1D(Form("hnmult_meson_%s",ntyp[i]),"",Nmult,minmult,maxmult);
        hnmult_pimeson[i] = new TH1D(Form("hnmult_lmeson_%s",ntyp[i]),"",Nmult,minmult,maxmult);
        hnmult_kmeson[i] = new TH1D(Form("hnmult_hmeson_%s",ntyp[i]),"",Nmult,minmult,maxmult);
        hnmult_frag[i] = new TH1D(Form("hnmult_frag_%s",ntyp[i]),"",Nmult,minmult,maxmult);
    }

    // Based on multiplicity
    // Momentum histograms for leading/other nucleons and mesons
    TH1D* hlead_nuc_Np[Ntyp];
    TH1D* hoth_nuc_Np[Ntyp];
    TH1D* hlead_meson_Np[Ntyp];
    TH1D* hoth_meson_Np[Ntyp];
    for(int i=0;i<NtypMult;i++){
        hlead_nuc_Np[i] = new TH1D(Form("hlead_nuc_Np_%s",ntypMult[i]),"",Nbins,minp,maxp);
        hoth_nuc_Np[i]  = new TH1D(Form("hoth_nuc_Np_%s" ,ntypMult[i]),"",Nbins,minp,maxp);
        hlead_meson_Np[i] = new TH1D(Form("hlead_meson_Np_%s",ntypMult[i]),"",Nbins,minp,maxp);
        hoth_meson_Np[i]  = new TH1D(Form("hoth_meson_Np_%s" ,ntypMult[i]),"",Nbins,minp,maxp);
    }

    // Histogram to store interaction type
    TH1D* hIntType = new TH1D("hIntType",";Interaction Type;",Ntyp,0,Ntyp);

    // Histogram to store interaction type based on multiplicity
    TH1D* hIntTypeMult = new TH1D("hIntTypeMult",";Interaction Type;",NtypMult,0,NtypMult);

    TChain* evts  = new TChain("hAinfoTree");
    TChain* setup = new TChain("setup");
    HPTuple*  hAinfo  = new HPTuple;
    std::ifstream ifs;	
    ifs.open(infiles);
    std::string line;

    while (ifs.good()) {
        getline(ifs,line);
        if(line.find(".root")>10000) continue;
        std::cout<<"Adding ntuple at : "<<line<<std::endl;

        evts->Add(line.c_str());
        setup->Add(line.c_str());
    }
    ifs.close();  
    evts->SetBranchAddress("hAinfo",&hAinfo);
    //Setup:
    double dens, A;
    int POT;
    double totalPOT = 0.;
    double incidentKE;
    setup->SetBranchAddress("density",&dens); // g/cc
    setup->SetBranchAddress("A",&A); // g/mol
    setup->SetBranchAddress("nof_events",&POT); // POT
    setup->SetBranchAddress("energy",&incidentKE); // GeV
    setup->GetEntry(0);
    // loop to get total POT
    for(int i=0;i<setup->GetEntries();i++){
        setup->GetEntry(i);
        totalPOT += 1.*POT;
    }

    double sigma_factor = A/(dens * NAval * dx * totalPOT); // mb
    double incidentE = incidentKE + protonMass; //GeV
    double incidentMom = sqrt(incidentE*incidentE - protonMass*protonMass); //GeV/c
    std::cout<<"=> sigma_factor "<< sigma_factor <<std::endl;
    std::cout<<"=> dens "<< dens <<std::endl;
    std::cout<<"=> A "<< A << std::endl;
    std::cout<<"=> totalPOT "<< totalPOT << std::endl;
    std::cout<<"=> incidentE "<< incidentE <<std::endl;
    std::cout<<"=> incidentKE "<< incidentKE <<std::endl;
    std::cout<<"=> incidentMom "<< incidentMom <<std::endl;

    std::cout<< (evts->GetNtrees()) <<" files were added to the chain"<<std::endl;

    //Loop and filling:
    //vector of momenta per events
    std::vector<double> vnucmom;
    std::vector<double> vmesmom;

    int nentries  = (int)evts->GetEntries();
    std::cout<<"Entries "<<nentries<<std::endl;;
    for(long int jentry=0;jentry<nentries;jentry++){
        if(jentry%(nentries/10) == 0) std::cout << "." << std::flush;
        int nb = evts->GetEntry(jentry);  

        int npart = int(hAinfo->prodpart.size());
        int nMes  = 0; // no. of pions, kaons, etc in FS
        int nNuc  = 0; // no. of nucleons in FS
        int nProton = 0; // no. of protons in FS
        int nNeutron = 0; // no. of neutrons in FS
        int nPiMes = 0; // no. of pions in FS
        int nKMes  = 0; // no. of kaons in FS
        int nFrag = 0; // no. of fragments in FS

        
        bool isEla    = false; // flag: elastic
        bool isQEl    = false; // flag: quasi-elastic
        bool isProd   = false; // flag: production 
        bool isFrag   = false; // flag: fragments
        bool isDisNuc = false; // flag: nuclear dissociation in nucleons
        bool isOther  = false; // flag: other

        //looking for charged pions and nucleons:
        vnucmom.clear();
        vmesmom.clear();
        for(int ipart=0;ipart<npart;ipart++){
            int tpdg = hAinfo->prodpart[ipart].pdg;
            if      (isMeson (tpdg))    nMes++;
            else if (isNucleon (tpdg))  nNuc++;
            else if (tpdg > 1000000000) nFrag++;

            if(tpdg == 2212) nProton++;
            if(tpdg == 2112) nNeutron++;
            if(isPiMeson (tpdg)) nPiMes++;
            if(isKMeson  (tpdg)) nKMes++;
            

            if(isNucleon (tpdg)){
                double px = hAinfo->prodpart[ipart].mom[0] / 1000.; //MeV/c -> GeV/c
                double py = hAinfo->prodpart[ipart].mom[1] / 1000.;
                double pz = hAinfo->prodpart[ipart].mom[2] / 1000.;
                double pp = sqrt(pow(px,2)+ pow(py,2)+ pow(pz,2) );
                vnucmom.push_back(pp);
            }

            if(isMeson (tpdg)){
                double px = hAinfo->prodpart[ipart].mom[0] / 1000.; //MeV/c -> GeV/c
                double py = hAinfo->prodpart[ipart].mom[1] / 1000.;
                double pz = hAinfo->prodpart[ipart].mom[2] / 1000.;
                double pp = sqrt(pow(px,2)+ pow(py,2)+ pow(pz,2) );
                vmesmom.push_back(pp);
            }
        }

        // flag the event
        // meson production
        if (nMes > 0){ 
            nProdEvts++;
            isProd = true;
        }
        // elastic-like?
        else if(nFrag == 1 && nNuc == 1){ 
            nElaEvts++;
            isEla = true;
        }
        // quasi-elastic
        else if(nNuc == 2 && nFrag <= 1){ 
            // sometimes QEL-like events have a nuclear fragment, like C11 in the FS
            // sometimes not
            nQElEvts++;
            isQEl = true;
        }
        //fragment events
        else if((nFrag > 1 && nNuc > 0) || (nFrag > 0 && nNuc > 2)) {
            // events with multiple nuclear fragments in the FS
            // or events with more than 2 nucleons and one or more fragments
            nFragEvts++;
            isFrag = true;
        }
        //only nucleons in the event
        else if(nFrag == 0 && nNuc > 0) {
            //this events are like target dissosiation but in many nucleons
            //,i.e/, not nuclear fragments
            nDisNucEvts++;
            isDisNuc = true;
            if(nNuc<8) {
                std::cout<<" -- This should never happen - DisNuc"<<std::endl;
                evts->Show (jentry);
            }
        }   
        else{
            isOther = true;
            std::cout<<" -- This should never happen - Other"<<std::endl;
            evts->Show (jentry);
        }

        int ixMult = -1;
        if(nProton == 1 && nMes == 0){
            n1p0mEvts++;
            ixMult = 0;
        }
        else if(nProton ==2 && nMes == 0){
            n2p0mEvts++;
            ixMult = 1;
        }
        else if(nProton > 2 && nMes == 0){
            nNpNmEvts++;
            ixMult = 2;
        }
        else if(nMes != 0){
            nNpNmEvts++;
            ixMult = 3;
        }
        else{
            nOtherEvts++;
            ixMult = 4;
        }
    
        //Filling histograms
        int idx = -1;
        if(isEla)   idx = 0;
        if(isQEl)   idx = 1;
        if(isFrag)  idx = 2;
        if(isDisNuc)idx = 3;
        if(isProd)  idx = 4;
        if(isOther) idx = 5;
        hIntType->Fill(idx);
        hIntTypeMult->Fill(ixMult);
        
        // Nucleon momenta
        if(vnucmom.size()>0){
            // Sort the nucleon momenta
            sort(vnucmom.begin()   , vnucmom.end());
            reverse(vnucmom.begin(), vnucmom.end());

            hlead_nuc[idx]->Fill(vnucmom[0]);
            hlead_nuc_Np[ixMult]->Fill(vnucmom[0]);
            for(unsigned int i=1;i<vnucmom.size();i++){
                hoth_nuc[idx]->Fill(vnucmom[i]);
                hoth_nuc_Np[ixMult]->Fill(vnucmom[i]);
            }
        }

        // Meson momenta
        if(vmesmom.size()>0){
            // Sort the meson momenta
            sort(vmesmom.begin()   , vmesmom.end());
            reverse(vmesmom.begin(), vmesmom.end());

            hlead_meson[idx]->Fill(vmesmom[0]);
            hlead_meson_Np[ixMult]->Fill(vmesmom[0]);
            for(unsigned int i=1;i<vmesmom.size();i++){
                hoth_meson[idx]->Fill(vmesmom[i]);
                hoth_meson_Np[ixMult]->Fill(vmesmom[i]);
            }
        }

        //multiplicity histograms
        hnmult_nuc[idx]->Fill(nNuc);
        hnmult_meson[idx]->Fill(nMes);
        hnmult_pimeson[idx]->Fill(nPiMes);
        hnmult_kmeson[idx]->Fill(nKMes);
        hnmult_frag[idx]->Fill(nFrag);
        
    } // end loop over entries

    // open a txt tile to save some stats
    ofstream qeInfo ((string (foutput->GetName()) + ".QEinfo").c_str());
    qeInfo << "Processing " << evts->GetNtrees() << " trees in the chain\n\n";
    qeInfo << setw (15) << "#Nentries" << setw (15) << "el_like" << setw (15)
            << "qe_like" << setw (15) << "frag_like" << setw (15) << "dis-nuc_like" << setw (15)
            << "prod_entries\n";
    qeInfo << setw (15) << nentries << setw (15) << nElaEvts << setw (15)
            << nQElEvts << setw (15) << nFragEvts << setw (15) << nDisNucEvts << setw (15) 
            << nProdEvts << "\n\n";
            
    qeInfo.close();

    foutput->cd();
    for(int i=0;i<Ntyp;i++){
        hlead_nuc[i]->Write();
        hoth_nuc[i]->Write();
        hlead_meson[i]->Write();
        hoth_meson[i]->Write();
        hnmult_nuc[i]->Write();
        hnmult_meson[i]->Write();
        hnmult_pimeson[i]->Write();
        hnmult_kmeson[i]->Write();
        hnmult_frag[i]->Write();
    }

    for(int i=0;i<NtypMult;i++){
        hlead_nuc_Np[i]->Write();
        hoth_nuc_Np[i]->Write();
        hlead_meson_Np[i]->Write();
        hoth_meson_Np[i]->Write();
    }

    hIntType->Write();
    hIntTypeMult->Write();
    
    // Write simple variables
    TVectorD* vPOT = new TVectorD(1);
    (*vPOT)[0] = totalPOT;
    vPOT->Write("POT");
    TVectorD* vSigma = new TVectorD(1);
    (*vSigma)[0] = sigma_factor;
    vSigma->Write("sigma_factor");
    TVectorD* vDens = new TVectorD(1);
    (*vDens)[0] = dens;
    vDens->Write("density");
    TVectorD* vA = new TVectorD(1);
    (*vA)[0] = A;
    vA->Write("A");
    TVectorD* vIncidentE = new TVectorD(1);
    (*vIncidentE)[0] = incidentE;
    vIncidentE->Write("incidentE");
    TVectorD* vIncidentMom = new TVectorD(1);
    (*vIncidentMom)[0] = incidentMom;
    vIncidentMom->Write("incidentMom");
    TVectorD* vIncidentKE = new TVectorD(1);
    (*vIncidentKE)[0] = incidentKE;
    vIncidentKE->Write("incidentKE");

    foutput->Close();
    std::cout<<"===>>>Running end"<<std::endl;;
}

///////////////////
void QElEvents(){
  std::cout<<"./QElEvents [infiles] [out_histfile]"<<std::endl;
  }
///////////////////
# ifndef __CINT__
int main(int argc, const char* argv[]){
  if(argc==1){
    QElEvents();
    exit (1);
  }  
  QElEvents(argv[1],argv[2]);
  return 0;
}
# endif