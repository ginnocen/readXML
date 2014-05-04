
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

void testweights()
{
  double effS[100], effB[100],effSig[100],effBac[100];
  double cutMin_tk1_12[100],cutMin_tk2_12[100],cutMin_tk1_21[100],cutMin_tk2_21[100];

  //const char* filename = "weights/Bs/TMVAClassification_CutsGA.weights.xml";
  const char* filename = "weights/Bs/12/TMVAClassification_CutsGA.weights.xml";
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
      void* cut = TMVA::gTools().GetChild(eff,"Cuts");
      TMVA::gTools().ReadAttr(cut,"cutMin_3",cutMin_tk1_12[i]);
      TMVA::gTools().ReadAttr(cut,"cutMin_4",cutMin_tk2_12[i]);
      eff = TMVA::gTools().GetNextChild(eff);
      //cout<<"eff"<<(i+1)<<eff<<endl;
      i++;
    }
  TMVA::gTools().xmlengine().FreeDoc(doc);

  const char* filename2 = "weights/Bs/21/TMVAClassification_CutsGA.weights.xml";
  void *doc2 = TMVA::gTools().xmlengine().ParseFile(filename2,TMVA::gTools().xmlenginebuffersize());
  cout<<"doc: "<<doc2<<endl;
  void* rootnode2 = TMVA::gTools().xmlengine().DocGetRootElement(doc2); // node "MethodSetup"
  cout<<"rootnode: "<<rootnode2<<endl;
  //gTools().ReadAttr(rootnode, "Method", fullMethodName);
  void* weight2 = TMVA::gTools().GetChild(rootnode2,"Weights");
  cout<<"weight: "<<weight2<<endl;
  void* eff2 = TMVA::gTools().GetChild(weight2,"Bin");
  cout<<"eff: "<<eff2<<endl;
  i=0;
  while(eff2)
    {
      if(i%10==0) cout<<i<<endl;
      //TMVA::gTools().ReadAttr(eff2, "effS", effS[i]);
      void* cut2 = TMVA::gTools().GetChild(eff2,"Cuts");
      TMVA::gTools().ReadAttr(cut2,"cutMin_3",cutMin_tk1_21[i]);
      TMVA::gTools().ReadAttr(cut2,"cutMin_4",cutMin_tk2_21[i]);
      eff2 = TMVA::gTools().GetNextChild(eff2);
      //cout<<"eff"<<(i+1)<<eff<<endl;
      i++;
    }
  TMVA::gTools().xmlengine().FreeDoc(doc2);

  TCanvas* c1 = new TCanvas("c1","Significance",200,10,700,500);
  c1->SetGrid();

  //TH1F *hr = c1->DrawFrame(-0.4,0,1.2,12);
  //hr->SetXTitle("X title");
  //hr->SetYTitle("Y title");
  //pad->GetFrame()->SetFillColor(21);
  //pad->GetFrame()->SetBorderSize(12);
  /*  
  TGraph *gtk1_12 = new TGraph(100,effS,cutMin_tk1_12);
  gtk1_12->SetTitle("");
  gtk1_12->GetXaxis()->SetTitle("signal efficiency");
  gtk1_12->SetLineColor(63);
  gtk1_12->SetLineWidth(3);
  gtk1_12->SetName("gtk1_12");
  gtk1_12->Draw("AC");

  TGraph *gtk2_12 = new TGraph(100,effS,cutMin_tk2_12);
  gtk2_12->SetLineColor(50);
  gtk2_12->SetLineWidth(3);
  gtk2_12->SetName("gtk2_12");
  gtk2_12->Draw("same");
  */
  
  TGraph *gtk1_21 = new TGraph(100,effS,cutMin_tk1_21);
  gtk1_21->SetLineColor(42);
  gtk1_21->SetLineWidth(3);
  gtk1_21->SetName("gtk1_21");
  gtk1_21->Draw("AC");

  TGraph *gtk2_21 = new TGraph(100,effS,cutMin_tk2_21);
  gtk2_21->SetLineColor(38);
  gtk2_21->SetLineWidth(3);
  gtk2_21->SetName("gtk2_21");
  gtk2_21->Draw("same");
  
  TLegend* leg = new TLegend(0,0.93,1.0,1.0);
  leg->AddEntry("gtk1_12", "gtk1_12","lp");
  leg->AddEntry("gtk2_12", "gtk2_12","lp");
  leg->AddEntry("gtk1_21", "gtk1_21","lp");
  leg->AddEntry("gtk2_21", "gtk2_21","lp");
  leg->Draw();

}
