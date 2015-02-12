void subsetdata() {
  //  gSystem->Load("$ROOTSYS/test/libEvent");

  //Get old file, old tree and set top branch address
  TFile *oldfile = new TFile("/data/dmeson/Ntuple/Dmesonana_Rereco_MBtrig_d0pt4p5_nodalphacuts_pt1p5_tight_3lumi_0131_part1_fortmva.root");
  TTree *oldtree = (TTree*)oldfile->Get("recodmesontree");
  Long64_t nentries = oldtree->GetEntries();

  Long64_t newentries = nentries/10;
  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile("smalldata.root","recreate");
  TTree *newtree = oldtree->CloneTree(newentries);
  newtree->Print();
  newtree->AutoSave();
  delete oldfile;
  delete newfile;
}
