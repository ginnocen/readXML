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
//#include "Rtypes.h"

#define BIN_NUM 10

void loopCut(float wSignal, float wBackground)
{

   TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140411_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_CandBase_skim.root");
   TFile* inputS = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140412_Kp_TriggerMatchingMuon_CandBase_skim.root");

   TTree *signal = (TTree*)inputS->Get("ntKp"); 
   TTree *background = (TTree*)inputB->Get("ntKp"); 

   int i,j;   
   int nentriesS,nentriesB,nentriesG;
   double maxy;
   TString basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.9&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
   TString basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&trk1Pt>0.9&&gen==22233";
   //TString basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbesttktkmass&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
   //TString basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbesttktkmass&&gen==22233";
   TString basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&(isSignal==1)";
   TString opt_cut = "chi2cl>6.81e-03&&(d0/d0Err)>3.30&&cos(dtheta)>-5.11e-01";
   TString opt_cut1 = "(d0/d0Err)>3.30&&cos(dtheta)>-5.11e-01";
   TString opt_cut2 = "chi2cl>6.81e-03&&cos(dtheta)>-5.11e-01";
   TString opt_cut3 = "chi2cl>6.81e-03&&(d0/d0Err)>3.30";

   float BIN_MIN=0,BIN_MAX=150;
   TH1D* hmassS = new TH1D("hmassS","",50,BIN_MIN,BIN_MAX);
   TH1D* hmassScut = new TH1D("hmassScut","",50,BIN_MIN,BIN_MAX);
   TH1D* hmassB = new TH1D("hmassB","",50,BIN_MIN,BIN_MAX);
   TH1D* hmassBcut = new TH1D("hmassBcut","",50,BIN_MIN,BIN_MAX);

   float signalEff[BIN_NUM],backgroundEff[BIN_NUM],variable[BIN_NUM],sig[BIN_NUM];
   background->Project("hmassB","mass",basic_cut_data.Data());
   signal->Project("hmassS","mass",basic_cut_mc.Data());
   float MIN=1,STEP=1;
   for(int i=0;i<10;i++)
     {
       variable[i]=MIN+i*STEP;
       char CUT[5];
       sprintf(CUT,"%.3f",variable[i]);
       cout<<CUT<<endl;
       //background->Project("hmassBcut","mass",Form("%s&&%s&&chi2cl>%s",basic_cut_data.Data(),opt_cut1.Data(),CUT));
       //signal->Project("hmassScut","mass",Form("%s&&%s&&chi2cl>%s",basic_cut_mc.Data(),opt_cut1.Data(),CUT));
       //background->Project("hmassBcut","mass",Form("%s&&%s&&(d0/d0Err)>%s",basic_cut_data.Data(),opt_cut2.Data(),CUT));
       //signal->Project("hmassScut","mass",Form("%s&&%s&&(d0/d0Err)>%s",basic_cut_mc.Data(),opt_cut2.Data(),CUT));
       //background->Project("hmassBcut","mass",Form("%s&&%s&&cos(dtheta)>%s",basic_cut_data.Data(),opt_cut3.Data(),CUT));
       //signal->Project("hmassScut","mass",Form("%s&&%s&&cos(dtheta)>%s",basic_cut_mc.Data(),opt_cut3.Data(),CUT));
       background->Project("hmassBcut","mass",Form("%s&&%s&&abs(trk1Dxy/trk1D0Err)>%s",basic_cut_data.Data(),opt_cut.Data(),CUT));
       signal->Project("hmassScut","mass",Form("%s&&%s&&abs(trk1Dxy/trk1D0Err)>%s",basic_cut_mc.Data(),opt_cut.Data(),CUT));
       signalEff[i]=hmassScut->GetEntries()*1.0/hmassS->GetEntries();
       backgroundEff[i]=hmassBcut->GetEntries()*1.0/hmassB->GetEntries();
       sig[i]=signalEff[i]*wSignal/sqrt(signalEff[i]*wSignal+backgroundEff[i]*wBackground);
       cout<<hmassScut->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut->GetEntries()*1.0/hmassB->GetEntries()<<"  "<<sig[i]<<endl;
     }

   TGraph* gsignalEff = new TGraph(10,variable,signalEff);
   TGraph* gbackgroundEff = new TGraph(10,variable,backgroundEff);
   TGraph* gsig = new TGraph(10,variable,sig);
   
   TCanvas* ceffS = new TCanvas("ceffS","",200,10,600,600);
   gsignalEff->GetYaxis()->SetTitle("Signal efficiency");
   gsignalEff->GetXaxis()->SetTitle("track Dxy/DxyErr cut");
   gsignalEff->Draw("A*");
   ceffS->SaveAs("plot_Bplus/SignalEff_cut_trk.gif");
   TCanvas* ceffB = new TCanvas("ceffB","",200,10,600,600);
   gbackgroundEff->GetYaxis()->SetTitle("Background efficiency");
   gbackgroundEff->GetXaxis()->SetTitle("track Dxy/DxyErr cut");
   gbackgroundEff->Draw("A*");
   ceffB->SaveAs("plot_Bplus/BackgroundEff_cut_trk.gif");
   TCanvas* csig = new TCanvas("csig","",200,10,600,600);
   gsig->GetYaxis()->SetTitle("Significance");
   gsig->GetXaxis()->SetTitle("track Dxy/DxyErr cut");
   gsig->Draw("A*");
   csig->SaveAs("plot_Bplus/Significance_cut_trk.gif");
   
   //plot
   /*
   hmassBcut->GetXaxis()->SetTitle("B mass");
   hmassBcut->GetYaxis()->SetTitle("Entries");
   TCanvas* cmassS = new TCanvas("cmassS","",200,10,600,600);
   hmassBcut->Draw();
   */

   //5.279 5.366
}
