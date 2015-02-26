#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TNamed.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include "Math/MinimizerOptions.h"

#include "PtBins.h"
using namespace std;

float ptmin = 7;
float ptmax = 9;

bool evtunprescaleMB = false;   //false to fit raw counts without unprescale MB trigger
bool isMC = false;

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;

float hiBin_low = -0.5;
float hiBin_high = 199.5;
float rapidityrange = 2.0;

TH1F* hfg_minbias;  //for D0

void book_hist()
{
  char hname[100], pt_range[1000];
  sprintf(pt_range, "pt: %.1f %.1f", ptmin, ptmax);
  sprintf(hname, "hfg_minbias");
  hfg_minbias = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
  hfg_minbias->Sumw2();
}

void write_histo( TFile* output)
{
  hfg_minbias->Write();
  output->Close();
}

int decideptbin( float dpt )
{
  int ipt = -1;
  for ( int i=0 ; i<NPT; i++)
    {
      if (dpt >= ptbins[i] && dpt < ptbins[i+1])  { ipt = i; break; }
    }
  if ( dpt > ptbins[NPT] ) ipt = NPT-1;
  return ipt;
}

void fit_hist( TH1F * histo, TCanvas *cfg, float ptlow, float pthigh)
{
  
  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(100000); 
  cfg->cd();
  
  histo->SetMarkerSize(0.8);
  histo->SetLineColor(2);
  histo->SetMarkerColor(2);
  histo->SetMarkerStyle(20);
  histo->GetXaxis()->SetNdivisions(505);
  histo->GetXaxis()->SetTitle("m_{#piK} (GeV)");
  histo->GetYaxis()->SetTitle("Counts");
  histo->GetXaxis()->SetRangeUser(cut_m_low, cut_m_high);
  //    TF1* fit_fun = new TF1("fit_fun", fitfunction, cut_m_low, cut_m_high, 6);
  //.. fit with a Gaussian and pol
  TF1* fit_fun = new TF1("fit_fun", "gausn(0) + pol2(3)", cut_m_low, cut_m_high);
  //    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + expo(3)", cut_m_low, cut_m_high);
  //    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + expo(6)", cut_m_low, cut_m_high);
  float max = histo->GetMaximum();
  
  float p0 = 1000, p1 = 1.87, p2 = 0.02;
  float p0_L = 0, p1_L = 1.84, p2_L = 0;
  float p0_H = 2*max, p1_H = 1.9, p2_H = 0.05;
  
  float p3 = -1. * max, p4 = max, p5 = -1. * max;
  
  int pass = 0;
  int fittingtry = 0;
  
  char sig_print[100], chi2_print[100], bkg_print[100], sign_print[100];
  
  while (!pass)
    {
      fit_fun->SetParameter(0, p0);
      fit_fun->SetParameter(1, p1);
      fit_fun->SetParameter(2, p2);
      
      //.. fit constraint ..
      fit_fun->SetParLimits(0, p0_L, p0_H);
      fit_fun->SetParLimits(1, p1_L, p1_H);
      fit_fun->SetParLimits(2, p2_L, p2_H);
      
      //fit_fun->SetParameter(3, p3);
      //fit_fun->SetParameter(4, p4);
      //fit_fun->SetParameter(5, p5);
      
      if(fittingtry == 0)
	{
	  histo->Fit(fit_fun,"","", cut_m_low, cut_m_high);
	}
      else
	{ 
	  //histo->Fit(fit_fun,"WL","", cut_m_low, cut_m_high);
	  histo->Fit(fit_fun,"","", cut_m_low, cut_m_high);
	}
      //.. draw foreground and background ..
      histo->Draw();
      
      TF1* fit_fun_1st = (TF1*)fit_fun->Clone("fit_fun_1st");
      fit_fun_1st->SetParameter(3, 0);
      fit_fun_1st->SetParameter(4, 0);
      fit_fun_1st->SetParameter(5, 0);
      //fit_fun_1st->Draw("same");
    
      TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
      //TF1* fit_fun_bg = new TF1("fit_fun_bg", fitfunction, cut_m_low, cut_m_high, 6);
      fit_fun_bg->SetParameter(0, 0);
      fit_fun_bg->SetParameter(1, 0);
      fit_fun_bg->SetParameter(2, 0);
      //fit_fun_bg->SetParameter(3, fit_fun->GetParameter(3));
      //fit_fun_bg->SetParameter(4, fit_fun->GetParameter(4));
      //fit_fun_bg->SetParameter(5, fit_fun->GetParameter(5));
    
      fit_fun_bg->SetLineColor(8);
      fit_fun_bg->Draw("same");
      
      fittingtry++;
      
      float binwidth = histo->GetBinWidth(10);
      float ptbinwidth = pthigh-ptlow;
      
      float Nsig = fit_fun->GetParameter(0)/(binwidth);
      float err_Nsig = fit_fun->GetParError(0)/(binwidth);
      float fitchi2 = fit_fun->GetChisquare();
      int noffreepara = fit_fun->GetNumberFreeParameters();
      int noffitpoints = fit_fun->GetNumberFitPoints();
      
      cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;
      
      float sigma = fit_fun->GetParameter(2);
      float mu    = fit_fun->GetParameter(1);
      
      //float Nsigfit = fit_fun_1st->Integral(mu-2*sigma,mu+2*sigma)/binwidth;
      float Nbkg = fit_fun_bg->Integral(mu-2*sigma,mu+2*sigma)/binwidth;
      cout << "Nsig integral "<<fit_fun_1st->Integral(mu-2*sigma,mu+2*sigma)/binwidth
	   <<" Nbkg integral "<<fit_fun_bg->Integral(mu-2*sigma,mu+2*sigma)/binwidth
	   <<" mu "<<mu<<" sigma "<<sigma<<" bin width "<<binwidth<<endl;
      cout << " pt min "<<ptlow<<" pt max "<<pthigh<<" fittingtry "<<fittingtry<<endl;
      cout << "Nsig total integral "<<fit_fun_1st->Integral(0, 10)/binwidth<<endl<<endl;
      
      if(!isMC)
	{
	  sprintf( sig_print,"N_{sig} = %7.1f #pm %7.1f", Nsig, err_Nsig);
	}
      else
	{
	  sprintf( sig_print,"N_{sig} = %7.5f #pm %7.5f", Nsig, err_Nsig);
	  sprintf( chi2_print, "#chi^{2}#/d.o.f = %3.2f", fitchi2/( noffitpoints - noffreepara));
	  sprintf( bkg_print, "N_{bkg} = %7.5f", Nbkg);
	  sprintf( sign_print, "S = %7.5f", Nsig/sqrt(Nsig+Nbkg));
	}

      
      if(fittingtry == 2)
	{
	  TLatex Tl;
	  Tl.SetNDC();
	  Tl.SetTextAlign(12);
	  Tl.SetTextSize(0.037);
	  Tl.DrawLatex(0.55,0.8, sig_print);
	  if(isMC)
	    {
	      Tl.DrawLatex(0.55,0.7, chi2_print);
	      Tl.DrawLatex(0.55,0.6, bkg_print);
	      Tl.DrawLatex(0.55,0.5, sign_print);
	    }
	}
      
      if (fittingtry == 2)  
	{
	  pass = 1;
	}
      if(!pass) 
	{
	  p0 = fit_fun->GetParameter(0);
	  p1 = fit_fun->GetParameter(1);
	  p2 = fit_fun->GetParameter(2);
	  //p1_L = 1.84, p2_L = 0;
	  //p1_H = 1.9, p2_H = 0.05;
        }
      
  }
  return;
}

void fit()
{
  book_hist();
  
  TH1D * hf_mb = new TH1D("hf_mb","hf_mb",10,-5,5);
  hf_mb->Sumw2();
  
  TFile * input = new TFile("/data/dmeson/Ntuple/Dmesonana_Rereco_MBtrig_d0pt4p5_nodalphacuts_pt1p5_tight_3lumi_0131_part1_fortmva.root");
  TTree * recodmesontree = (TTree *) input->Get("recodmesontree");

  int MinBias;
  int MinBias_Prescl;
  
  int ndcand;
  int hiBin;
  double pthatweight;
  double trigweight;

  vector<int> *dtype = 0, *passingcuts = 0;
  vector<float> *dcandmass = 0, *dcandpt = 0, *dcandy = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandcosalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
  vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0;
  vector<float> *dcanddau1pt = 0, *dcanddau2pt = 0;
  vector<float> *dcandeta = 0;
  
  recodmesontree->SetBranchAddress("MinBias", &MinBias);
  recodmesontree->SetBranchAddress("MinBias_Prescl", &MinBias_Prescl);
  recodmesontree->SetBranchAddress("hiBin", &hiBin);
  recodmesontree->SetBranchAddress("pthatweight", &pthatweight);
  recodmesontree->SetBranchAddress("trigweight", &trigweight);
  recodmesontree->SetBranchAddress("ndcand", &ndcand);
  recodmesontree->SetBranchAddress("dtype", &dtype);
  recodmesontree->SetBranchAddress("passingcuts", &passingcuts);
  recodmesontree->SetBranchAddress("dcandmass", &dcandmass);
  recodmesontree->SetBranchAddress("dcandpt", &dcandpt);
  recodmesontree->SetBranchAddress("dcandy", &dcandy);
  recodmesontree->SetBranchAddress("dcandphi", &dcandphi);
  recodmesontree->SetBranchAddress("dcandffls3d", &dcandffls3d);
  recodmesontree->SetBranchAddress("dcandcosalpha", &dcandcosalpha);
  recodmesontree->SetBranchAddress("dcandfprob", &dcandfprob);
  recodmesontree->SetBranchAddress("dcandfchi2", &dcandfchi2);
  recodmesontree->SetBranchAddress("dcanddau1eta", &dcanddau1eta);
  recodmesontree->SetBranchAddress("dcanddau2eta", &dcanddau2eta);
  recodmesontree->SetBranchAddress("dcanddau1pt", &dcanddau1pt);
  recodmesontree->SetBranchAddress("dcanddau2pt", &dcanddau2pt);
  recodmesontree->SetBranchAddress("dcandeta", &dcandeta);
  
  for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
    {
      recodmesontree->GetEntry(entry);
      if( entry % 100000 == 0 )  cout << entry+1 << "st event" << endl;
      if( !MinBias ) continue;
      if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() ) cout << "Error!!!!!!!!" << endl;
      if( hiBin < hiBin_low || hiBin > hiBin_high )   continue;
      
      hf_mb->Fill(MinBias, MinBias_Prescl);
      for( int icand = 0; icand < ndcand; icand++ )
	{
	  if( dtype->at(icand) != 2 )   cout << " Error!!!!!!! Just working on D0 now" << endl;
	  double effectiveffls3dcut = 2;//100000.;
	  //if( dcandpt->at(icand) < cut_pt_edge )
	  //effectiveffls3dcut = ffls3dcut[0];
	  //else 
	  //effectiveffls3dcut = ffls3dcut[1];
	  
	  if( dcandffls3d->at(icand) < ffls3dcut[0] )   continue;
	  if( dcandcosalpha->at(icand) < cosalphacut || dcandfprob->at(icand) < fprobcut )  continue;
	  
	  //if( TMath::Abs( dcandy->at(icand) ) > rapidityrange )  continue;

	  if( TMath::Abs( dcandeta->at(icand) ) > 2.0 )  continue;
	  if( TMath::Abs( dcanddau1pt->at(icand) ) < 1.5 || TMath::Abs( dcanddau2pt->at(icand) ) < 1.5 )   continue;
	  if( TMath::Abs( dcanddau1eta->at(icand) ) > 2.4 || TMath::Abs( dcanddau2eta->at(icand) ) > 2.4 )   continue;
	  if( dcandpt->at(icand)>ptmax || dcandpt->at(icand)<ptmin) continue;

	  int ipt = decideptbin(dcandpt->at(icand));
	  if(ipt<0) continue;
	  //cout << " pt: " << dcandpt->at(icand) << "  ipt: " << ipt << endl;
	  double weight=1.0;
	  if(!isMC)
	    {
	      weight = MinBias_Prescl;
	    }
	  else
	    {
	      weight = pthatweight;
	    }
	  if( !evtunprescaleMB )
	    {
	      weight = 1.0;
	    }
	  hfg_minbias->Fill(dcandmass->at(icand), weight);
	  
	}
    }
  
  
  //  recodmesontree->Project("hfg_minbias","dcandmass",Form("dcandy>-2.0&&dcandy<2.0&&dcandpt>%f&&dcandpt<%f&&dcanddau1pt>1.5&&dcanddau2pt>1.5&&dcandffls3d>%f&&dcandcosalpha>%f&&dcandfprob>%f",ptmin,ptmax,ffls3dcut[0],cosalphacut,fprobcut));

  //hfg_minbias->Draw();

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  /*
  TH1D * N_mb = new TH1D("N_mb","N_mb",NPT,ptbins);
  N_mb->Sumw2();
  */

  TCanvas* cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 500, 500);
  fit_hist(hfg_minbias, cfg_mb, ptmin, ptmax);

  cfg_mb->SaveAs(Form("plots/fit/massSpectrum_%.1f_%.1f",ptmin,ptmax));

  /*
  char cfgname[200];
  sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f.pdf",NPT, evtunprescaleMB, hiBin_low, hiBin_high);
  cfg_mb->SaveAs(cfgname);
  sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f.gif",NPT, evtunprescaleMB, hiBin_low, hiBin_high);
  cfg_mb->SaveAs(cfgname);
  
  char outputfile[200];
  sprintf(outputfile,"Dspectrum_pbpb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f.root", NPT, evtunprescaleMB, hiBin_low, hiBin_high);
  TFile * output = new TFile(outputfile,"RECREATE");
  hf_mb->Write();
  N_mb->Write();
  cfg_mb->Write();
  write_histo( output );
  */
}
