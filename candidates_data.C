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

TString selection="Bs_chi2_trkPt";

TString cutBp = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.9";
TString cutBstar = "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.7&&trk2Pt>0.7";
TString cutBs = "(HlT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.7&&trk2Pt>0.7";


void candidates_data()
{

   TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140418_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root");

   TTree *dataBp = (TTree*)inputB->Get("ntKp"); 
   TTree *dataB0 = (TTree*)inputB->Get("ntKstar"); 
   TTree *dataBs = (TTree*)inputB->Get("ntphi"); 
   
   int BIN_MIN,BIN_MAX,BIN_NUM;

   if(selection=="Bplus_chi2_trkPt")
     {
       BIN_MIN=0;
       BIN_MAX=18;
       BIN_NUM=18;
     }
   if(selection=="Bzero_chi2_trkPt")
     {
       BIN_MIN=0;
       BIN_MAX=60;
       BIN_NUM=60;
     }
   if(selection=="Bs_chi2_trkPt")
     {
       BIN_MIN=0;
       BIN_MAX=14;
       BIN_NUM=14;
     }

   TH1D* hcand = new TH1D("hcand","",BIN_NUM,BIN_MIN,BIN_MAX);
   int nentries;
   if(selection=="Bplus_chi2_trkPt") 
     {
       setbranch(dataBp);
       nentries = dataBp->GetEntries();
     }
   if(selection=="Bzero_chi2_trkPt") 
     {
       setbranch(dataB0);
       nentries = dataB0->GetEntries();
     }
   if(selection=="Bs_chi2_trkPt") 
     {
       setbranch(dataBs);
       nentries = dataBs->GetEntries();
     }
   //nentries = 1000000;

   float sum=0;
   float num=0;
   int i;
   for(i=0;i<nentries;i++)
     {
       if(i%1000000==0) cout<<i<<" / "<<nentries<<endl;
       if(selection=="Bplus_chi2_trkPt") dataBp->GetEntry(i);
       if(selection=="Bzero_chi2_trkPt") dataB0->GetEntry(i);
       if(selection=="Bs_chi2_trkPt") dataBs->GetEntry(i);
       int count=0;
       for(int j=0;j<size;j++)
	 {
	   if(selection=="Bplus_chi2_trkPt") 
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93))&&(pt[j]>10.)&&trk1Pt[j]>0.9) count++;
	     }
	   if(selection=="Bzero_chi2_trkPt") 
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93))&&(pt[j]>10.)&&trk1Pt[j]>0.7&&trk2Pt[j]>0.7) count++;
	     }
	   if(selection=="Bs_chi2_trkPt") 
	     {
	       if((HLT_PAMu3_v1)&&abs(mumumass[j]-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93))&&(pt[j]>10.)&&trk1Pt[j]>0.7&&trk2Pt[j]>0.7) count++;
	     }
	 }
       if(count)
	 {
	   sum+=count;
	   num++;
	   hcand->Fill(count);
	 }
     }

   cout<<"mean number  "<<(sum/num)<<endl;

   float maxy;
   TCanvas* cB = new TCanvas("cB","",200,10,600,600);
   hcand->GetXaxis()->SetTitle("number of candidate");
   hcand->GetYaxis()->SetTitle("events");
   hcand->Draw();

   gStyle->SetHistLineStyle(1);
   gStyle->SetHistLineColor(kRed+1);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistFillStyle(3354);
   gStyle->SetHistFillColor(kRed);
   gStyle->SetTitleYOffset(1.7);
   hcand->UseCurrentStyle();

   TLegend* leg1p = new TLegend(0.75,0.85,0.90,0.92);
   if(selection=="Bplus_chi2_trkPt") leg1p->AddEntry("NULL","B^{+}","");
   if(selection=="Bzero_chi2_trkPt") leg1p->AddEntry("NULL","B^{0}","");
   if(selection=="Bs_chi2_trkPt") leg1p->AddEntry("NULL","Bs","");

   leg1p->SetFillStyle(kWhite);
   leg1p->SetLineColor(kWhite);
   leg1p->Draw();
   cB->SaveAs(Form("plot_%s/candidates.png",selection.Data())); 


}
