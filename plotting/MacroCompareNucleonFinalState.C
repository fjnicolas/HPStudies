
// Run as: CompareNucleonFinalState("../G4/AnaQE/EnergyScan/output_e8..root", "QQSP_BERT", "../G4/AnaQE/EnergyScan/output_e8..root", "FTFP_BERT");

const double maxMomentum = 12.5;

void Plot2Histos(std::string histoname, std::string title, TFile* fileA, TFile *fileB, std::string labelA, std::string labelB){

        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.25);

        THStack *hs = new THStack("hs", histoname.c_str());
        TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9);

        TH1D *hA = (TH1D*)fileA->Get(histoname.c_str());    
        hA->SetLineColor(kRed+1);
        hA->SetLineWidth(2);
        hs->Add(hA);
        legend->AddEntry(hA, labelA.c_str(), "l");
        
        if(labelB != ""){
            TH1D *hB = (TH1D*)fileB->Get(histoname.c_str());
            hB->SetLineColor(kAzure+1);
            hB->SetLineWidth(2);
            hs->Add(hB);
            legend->AddEntry(hB, labelB.c_str(), "l");
        }

        hs->Draw("nostack");
        hs->SetTitle(title.c_str());
        hs->GetYaxis()->SetTitleOffset(1.5);
        hs->GetXaxis()->SetRangeUser(0, maxMomentum);
        legend->Draw("same");
}

void MacroCompareNucleonFinalState(){
    std::cout<<"MacroCompareNucleonFinalState"<<std::endl;
}

void CompareNucleonFinalState(std::string filenameA, std::string labelA, std::string filenameB="", std::string labelB=""){

    TFile *fA = new TFile(filenameA.c_str());
    TFile *fB = new TFile;
    if (filenameB != "") fB = new TFile(filenameB.c_str());

    // Elastic case
    TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
    c1->Divide(2, 1);
    c1->cd(1);
    Plot2Histos("hlead_nuc_ela_like", "Lead nucleon (elastic);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);
    c1->cd(2);
    Plot2Histos("hoth_nuc_ela_like", "Other nucleon (elastic);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);

    // QE case
    TCanvas *c2 = new TCanvas("c2", "c2", 1000, 500);
    c2->Divide(2, 1);
    c2->cd(1);
    Plot2Histos("hlead_nuc_qel_like", "Lead nucleon (QE);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);
    c2->cd(2);
    Plot2Histos("hoth_nuc_qel_like", "Other nucleon (QE);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);

    // Frag case
    TCanvas *c3 = new TCanvas("c3", "c3", 1000, 500);
    c3->Divide(2, 1);
    c3->cd(1);
    Plot2Histos("hlead_nuc_frag_like", "Lead nucleon (frag);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);
    c3->cd(2);
    Plot2Histos("hoth_nuc_frag_like", "Other nucleon (frag);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);

    // Dis case
    TCanvas *c4 = new TCanvas("c4", "c4", 1000, 500);
    c4->Divide(2, 2);
    c4->cd(1);
    Plot2Histos("hlead_nuc_disnuc_like", "Lead nucleon (dis);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);
    c4->cd(2);
    Plot2Histos("hoth_nuc_disnuc_like", "Other nucleon (dis);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);

    // For mesons
    TCanvas *c5 = new TCanvas("c5", "c5", 1000, 500);
    c5->Divide(2, 2);
    c5->cd(1);
    Plot2Histos("hlead_nuc_meson_prod", "Lead nucleon (prod);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);
    c5->cd(2);
    Plot2Histos("hoth_nuc_meson_prod", "Other nucleon (prod);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);    
    c5->cd(3);
    Plot2Histos("hlead_meson_meson_prod", "Lead meson (prod);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);
    c5->cd(4);
    Plot2Histos("hoth_meson_meson_prod", "Other meson (prod);Momentum [GeV/c];# entries", fA, fB, labelA, labelB);


    // remove previous plots directory and create a new one
    system("rm -rf _plots_finalstates");
    system("mkdir _plots_finalstates");
    
    c1->SaveAs("_plots_finalstates/momentum_elastic.pdf");
    c2->SaveAs("_plots_finalstates/momentum_qe.pdf");
    c3->SaveAs("_plots_finalstates/momentum_frag.pdf");
    c4->SaveAs("_plots_finalstates/momentum_dis.pdf");
    c5->SaveAs("_plots_finalstates/momentum_meson.pdf");


    // For particle multiplicities - Elastic case
    TCanvas *c1_M = new TCanvas("c1_M", "c1_ElasticLike", 1000, 500);
    c1_M->Divide(3, 2);
    c1_M->cd(1);
    Plot2Histos("hnmult_nuc_ela_like", ";# nucleons;# entries", fA, fB, labelA, labelB);
    c1_M->cd(2);
    Plot2Histos("hnmult_meson_ela_like", ";# mesons;# entries", fA, fB, labelA, labelB);
    c1_M->cd(3);
    Plot2Histos("hnmult_lmeson_ela_like", ";# pi mesons;# entries", fA, fB, labelA, labelB);
    c1_M->cd(4);
    Plot2Histos("hnmult_hmeson_ela_like", ";# K mesons;# entries", fA, fB, labelA, labelB);
    c1_M->cd(5);
    Plot2Histos("hnmult_frag_ela_like", ";# fragments;# entries", fA, fB, labelA, labelB);

    // For particle multiplicities - QE case
    TCanvas *c2_M = new TCanvas("c2_M", "c2_QELike", 1000, 500);
    c2_M->Divide(3, 2);
    c2_M->cd(1);
    Plot2Histos("hnmult_nuc_qel_like", ";# nucleons;# entries", fA, fB, labelA, labelB);
    c2_M->cd(2);
    Plot2Histos("hnmult_meson_qel_like", ";# mesons;# entries", fA, fB, labelA, labelB);
    c2_M->cd(3);
    Plot2Histos("hnmult_lmeson_qel_like", ";# pi mesons;# entries", fA, fB, labelA, labelB);
    c2_M->cd(4);
    Plot2Histos("hnmult_hmeson_qel_like", ";# K mesons;# entries", fA, fB, labelA, labelB);
    c2_M->cd(5);
    Plot2Histos("hnmult_frag_qel_like", ";# fragments;# entries", fA, fB, labelA, labelB);

    // For particle multiplicities - Frag case
    TCanvas *c3_M = new TCanvas("c3_M", "c3_Fragments", 1000, 500);
    c3_M->Divide(3, 2);
    c3_M->cd(1);
    Plot2Histos("hnmult_nuc_frag_like", ";# nucleons;# entries", fA, fB, labelA, labelB);
    c3_M->cd(2);
    Plot2Histos("hnmult_meson_frag_like", ";# mesons;# entries", fA, fB, labelA, labelB);
    c3_M->cd(3);
    Plot2Histos("hnmult_lmeson_frag_like", ";# pi mesons;# entries", fA, fB, labelA, labelB);
    c3_M->cd(4);
    Plot2Histos("hnmult_hmeson_frag_like", ";# K mesons;# entries", fA, fB, labelA, labelB);
    c3_M->cd(5);
    Plot2Histos("hnmult_frag_frag_like", ";# fragments;# entries", fA, fB, labelA, labelB);

    // For particle multiplicities - Dis case
    TCanvas *c4_M = new TCanvas("c4_M", "c4_Dissociation", 1000, 500);
    c4_M->Divide(3, 2);
    c4_M->cd(1);
    Plot2Histos("hnmult_nuc_disnuc_like", ";# nucleons;# entries", fA, fB, labelA, labelB);
    c4_M->cd(2);
    Plot2Histos("hnmult_meson_disnuc_like", ";# mesons;# entries", fA, fB, labelA, labelB);
    c4_M->cd(3);
    Plot2Histos("hnmult_lmeson_disnuc_like", ";# pi mesons;# entries", fA, fB, labelA, labelB);
    c4_M->cd(4);
    Plot2Histos("hnmult_hmeson_disnuc_like", ";# K mesons;# entries", fA, fB, labelA, labelB);
    c4_M->cd(5);
    Plot2Histos("hnmult_frag_disnuc_like", ";# fragments;# entries", fA, fB, labelA, labelB);

    // For particle multiplicities - meson case
    TCanvas *c5_M = new TCanvas("c5_M", "c5_Meson", 1000, 500);
    c5_M->Divide(3, 2);
    c5_M->cd(1);
    Plot2Histos("hnmult_nuc_meson_prod", ";# nucleons;# entries", fA, fB, labelA, labelB);
    c5_M->cd(2);
    Plot2Histos("hnmult_meson_meson_prod", ";# mesons;# entries", fA, fB, labelA, labelB);
    c5_M->cd(3);
    Plot2Histos("hnmult_lmeson_meson_prod", ";# pi mesons;# entries", fA, fB, labelA, labelB);
    c5_M->cd(4);
    Plot2Histos("hnmult_hmeson_meson_prod", ";# K mesons;# entries", fA, fB, labelA, labelB);
    c5_M->cd(5);
    Plot2Histos("hnmult_frag_meson_prod", ";# fragments;# entries", fA, fB, labelA, labelB);

    c1_M->SaveAs("_plots_finalstates/multiplicities_elastic.pdf");
    c2_M->SaveAs("_plots_finalstates/multiplicities_qe.pdf");
    c3_M->SaveAs("_plots_finalstates/multiplicities_frag.pdf");
    c4_M->SaveAs("_plots_finalstates/multiplicities_dis.pdf");
    c5_M->SaveAs("_plots_finalstates/multiplicities_meson.pdf");

    return;

}