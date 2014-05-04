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

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916

#define BIN_NUM 50
TString selection="Bs_chi2_trkPt";

void tkpt()
{

   TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140418_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_CandBase_skim.root");
   TFile* inputS = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140418_Phi_TriggerMatchingMuon_CandBase_skim.root");

   TTree *signal = (TTree*)inputS->Get("ntphi"); 
   TTree *background = (TTree*)inputB->Get("ntphi"); 

   int i,j;   
   TString basic_cut_data;
   TString basic_cut_mc;
   TString basic_cut_gen;
   TString opt_cut;
   TString opt_cut1;
   TString opt_cut2;
   TString opt_cut3;
   TString opt_cut4;
   TString opt_cut5;
   TString opt_cut6;
   float wSignal;
   float wBackground;
   

   if(selection=="Bplus_chi2_trkPt")
     {
       basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
       basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&(gen==22233)";
       basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&isSignal==1";
       opt_cut = "1.3283188406344560e-02&&(d0/d0Err)>3.4071262144478291e+00&&cos(dtheta)>-3.4655284177017442e-01";

       wSignal = 543.54;
       wBackground = 1774.49;
     }
   if(selection=="Bzero_chi2_trkPt")
     {
       basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
       basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&(gen==22233||gen==41000)";
       basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&(isSignal==4||isSignal==5)";
       opt_cut = "chi2cl>1.6536910598464905e-01&&(d0/d0Err)>4.1594866121765888e+00&&cos(dtheta)>7.5031353021307590e-01&&abs(tktkmass-0.89594)<2.3268807851886225e-01";

       wSignal = 228.097;
       wBackground = 3315.63;
     }
   if(selection=="Bs_chi2_trkPt")
     {
       basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&abs(mass-5.366)>0.2&&abs(mass-5.366)<0.3";
       basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&gen==22233";
       basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&isSignal==6";
       opt_cut = "chi2cl>3.7135302389090241e-02&&(d0/d0Err)>3.3736922985841797e+00&&cos(dtheta)>2.5997067060605700e-01&&abs(tktkmass-1.019455)<1.5508735352954923e-02";

       wSignal = 51.2328;
       wBackground = 716.288;
     }


   float BIN_MIN=0,BIN_MAX=150;
   TH1D* hmassS = new TH1D("hmassS","",50,BIN_MIN,BIN_MAX);
   TH1D* hmassB = new TH1D("hmassB","",50,BIN_MIN,BIN_MAX);

   TH1D* hmassScut_tkpt = new TH1D("hmassScut_tkpt","",50,BIN_MIN,BIN_MAX);
   TH1D* hmassBcut_tkpt = new TH1D("hmassBcut_tkpt","",50,BIN_MIN,BIN_MAX);


   float signalEff[BIN_NUM],backgroundEff[BIN_NUM],variable[BIN_NUM],sig[BIN_NUM];
   background->Project("hmassB","mass",basic_cut_data.Data());
   signal->Project("hmassS","mass",basic_cut_mc.Data());
   float MIN,STEP;

   //MIN=0.3;
   STEP=0.05;
   MIN=0.35;
   for(i=0;i<40;i++)
     {
       variable[i]=MIN+i*STEP;
       char CUT[5];
       sprintf(CUT,"%.3f",variable[i]);
       cout<<CUT<<"  ";
       //background->Project("hmassBcut_tkpt","mass",Form("%s&&%s&&trk1Pt>%s&&trk2Pt>%s",basic_cut_data.Data(),opt_cut.Data(),CUT,CUT));
       //signal->Project("hmassScut_tkpt","mass",Form("%s&&%s&&trk1Pt>%s&&trk2Pt>%s",basic_cut_mc.Data(),opt_cut.Data(),CUT,CUT));
       background->Project("hmassBcut_tkpt","mass",Form("%s&&trk1Pt>%s&&trk2Pt>%s",basic_cut_data.Data(),CUT,CUT));
       signal->Project("hmassScut_tkpt","mass",Form("%s&&trk1Pt>%s&&trk2Pt>%s",basic_cut_mc.Data(),CUT,CUT));
       signalEff[i]=hmassScut_tkpt->GetEntries()*1.0/hmassS->GetEntries();
       backgroundEff[i]=hmassBcut_tkpt->GetEntries()*1.0/hmassB->GetEntries();
       if(backgroundEff[i]==0)
	 {
	   cout<<"no background"<<endl;
	   break;
	 }
       sig[i]=(signalEff[i]*wSignal)/sqrt(backgroundEff[i]*wBackground+signalEff[i]*wSignal);
       cout<<hmassScut_tkpt->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut_tkpt->GetEntries()*1.0/hmassB->GetEntries()<<"  "<<sig[i]<<endl;
     }
   TGraph* gsignalEff_tkpt = new TGraph(i,variable,signalEff);
   TGraph* gbackgroundEff_tkpt = new TGraph(i,variable,backgroundEff);
   TGraph* gsig_tkpt = new TGraph(i,variable,sig);
   gsignalEff_tkpt->SetTitle("");
   gbackgroundEff_tkpt->SetTitle("");
   gsig_tkpt->SetTitle("");
   
   TCanvas* ceffS_tkpt = new TCanvas("ceffS_tkpt","",200,10,600,600);
   TLegend* leg1p = new TLegend(0.77,0.75,0.87,0.92);
   leg1p->AddEntry("NULL","Bs","");
   leg1p->SetFillStyle(kWhite);
   leg1p->SetLineColor(kWhite);
   gsignalEff_tkpt->GetYaxis()->SetTitle("Signal efficiency");
   gsignalEff_tkpt->GetXaxis()->SetTitle("track pT cut");
   gsignalEff_tkpt->Draw("A*");
   leg1p->Draw();
   ceffS_tkpt->SaveAs(Form("plot_%s/SignalEff_cut_noopt_tkpt.pdf",selection.Data()));
   TCanvas* ceffB_tkpt = new TCanvas("ceffB_tkpt","",200,10,600,600);
   gbackgroundEff_tkpt->GetYaxis()->SetTitle("Background efficiency");
   gbackgroundEff_tkpt->GetXaxis()->SetTitle("track pT cut");
   gbackgroundEff_tkpt->Draw("A*");
   leg1p->Draw();
   ceffB_tkpt->SaveAs(Form("plot_%s/BackgroundEff_cut_noopt_tkpt.pdf",selection.Data()));
   TCanvas* csig_tkpt = new TCanvas("csig_tkpt","",200,10,600,600);
   gsig_tkpt->GetYaxis()->SetTitle("s/sqrt(s+b)");
   gsig_tkpt->GetXaxis()->SetTitle("track pT cut");
   gsig_tkpt->Draw("A*");
   leg1p->Draw();
   csig_tkpt->SaveAs(Form("plot_%s/Significance_cut_noopt_tkpt.pdf",selection.Data()));

   cout<<"#########################################"<<endl;


   //plot
   /*
   hmassBcut->GetXaxis()->SetTitle("B mass");
   hmassBcut->GetYaxis()->SetTitle("Entries");
   TCanvas* cmassS = new TCanvas("cmassS","",200,10,600,600);
   hmassBcut->Draw();
   */

   //5.279 5.366
}
