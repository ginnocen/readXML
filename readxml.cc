#include <iostream>
#include <cstdlib>
#include "TH1F.h"
#include "TMath.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TXMLEngine.h"
#include "Tools.h"
#include "TGaxis.h"
#include "TLegend.h"
#include <map>
#include <string>
#include <cmath>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "Rtypes.h"
#include "TF1.h"
#include <fstream>

#define BIN_NUM 100
#define Nsigma 2

TString channel = "Dzero_PbPb";
Float_t ptmin = 4.5;
Float_t ptmax = 5.5;//100.;

void calRatio(float* results)
{

  TFile* inputB;
  TFile* inputS;
  TTree *signal;
  TTree *background;
  TTree *generated;

  if(channel=="Dzero_pp")
    {
      inputB = new TFile("/afs/cern.ch/work/j/jisun/public/Dmesonana/Dmesonana_PPJet_Jettrig_obj_pt0p5_d0dstar_alpha1p0_highpurity_1209_all_v1.root");
      inputS = new TFile("/afs/cern.ch/work/j/jisun/public/Dmesonana/Dmesonana_hiforest_D0filtered_2760GeV_D0pt3_pthat015305080120_1220_1222_all_v1.root");
      signal = (TTree*)inputS->Get("recodmesontree");
      background = (TTree*)inputB->Get("recodmesontree");
      generated = (TTree*)inputS->Get("gendmesontree");
    }

  if(channel=="Dzero_PbPb")
    {
      inputB = new TFile("smalldata.root");//"/data/dmeson/Ntuple/Dmesonana_Rereco_MBtrig_d0pt4p5_nodalphacuts_pt1p5_tight_3lumi_0131_part1_fortmva.root");
      inputS = new TFile("/data/dmeson/Ntuple/Dmesonana_hiforest_PbPb_Pyquen_D0embedded_D0pt3_pthat015305080_1217_1223_all_v1.root");
      signal = (TTree*)inputS->Get("recodmesontree");
      background = (TTree*)inputB->Get("recodmesontree");
      generated = (TTree*)inputS->Get("gendmesontree");
    }

  int i,j;
  int nentriesS,nentriesB,nentriesG;
  double maxy;

  TString basic_cut_data;
  TString basic_cut_mc;
  TString basic_cut_gen;

  if(channel=="Dzero_pp")
    {
      basic_cut_data="dcandeta>-2.0&&dcandeta<2.0&&dcanddau1pt>0.5&&dcanddau2pt>0.5&&abs(dcandmass-1.864)>0.1&&abs(dcandmass-1.864)<0.15";
      basic_cut_mc="dcandeta>-2.0&&dcandeta<2.0&&dcanddau1pt>0.5&&dcanddau2pt>0.5&&matchedtogen!=0";
      basic_cut_gen="deta>-2&&deta<2";
    }
  if(channel=="Dzero_PbPb")
    {
      basic_cut_data="dcandeta>-2.0&&dcandeta<2.0&&dcanddau1pt>1.5&&dcanddau2pt>1.5&&abs(dcandmass-1.864)>0.1&&abs(dcandmass-1.864)<0.15";
      basic_cut_mc="MinBias&&dcandeta>-2.0&&dcandeta<2.0&&dcanddau1pt>1.5&&dcanddau2pt>1.5&&(matchedtogen&&nongendoublecounted)";
      basic_cut_gen="deta>-2&&deta<2";
    }

  //Fill histogram
  TH1D* hmassS = new TH1D("hmassS","",50,1.6,2.2);
  TH1D* hmassG = new TH1D("hmassG","",50,-10,10);
  TH1D* hmassB = new TH1D("hmassB","",50,0,10);
    background->Project("hmassB","dcandmass",Form("%s&&dcandpt>%f&&dcandpt<%f",basic_cut_data.Data(),ptmin,ptmax));
  signal->Project("hmassS","dcandmass",Form("%s&&dcandpt>%f&&dcandpt<%f",basic_cut_mc.Data(),ptmin,ptmax));
  generated->Project("hmassG","deta",Form("%s&&dpt>%f&&dpt<%f",basic_cut_gen.Data(),ptmin,ptmax));

  //Get sigma
  hmassS->GetXaxis()->SetTitle("B mass (Signal)");
  hmassS->GetYaxis()->SetTitle("Entries");
  TCanvas* cmassS = new TCanvas("cmassS","",200,10,600,600);
  hmassS->Draw();
  TF1* fmass = new TF1("fmass","[0]*([3]*Gaus(x,[1],[2])+(1-[3])*Gaus(x,[1],[4]))");
  fmass->SetParLimits(2,0.005,0.05);
  fmass->SetParLimits(3,0,1);
  double setparam1=1.86;
  double setparam2=0.01;
  double setparam4=0.08;
  fmass->SetParameter(1,setparam1);
  fmass->SetParameter(2,setparam2);
  fmass->SetParameter(4,setparam4);
  fmass->FixParameter(3,1);
  hmassS->Fit("fmass","","",1.6,2.2);
  cmassS->SaveAs(Form("plots/plot_%s/Signal.pdf",channel.Data()));
  float sigma=fmass->GetParameter(2);

  //Background
  hmassB->GetXaxis()->SetTitle("B mass (Background)");
  hmassB->GetYaxis()->SetTitle("Entries");
  TCanvas* cmassB = new TCanvas("cmassB","",200,10,600,600);
  hmassB->Draw();
  cmassB->SaveAs(Form("plots/plot_%s/Background.pdf",channel.Data()));

  nentriesB = hmassB->GetEntries();
  nentriesS = hmassS->GetEntries();
  nentriesG = hmassG->GetEntries();


  ifstream getdata("fonlls/fo_Dzero_pp_2.76_eta2.dat");
  if(!getdata.is_open()) cout<<"Opening the file fails"<<endl;

  const int Nmax = 1000;
  float central[Nmax],pt[Nmax]; //make this vector
  float tem;

  int nbin=0;  
  while (!getdata.eof())
    {
      getdata>>pt[nbin]>>central[nbin]>>tem>>tem>>tem>>tem>>tem>>tem>>tem>>tem;
      if (pt[nbin]>=ptmin && pt[nbin]<=ptmax) nbin++;
    }
  //  nbin--;

  TH1D *fonll = new TH1D("fonll","fonll",nbin-1,pt);
  for (int i=0;i<nbin;i++)
    {    fonll->SetBinContent(i,central[i]);
      std::cout<< " i "<<i<<" pt "<<pt[i]<<" fonll "<<central[i]<<std::endl;
    }

  fonll->Draw();
  TCanvas v3;
  std::cout<<Form("%s&&dpt>%f&&dpt<%f",basic_cut_gen.Data(),ptmin,ptmax)<<std::endl;
  std::cout<<Form("%s&&dcandpt>%f&&dcandpt<%f",basic_cut_mc.Data(),ptmin,ptmax)<<std::endl;
  //  generated->Draw("dpt",Form("%s&&dpt>%f&&dpt<%f",basic_cut_gen.Data(),ptmin,ptmax));
  //signal->Draw("dcandpt",Form("%s&&dcandpt>%f&&dcandpt<%f",basic_cut_mc.Data(),ptmin,ptmax),"same");

  TH1D* gen = new TH1D("gen","gen",nbin-1,pt);
  TH1D* rec = new TH1D("rec","rec",nbin-1,pt);
  TH1D* eff = new TH1D("eff","eff",nbin-1,pt);
  generated->Project("gen","dpt",Form("%s&&dpt>%f&&dpt<%f",basic_cut_gen.Data(),ptmin,ptmax));
  signal   ->Project("rec","dcandpt",Form("%s&&dcandpt>%f&&dcandpt<%f",basic_cut_mc.Data(),ptmin,ptmax));

  eff->Divide(rec,gen,1.,1.,"B");

  TH1D* theoryreco = new TH1D("theoryreco","theoryreco",nbin-1,pt);
  theoryreco->Multiply(eff,fonll,1,1,"B");


  double yieldDzero_pp=0,yieldDzero_PbPb;
  double nevent=background->GetEntries();
  double imin,imax;
  imin = (ptmin-2.0)/0.25;
  imax = (ptmax-2.0)/0.25;

  double Taa = 5.65;
  double sigmaAA = 7660; //mb
  double BR = 0.0387;
  double deltapt = 0.25;
  //central[i] - in pb/GeV/c
  for(i=imin;i<imax;i++)
    {
      if(channel=="Dzero_pp") yieldDzero_pp+=central[i]*5.4*0.0387*0.25;
      //if(channel=="Dzero_PbPb") yieldDzero_pp+=central[i]*166*(1.e-6)*0.0387*0.25*5.65*7660;
      if(channel=="Dzero_PbPb") yieldDzero_pp+=central[i];
    }

  double yieldDzero = theoryreco->Integral();

  yieldDzero_pp*=(1.e-9)*BR*deltapt*Taa*nevent/sigmaAA;
  yieldDzero*=(1.e-9)*BR*deltapt*Taa * nevent/sigmaAA;

  float effacc=nentriesS*1.0/nentriesG;
  std::cout<<"yield "<<yieldDzero<<" yieldDzero_pp*effacc "<<yieldDzero_pp*effacc<< std::endl;

  cout<<"nentriesS  "<<nentriesS<<"  nentriesG  "<<nentriesG<<endl;
  if(channel=="Dzero_pp")
    {
      results[0] = nentriesB*Nsigma*sigma/0.05;
      results[1] = yieldDzero;//yieldDzero_pp*effacc;
      cout<<setw(10)<<"# of bkg:"<<setw(5)<<nentriesB<<setw(10)<<"eff*acc:"<<setw(5)<<effacc<<setw(10)<<"sigma:"<<setw(5)<<sigma<<setw(16)<<"fonll expected:"<<setw(7)<<yieldDzero_pp<<endl;
      cout<<setw(10)<<"background weight:"<<setw(5)<<nentriesB*Nsigma*sigma/0.05<<setw(10)<<"signal weight:"<<setw(5)<<yieldDzero_pp*effacc<<endl;
    }
  if(channel=="Dzero_PbPb")
    {
      results[0] = nentriesB*Nsigma*sigma/0.05;
      results[1] = yieldDzero_pp*effacc;
      cout<<setw(10)<<"# of bkg:"<<setw(5)<<nentriesB<<setw(10)<<"eff*acc:"<<setw(5)<<effacc<<setw(10)<<"sigma:"<<setw(5)<<sigma<<setw(16)<<"fonll expected:"<<setw(7)<<yieldDzero_pp<<endl;
      cout<<setw(10)<<"background weight:"<<setw(5)<<nentriesB*Nsigma*sigma/0.05<<setw(10)<<"signal weight:"<<setw(5)<<yieldDzero_pp*effacc<<endl;
    }
  
}

void readxml()
{
  //read weight file
  cout<<"########### reading WEIGHTS files #############"<<endl;
  double effS[100], effB[100],effSig[100],effBac[100];
  const char* filename = Form("weights/%s/TMVAClassification_CutsGA.weights.xml",channel.Data());
  void *doc = TMVA::gTools().xmlengine().ParseFile(filename,TMVA::gTools().xmlenginebuffersize());
  cout<<"doc: "<<doc<<endl;
  void* rootnode = TMVA::gTools().xmlengine().DocGetRootElement(doc); // node "MethodSetup"
  cout<<"rootnode: "<<rootnode<<endl;
  //gTools().ReadAttr(rootnode, "Method", fullMethodName);
  void* weight = TMVA::gTools().GetChild(rootnode,"Weights");
  cout<<"weight: "<<weight<<endl;
  void* eff = TMVA::gTools().GetChild(weight,"Bin");
  cout<<"eff: "<<eff<<endl;
  int i=0;
  while(eff)
    {
      //if(i%20==0) cout<<i<<endl;
      TMVA::gTools().ReadAttr(eff, "effS", effS[i]);
      TMVA::gTools().ReadAttr(eff, "effB", effB[i]);
      eff = TMVA::gTools().GetNextChild(eff);
      i++;
    }

  cout<<endl;
  TMVA::gTools().xmlengine().FreeDoc(doc);


  float wSignal=0;
  float wBackground=0;
  float* weights=new float[2];
  calRatio(weights);
  wSignal = weights[1];
  wBackground = weights[0];
  cout<<setw(10)<<"wSignal:"<<setw(5)<<wSignal<<setw(10)<<"wBackground:"<<setw(5)<<wBackground<<endl;

  double max;
  int maxindex;
  effS[0]=0;
  for(i=1;i<100;i++)
    {
      //if(i%10==0) cout<<i<<endl;
      effSig[i] = wSignal*effS[i]/sqrt(wSignal*effS[i]+wBackground*effB[i]);
      if(i==1)
	{
	  max=effSig[1];
	  maxindex=1;
	}
      else if(effSig[i]>max)
	{
	  max=effSig[i];
	  maxindex=i;
	}
    }
  cout<<"maxindex: "<<effS[maxindex]<<"  max:"<<max<<endl;
  cout<<"################################################"<<endl;
  cout<<endl;

  TGraph* gsig = new TGraph(100,effS,effSig);
  gsig->SetTitle("");
  TCanvas* csig = new TCanvas("c1","",200,100,600,600);
  csig->SetGrid();
  gsig->Draw("A*");
  TLegend* leg = new TLegend(0.08,0.91,0.15,0.98);
  if(channel=="Dzero_pp") leg->AddEntry("null", "D^{0}","");
  leg->SetFillColor(kWhite);
  leg->Draw();
  csig->SaveAs(Form("plots/plot_%s/sig-eff_%.1f_%.1f.pdf",channel.Data(),ptmin,ptmax));

}
