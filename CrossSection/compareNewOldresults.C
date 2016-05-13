#include "uti.h"

void compareNewOldresults(int option=2)
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

 // const int nHistos=4;
  const int nFiles=4;
  int colors[4]={1,1,2,2};
  TString namehisto;
  TString namegraph;
  TString title;
  double min=0;
  double max=0;
  bool isislogy=false;
  
  
  TString myfiles[nFiles];
  
  if(option==0){
  myfiles[0] ="ROOTfiles/outputRAA.root";
  myfiles[1] ="ROOTfiles/outputRAAMB.root";
  myfiles[2] ="/afs/cern.ch/user/g/ginnocen/public/ImportantFilesHIN16002/DntupleRunII_preapproval/CrossSection/ROOTfiles/outputRAA.root";
  myfiles[3] ="/afs/cern.ch/user/g/ginnocen/public/ImportantFilesHIN16002/DntupleRunII_preapproval/CrossSection/ROOTfiles/outputRAAMB.root";
  namehisto="hNuclearModification";
  namegraph="gNuclearModification";
  min=0;
  max=1.4;
  title="R_{AA}(0-100)";
  }
 if(option==1){
  myfiles[0] ="ROOTfilesCent10/outputRAA.root";
  myfiles[1] ="ROOTfilesCent10/outputRAAMB.root";
  myfiles[2] ="/afs/cern.ch/user/g/ginnocen/public/ImportantFilesHIN16002/DntupleRunII_preapproval/CrossSection/ROOTfilesCent10/outputRAA.root";
  myfiles[3] ="/afs/cern.ch/user/g/ginnocen/public/ImportantFilesHIN16002/DntupleRunII_preapproval/CrossSection/ROOTfilesCent10/outputRAAMB.root";
  namehisto="hNuclearModification";
  namegraph="gNuclearModification";
  min=0;
  max=1.4;
  title="R_{AA}(0-100)";
  }
 if(option==2){
  myfiles[0] ="ROOTfiles/CrossSectionFONLLPP.root";
  myfiles[1] ="ROOTfiles/CrossSectionFONLLPPMB.root";
  myfiles[2] ="/afs/cern.ch/user/g/ginnocen/public/ImportantFilesHIN16002/DntupleRunII_preapproval/CrossSection/ROOTfiles/CrossSectionFONLLPP.root";
  myfiles[3] ="/afs/cern.ch/user/g/ginnocen/public/ImportantFilesHIN16002/DntupleRunII_preapproval/CrossSection/ROOTfiles/CrossSectionFONLLPPMB.root";
  namehisto="hPtSigma";
  namegraph="gaeCrossSyst";
  min=10;
  max=1.e12;
  isislogy=true;
  title="d#sigma/d_{p_{T}}";
  }


  
  double minxhisto=0.;
  double maxxhisto=100.;
  
  TH1D* histogram[nFiles];
  TGraphAsymmErrors* graph[nFiles];
  TH2D* hempty;
  TFile* files[nFiles];
  TLegendEntry *entry[2];

  

  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    histogram[ifile] = (TH1D*)files[ifile]->Get(namehisto.Data());
    graph[ifile] = (TGraphAsymmErrors*)files[ifile]->Get(namegraph.Data());
  }
  TCanvas* canvas = new TCanvas("canvas","",600,600);
  gPad->SetLogx();
  if(isislogy) gPad->SetLogy();
  hempty=new TH2D("hempty","",100,0,100,50,min,max);
      hempty->SetLineWidth(3);
      hempty->GetYaxis()->CenterTitle();
      hempty->GetYaxis()->SetTitle(title.Data());
      hempty->GetXaxis()->SetRangeUser(-10,100);//1.
      hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      hempty->GetXaxis()->SetTitleOffset(0.95);//0.9
      hempty->GetYaxis()->SetTitleOffset(1.25);//1.
      hempty->GetXaxis()->SetTitleSize(0.060);//0.045
      hempty->GetYaxis()->SetTitleSize(0.060);//0.045
      hempty->GetXaxis()->SetTitleFont(42);
      hempty->GetYaxis()->SetTitleFont(42);
      hempty->GetXaxis()->SetLabelFont(42);
      hempty->GetYaxis()->SetLabelFont(42);  
      hempty->GetXaxis()->SetLabelSize(0.050);//0.035
      hempty->GetYaxis()->SetLabelSize(0.050);//0.035  

  TLegend *legendSigma=new TLegend(0.3104027,0.8058042,0.6392617,0.8634965,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);

  hempty  ->Draw();
    for (int ifile=0;ifile<nFiles;ifile++){
      histogram[ifile]  ->SetLineColor(colors[ifile]);
      histogram[ifile]   ->SetMarkerColor(colors[ifile]);
      histogram[ifile] ->Draw("psame");  
      graph[ifile]  ->SetLineColor(colors[ifile]);
      graph[ifile]   ->SetMarkerColor(colors[ifile]);
      graph[ifile] ->Draw("5same");  

  }
    entry[0]=legendSigma->AddEntry(histogram[0],"approval results","pf");
    entry[0]->SetTextFont(42);
    entry[0]->SetLineColor(1);
    entry[0]->SetTextColor(1);
    entry[0]->SetMarkerColor(1);
    entry[1]=legendSigma->AddEntry(histogram[2],"pre-approval results","pf");
    entry[1]->SetTextFont(42);
    entry[1]->SetLineColor(2);
    entry[1]->SetTextColor(2);
    entry[1]->SetMarkerColor(2);
    legendSigma->Draw();

  if(option==0) canvas->SaveAs("NewOldComparisonPbPb0100.pdf");
  if(option==1) canvas->SaveAs("NewOldComparisonPbPb010.pdf");
  if(option==2) canvas->SaveAs("NewOldComparisonCrossSection.pdf");

}