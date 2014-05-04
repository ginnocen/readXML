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

TString selection="Bzero_chi2_trkPt";

TString cutBp = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e-01";
TString cutB0 = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01";
TString cutBs = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01";


void tktkmass()
{

   TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140418_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_CandBase_skim.root");
   TFile* inputSB0 = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140418_Kstar_TriggerMatchingMuon_CandBase_skim.root");
   TFile* inputSBs = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140418_Phi_TriggerMatchingMuon_CandBase_skim.root");

   //TTree *dataBp = (TTree*)inputB->Get("ntKp"); 
   TTree *dataB0 = (TTree*)inputB->Get("ntKstar"); 
   TTree *dataBs = (TTree*)inputB->Get("ntphi"); 
   TTree *mcB0 = (TTree*)inputSB0->Get("ntKstar"); 
   TTree *mcBs = (TTree*)inputSBs->Get("ntphi"); 
   
   float BIN_MIN,BIN_MAX;

   if(selection=="Bzero_chi2_trkPt")
     {
       BIN_MIN=0.6;
       BIN_MAX=1.3;
     }
   if(selection=="Bs_chi2_trkPt")
     {
       BIN_MIN=1.0;
       BIN_MAX=1.05;
     }

   TH1D* hdataB = new TH1D("hdataB","",35,BIN_MIN,BIN_MAX);
   TH1D* hmcB = new TH1D("hmcB","",35,BIN_MIN,BIN_MAX);

   if(selection=="Bzero_chi2_trkPt")
     {
       dataB0->Project("hdataB","tktkmass",Form("%s&&mass>5.26&&mass<5.30",cutB0.Data()));
       mcB0->Project("hmcB","tktkmass","(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&(gen==22233||gen==41000)&&trk1Pt>0.7&&trk2Pt>0.7");
     }
   if(selection=="Bs_chi2_trkPt")
     {
       dataBs->Project("hdataB","tktkmass",Form("%s&&mass>5.35&&mass<5.39",cutBs.Data()));
       mcBs->Project("hmcB","tktkmass","(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&gen==22233&&trk1Pt>0.7&&trk2Pt>0.7");
     }

   hdataB->Sumw2();
   hdataB->Scale(1.0/hdataB->Integral());
   hmcB->Scale(1.0/hmcB->Integral());

   
   float maxy;
   TCanvas* cB = new TCanvas("cB","",200,10,600,600);
   if(hdataB->GetMaximum()>hmcB->GetMaximum()) maxy=hdataB->GetMaximum();
   else maxy = hmcB->GetMaximum();
   //hdataB->GetXaxis()->SetNdivisions(505,kTRUE);
   hdataB->GetXaxis()->SetTitle("tktkmass");
   hdataB->GetYaxis()->SetTitle("Entries");
   hdataB->SetMaximum(maxy*1.1);
   hdataB->Draw();
   //gStyle->SetHistLineStyle(1);
   //gStyle->SetHistLineColor(kBlue);
   //gStyle->SetHistLineWidth(3);
   //gStyle->SetHistFillStyle(1001);
   //gStyle->SetHistFillColor(kBlue-9);
   //hdataB->UseCurrentStyle();
   hmcB->Draw("same");
   gStyle->SetHistLineStyle(1);
   gStyle->SetHistLineColor(kRed);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistFillStyle(3354);
   gStyle->SetHistFillColor(kRed);
   hmcB->UseCurrentStyle();
   TLegend* leg1 = new TLegend(0.20,0.75,0.60,0.92);
   leg1->AddEntry(hdataB,"data","pl");
   leg1->AddEntry(hmcB,"MC","f");
   leg1->SetFillStyle(kWhite);
   leg1->SetLineColor(kWhite);
   leg1->Draw();
   TLegend* leg1p = new TLegend(0.75,0.85,0.90,0.92);
   if(selection=="Bplus_chi2_trkPt") leg1p->AddEntry("NULL","B^{+}","");
   if(selection=="Bzero_chi2_trkPt") leg1p->AddEntry("NULL","B^{0}","");
   if(selection=="Bs_chi2_trkPt") leg1p->AddEntry("NULL","Bs","");
   leg1p->SetFillStyle(kWhite);
   leg1p->SetLineColor(kWhite);
   leg1p->Draw();
   cB->SaveAs(Form("plot_%s/tktkmass.png",selection.Data())); 


}
