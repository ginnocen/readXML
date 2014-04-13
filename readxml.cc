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


void calRatio(float* results)
{
  TString channel = "Bplus";

  TFile* inputB = new TFile("/export/d00/scratch/jwang/nt_20140411_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_CandBase_skim.root");
  TFile* inputS = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140412_Kp_TriggerMatchingMuon_CandBase_skim.root");
  TTree *signal = (TTree*)inputS->Get("ntKp");
  TTree *background = (TTree*)inputB->Get("ntKp");
  TTree *generated = (TTree*)inputS->Get("ntGen");

  int i,j;
  int nentriesS,nentriesB,nentriesG;
  double maxy;

  TString basic_cut_data;
  TString basic_cut_mc;
  TString basic_cut_gen;

  if(channel=="Bplus")
    {
      basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&trk1Pt>0.9&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
      basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&trk1Pt>0.9&&gen==22233";
      basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&isSignal==1";
    }
  //TString basic_cut_data="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&(pt>10.)&&isbesttktkmass&&abs(mass-5.279)>0.2&&abs(mass-5.279)<0.3";
  //TString basic_cut_mc="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&abs(y+0.465)<1.93&&(pt>10.)&&isbesttktkmass&&gen==22233";
  //TString basic_cut_gen="abs(y+0.465)<1.93&&(pt>10.)&&(isSignal==4||isSignal==5)";

  TH1D* hmassS = new TH1D("hmassS","",50,5,6);
  TH1D* hmassG = new TH1D("hmassG","",50,0,10);
  TH1D* hmassB = new TH1D("hmassB","",50,3,7);
  background->Project("hmassB","mass",basic_cut_data.Data());
  signal->Project("hmassS","mass",basic_cut_mc.Data());
  generated->Project("hmassG","isSignal",basic_cut_gen.Data());

  //plot

  hmassS->GetXaxis()->SetTitle("B mass (Signal)");
  hmassS->GetYaxis()->SetTitle("Entries");
  TCanvas* cmassS = new TCanvas("cmassS","",200,10,600,600);
  hmassS->Draw();
  TF1* fmass = new TF1("fmass","[0]*Gaus(x,[1],[2])");
  fmass->SetParLimits(2,0.01,0.05);
  double setparam1=5.28;
  double setparam2=0.05;
  fmass->SetParameter(1,setparam1);
  fmass->SetParameter(2,setparam2);

  hmassS->Fit("fmass","","",5,6);
  cmassS->SaveAs(Form("plot_%s/Signal.gif",channel.Data()));

  hmassB->GetXaxis()->SetTitle("B mass (Background)");
  hmassB->GetYaxis()->SetTitle("Entries");
  TCanvas* cmassB = new TCanvas("cmassB","",200,10,600,600);
  hmassB->Draw();
  cmassB->SaveAs(Form("plot_%s/Background.gif",channel.Data()));

  nentriesB = hmassB->GetEntries();
  nentriesS = hmassS->GetEntries();
  nentriesG = hmassG->GetEntries();

  ifstream getdata("fo_pPb_pt.dat");
  if(!getdata.is_open())
    {
      cout<<"Opening the file fails"<<endl;
    }
  float central[220];
  float tem;
  for(i=0;i<220;i++)
    {
      getdata>>tem;
      getdata>>central[i];
      getdata>>tem;
      getdata>>tem;
      getdata>>tem;
      getdata>>tem;
      getdata>>tem;
      getdata>>tem;
      getdata>>tem;
      getdata>>tem;
    }
  double yieldBplus=0,yieldBzero=0,yieldBs=0;
  for(i=20;i<220;i++)
    {
      yieldBplus+=central[i]*2*(35.e-3)*0.401*208*6.09604e-5;
      yieldBzero+=central[i]*2*(35.e-3)*0.401*208*5.244e-5;
      yieldBs+=central[i]*2*(35.e-3)*0.105*208*2.89977e-5;
    }
  float sigma=fmass->GetParameter(2);
  float effacc=nentriesS*1.0/nentriesG;
  if(channel=="Bplus")
    {
      results[0] = nentriesB*2*sigma/0.1;
      results[1] = yieldBplus*effacc;
      cout<<"# of bkg: "<<nentriesB<<"    eff*acc: "<<effacc<<"  sigma: "<<sigma<<"  fonll expected: "<<yieldBplus<<endl;
      cout<<"background weight: "<<nentriesB*2*sigma/0.1<<"   signal weight: "<<yieldBplus*effacc<<endl;
    }
  if(channel=="Bzero")
    {
      results[0] = nentriesB*2*sigma/0.1;
      results[1] = yieldBzero*effacc;
      cout<<"# of bkg: "<<nentriesB<<"    eff*acc: "<<effacc<<"  sigma: "<<sigma<<"  fonll expected: "<<yieldBzero<<endl;
      cout<<"background weight: "<<nentriesB*2*sigma/0.1<<"   signal weight: "<<yieldBzero*effacc<<endl;
    }
  if(channel=="Bs")
    {
      results[0] = nentriesB*2*sigma/0.1;
      results[1] = yieldBzero*effacc;
      cout<<"# of bkg: "<<nentriesB<<"    eff*acc: "<<effacc<<"  sigma: "<<sigma<<"  fonll expected: "<<yieldBs<<endl;
      cout<<"background weight: "<<nentriesB*2*sigma/0.1<<"   signal weight: "<<yieldBs*effacc<<endl;
    }
}

void readxml()
{
  TString channel = "Bplus";

  //read weight file
  cout<<"########### reading WEIGHTS files #############"<<endl;
  double effS[100], effB[100],effSig[100],effBac[100];
  const char* filename = "weights/Bplus/TMVAClassification_CutsGA.weights.xml";
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
      if(i%20==0) cout<<i<<endl;
      TMVA::gTools().ReadAttr(eff, "effS", effS[i]);
      TMVA::gTools().ReadAttr(eff, "effB", effB[i]);
      eff = TMVA::gTools().GetNextChild(eff);
      i++;
    }
  cout<<"################################################"<<endl;
  cout<<endl;
  TMVA::gTools().xmlengine().FreeDoc(doc);

  cout<<"############# caculating weights ###############"<<endl;
  float wSignal=0;
  float wBackground=0;
  float* weights=new float[2];
  calRatio(weights);
  wSignal = weights[1];
  wBackground = weights[0];
  cout<<"wSignal: "<<wSignal<<"wBackground: "<<wBackground<<endl;
  cout<<"################################################"<<endl;
  cout<<endl;

  cout<<"########## caculating significance #############"<<endl;
  double max;
  int maxindex;
  effS[0]=0;
  for(i=1;i<100;i++)
    {
      if(i%10==0) cout<<i<<endl;
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
  TCanvas* csig = new TCanvas("c1","",200,100,600,600);
  csig->SetGrid();
  gsig->Draw("A*");
  TLegend* leg = new TLegend(0.08,0.91,0.15,0.98);
  leg->AddEntry("null", "B^{+}","");
  leg->SetFillColor(kWhite);
  leg->Draw();
  csig->SaveAs(Form("plot_%s/Significance.gif",channel.Data()));
}
