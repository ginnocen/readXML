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


void candidates_Bzero()
{

   TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140427_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root");
   //TFile* inputS = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kstar_TriggerMatchingMuon_EvtBase_skim.root");
   TFile* inputS = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root");

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
       BIN_MAX=6;
       BIN_NUM=5;
     }
   if(selection=="Bzero_trkPt")
     {
       BIN_MIN=1;
       BIN_MAX=12;
       BIN_NUM=11;
     }
   if(selection=="Bs_trkPt")
     {
       BIN_MIN=0;
       BIN_MAX=5;
       BIN_NUM=5;
     }

   TH1D* hcandB = new TH1D("hcandB","",BIN_NUM,BIN_MIN,BIN_MAX);
   TH1D* hcandS = new TH1D("hcandS","",BIN_NUM,BIN_MIN,BIN_MAX);
   int nentriesB,nentriesS;

   float sumB=0,sumS=0;
   float numB=0,numS=0;
   int i;


   if(selection=="Bplus_trkPt") 
     {
       setbranch(dataBp);
       nentriesB = dataBp->GetEntries();
     }
   if(selection=="Bzero_trkPt") 
     {
       setbranch(dataB0);
       nentriesB = dataB0->GetEntries();
     }
   if(selection=="Bs_trkPt") 
     {
       setbranch(dataBs);
       nentriesB = dataBs->GetEntries();
     }

   //nentriesB = 1000000;
   for(i=0;i<nentriesB;i++)
     {
       if(i%1000000==0) cout<<i<<" / "<<nentriesB<<endl;
       if(selection=="Bplus_trkPt") dataBp->GetEntry(i);
       if(selection=="Bzero_trkPt") dataB0->GetEntry(i);
       if(selection=="Bs_trkPt") dataBs->GetEntry(i);
       int count=0;
       for(int j=0;j<size;j++)
	 {
	   if(selection=="Bplus_trkPt") 
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93))&&(pt[j]>10.)&&trk1Pt[j]>0.9&&chi2cl[j]>1.32e-02&&(d0[j]/d0Err[j])>3.41&&cos(dtheta[j])>-3.46e-01) count++;
	     }
	   if(selection=="Bzero_trkPt") 
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93))&&(pt[j]>10.)&&trk1Pt[j]>0.7&&trk2Pt[j]>0.7&&chi2cl[j]>1.65e-01&&(d0[j]/d0Err[j])>4.16&&cos(dtheta[j])>7.50e-01&&abs(tktkmass[j]-0.89594)<2.33e-01&&abs(mass[j]-5.279)<0.08) count++;
	     }
	   if(selection=="Bs_trkPt") 
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93))&&(pt[j]>10.)&&trk1Pt[j]>0.7&&trk2Pt[j]>0.7&&chi2cl[j]>3.71e-02&&(d0[j]/d0Err[j])>3.37&&cos(dtheta[j])>2.60e-01&&abs(tktkmass[j]-1.019455)<1.55e-02) count++;
	     }
	 }
       if(count)
	 {
	   sumB+=count;
	   numB++;
	   hcandB->Fill(count);
	 }
     }

   /////////////////////////////////////////////////////////////////////////

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

   for(i=0;i<nentriesS;i++)
     {
       if(i%1000000==0) cout<<i<<" / "<<nentriesS<<endl;
       if(selection=="Bplus_trkPt") mcBp->GetEntry(i);
       if(selection=="Bzero_trkPt") mcB0->GetEntry(i);
       if(selection=="Bs_trkPt") mcBs->GetEntry(i);
       int count=0;
       for(int j=0;j<size;j++)
	 {
	   if(selection=="Bplus_trkPt")
	     {	       
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&abs(y[j]+0.465)<1.93&&(pt[j]>10.)&&trk1Pt[j]>0.9&&chi2cl[j]>1.32e-02&&(d0[j]/d0Err[j])>3.41&&cos(dtheta[j])>-3.46e-01) count++;
	     }
	   if(selection=="Bzero_trkPt")
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&abs(y[j]+0.465)<1.93&&(pt[j]>10.)&&trk1Pt[j]>0.7&&trk2Pt[j]>0.7&&chi2cl[j]>1.65e-01&&(d0[j]/d0Err[j])>4.16&&cos(dtheta[j])>7.50e-01&&abs(tktkmass[j]-0.89594)<2.33e-01) count++;
	     }
	   if(selection=="Bs_trkPt") 
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&abs(y[j]+0.465)<1.93&&(pt[j]>10.)&&trk1Pt[j]>0.7&&trk2Pt[j]>0.7&&chi2cl[j]>3.71e-02&&(d0[j]/d0Err[j])>3.37&&cos(dtheta[j])>2.60e-01&&abs(tktkmass[j]-1.019455)<1.55e-02) count++;
	     }
	 }
       if(count)
	 {
	   sumS+=count;
	   numS++;
	   hcandS->Fill(count);
	 }
     }

   cout<<"mean number Data "<<(sumB/numB)<<"  mean number MC "<<(sumS/numS)<<endl;

   hcandB->Scale(1./hcandB->Integral());
   hcandS->Scale(1./hcandS->Integral());

   float maxy;

   TCanvas* cB = new TCanvas("cB","",200,10,600,600);
   hcandS->GetXaxis()->SetTitle("number of candidate");
   hcandS->GetYaxis()->SetTitle("events");
   hcandS->Draw();

   gStyle->SetHistLineStyle(1);
   gStyle->SetHistLineColor(kBlue);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistFillStyle(1001);
   gStyle->SetHistFillColor(kBlue-9);
   //gStyle->SetTitleYOffset(1.7);
   hcandS->UseCurrentStyle();

   hcandB->Draw("same");

   gStyle->SetHistLineStyle(1);
   gStyle->SetHistLineColor(kRed);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistFillStyle(3354);
   gStyle->SetHistFillColor(kRed);
   //gStyle->SetTitleYOffset(1.7);
   hcandB->UseCurrentStyle();

   TLegend* leg1 = new TLegend(0.55,0.75,0.90,0.85);
   leg1->AddEntry(hcandS,"MC","f");
   leg1->AddEntry(hcandB,"data","f");
   leg1->SetFillStyle(kWhite);
   leg1->SetLineColor(kWhite);
   leg1->Draw();

   TLegend* leg1p = new TLegend(0.55,0.85,0.80,0.92);
   if(selection=="Bplus_trkPt") leg1p->AddEntry("NULL","B^{+}","");
   if(selection=="Bzero_trkPt") leg1p->AddEntry("NULL","B^{0}","");
   if(selection=="Bs_trkPt") leg1p->AddEntry("NULL","Bs","");

   leg1p->SetFillStyle(kWhite);
   leg1p->SetLineColor(kWhite);
   leg1p->Draw();
   cB->SaveAs(Form("plot_%s/candidates_compare.png",selection.Data())); 

}
