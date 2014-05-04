#include "TH1F.h"
#include <cmath>
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <fstream>
#include <iostream>

#define BIN_NUM 220//pPb_pt:220,pPb_y:40,pp_pt:222,pp_y:45
#define REBIN 6//pPb_pt:6,pPb_y:4,pp_pt:8,pp_y:4
#define REBINp 7//pPb_pt:7,pPb_y:5,pp_pt:9,pp_y:5
#define HMIN 5//pPb_pt:5,pPb_y:-2,pp_pt:9,pp_y:0
#define HMAX 60//pPb_pt:60,pPb_y:2,pp_pt:120,pp_y:2.25                                                                                                                                                               

void yield()
{
  ifstream getdata("fo_pPb_pt.dat");

  if(!getdata.is_open())
    {
      cout<<"Opening the file fails"<<endl;
    }

  float central[BIN_NUM];
  float min_all[BIN_NUM],max_all[BIN_NUM],min_sc[BIN_NUM],max_sc[BIN_NUM],min_mass[BIN_NUM],max_mass[BIN_NUM],min_pdf[BIN_NUM],max_pdf[BIN_NUM];
  int i;
  float tem;
  for(i=0;i<BIN_NUM;i++)
    {
      getdata>>tem;
      getdata>>central[i];
      getdata>>min_all[i];
      getdata>>max_all[i];
      getdata>>min_sc[i];
      getdata>>max_sc[i];
      getdata>>min_mass[i];
      getdata>>max_mass[i];
      getdata>>min_pdf[i];
      getdata>>max_pdf[i];
    }

  double yieldBplus=0,yieldBzero=0,yieldBs=0;
  for(i=20;i<220;i++)
    {
      yieldBplus+=central[i]*(35.e-3)*0.401*208*6.09604e-5;
      yieldBzero+=central[i]*(35.e-3)*0.401*208*5.244e-5;
      yieldBs+=central[i]*(35.e-3)*0.105*208*2.89977e-5;
    }
  cout<<"Yield of Bp->Jpsi,K+: "<<yieldBplus<<endl;
  cout<<"Yield of B0->Jpsi,K*: "<<yieldBzero<<endl;
  cout<<"Yield of Bs->Jpsi,phi: "<<yieldBs<<endl;
}
