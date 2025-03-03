
#include <iostream>
#include <fstream>
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include "hptuple.hh"

using namespace std;

//Compiling: g++ -o CreateMCXSec_QE CreateMCXSec_QE.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict

//constants:
// NA=6.022e23; // atoms/mol
// cm2_per_mb=1e-27
const double NAval = 6.022e-4;  // NAval = NA * cm2_per_mb
const double dx    = 0.7;       // cm target thickness
const double pival = 3.14159265; // approx

//Kinematics
const int Nmom = 14;
const double vmom[Nmom+1] = {0.75,1.00,1.25,1.50,1.75,2.00,2.25,2.50,2.75,3.00,3.25,4.00,5.00,6.50,8.00};

// Particle types
const int Npar =  4;
const char* part[Npar] = {"pip","pim","prt","neu"};

int getpartidx(int tpdg);

bool isQEEvent(HPTuple* hAinfo);

void CreateMCXSec();

void CreateMCXSec(const char* infiles, const char* out_histfile){

  //--- Output file
  TFile* foutput = new TFile(out_histfile,"RECREATE");

  //--- Histograms for multiplicity and cross section
  TH1D* hmult[Npar];
  TH1D* hxsec[Npar];
  TH1D* hmultQE[Npar];
  TH1D* hxsecQE[Npar];
  for(int i=0;i<Npar;i++){
    hmult[i] = new TH1D(Form("hmultA_%s",part[i]),"",Nmom,vmom);
    hxsec[i] = new TH1D(Form("hxsecA_%s",part[i]),"",Nmom,vmom);
    hmultQE[i] = new TH1D(Form("hmultQE_%s",part[i]),"",Nmom,vmom);
    hxsecQE[i] = new TH1D(Form("hxsecQE_%s",part[i]),"",Nmom,vmom);
  }
  
  //--- Input files
  TChain* evts  = new TChain("hAinfoTree");
  TChain* setup = new TChain("setup");
  HPTuple*  hAinfo  = new HPTuple;
  std::ifstream ifs;	
  ifs.open(infiles);
  std::string line;
  int counter = 0;
  while (ifs.good()) {
    getline(ifs,line);
    if(line.find(".root")>10000)continue;

    evts->Add(line.c_str());
    std::cout<<"Adding ntuple at : "<<line<<std::endl;

    setup->Add(line.c_str());
    counter++;
  }
  ifs.close();
  evts->SetBranchAddress("hAinfo",&hAinfo);
  std::cout<< (evts->GetNtrees()) <<" files were added to the chain"<<std::endl;

  // Target and POT setup
  double dens, A;
  int POT;
  double incidentE;
  setup->SetBranchAddress("energy",&incidentE); // GeV
  setup->SetBranchAddress("density",&dens); // g/cc
  setup->SetBranchAddress("A",&A); // g/mol
  setup->SetBranchAddress("nof_events",&POT); // POT

  setup->GetEntry(0);
  double dPOT = double(POT);
  dPOT *= double(counter); //adding all POT per file
  double sigma_factor = A/(dens * NAval * dx * dPOT); // mb  


  std::cout<<"=> POT: "<<dPOT<<std::endl;
  std::cout<<"=> A "<< A << std::endl;
  std::cout<<"=> incident energy "<< incidentE <<std::endl;
  std::cout<<"=> dens "<< dens <<std::endl;
  std::cout<<"=> sigma_factor "<< sigma_factor <<std::endl;

  //--- Loop and filling:
  int nentries  = (int)evts->GetEntries();
  std::cout<<"Entries "<<nentries<<std::endl;;

  for(long int jentry=0;jentry<nentries;jentry++){
     if(jentry%(nentries/10) == 0) std::cout << "." << std::flush;
     int nb = evts->GetEntry(jentry);  
    
    int npart = int(hAinfo->prodpart.size());

    bool isQE = isQEEvent(hAinfo);

    // looking for charged pions and nucleons:
    for(int ipart=0;ipart<npart;ipart++){
      
      // get particle type index
      int idx = getpartidx(hAinfo->prodpart[ipart].pdg);      
      if(idx<0)continue;
      
      // get kinematics
      double px = hAinfo->prodpart[ipart].mom[0] / 1000.; //MeV/c -> GeV/c
      double py = hAinfo->prodpart[ipart].mom[1] / 1000.;
      double pz = hAinfo->prodpart[ipart].mom[2] / 1000.;
      double pp = sqrt(pow(px,2)+ pow(py,2)+ pow(pz,2) );
      double aa = 1000.*acos(pz/pp); //mrad
      
      // fill histograms
      hmult[idx]->Fill(pp);
      hxsec[idx]->Fill(pp);

      if(isQE){
        hmultQE[idx]->Fill(pp);
        hxsecQE[idx]->Fill(pp);
      }
    } // end loop over particles
    
  } // end loop over entries
  
  // Scale multiplicity histograms
  for(int i=0;i<Npar;i++){
    hmult[i]->Scale(1./dPOT);
  }
  
  // Cross Sections:
  int Nmom = hxsec[0]->GetXaxis()->GetNbins();
  for(int i=1;i<=Nmom;i++){
    double pmin   = hxsec[0]->GetXaxis()->GetBinLowEdge(i);
    double pmax   = hxsec[0]->GetXaxis()->GetBinUpEdge(i);
    double deltap = pmax - pmin;

    // loop over particles
    for(int k=0;k<Npar;k++){
      
      // total cross section
      double xsecval = hxsec[k]->GetBinContent(i);
      xsecval *= (sigma_factor/ (deltap) );
      hxsec[k]->SetBinContent(i,xsecval);

      // QE cross section
      xsecval = hxsecQE[k]->GetBinContent(i);
      xsecval *= (sigma_factor/ (deltap) );
      hxsecQE[k]->SetBinContent(i,xsecval);

    } // end particle loop
    
    
  } // end loop on mom

  // Write output histograms
  foutput->mkdir("mult");
  foutput->mkdir("xsec");
  for(int i=0;i<Npar;i++){
    foutput->cd("mult");
    hmult[i]->Write();
    hmultQE[i]->Write();
    foutput->cd("xsec");
    hxsec[i]->Write();
    hxsecQE[i]->Write();
  }
  // Write incident energy variable
  foutput->cd();
  TH1D* hIncidentE = new TH1D("hIncidentE",";Incident Energy (GeV);",1, incidentE-0.1, incidentE+0.1);
  hIncidentE->Fill(incidentE);
  hIncidentE->Write();

  foutput->Close();
  std::cout<<"===>>>Running end"<<std::endl;;
}

/////////////////// Get particle index
int getpartidx(int tpdg){
  int tidx = -1;
  if(tpdg == 211)tidx=0;
  if(tpdg ==-211)tidx=1;
  if(tpdg ==2212)tidx=2;
  if(tpdg ==2112)tidx=3;
  return tidx;
}

/////////////////// Check QE event
bool isQEEvent(HPTuple* hAinfo){
  int npart = int(hAinfo->prodpart.size());
  int countLightMesons = 0;
  int countNucleons = 0;
  int countFragments = 0;
  for(int ipart=0;ipart<npart;ipart++){
    int pdg = hAinfo->prodpart[ipart].pdg;
    if(abs(pdg)==211 || pdg==111 || abs(pdg)==321 || pdg==130 || pdg==310) countLightMesons++;
    if(pdg==2212 || pdg==2112) countNucleons++;
    if(pdg>1000000000) countFragments++;
  }

  if(countLightMesons==0 && countNucleons==2 && countFragments<=1) return true;
  return false;
}

/////////////////// CreateMCXSec
void CreateMCXSec(){
  std::cout<<"./CreateMCXSec [infiles] [out_histfile]"<<std::endl;
  }

/////////////////// Main
# ifndef __CINT__
int main(int argc, const char* argv[]){
  if(argc==1){
    CreateMCXSec();
    exit (1);
  }  
  CreateMCXSec(argv[1],argv[2]);
  return 0;
}
# endif
