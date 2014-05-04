#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include "TMath.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraph.h"
//#include "Rtypes.h"

#define BIN_NUM 10

TString selection="Bs_chi2_trkPt";

TString cutBp = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e-01";
TString cutB0 = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01";
TString cutBs = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02";

//TString cutBp = "1";
//TString cutB0 = "1";
//TString cutBs = "1";

void checkdimuon(TTree* nt, double ptmin, double ptmax, TString cutB)
{
   static int count=0;
   count++;
   float BIN_MIN=2.8,BIN_MAX=3.3;
   TH1D* hbmumuB = new TH1D("hbmumuB","",50,BIN_MIN,BIN_MAX);
   TH1D* hjpsiB = new TH1D("hjpsiB","",50,BIN_MIN,BIN_MAX);
   nt->Project("hbmumuB","mumumass",Form("%s&&((Run>=210498&&Run<=211256&&(y+0.465)>%f&&(y+0.465)<%f)||(Run>=211313&&Run<=211631&&(y-0.465)>%f&&(y-0.465)<%f))",cutB.Data(),ptmin,ptmax,ptmin,ptmax));
   nt->Project("hjpsiB","ujmass",Form("%s&&((Run>=210498&&Run<=211256&&(y+0.465)>%f&&(y+0.465)<%f)||(Run>=211313&&Run<=211631&&(y-0.465)>%f&&(y-0.465)<%f))",cutB.Data(),ptmin,ptmax,ptmin,ptmax));


   float maxy;
   TCanvas* cB = new TCanvas(Form("cB%d",count),"",200,10,600,600);
   if(hbmumuB->GetMaximum()>hjpsiB->GetMaximum()) maxy=hbmumuB->GetMaximum();
   else maxy = hjpsiB->GetMaximum();
   hbmumuB->GetXaxis()->SetTitle("#mu#mu mass");
   hbmumuB->GetYaxis()->SetTitle("Entries");
   hbmumuB->SetMaximum(maxy*1.1);
   hbmumuB->Draw();
   gStyle->SetHistLineStyle(1);
   gStyle->SetHistLineColor(kBlue);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistFillStyle(1001);
   gStyle->SetHistFillColor(kBlue-9);
   hbmumuB->UseCurrentStyle();
   hjpsiB->Draw("same");
   gStyle->SetHistLineStyle(1);
   gStyle->SetHistLineColor(kRed);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistFillStyle(3354);
   gStyle->SetHistFillColor(kRed);
   hjpsiB->UseCurrentStyle();
   TLegend* leg1 = new TLegend(0.20,0.75,0.60,0.92);
   leg1->AddEntry(hbmumuB,"#mu#mu invariant mass","f");
   leg1->AddEntry(hjpsiB,"J/#psi mass after fitting","f");
   leg1->SetFillStyle(kWhite);
   leg1->SetLineColor(kWhite);
   leg1->Draw();
   TLegend* leg1p = new TLegend(0.67,0.75,0.90,0.92);
   if(selection=="Bplus_chi2_trkPt") leg1p->AddEntry("NULL","B^{+}","");
   if(selection=="Bzero_chi2_trkPt") leg1p->AddEntry("NULL","B^{0}","");
   if(selection=="Bs_chi2_trkPt") leg1p->AddEntry("NULL","Bs","");
   leg1p->AddEntry("NULL",Form("%.2f<y_{CM}<%.2f",ptmin,ptmax),"");
   leg1p->SetFillStyle(kWhite);
   leg1p->SetLineColor(kWhite);
   leg1p->Draw();
   cB->SaveAs(Form("plot_%s/dimuony_%d.png",selection.Data(),count)); 

}


void muony()
{

   TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140418_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_CandBase_skim.root");

   TTree *treeBp = (TTree*)inputB->Get("ntKp"); 
   TTree *treeB0 = (TTree*)inputB->Get("ntKstar"); 
   TTree *treeBs = (TTree*)inputB->Get("ntphi"); 
   
   const int nBins=4;
   double ptBins[nBins+1]={-1.93,-1.0,0,1.0,1.93};
   for(int i=0;i<nBins;i++)
     {
       if(selection=="Bplus_chi2_trkPt") checkdimuon(treeBp,ptBins[i],ptBins[i+1],cutBp);
       if(selection=="Bzero_chi2_trkPt") checkdimuon(treeB0,ptBins[i],ptBins[i+1],cutB0);
       if(selection=="Bs_chi2_trkPt") checkdimuon(treeBs,ptBins[i],ptBins[i+1],cutBs);
     }
}
