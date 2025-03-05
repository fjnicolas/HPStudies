
// Create differential cross sections as a function of 4 momentum transfer (t)
// Approximation t~p**2theta**2
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

// Histogram limits
const double tMin = 0.0;  // GeV^2
const double tMax = 0.15; // GeV^2
const int Nt = 30;

// Particle types
const int Ntypes = 4;
const char* part[Ntypes] = {"QElike", "prod", [2]="forw", [3]="prodContamination"};

int getpartidx(int tpdg);

bool isQEEvent(HPTuple* hAinfo);
bool isProduction(HPTuple* hAinfo);
bool isSingleChargedForwardEMPHATIC(HPTuple* hAinfo);

int getLeadingNucleonEntry(HPTuple* hAinfo);

void CreateMCXSec();

void CreateMCXSec(const char* infiles, const char* out_histfile, const double incidentP){

  //--- Output file
  TFile* foutput = new TFile(out_histfile,"RECREATE");

  //--- Histograms for multiplicity and cross section
  TH1D* hmult[Ntypes];
  TH1D* hxsec[Ntypes];
  for(int i=0;i<Ntypes;i++){
    hmult[i] = new TH1D(Form("hmultA_%s",part[i]),"", Nt, tMin, tMax);
    hxsec[i] = new TH1D(Form("hxsecA_%s",part[i]),"", Nt, tMin, tMax);
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

    // check if meson production
    bool isProd = isProduction(hAinfo);

    // get leading nucleon entry
    int leadNucEntry = getLeadingNucleonEntry(hAinfo);
    if(leadNucEntry<0)continue;

    // get the angle of the leading nucleon with respect to the beam (z-axis)
    double px = hAinfo->prodpart[leadNucEntry].mom[0] / 1000.; //MeV/c -> GeV/c
    double py = hAinfo->prodpart[leadNucEntry].mom[1] / 1000.;
    double pz = hAinfo->prodpart[leadNucEntry].mom[2] / 1000.;
    double pp = sqrt(pow(px,2)+ pow(py,2)+ pow(pz,2) );
    double aa = acos(pz/pp); // mrad

    // fill histograms

    // QE
    if(!isProd){
      hmult[0]->Fill( incidentP * incidentP * aa * aa );
      hxsec[0]->Fill( incidentP * incidentP * aa * aa );
    }

    if( isProd ){
      hmult[1]->Fill( incidentP * incidentP * aa * aa );
      hxsec[1]->Fill( incidentP * incidentP * aa * aa );

      if( isSingleChargedForwardEMPHATIC(hAinfo) ){
        hmult[3]->Fill( incidentP * incidentP * aa * aa );
        hxsec[3]->Fill( incidentP * incidentP * aa * aa );
      }
    }

    if( isSingleChargedForwardEMPHATIC(hAinfo) ){
      hmult[2]->Fill( incidentP * incidentP * aa * aa );
      hxsec[2]->Fill( incidentP * incidentP * aa * aa );
    }
    
    
  } // end loop over entries
  
  
  // Cross Sections:
  double delta_t = (tMax - tMin)/Nt;
  for(int i=1;i<=Nt;i++){

    // loop over the histograms
    for(int k=0;k<Ntypes;k++){
      
      // differential cross section
      double xsecval = hxsec[k]->GetBinContent(i);
      xsecval *= (sigma_factor/delta_t);
      hxsec[k]->SetBinContent(i,xsecval);
    
    } // end loop on histograms
    
  } // end loop on t

  // Write output histograms
  foutput->mkdir("mult");
  foutput->mkdir("xsec");
  for(int i=0;i<Ntypes;i++){
    foutput->cd("mult");
    hmult[i]->Write();
    foutput->cd("xsec");
    hxsec[i]->Write();
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
  int countMesons = 0;
  int countNucleons = 0;
  int countFragments = 0;
  for(int ipart=0;ipart<npart;ipart++){
    int pdg = hAinfo->prodpart[ipart].pdg;
    if(abs(pdg)==211 || pdg==111 || abs(pdg)==321 || pdg==130 || pdg==310) countMesons++;
    if(pdg==2212 || pdg==2112) countNucleons++;
    if(pdg>1000000000) countFragments++;
  }

  if(countMesons==0 && countNucleons==2 && countFragments<=1) return true;
  return false;
}

bool isProduction(HPTuple* hAinfo){
  int npart = int(hAinfo->prodpart.size());
  int countMesons = 0;
  int countNucleons = 0;
  int countFragments = 0;
  for(int ipart=0;ipart<npart;ipart++){
    int pdg = hAinfo->prodpart[ipart].pdg;
    if(abs(pdg)==211 || pdg==111 || abs(pdg)==321 || pdg==130 || pdg==310) countMesons++;
    if(pdg==2212 || pdg==2112) countNucleons++;
    if(pdg>1000000000) countFragments++;
  }

  return countMesons>0;
}

bool isSingleChargedForwardEMPHATIC(HPTuple* hAinfo){
  int npart = int(hAinfo->prodpart.size());
  int countCharged = 0;
  for(int ipart=0;ipart<npart;ipart++){
    int pdg = hAinfo->prodpart[ipart].pdg;
    if(abs(pdg)==211 || abs(pdg)==321 || abs(pdg)==2212){
      // get theta angle
      double px = hAinfo->prodpart[ipart].mom[0];
      double py = hAinfo->prodpart[ipart].mom[1];
      double pz = hAinfo->prodpart[ipart].mom[2];
      double pp = sqrt(px*px + py*py + pz*pz);
      double aa = acos(pz/pp)*1000;

      // EMPHATIC tolerance is 20 mrad
      if(aa<20) countCharged++;
    }
  }

  return countCharged==1;
}

int getLeadingNucleonEntry(HPTuple* hAinfo){

  double maxp = 0;
  int maxp_entry = -1;

  int npart = int(hAinfo->prodpart.size());

  for(int ipart=0;ipart<npart;ipart++){
    int pdg = hAinfo->prodpart[ipart].pdg;
    if(pdg==2212 || pdg==2112){
      double px = hAinfo->prodpart[ipart].mom[0];
      double py = hAinfo->prodpart[ipart].mom[1];
      double pz = hAinfo->prodpart[ipart].mom[2];
      double pp = sqrt(px*px + py*py + pz*pz);

      if(pp>maxp){
        maxp = pp;
        maxp_entry = ipart;
      }
    }
  }

  return maxp_entry;

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
  CreateMCXSec(argv[1], argv[2], atof(argv[3]));
  return 0;
}
# endif
