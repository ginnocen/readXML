#include <cstdlib>
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
//#include "Rtypes.h"

void checkeff()
{
   TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140411_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_CandBase_skim.root");
   TFile* inputS = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140411_Kstar_TriggerMatchingMuon_CandBase_skim.root");

   TTree *signal = (TTree*)inputS->Get("ntKstar"); 
   TTree *background = (TTree*)inputB->Get("ntKstar"); 

   int i,j;   
   int nentriesS,nentriesB,nentriesG;
   double maxy;
   //TString basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.9&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
   //TString basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&trk1Pt>0.9&&gen==22233";
   TString basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbesttktkmass&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
   TString basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbesttktkmass&&gen==22233";
   TString basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&(isSignal==4||isSignal==5)";
   TString opt_cut = "chi2cl>5.4373726231815425e-02&&(d0/d0Err)>2.3783149037515692e+00&&cos(dtheta)>-1.9402273952924876e-02&&abs(tktkmass-0.89591)<1.2650602139810557e-01";

   TH1D* hmassS = new TH1D("hmassS","",50,3,7);
   TH1D* hmassScut = new TH1D("hmassScut","",50,3,7);
   TH1D* hmassB = new TH1D("hmassB","",50,3,7);
   TH1D* hmassBcut = new TH1D("hmassBcut","",50,5,6);

   background->Project("hmassB","mass",basic_cut_data.Data());
   signal->Project("hmassS","mass",basic_cut_mc.Data());
   background->Project("hmassBcut","mass",Form("%s&&%s",basic_cut_data.Data(),opt_cut.Data()));
   signal->Project("hmassScut","mass",Form("%s&&%s",basic_cut_mc.Data(),opt_cut.Data()));
   
   cout<<hmassScut->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut->GetEntries()*1.0/hmassB->GetEntries()<<endl;

   
   //plot
   /*
   hmassBcut->GetXaxis()->SetTitle("B mass");
   hmassBcut->GetYaxis()->SetTitle("Entries");
   TCanvas* cmassS = new TCanvas("cmassS","",200,10,600,600);
   hmassBcut->Draw();
   */

   //5.279 5.366
}
