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
#include "TStyle.h"
#include "TLegend.h"
//#include "Rtypes.h"
#include "candidates.h"

TString selection="Bzero_trkPt";

TString cutBp = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.9&&abs()";
TString cutBstar = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.7&&trk2Pt>0.7";
TString cutBs = "(HlT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.7&&trk2Pt>0.7";
TString cutMC = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&gen==22233";


void eff()
{

   TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140427_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root");
   TFile* inputS;
   if(selection=="Bplus_trkPt") inputS= new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kp_TriggerMatchingMuon_EvtBase_skim.root");
   if(selection=="Bzero_trkPt") inputS= new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kstar_TriggerMatchingMuon_EvtBase_skim.root");
   if(selection=="Bs_trkPt") inputS= new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Phi_TriggerMatchingMuon_EvtBase_skim.root");
   //TFile* inputS = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root");

   TTree *dataBp = (TTree*)inputB->Get("ntKp"); 
   TTree *dataB0 = (TTree*)inputB->Get("ntKstar"); 
   TTree *dataBs = (TTree*)inputB->Get("ntphi"); 

   TTree *mcBp = (TTree*)inputS->Get("ntKp"); 
   TTree *mcB0 = (TTree*)inputS->Get("ntKstar"); 
   TTree *mcBs = (TTree*)inputS->Get("ntphi"); 

   int BIN_MIN,BIN_MAX,BIN_NUM;

   if(selection=="Bplus_trkPt")
     {
       BIN_MIN=1;
       BIN_MAX=9;
       BIN_NUM=8;
     }
   if(selection=="Bzero_trkPt")
     {
       BIN_MIN=1;
       BIN_MAX=15;
       BIN_NUM=14;
     }
   if(selection=="Bs_trkPt")
     {
       BIN_MIN=1;
       BIN_MAX=9;
       BIN_NUM=8;
     }

   TH1D* hcandB = new TH1D("hcandB","",BIN_NUM,BIN_MIN,BIN_MAX);
   TH1D* hcandS = new TH1D("hcandS","",BIN_NUM,BIN_MIN,BIN_MAX);
   TH1D* heffS = new TH1D("heffS","",BIN_NUM,BIN_MIN,BIN_MAX);
   int nentriesB,nentriesS;

   float sumB=0,sumS=0;
   float numB=0,numS=0;
   int i;

   if(selection=="Bplus_trkPt") 
     {
       setbranch(mcBp);
       nentriesS = mcBp->GetEntries();
     }
   if(selection=="Bzero_trkPt") 
     {
       setbranch(mcB0);
       nentriesS = mcB0->GetEntries();
     }
   if(selection=="Bs_trkPt") 
     {
       setbranch(mcBs);
       nentriesS = mcBs->GetEntries();
     }
   //nentriesS = 1000000;

   cout<<nentriesS<<endl;

   for(i=0;i<nentriesS;i++)
     {
       if(i%1000000==0) cout<<i<<" / "<<nentriesS<<endl;
       if(selection=="Bplus_trkPt") mcBp->GetEntry(i);
       if(selection=="Bzero_trkPt") mcB0->GetEntry(i);
       if(selection=="Bs_trkPt") mcBs->GetEntry(i);
       int count=0;
       int matching=0;
       for(int j=0;j<size;j++)
	 {
	   if(selection=="Bplus_trkPt")
	     {	       
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&abs(y[j]+0.465)<1.93&&(pt[j]>10.)&&trk1Pt[j]>0.9&&chi2cl[j]>1.32e-02&&(d0[j]/d0Err[j])>3.41&&cos(dtheta[j])>-3.46e-01&&abs(mass[j]-5.279)<0.04) 
		 {
		   count++;
		   if(gen[j]==23333 && isbestchi2[j]) matching++;
		 }
	     }
	   if(selection=="Bzero_trkPt")
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&abs(y[j]+0.465)<1.93&&(pt[j]>10.)&&trk1Pt[j]>0.7&&trk2Pt[j]>0.7&&chi2cl[j]>1.65e-01&&(d0[j]/d0Err[j])>4.16&&cos(dtheta[j])>7.50e-01&&abs(tktkmass[j]-0.89594)<2.33e-01&&abs(mass[j]-5.279)<0.08)
		 {
		   count++;
		   if((gen[j]==23333||gen[j]==41000) && isbestchi2[j]) matching++;
		 }
	     }
	   if(selection=="Bs_trkPt") 
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&abs(y[j]+0.465)<1.93&&(pt[j]>10.)&&trk1Pt[j]>0.7&&trk2Pt[j]>0.7&&chi2cl[j]>3.71e-02&&(d0[j]/d0Err[j])>3.37&&cos(dtheta[j])>2.60e-01&&abs(tktkmass[j]-1.019455)<1.55e-02&&abs(mass[j]-5.366)<0.03)
		 {
		   count++;
		   if(gen[j]==23333 && isbestchi2[j]) matching++;
		 }
	     }
	 }
       if(count)
	 {
	   sumS+=count;
	   numS++;
	   hcandS->Fill(count);
	   if(matching) heffS->Fill(count);
	 }
     }
   
   for(int j=0;j<BIN_NUM;j++)
     {
       float total = hcandS->GetBinContent(j+1);
       float passing = heffS->GetBinContent(j+1);
       cout<<(j+1)<<"  "<<total<<"  "<<passing<<endl;
     }
   heffS->Divide(hcandS);
   
   TCanvas* cB = new TCanvas("cB","",200,10,600,600);
   heffS->GetXaxis()->SetTitle("number of candidate");
   heffS->GetYaxis()->SetTitle("Matching probability");
   heffS->Draw();

   gStyle->SetHistLineStyle(1);
   gStyle->SetHistLineColor(kBlue);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistFillStyle(3354);
   gStyle->SetHistFillColor(kBlue-9);
   heffS->UseCurrentStyle();


   TLegend* leg1p = new TLegend(0.55,0.85,0.80,0.92);
   if(selection=="Bplus_trkPt") leg1p->AddEntry("NULL","B^{+}","");
   if(selection=="Bzero_trkPt") leg1p->AddEntry("NULL","B^{0}","");
   if(selection=="Bs_trkPt") leg1p->AddEntry("NULL","Bs","");

   leg1p->SetFillStyle(kWhite);
   leg1p->SetLineColor(kWhite);
   leg1p->Draw();
   cB->SaveAs(Form("plot_%s/candidates_eff.png",selection.Data())); 

}
