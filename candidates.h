
#define XB 1000

int HLT_PAMu3_v1;
int size;
float mass[XB];
float mumumass[XB];
int Run;
float y[XB];
float pt[XB];
float trk1Pt[XB];
float trk2Pt[XB];
float gen[XB];

float d0[XB];
float d0Err[XB];
float tktkmass[XB];
float dtheta[XB];
float chi2cl[XB];
int isbestchi2[XB];

void setbranch(TTree* root)
{
  root->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
  root->SetBranchAddress("size",&size);
  root->SetBranchAddress("mumumass",mumumass);
  root->SetBranchAddress("mass",mass);
  root->SetBranchAddress("Run",&Run);
  root->SetBranchAddress("y",y);
  root->SetBranchAddress("pt",pt);
  root->SetBranchAddress("trk1Pt",trk1Pt);
  root->SetBranchAddress("trk2Pt",trk2Pt);
  root->SetBranchAddress("gen",gen);
  root->SetBranchAddress("d0",d0);
  root->SetBranchAddress("d0Err",d0Err);
  root->SetBranchAddress("tktkmass",tktkmass);
  root->SetBranchAddress("chi2cl",chi2cl);
  root->SetBranchAddress("dtheta",dtheta);
  root->SetBranchAddress("isbestchi2",isbestchi2);
}
