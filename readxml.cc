
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

#define BIN_NUM 100

void readxml()
{
  double effS[100], effB[100],effSig[100],effBac[100];
  //double cutMin_0[100], cutMax_0[100], cutMin_1[100], cutMax_1[100], cutMin_2[100], cutMax_2[100], cutMin_3[100], cutMax_3[100];

  const char* filename = "weights/Bs/TMVAClassification_CutsGA.weights.xml";
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
      if(i%10==0) cout<<i<<endl;
      TMVA::gTools().ReadAttr(eff, "effS", effS[i]);
      TMVA::gTools().ReadAttr(eff, "effB", effB[i]);
      eff = TMVA::gTools().GetNextChild(eff);
      //cout<<"eff"<<(i+1)<<eff<<endl;
      i++;
    }
  TMVA::gTools().xmlengine().FreeDoc(doc);

  double wSignal=0;
  double wBackground=0;
  int flag=3;
  if(flag==1)
    {
      wSignal=444;
      wBackground=52772*2.27886e-02/0.1;
    }
  else if(flag==3)
    {
      wSignal=47;
      wBackground=40473*1.43773e-02/0.1;
    }
  else if(flag==2)
    {
      wSignal=355;
      wBackground=367028*1.88392e-02/0.1;
    }

  double max;
  int maxindex;
  for(i=1;i<100;i++)
    {
      if(i%10==0) cout<<i<<endl;
      effBac[i] = 5*effB[i];
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
      //cout<<effS[i]<<"  "<<effB[i]<<"  "<<effSig[i]<<endl;
    }
  cout<<"maxindex: "<<effS[maxindex]<<"  max:"<<max<<endl;

  TCanvas* c1 = new TCanvas("c1","Significance",200,10,700,500);
  c1->SetGrid();
  //TPad *pad = new TPad("pad","",0,0,1,1);
  //pad->SetFillColor(42);
  //pad->SetGrid();
  //pad->Draw();
  //pad->cd();

  //TH1F *hr = c1->DrawFrame(-0.4,0,1.2,12);
  //hr->SetXTitle("X title");
  //hr->SetYTitle("Y title");
  //pad->GetFrame()->SetFillColor(21);
  //pad->GetFrame()->SetBorderSize(12);

  TGraph *gsig = new TGraph(100,effS,effSig);
  gsig->SetTitle("");
  gsig->GetXaxis()->SetTitle("signal efficiency");
  gsig->SetLineColor(63);
  gsig->SetLineWidth(3);
  gsig->SetName("gsig");
  gsig->Draw("AC");

  TGraph *gbac = new TGraph(100,effS,effBac);
  gbac->SetLineColor(50);
  gbac->SetLineWidth(3);
  gbac->SetName("gbac");
  gbac->Draw("same");

  TLegend* leg = new TLegend(0,0.93,1.0,1.0);
  leg->AddEntry("gsig", "Significance","lp");
  leg->AddEntry("gbac", "Background efficiency","lp");
  leg->Draw();

}
