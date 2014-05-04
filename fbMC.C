
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
#include "TLegend.h"
//#include "Rtypes.h"

#define BIN_NUM 10

TString selection="Bs_chi2_trkPt";

//TString cutBp = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e-01";
//TString cutB0 = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01";
//TString cutBs = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02";

TString cutBpF = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e-01";
TString cutB0F = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01";
TString cutBsF = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02";

TString cutBpB = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y-0.465)<1.93&&(pt>10.)&&isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e-01";
TString cutB0B = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y-0.465)<1.93&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01";
TString cutBsB = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y-0.465)<1.93&&(pt>10.)&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02";

//TString cutBpF = "pt>10.&&abs(y+0.465)<1.93";
//TString cutB0F = "pt>10.&&abs(y+0.465)<1.93";
//TString cutBsF = "pt>10.&&abs(y+0.465)<1.93";

//TString cutBpB = "pt>10.&&abs(y-0.465)<1.93";
//TString cutB0B = "pt>10.&&abs(y-0.465)<1.93";
//TString cutBsB = "pt>10.&&abs(y-0.465)<1.93";

void fbMC()
{

  //TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140427_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_CandBase_skim.root");
   TFile* inputSbplusF = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kp_TriggerMatchingMuon_EvtBase_skim.root");
   TFile* inputSbzeroF = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kstar_TriggerMatchingMuon_EvtBase_skim.root");
   TFile* inputSbsF = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Phi_TriggerMatchingMuon_EvtBase_skim.root");

   TFile* inputSbplusB = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140501_Hijing_PPb502_MinimumBias_HIJINGemb_BuJpsiKp_5TeV_boostPbp.root");
   TFile* inputSbzeroB = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140501_Hijing_PPb502_MinimumBias_HIJINGemb_BdJpsiKstar_5TeV_boostPbp.root");
   TFile* inputSbsB = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140501_Hijing_PPb502_MinimumBias_HIJINGemb_BuJpsiKp_5TeV_boostPbp.root");

   TTree *recoBpF = (TTree*)inputSbplusF->Get("ntKp"); 
   TTree *recoB0F = (TTree*)inputSbzeroF->Get("ntKstar"); 
   TTree *recoBsF = (TTree*)inputSbsF->Get("ntphi"); 

   TTree *recoBpB = (TTree*)inputSbplusB->Get("ntKp"); 
   TTree *recoB0B = (TTree*)inputSbzeroB->Get("ntKstar"); 
   TTree *recoBsB = (TTree*)inputSbsB->Get("ntphi"); 
   
   TTree *genBpF = (TTree*)inputSbplusF->Get("ntGen"); 
   TTree *genBpB = (TTree*)inputSbplusB->Get("ntGen"); 
   TTree *genB0F = (TTree*)inputSbzeroF->Get("ntGen"); 
   TTree *genB0B = (TTree*)inputSbzeroB->Get("ntGen"); 
   TTree *genBsF = (TTree*)inputSbsF->Get("ntGen"); 
   TTree *genBsB = (TTree*)inputSbsB->Get("ntGen"); 

   const int nBins=4;
   //double ptBins[nBins+1]={10,15,20,25,30,60};
   //double ptBins[nBins+1]={10,15,20,60};
   //double ptBins[nBins+1]={10,60};
   double ptBins[nBins+1]={-1.93,-1.0,0,1.0,1.93};

   static int count=0;
   count++;
   float BIN_MIN=2.8,BIN_MAX=3.3;
   TH1D* hMCB = new TH1D("hMCB","",nBins,ptBins);
   TH1D* hGenB = new TH1D("hGenB","",nBins,ptBins);
   TH1D* hMCF = new TH1D("hMCF","",nBins,ptBins);
   TH1D* hGenF = new TH1D("hGenF","",nBins,ptBins);

   if(selection=="Bplus_chi2_trkPt")
     {
       recoBpF->Project("hMCF","y+0.465",cutBpF);
       genBpF->Project("hGenF","y+0.465","pt>10.&&abs(y+0.465)<1.93&&isSignal==1");
       recoBpB->Project("hMCB","-y+0.465",cutBpB);
       genBpB->Project("hGenB","-y+0.465","pt>10.&&abs(y-0.465)<1.93&&isSignal==1");
     }
   if(selection=="Bzero_chi2_trkPt")
     {
       recoB0F->Project("hMCF","y+0.465",cutB0F);
       genB0F->Project("hGenF","y+0.465","pt>10.&&abs(y+0.465)<1.93&&(isSignal==4||isSignal==5)");
       recoB0B->Project("hMCB","-y+0.465",cutB0B);
       genB0B->Project("hGenB","-y+0.465","pt>10.&&abs(y-0.465)<1.93&&(isSignal==4||isSignal==5)");
     }
   if(selection=="Bs_chi2_trkPt")
     {
       recoBsF->Project("hMCF","pt",cutBsF);
       genBsF->Project("hGenF","pt","pt>10.&&abs(y+0.465)<1.93&&isSignal==6");
       recoBsB->Project("hMCB","pt",cutBsB);
       genBsB->Project("hGenB","pt","pt>10.&&abs(y-0.465)<1.93&&isSignal==6");
     }

   hMCF->Sumw2();
   hGenF->Sumw2();
   hMCB->Sumw2();
   hGenB->Sumw2();
   
   hMCF->Divide(hGenF);
   hMCB->Divide(hGenB);
   hMCF->Divide(hMCB);

   hMCF->SetMinimum(0.4);
   hMCF->SetMaximum(2.);

   TCanvas* cB = new TCanvas("cB","",200,10,600,600);
   hMCF->GetXaxis()->SetTitle("p_{T}/ GeV/c");
   hMCF->GetYaxis()->SetTitle("Efficiency pPb/Pbp");
   hMCF->Draw();
   TLegend* leg1p = new TLegend(0.75,0.75,0.85,0.85);
   if(selection=="Bplus_chi2_trkPt") leg1p->AddEntry("NULL","B^{+}","");
   if(selection=="Bzero_chi2_trkPt") leg1p->AddEntry("NULL","B^{0}","");
   if(selection=="Bs_chi2_trkPt") leg1p->AddEntry("NULL","Bs","");
   leg1p->SetFillStyle(kWhite);
   leg1p->SetLineColor(kWhite);
   leg1p->Draw();
   cB->SaveAs(Form("plot_%s/FBeff_cut.png",selection.Data(),count)); 

}
