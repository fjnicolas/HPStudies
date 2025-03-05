
// Run as: 
// CompareXSections("xsec/hxsecA_prt", "MCXsec_Be_8GeV.root", "8 GeV", "MCXsec_Be_30GeV.root", "30 GeV")

void MacroCompareXSections(){
    std::cout<<"MacroCompareXSections"<<std::endl;
}

void CompareXSections(std::string xsecPlot, std::string filenameA, std::string labelA, std::string filenameB, std::string labelB){

    TFile *fA = new TFile(filenameA.c_str());
    TFile *fB = new TFile(filenameB.c_str());

    // Elastic case
    TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
    c1->Divide(2, 2);

    TH2D *hA = (TH2D*)fA->Get(xsecPlot.c_str());
    TH2D *hB = (TH2D*)fB->Get(xsecPlot.c_str());
    
    c1->cd(1);
    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.25);
    hA->SetStats(0);
    hA->Draw("colz");
    hA->SetTitle((labelA + " " + xsecPlot).c_str());
    hA->GetXaxis()->SetTitle("Momentum [GeV/c]");
    hA->GetYaxis()->SetTitle("Angle [mrad]");
    hA->GetZaxis()->SetTitle("#sigma [mbar]");

    c1->cd(2);

    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.25);
    hB->SetStats(0);
    hB->Draw("colz");
    hB->SetTitle((labelB + " " + xsecPlot).c_str());
    hB->GetXaxis()->SetTitle("Momentum [GeV/c]");
    hB->GetYaxis()->SetTitle("Angle [mrad]");
    hB->GetZaxis()->SetTitle("#sigma [mbar]");


    c1->cd(3);
    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.25);
    TH2D *hRatio = (TH2D*)hA->Clone("hRatio");
    hRatio->Add(hB, -1);
    hRatio->Divide(hB);
    hRatio->SetStats(0);
    hRatio->Draw("colz");
    hRatio->SetTitle("Ratio");
    hRatio->GetXaxis()->SetTitle("Momentum [GeV/c]");
    hRatio->GetYaxis()->SetTitle("Angle [mrad]");
    hRatio->GetZaxis()->SetTitle("#sigma_{A}-#sigma_{B}/#sigma_{B}");

    c1->cd(4);
    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.25);
    TH2D *hDiff = (TH2D*)hA->Clone("hDiff");
    hDiff->Add(hB, -1);
    hDiff->SetStats(0);
    hDiff->Draw("colz");
    hDiff->SetTitle("Difference");
    hDiff->GetXaxis()->SetTitle("Momentum [GeV/c]");
    hDiff->GetYaxis()->SetTitle("Angle [mrad]");
    hDiff->GetZaxis()->SetTitle("#Delta#sigma [mbar]");


    c1->Update();
    c1->WaitPrimitive();

}