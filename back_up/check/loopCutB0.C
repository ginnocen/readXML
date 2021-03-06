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

#define BIN_NUM 10
TString selection="Bzero_chi2_trkPt";

void loopCutB0()
{

  TFile* inputB = new TFile("/mnt/hadoop/cms/store/user/jwang/nt_20140418_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_CandBase_skim.root");
  TFile* inputS = new TFile("/mnt/hadoop/cms/store/user/jwang/nt_BoostedMC_20140418_Kstar_TriggerMatchingMuon_CandBase_skim.root");

  TTree *signal = (TTree*)inputS->Get("ntKstar"); 
  TTree *background = (TTree*)inputB->Get("ntKstar"); 

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
   

  if(selection=="Bzero_tktkmass")
    {
      basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>=10.)&&isbesttktkmass&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
      basic_cut_mc= "(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>=10.)&&isbesttktkmass&&(gen==22233||gen==41000)";
      basic_cut_gen= "abs(y+0.465)<1.93&&(pt>10.)&&(isSignal==4||isSignal==5)";
      opt_cut = "chi2cl>2.4940750750547171e-02&&(d0/d0Err)>6.2418209779282439e+00&&cos(dtheta)>6.2943965875754193e-01&&abs(trk1Dxy/trk1D0Err)>1.6349051914348824e+00&&abs(tktkmass-0.89594)<1.1766964837812614e-01";
      opt_cut1 = "(d0/d0Err)>6.2418209779282439e+00&&cos(dtheta)>6.2943965875754193e-01&&abs(trk1Dxy/trk1D0Err)>1.6349051914348824e+00&&abs(tktkmass-0.89594)<1.1766964837812614e-01";
      opt_cut2 = "chi2cl>2.4940750750547171e-02&&cos(dtheta)>6.2943965875754193e-01&&abs(trk1Dxy/trk1D0Err)>1.6349051914348824e+00&&abs(tktkmass-0.89594)<1.1766964837812614e-01";
      opt_cut3 = "chi2cl>2.4940750750547171e-02&&(d0/d0Err)>6.2418209779282439e+00&&abs(trk1Dxy/trk1D0Err)>1.6349051914348824e+00&&abs(tktkmass-0.89594)<1.1766964837812614e-01";
      opt_cut4 = "chi2cl>2.4940750750547171e-02&&(d0/d0Err)>6.2418209779282439e+00&&cos(dtheta)>6.2943965875754193e-01&&abs(tktkmass-0.89594)<1.1766964837812614e-01";
      opt_cut5 = "chi2cl>2.4940750750547171e-02&&(d0/d0Err)>6.2418209779282439e+00&&cos(dtheta)>6.2943965875754193e-01&&abs(trk1Dxy/trk1D0Err)>1.6349051914348824e+00&&abs(tktkmass-0.89594)<1.1766964837812614e-01";
      opt_cut6 = "chi2cl>2.4940750750547171e-02&&(d0/d0Err)>6.2418209779282439e+00&&cos(dtheta)>6.2943965875754193e-01&&abs(trk1Dxy/trk1D0Err)>1.6349051914348824e+00";


      wSignal = 312.861;
      wBackground = 5475.46;
    }


  if(selection=="Bzero_chi2")
    {
      basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3&&trk1Pt>0.7&&trk2Pt>0.7";
      basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&(gen==22233||gen==41000)&&trk1Pt>0.7&&trk2Pt>0.7";
      basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&(isSignal==4||isSignal==5)";
      opt_cut = "chi2cl>1.1427696176323097e-01&&(d0/d0Err)>3.5266531666863732e+00&&cos(dtheta)>6.4006237112916997e-01&&abs(tktkmass-0.89594)<2.3268807851886225e-01";


      wSignal = 267.863;
      wBackground = 2666.05;
    }

  if(selection=="Bzero_chi2_trkPt")
    {
      basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbestchi2&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3&&trk1Pt>0.7&&trk2Pt>0.7";
      basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbestchi2&&(gen==22233||gen==41000)&&trk1Pt>0.7&&trk2Pt>0.7";
      basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&(isSignal==4||isSignal==5)";
      opt_cut = "chi2cl>1.6536910598464905e-01&&(d0/d0Err)>4.1594866121765888e+00&&cos(dtheta)>7.5031353021307590e-01&&abs(tktkmass-0.89594)<2.3268807851886225e-01";
      opt_cut1 = "(d0/d0Err)>4.1594866121765888e+00&&cos(dtheta)>7.5031353021307590e-01&&abs(tktkmass-0.89594)<2.3268807851886225e-01";
      opt_cut2 = "chi2cl>1.6536910598464905e-01&&cos(dtheta)>7.5031353021307590e-01&&abs(tktkmass-0.89594)<2.3268807851886225e-01";
      opt_cut3 = "chi2cl>1.6536910598464905e-01&&(d0/d0Err)>4.1594866121765888e+00&&abs(tktkmass-0.89594)<2.3268807851886225e-01";
      opt_cut6 = "chi2cl>1.6536910598464905e-01&&(d0/d0Err)>4.1594866121765888e+00&&cos(dtheta)>7.5031353021307590e-01";
      wSignal = 228.097;
      wBackground = 3315.63;
    }

  float BIN_MIN=0,BIN_MAX=150;
  TH1D* hmassS = new TH1D("hmassS","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassB = new TH1D("hmassB","",50,BIN_MIN,BIN_MAX);

  TH1D* hmassScut_chi2 = new TH1D("hmassScut_chi2","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassBcut_chi2 = new TH1D("hmassBcut_chi2","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassScut_d0 = new TH1D("hmassScut_d0","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassBcut_d0 = new TH1D("hmassBcut_d0","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassScut_theta = new TH1D("hmassScut_theta","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassBcut_theta = new TH1D("hmassBcut_theta","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassScut_trk1 = new TH1D("hmassScut_trk1","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassBcut_trk1 = new TH1D("hmassBcut_trk1","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassScut_trk2 = new TH1D("hmassScut_trk2","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassBcut_trk2 = new TH1D("hmassBcut_trk2","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassScut_tktkmass = new TH1D("hmassScut_tktkmass","",50,BIN_MIN,BIN_MAX);
  TH1D* hmassBcut_tktkmass = new TH1D("hmassBcut_tktkmass","",50,BIN_MIN,BIN_MAX);

  float signalEff[BIN_NUM],backgroundEff[BIN_NUM],variable[BIN_NUM],sig[BIN_NUM];
  background->Project("hmassB","mass",basic_cut_data.Data());
  signal->Project("hmassS","mass",basic_cut_mc.Data());
  float MIN,STEP;

  MIN=0;
  STEP=0.05;
  for(i=0;i<10;i++)
    {
      variable[i]=MIN+i*STEP;
      char CUT[5];
      sprintf(CUT,"%.3f",variable[i]);
      cout<<CUT<<"  ";
      background->Project("hmassBcut_chi2","mass",Form("%s&&%s&&chi2cl>%s",basic_cut_data.Data(),opt_cut1.Data(),CUT));
      signal->Project("hmassScut_chi2","mass",Form("%s&&%s&&chi2cl>%s",basic_cut_mc.Data(),opt_cut1.Data(),CUT));
      signalEff[i]=hmassScut_chi2->GetEntries()*1.0/hmassS->GetEntries();
      backgroundEff[i]=hmassBcut_chi2->GetEntries()*1.0/hmassB->GetEntries();
      sig[i]=signalEff[i]*wSignal/sqrt(signalEff[i]*wSignal+backgroundEff[i]*wBackground);
      cout<<hmassScut_chi2->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut_chi2->GetEntries()*1.0/hmassB->GetEntries()<<"  "<<sig[i]<<endl;
    }
  TGraph* gsignalEff_chi2 = new TGraph(10,variable,signalEff);
  TGraph* gbackgroundEff_chi2 = new TGraph(10,variable,backgroundEff);
  TGraph* gsig_chi2 = new TGraph(10,variable,sig);
  gsignalEff_chi2->SetTitle("");
  gbackgroundEff_chi2->SetTitle("");
  gsig_chi2->SetTitle("");

  TCanvas* ceffS_chi2 = new TCanvas("ceffS_chi2","",200,10,600,600);
  gsignalEff_chi2->GetYaxis()->SetTitle("Signal efficiency");
  gsignalEff_chi2->GetXaxis()->SetTitle("chi2 cut");
  gsignalEff_chi2->Draw("A*");
  ceffS_chi2->SaveAs(Form("plot_%s/SignalEff_cut_chi2.pdf",selection.Data()));
  TCanvas* ceffB_chi2 = new TCanvas("ceffB_chi2","",200,10,600,600);
  gbackgroundEff_chi2->GetYaxis()->SetTitle("Background efficiency");
  gbackgroundEff_chi2->GetXaxis()->SetTitle("chi2 cut");
  gbackgroundEff_chi2->Draw("A*");
  ceffB_chi2->SaveAs(Form("plot_%s/BackgroundEff_cut_chi2.pdf",selection.Data()));
  TCanvas* csig_chi2 = new TCanvas("csig_chi2","",200,10,600,600);
  gsig_chi2->GetYaxis()->SetTitle("Significance");
  gsig_chi2->GetXaxis()->SetTitle("chi2 cut");
  gsig_chi2->Draw("A*");
  csig_chi2->SaveAs(Form("plot_%s/Significance_cut_chi2.pdf",selection.Data()));

  cout<<"#########################################"<<endl;

  MIN=0;
  STEP=1;
  for(i=0;i<10;i++)
    {
      variable[i]=MIN+i*STEP;
      char CUT[5];
      sprintf(CUT,"%.3f",variable[i]);
      cout<<CUT<<"  ";
      background->Project("hmassBcut_d0","mass",Form("%s&&%s&&(d0/d0Err)>%s",basic_cut_data.Data(),opt_cut2.Data(),CUT));
      signal->Project("hmassScut_d0","mass",Form("%s&&%s&&(d0/d0Err)>%s",basic_cut_mc.Data(),opt_cut2.Data(),CUT));
      signalEff[i]=hmassScut_d0->GetEntries()*1.0/hmassS->GetEntries();
      backgroundEff[i]=hmassBcut_d0->GetEntries()*1.0/hmassB->GetEntries();
      sig[i]=signalEff[i]*wSignal/sqrt(signalEff[i]*wSignal+backgroundEff[i]*wBackground);
      cout<<hmassScut_d0->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut_d0->GetEntries()*1.0/hmassB->GetEntries()<<"  "<<sig[i]<<endl;
    }

  TGraph* gsignalEff_d0 = new TGraph(10,variable,signalEff);
  TGraph* gbackgroundEff_d0 = new TGraph(10,variable,backgroundEff);
  TGraph* gsig_d0 = new TGraph(10,variable,sig);
  gsignalEff_d0->SetTitle("");
  gbackgroundEff_d0->SetTitle("");
  gsig_d0->SetTitle("");   

  TCanvas* ceffS_d0 = new TCanvas("ceffS_d0","",200,10,600,600);
  gsignalEff_d0->GetYaxis()->SetTitle("Signal efficiency");
  gsignalEff_d0->GetXaxis()->SetTitle("d0/d0Err cut");
  gsignalEff_d0->Draw("A*");
  ceffS_d0->SaveAs(Form("plot_%s/SignalEff_cut_d0.pdf",selection.Data()));
  TCanvas* ceffB_d0 = new TCanvas("ceffB_d0","",200,10,600,600);
  gbackgroundEff_d0->GetYaxis()->SetTitle("Background efficiency");
  gbackgroundEff_d0->GetXaxis()->SetTitle("d0/d0Err cut");
  gbackgroundEff_d0->Draw("A*");
  ceffB_d0->SaveAs(Form("plot_%s/BackgroundEff_cut_d0.pdf",selection.Data()));
  TCanvas* csig_d0 = new TCanvas("csig_d0","",200,10,600,600);
  gsig_d0->GetYaxis()->SetTitle("Significance");
  gsig_d0->GetXaxis()->SetTitle("d0/d0Err cut");
  gsig_d0->Draw("A*");
  csig_d0->SaveAs(Form("plot_%s/Significance_cut_d0.pdf",selection.Data()));


  cout<<"#########################################"<<endl;


  MIN=0;
  if(selection=="Bzero_chi2") MIN=-1;
  STEP=0.1;
  for(i=0;i<10;i++)
    {
      variable[i]=MIN+i*STEP;
      char CUT[5];
      sprintf(CUT,"%.3f",variable[i]);
      cout<<CUT<<"  ";
      background->Project("hmassBcut_theta","mass",Form("%s&&%s&&cos(dtheta)>%s",basic_cut_data.Data(),opt_cut3.Data(),CUT));
      signal->Project("hmassScut_theta","mass",Form("%s&&%s&&cos(dtheta)>%s",basic_cut_mc.Data(),opt_cut3.Data(),CUT));
      signalEff[i]=hmassScut_theta->GetEntries()*1.0/hmassS->GetEntries();
      backgroundEff[i]=hmassBcut_theta->GetEntries()*1.0/hmassB->GetEntries();
      sig[i]=signalEff[i]*wSignal/sqrt(signalEff[i]*wSignal+backgroundEff[i]*wBackground);
      cout<<hmassScut_theta->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut_theta->GetEntries()*1.0/hmassB->GetEntries()<<"  "<<sig[i]<<endl;
    }

  TGraph* gsignalEff_theta = new TGraph(10,variable,signalEff);
  TGraph* gbackgroundEff_theta = new TGraph(10,variable,backgroundEff);
  TGraph* gsig_theta = new TGraph(10,variable,sig);
  gsignalEff_theta->SetTitle("");
  gbackgroundEff_theta->SetTitle("");
  gsig_theta->SetTitle("");

  TCanvas* ceffS_theta = new TCanvas("ceffS_theta","",200,10,600,600);
  gsignalEff_theta->GetYaxis()->SetTitle("Signal efficiency");
  gsignalEff_theta->GetXaxis()->SetTitle("cos(dtheta) cut");
  gsignalEff_theta->Draw("A*");
  ceffS_theta->SaveAs(Form("plot_%s/SignalEff_cut_theta.pdf",selection.Data()));
  TCanvas* ceffB_theta = new TCanvas("ceffB_theta","",200,10,600,600);
  gbackgroundEff_theta->GetYaxis()->SetTitle("Background efficiency");
  gbackgroundEff_theta->GetXaxis()->SetTitle("cos(dtheta) cut");
  gbackgroundEff_theta->Draw("A*");
  ceffB_theta->SaveAs(Form("plot_%s/BackgroundEff_cut_theta.pdf",selection.Data()));
  TCanvas* csig_theta = new TCanvas("csig_theta","",200,10,600,600);
  gsig_theta->GetYaxis()->SetTitle("Significance");
  gsig_theta->GetXaxis()->SetTitle("cos(theta) cut");
  gsig_theta->Draw("A*");
  csig_theta->SaveAs(Form("plot_%s/Significance_cut_theta.pdf",selection.Data()));

  cout<<"#########################################"<<endl;

  /*
   MIN=0;
   STEP=0.3;
   for(i=0;i<10;i++)
     {
       variable[i]=MIN+i*STEP;
       char CUT[5];
       sprintf(CUT,"%.3f",variable[i]);
       cout<<CUT<<"  ";
       background->Project("hmassBcut_trk1","mass",Form("%s&&%s&&abs(trk1Dxy/trk1D0Err)>%s",basic_cut_data.Data(),opt_cut4.Data(),CUT));
       signal->Project("hmassScut_trk1","mass",Form("%s&&%s&&abs(trk1Dxy/trk1D0Err)>%s",basic_cut_mc.Data(),opt_cut4.Data(),CUT));
       signalEff[i]=hmassScut_trk1->GetEntries()*1.0/hmassS->GetEntries();
       backgroundEff[i]=hmassBcut_trk1->GetEntries()*1.0/hmassB->GetEntries();
       sig[i]=signalEff[i]*wSignal/sqrt(signalEff[i]*wSignal+backgroundEff[i]*wBackground);
       cout<<hmassScut_trk1->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut_trk1->GetEntries()*1.0/hmassB->GetEntries()<<"  "<<sig[i]<<endl;
     }
   TGraph* gsignalEff_trk1 = new TGraph(10,variable,signalEff);
   TGraph* gbackgroundEff_trk1 = new TGraph(10,variable,backgroundEff);
   TGraph* gsig_trk1 = new TGraph(10,variable,sig);
   gsignalEff_trk1->SetTitle("");
   gbackgroundEff_trk1->SetTitle("");
   gsig_trk1->SetTitle("");
   
   TCanvas* ceffS_trk1 = new TCanvas("ceffS_trk1","",200,10,600,600);
   gsignalEff_trk1->GetYaxis()->SetTitle("Signal efficiency");
   gsignalEff_trk1->GetXaxis()->SetTitle("track1 Dxy/DxyErr cut");
   gsignalEff_trk1->Draw("A*");
   ceffS_trk1->SaveAs(Form("plot_%s/SignalEff_cut_trk1.pdf",selection.Data()));
   TCanvas* ceffB_trk1 = new TCanvas("ceffB_trk1","",200,10,600,600);
   gbackgroundEff_trk1->GetYaxis()->SetTitle("Background efficiency");
   gbackgroundEff_trk1->GetXaxis()->SetTitle("track1 Dxy/DxyErr cut");
   gbackgroundEff_trk1->Draw("A*");
   ceffB_trk1->SaveAs(Form("plot_%s/BackgroundEff_cut_trk1.pdf",selection.Data()));
   TCanvas* csig_trk1 = new TCanvas("csig_trk1","",200,10,600,600);
   gsig_trk1->GetYaxis()->SetTitle("Significance");
   gsig_trk1->GetXaxis()->SetTitle("track1 Dxy/DxyErr cut");
   gsig_trk1->Draw("A*");
   csig_trk1->SaveAs(Form("plot_%s/Significance_cut_trk1.pdf",selection.Data()));
   cout<<"#########################################"<<endl;
   MIN=0;
   STEP=0.3;
   for(i=0;i<10;i++)
     {
       variable[i]=MIN+i*STEP;
       char CUT[5];
       sprintf(CUT,"%.3f",variable[i]);
       cout<<CUT<<"  ";
       background->Project("hmassBcut_trk2","mass",Form("%s&&%s&&abs(trk2Dxy/trk2D0Err)>%s",basic_cut_data.Data(),opt_cut5.Data(),CUT));
       signal->Project("hmassScut_trk2","mass",Form("%s&&%s&&abs(trk2Dxy/trk2D0Err)>%s",basic_cut_mc.Data(),opt_cut5.Data(),CUT));
       signalEff[i]=hmassScut_trk2->GetEntries()*1.0/hmassS->GetEntries();
       backgroundEff[i]=hmassBcut_trk2->GetEntries()*1.0/hmassB->GetEntries();
       sig[i]=signalEff[i]*wSignal/sqrt(signalEff[i]*wSignal+backgroundEff[i]*wBackground);
       cout<<hmassScut_trk2->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut_trk2->GetEntries()*1.0/hmassB->GetEntries()<<"  "<<sig[i]<<endl;
     }
   TGraph* gsignalEff_trk2 = new TGraph(10,variable,signalEff);
   TGraph* gbackgroundEff_trk2 = new TGraph(10,variable,backgroundEff);
   TGraph* gsig_trk2 = new TGraph(10,variable,sig);
   gsignalEff_trk2->SetTitle("");
   gbackgroundEff_trk2->SetTitle("");
   gsig_trk2->SetTitle("");   
   TCanvas* ceffS_trk2 = new TCanvas("ceffS_trk2","",200,10,600,600);
   gsignalEff_trk2->GetYaxis()->SetTitle("Signal efficiency");
   gsignalEff_trk2->GetXaxis()->SetTitle("track2 Dxy/DxyErr cut");
   gsignalEff_trk2->Draw("A*");
   ceffS_trk2->SaveAs(Form("plot_%s/SignalEff_cut_trk2.pdf",selection.Data()));
   TCanvas* ceffB_trk2 = new TCanvas("ceffB_trk2","",200,10,600,600);
   gbackgroundEff_trk2->GetYaxis()->SetTitle("Background efficiency");
   gbackgroundEff_trk2->GetXaxis()->SetTitle("track2 Dxy/DxyErr cut");
   gbackgroundEff_trk2->Draw("A*");
   ceffB_trk2->SaveAs(Form("plot_%s/BackgroundEff_cut_trk2.pdf",selection.Data()));
   TCanvas* csig_trk2 = new TCanvas("csig_trk2","",200,10,600,600);
   gsig_trk2->GetYaxis()->SetTitle("Significance");
   gsig_trk2->GetXaxis()->SetTitle("track2 Dxy/DxyErr cut");
   gsig_trk2->Draw("A*");
   csig_trk2->SaveAs(Form("plot_%s/Significance_cut_trk2.pdf",selection.Data()));
  */
  cout<<"#########################################"<<endl;

  MIN=0.01;
  STEP=0.05;
  for(i=0;i<10;i++)
    {
      variable[i]=MIN+i*STEP;
      char CUT[5];
      sprintf(CUT,"%.3f",variable[i]);
      cout<<CUT<<"  ";
      background->Project("hmassBcut_tktkmass","mass",Form("%s&&%s&&abs(tktkmass-0.89594)<%s",basic_cut_data.Data(),opt_cut6.Data(),CUT));
      signal->Project("hmassScut_tktkmass","mass",Form("%s&&%s&&abs(tktkmass-0.89594)<%s",basic_cut_mc.Data(),opt_cut6.Data(),CUT));
      signalEff[i]=hmassScut_tktkmass->GetEntries()*1.0/hmassS->GetEntries();
      backgroundEff[i]=hmassBcut_tktkmass->GetEntries()*1.0/hmassB->GetEntries();
      sig[i]=signalEff[i]*wSignal/sqrt(signalEff[i]*wSignal+backgroundEff[i]*wBackground);
      cout<<hmassScut_tktkmass->GetEntries()*1.0/hmassS->GetEntries()<<"  "<<hmassBcut_tktkmass->GetEntries()*1.0/hmassB->GetEntries()<<"  "<<sig[i]<<endl;
    }

  TGraph* gsignalEff_tktkmass = new TGraph(10,variable,signalEff);
  TGraph* gbackgroundEff_tktkmass = new TGraph(10,variable,backgroundEff);
  TGraph* gsig_tktkmass = new TGraph(10,variable,sig);
  gsignalEff_tktkmass->SetTitle("");
  gbackgroundEff_tktkmass->SetTitle("");
  gsig_tktkmass->SetTitle("");   

  TCanvas* ceffS_tktkmass = new TCanvas("ceffS_tktkmass","",200,10,600,600);
  gsignalEff_tktkmass->GetYaxis()->SetTitle("Signal efficiency");
  gsignalEff_tktkmass->GetXaxis()->SetTitle("abs(tktkmass-KSTAR_MASS) cut");
  gsignalEff_tktkmass->Draw("A*");
  ceffS_tktkmass->SaveAs(Form("plot_%s/SignalEff_cut_tktkmass.pdf",selection.Data()));
  TCanvas* ceffB_tktkmass = new TCanvas("ceffB_tktkmass","",200,10,600,600);
  gbackgroundEff_tktkmass->GetYaxis()->SetTitle("Background efficiency");
  gbackgroundEff_tktkmass->GetXaxis()->SetTitle("abs(tktkmass-KSTAR_MASS) cut");
  gbackgroundEff_tktkmass->Draw("A*");
  ceffB_tktkmass->SaveAs(Form("plot_%s/BackgroundEff_cut_tktkmass.pdf",selection.Data()));
  TCanvas* csig_tktkmass = new TCanvas("csig_tktkmass","",200,10,600,600);
  gsig_tktkmass->GetYaxis()->SetTitle("Significance");
  gsig_tktkmass->GetXaxis()->SetTitle("abs(tktkmass-KSTAR_MASS) cut");
  gsig_tktkmass->Draw("A*");
  csig_tktkmass->SaveAs(Form("plot_%s/Significance_cut_tktkmass.pdf",selection.Data()));


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
