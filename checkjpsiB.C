#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>
#include <TH1F.h>
#include "loopcand.h"
#include <TCanvas.h>

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916

void checkjpsiB(bool REAL=1){
  //////////////////////////////////////////////////////////Phi
  //   This file has been automatically generated 
  //     (Thu Nov 21 13:34:42 2013 by ROOT version5.27/06b)
  //   from TTree root/root
  //   found on file: merged_pPbData_20131114.root
  //////////////////////////////////////////////////////////

  if(REAL) cout<<"--- REAL DATA ---"<<endl;
  else cout<<"--- MC ---"<<endl;


  //File type
  TChain* root = new TChain("demo/root");
  root->Add("/export/d00/scratch/jwang/Bfinder_20140309_PAMuon_HIRun2013_PromptReco_v1_MuonMatching.root");
  root->Add("/export/d00/scratch/jwang/Bfinder_20140319_PAMuon_HIRun2013_28Sep2013_v1_MuonMatching.root");
  setBranch(root);

  /*
    TTree *hlt = (TTree*)f->Get("hltanalysis/HltTree");
    if (root->GetEntries()!=hlt->GetEntries()) {
    cout <<"Inconsistent number of entries!!!"<<endl;
    cout <<"HLT tree: "<<hlt->GetEntries()<<endl;
    cout <<"Bfinder tree: "<<root->GetEntries()<<endl;
    }
  */
  
  Long64_t nentries = root->GetEntries();
  Long64_t nbytes = 0;
  TLorentzVector* b4P = new TLorentzVector;
  TLorentzVector bGen;
  int type,flag;
  int flagEvt=0;  
  int offsetHltTree=0;

  float ujmass=0,mumumass=0;
  float mu1px,mu1py,mu1pz,mu1E;
  float mu2px,mu2py,mu2pz,mu2E;

  float BIN_MIN=2.7,BIN_MAX=3.5;
  TH1D* hmumuB = new TH1D("hmumuB","",50,BIN_MIN,BIN_MAX);
  TH1D* hjpsiB = new TH1D("hjpsiB","",50,BIN_MIN,BIN_MAX);

  for (Long64_t i=0; i<nentries;i++) {
    nbytes += root->GetEntry(i);
    /*
      flagEvt=0;
      while (flagEvt==0)
      {
      hlt->GetEntry(i+offsetHltTree);
      cout <<offsetHltTree<<" "<<Bfr_HLT_Event<<" "<<EvtInfo_EvtNo<<endl;
      if (Bfr_HLT_Event==EvtInfo_EvtNo && Bfr_HLT_Run==EvtInfo_RunNo) flagEvt=1; else offsetHltTree++;
      } 
    */
    if (i%1000000==0) cout <<i<<" / "<<nentries<<"   offset HLT:"<<offsetHltTree<<endl;

    for (int j=0;j<BInfo_size;j++) 
      {
	
	mu1px = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*cos(MuonInfo_phi[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
	mu1py = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*sin(MuonInfo_phi[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
	mu1pz = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*sinh(MuonInfo_eta[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
	b4P->SetXYZM(mu1px,mu1py,mu1pz,MUON_MASS);
	mu1E = b4P->E();

	mu2px = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*cos(MuonInfo_phi[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
	mu2py = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*sin(MuonInfo_phi[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
	mu2pz = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*sinh(MuonInfo_eta[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
	b4P->SetXYZM(mu2px,mu2py,mu2pz,MUON_MASS);
	mu2E = b4P->E();
	
	b4P->SetPxPyPzE(mu1px+mu2px,
			mu1py+mu2py,
			mu1pz+mu2pz,
			mu1E+mu2E);
	mumumass = b4P->Mag();
	hmumuB->Fill(mumumass);
	ujmass = BInfo_uj_mass[BInfo_rfuj_index[j]];
	hjpsiB->Fill(ujmass);
      }
    
  }

  float maxy;
  TCanvas* cB = new TCanvas("cB","",200,10,600,600);
  if(hmumuB->GetMaximum()>hjpsiB->GetMaximum()) maxy=hmumuB->GetMaximum();
  else maxy = hjpsiB->GetMaximum();
  hmumuB->GetXaxis()->SetTitle("#mu#mu mass");
  hmumuB->GetYaxis()->SetTitle("Entries");
  hmumuB->SetMaximum(maxy*1.1);
  hmumuB->Draw();
  gStyle->SetHistLineStyle(1);
  gStyle->SetHistLineColor(kBlue);
  gStyle->SetHistLineWidth(3);
  gStyle->SetHistFillStyle(1001);
  gStyle->SetHistFillColor(kBlue-9);
  hmumuB->UseCurrentStyle();
  hjpsiB->Draw("same");
  gStyle->SetHistLineStyle(1);
  gStyle->SetHistLineColor(kRed);
  gStyle->SetHistLineWidth(3);
  gStyle->SetHistFillStyle(3354);
  gStyle->SetHistFillColor(kRed);
  hjpsiB->UseCurrentStyle();
  TLegend* leg1 = new TLegend(0.20,0.75,0.60,0.92);
  leg1->AddEntry(hmumuB,"#mu#mu invariant mass","f");
  leg1->AddEntry(hjpsiB,"J/#psi mass after fitting","f");
  leg1->SetFillStyle(kWhite);
  leg1->SetLineColor(kWhite);
  leg1->Draw();
  TLegend* leg1p = new TLegend(0.67,0.75,0.90,0.92);
  leg1p->AddEntry("NULL","inclusive #mu#mu","");
  leg1p->SetFillStyle(kWhite);
  leg1p->SetLineColor(kWhite);
  leg1p->Draw();
  cB->SaveAs("dimuon_matchingB.png");
}


