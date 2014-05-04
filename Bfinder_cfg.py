# 2014Feb05   twang   fix HI MC HLT process name
# 2014Mar08   twang   add patMuonsWithTrigger
import FWCore.ParameterSet.Config as cms

### Run on MC?
runOnMC = True

### HI label?
HIFormat = True
#HIFormat = False

### Include SIM tracks for matching?
UseGenPlusSim = False

### Using pat muon with trigger or not
UsepatMuonsWithTrigger = True

process = cms.Process("demo")
process.load("FWCore.MessageService.MessageLogger_cfi")
### Set TransientTrackBuilder
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
### Set Geometry/GlobalTag/BField
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("Configuration.Geometry.GeometryIdeal_cff")
#process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")

### keep only Pat:: part
from PhysicsTools.PatAlgos.patEventContent_cff import *
### output module
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('test.root'),
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
    outputCommands = cms.untracked.vstring('drop *',
    )
)

### Set maxEvents
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

### Set global tag
if runOnMC:
    #process.GlobalTag.globaltag = cms.string( 'START53_V7F::All' )  #Summer12_DR53X
    #process.GlobalTag.globaltag = cms.string( 'STARTHI53_V26::All' )
    #process.GlobalTag.globaltag = cms.string( 'START52_V5::All' )
    #process.GlobalTag.globaltag = cms.string( 'START52_V7::All' )
    #process.GlobalTag.globaltag = cms.string( 'START53_V17::All' )
    #process.GlobalTag.globaltag = cms.string( 'START53_V27::All' )
    process.GlobalTag.globaltag = cms.string( 'STARTHI53_V27::All' )
else:
    #process.GlobalTag.globaltag = cms.string( 'FT_53_V6_AN2::All' ) #for 2012AB
    #process.GlobalTag.globaltag = cms.string( 'FT_53_V10_AN2::All' )#for 2012C
    #process.GlobalTag.globaltag = cms.string( 'FT_P_V42_AN2::All' ) #for 2012D
    #process.GlobalTag.globaltag = cms.string( 'GR_P_V43D::All' )
    process.GlobalTag.globaltag = cms.string( 'GR_P_V43F::All' )

### PoolSource will be ignored when running crab
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_9_1_EYe.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_208_1_lQS.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_214_1_NQ4.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_216_1_6tY.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_331_1_H5j.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_377_1_142.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_203_1_dHx.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_244_1_XYD.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_37_1_SsA.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_43_1_aER.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_70_1_QVp.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_77_1_zsq.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_89_1_Quu.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_87_1_0xn.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_207_1_nDN.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_550_1_huV.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_561_1_Jyt.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_646_1_sJT.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_705_1_nxk.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_710_1_UcM.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_98_1_WsA.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_175_1_JGR.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_210_1_6dq.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_222_1_yju.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_241_1_YHd.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_417_1_qfm.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_468_1_fcM.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_492_1_eKA.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_523_1_RK5.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_598_1_S8I.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_601_1_ppK.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_661_1_yuE.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_8_1_yVn.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_128_1_yP1.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_201_1_8hf.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_198_1_aP0.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_44_1_2Hd.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_167_1_ETy.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_195_1_pr9.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_235_1_OE0.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_278_1_S28.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_6_1_I9W.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_148_1_dow.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_249_1_tvt.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_312_1_lLE.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_389_1_IaQ.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_442_1_29f.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_514_1_hx9.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_640_1_JVs.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_152_1_me7.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_155_1_FFh.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_200_1_USm.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_67_1_E1X.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_166_1_vYW.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_205_1_R6v.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_282_1_qAE.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_431_1_b0y.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_484_1_4EZ.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_485_1_gEZ.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_508_1_Kjs.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_522_1_pFj.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_618_1_Rys.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_634_1_iKd.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_753_1_4Fr.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_36_1_vb4.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_45_1_ZCs.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_29_1_MNd.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_33_1_j8k.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_74_1_BdR.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_133_1_bUO.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_138_1_AQg.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_220_1_toh.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_237_1_RTU.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_250_1_mvU.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_299_1_cq1.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_353_1_Tf6.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_366_1_D7U.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_439_1_TEH.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_32_1_2Ca.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_81_1_wQO.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_103_1_PQ0.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_35_1_Mn7.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_28_1_udM.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_68_1_WnW.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_161_1_POg.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_416_1_joj.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_481_1_FKV.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_728_1_mlL.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_742_1_7Hp.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_778_1_VYI.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_788_1_TWj.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_847_1_U00.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_920_1_PS0.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_53_1_zPz.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_169_1_Vbn.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_334_1_XDD.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_384_1_Igc.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_466_1_8zb.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_654_1_r2G.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_988_1_Khv.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_97_1_Qk7.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_171_1_k9Z.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_240_1_wsP.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_493_1_iow.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_488_1_3Ey.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_19_1_18T.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_82_1_h8s.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_183_1_jk6.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_287_1_Vnh.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_316_1_W2P.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_432_1_qwt.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_449_1_ACz.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_462_1_4Fw.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_489_1_XcC.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_574_1_jS8.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_570_1_mh2.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_635_1_gga.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_643_1_BTn.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_694_1_dJj.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_712_1_5BB.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_845_1_UAh.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_918_1_0PE.root",
 "root://cluster142.knu.ac.kr//store/user/hckim/Hijing_PPb502_MinimumBias/HIJINGemb_BsJpsiPhi_5TeV_boostPbp_RECO_part/e660cc237a5ddba47e5792715ce31f6d/HIJINGemb_BsJpsiPhi_TuneZ2star_5TeV_boostPbp_RECO_STARTHI53_V27_evt100_1000_1_zFV.root"
   )
)
#process.load("_eos_cms_store_user_twang_HIBmeson_20131220_test_20140106_JpsiKp_cff")

### Set basic filter
process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
        #vertexCollection = cms.InputTag('offlinePrimaryVertices'),
        vertexCollection = cms.InputTag('offlinePrimaryVerticesWithBS'),
        minimumNDOF = cms.uint32(4) ,
        maxAbsZ = cms.double(24),
        maxd0 = cms.double(2)
)

process.noscraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
        debugOn = cms.untracked.bool(False),
        numtrack = cms.untracked.uint32(10),
        thresh = cms.untracked.double(0.25)
)

#process.filter = cms.Sequence(process.primaryVertexFilter+process.noscraping)
process.filter = cms.Sequence(process.noscraping)

##Producing Gen list with SIM particles
process.genParticlePlusGEANT = cms.EDProducer("GenPlusSimParticleProducer",
        src           = cms.InputTag("g4SimHits"), # use "famosSimHits" for FAMOS
        setStatus     = cms.int32(8),             # set status = 8 for GEANT GPs
        filter        = cms.vstring("pt > 0.0"),  # just for testing (optional)
            genParticles   = cms.InputTag("genParticles") # original genParticle list
)

### Setup Pat
### Ref: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATMCMatching
process.load("PhysicsTools.PatAlgos.patSequences_cff")
if HIFormat:
        process.muonMatch.matched = cms.InputTag("hiGenParticles")
        process.genParticlePlusGEANT.genParticles = cms.InputTag("hiGenParticles")

##Using GEN plus SIM list for matching
if UseGenPlusSim:
        process.muonMatch.matched = cms.InputTag("genParticlePlusGEANT")

#process.allLayer1Jets.addJetCorrFactors = False
from PhysicsTools.PatAlgos.tools.trackTools import *
#process.load( 'PhysicsTools.PatAlgos.mcMatchLayer0.muonMatch_cff' )

if runOnMC:
    makeTrackCandidates(process,              # patAODTrackCands
        label='TrackCands',                   # output collection will be 'allLayer0TrackCands', 'allLayer1TrackCands', 'selectedLayer1TrackCands'
        tracks=cms.InputTag('generalTracks'), # input track collection
        particleType='pi+',                   # particle type (for assigning a mass)
        preselection='pt > 0.3',              # preselection cut on candidates. Only methods of 'reco::Candidate' are available
        selection='pt > 0.3',                 # Selection on PAT Layer 1 objects ('selectedLayer1TrackCands')
        isolation={},                         # Isolations to use ('source':deltaR; set to {} for None)
        isoDeposits=[],
        mcAs='muon'                           # Replicate MC match as the one used for Muons
    );                                        # you can specify more than one collection for this
    ### MC+mcAs+Match/pat_label options
    #process.patTrackCandsMCMatch.matched = cms.InputTag("hiGenParticles")
    process.patTrackCandsMCMatch.resolveByMatchQuality = cms.bool(True)
    process.patTrackCandsMCMatch.resolveAmbiguities = cms.bool(True)
    process.patTrackCandsMCMatch.checkCharge = cms.bool(True)
    process.patTrackCandsMCMatch.maxDPtRel = cms.double(0.5)
    process.patTrackCandsMCMatch.maxDeltaR = cms.double(0.7)
    process.patTrackCandsMCMatch.mcPdgId = cms.vint32(111, 211, 311, 321)
    process.patTrackCandsMCMatch.mcStatus = cms.vint32(1)
    l1cands = getattr(process, 'patTrackCands')
    l1cands.addGenMatch = True

else :
    makeTrackCandidates(process,              # patAODTrackCands
        label='TrackCands',                   # output collection will be 'allLayer0TrackCands', 'allLayer1TrackCands', 'selectedLayer1TrackCands'
        tracks=cms.InputTag('generalTracks'), # input track collection
        particleType='pi+',                   # particle type (for assigning a mass)
        preselection='pt > 0.3',              # preselection cut on candidates. Only methods of 'reco::Candidate' are available
        selection='pt > 0.3',                 # Selection on PAT Layer 1 objects ('selectedLayer1TrackCands')
        isolation={},                         # Isolations to use ('source':deltaR; set to {} for None)
        isoDeposits=[],
        mcAs=None                             # Replicate MC match as the one used for Muons
    );                                        # you can specify more than one collection for this
    l1cands = getattr(process, 'patTrackCands')
    l1cands.addGenMatch = False
from PhysicsTools.PatAlgos.tools.coreTools import *
removeAllPATObjectsBut(process, ['Muons'])
#removeSpecificPATObjects(process, ['Jets'])

if not runOnMC :
        removeMCMatching(process, ['All'] )
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
###Criterias from Hyunchul's
process.muonL1Info.maxDeltaR = 0.3
process.muonL1Info.fallbackToME1 = True
process.muonMatchHLTL1.maxDeltaR = 0.3
process.muonMatchHLTL1.fallbackToME1 = True
process.muonMatchHLTL2.maxDeltaR = 0.3
process.muonMatchHLTL2.maxDPtRel = 10.0
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0
process.muonMatchHLTCtfTrack.maxDeltaR = 0.1
process.muonMatchHLTCtfTrack.maxDPtRel = 10.0
process.muonMatchHLTTrackMu.maxDeltaR = 0.1
process.muonMatchHLTTrackMu.maxDPtRel = 10.0

### Set Bfinder option
process.demo = cms.EDAnalyzer('Bfinder',
        Bchannel                = cms.vint32(
                1,#RECONSTRUCTION: J/psi + K
                1,#RECONSTRUCTION: J/psi + Pi
                1,#RECONSTRUCTION: J/psi + Ks
                1,#RECONSTRUCTION: J/psi + K* (K+, Pi-)
                1,#RECONSTRUCTION: J/psi + K* (K-, Pi+)
                1,#RECONSTRUCTION: J/psi + phi
                1,),#RECONSTRUCTION: J/psi + pi pi <= psi', X(3872), Bs->J/psi f0
        HLTLabel        = cms.InputTag('TriggerResults::HLT'),
    GenLabel        = cms.InputTag('genParticles'),
        MuonLabel       = cms.InputTag('selectedPatMuons'),         #selectedPatMuons
        TrackLabel      = cms.InputTag('selectedPatTrackCands'),    #selectedPat
    PUInfoLabel     = cms.InputTag("addPileupInfo"),
    BSLabel     = cms.InputTag("offlineBeamSpot"),
    PVLabel     = cms.InputTag("offlinePrimaryVerticesWithBS")
)
if HIFormat:
        process.demo.GenLabel = cms.InputTag('hiGenParticles')

if UseGenPlusSim:
        process.demo.GenLabel = cms.InputTag('genParticlePlusGEANT')

if UsepatMuonsWithTrigger:
        process.demo.MuonLabel = cms.InputTag('patMuonsWithTrigger')
        if runOnMC:
                addMCinfo(process)

### SetUp HLT info
process.load('Bfinder.HiHLTAlgos.hltanalysis_cff')
process.hltanalysis.dummyBranches = cms.untracked.vstring()
#if HIFormat:
        #process.hltanalysis.HLTProcessName = cms.string("HISIGNAL")
        #process.hltanalysis.hltresults = cms.InputTag("TriggerResults","","HISIGNAL")
        #process.hltanalysis.l1GtObjectMapRecord = cms.InputTag("hltL1GtObjectMap::HISIGNAL")
process.hltAna = cms.Path(process.filter*process.hltanalysis)

### Set output
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Bfinder_all.root')
)

if runOnMC:
        process.patDefaultSequence *= process.genParticlePlusGEANT

if UsepatMuonsWithTrigger:
        process.patDefaultSequence *= process.patMuonsWithTriggerSequence

process.p = cms.Path(
        process.filter*process.patDefaultSequence*process.demo
)

process.schedule = cms.Schedule(
        process.p
        ,process.hltAna
)
