/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Dileptons Analysis Framework                                         **
**                                                                          **
** Constantin Heidegger, CERN, Summer 2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef DATASAMPLE_HH
#define DATASAMPLE_HH

#include "TROOT.h"
#include "TString.h"

#include "src/body_helper/Tools.cc"

enum SampleType {
	data,
	mc
};


class DataSample{

public:

	// Member Functions

	DataSample(TString, TString);
	virtual ~DataSample();
	void CheckFile(TString);
	void SetParametersFromInfoFile(TString);

	void SetCrossSection(float);
	void SetDataSetName(TString);
	void SetEventWeight(float);
	void SetLineColor(TString);
	void SetLineStyle(TString);
	void SetMaxEntries(Long64_t);
	void SetName(TString);
	void SetPath(TString);
	void SetTotEntries(Long64_t = 0);
	void SetType(SampleType);

	TString GetName();
	float GetEventWeight();
	TString GetDataSetName();
	TString GetPath();
	float GetCrossSection();
	SampleType GetType();
	TString GetLineColor();
	TString GetLineStyle();
	Long64_t GetTotEntries();
	Long64_t GetMaxEntries();

	void CloseTree();
	void GetTreeEntry(Long64_t);
	void OpenTree();
	
	TString Name;
	TString DataSetName;
	TString Path;
	TString CrossSection;
	SampleType Type;
	TString LineColor;
	TString LineStyle;
	Long64_t TotEntries;
	Long64_t MaxEntries;
	TFile * RootFile;
	TTree * RootTree;





	std::pair<TString , float> getNameAndXsec(TString file){
	// DATA SAMPLES
		if(file.Contains("DoubleMu"))
			return std::make_pair("doublemu", 1.);
		else if(file.Contains("DoubleElectron"))
			return std::make_pair("doubleelectron", 1.);
	// TTbar samples
		else if(file.Contains("TTJets") && file.Contains("MassiveB") )
			return std::make_pair("ttjets", 245.8);
		else if(file.Contains("TTJets") && file.Contains("SemiLept") )
			return std::make_pair("ttjets", 102.5);
		else if(file.Contains("TTJets") && file.Contains("FullLept") )
			return std::make_pair("ttjets", 24.6);
	// WJets samples
		else if(file.Contains("WJetsToLNu"))
			return std::make_pair("wjets", 37509.);
		else if(file.Contains("W1Jets"))
			return std::make_pair("w1jets", 6642.);
		else if(file.Contains("W2Jets"))
			return std::make_pair("w2jets", 2152.);
		else if(file.Contains("W3Jets"))
			return std::make_pair("w1jets", 638.4);
		else if(file.Contains("W4Jets"))
			return std::make_pair("w4jets", 263.2);
	// DYJets samples
		else if(file.Contains("DYJets") && file.Contains("M-50"))
			return std::make_pair("dyjets", 3504.);
		else if(file.Contains("DYJets") && file.Contains("M-10To50"))
			return std::make_pair("dyjets", 877.);
	// MuEnriched QCD
		else if(file.Contains("QCD") && file.Contains("Pt_20_MuEnrichedPt_15"))
			return std::make_pair("qcdmuenr", 3.64E8*3.7E-4);
		else if(file.Contains("QCD") && file.Contains("20to30_MuEnrichedPt5"))
			return std::make_pair("qcdmuenr", 2.87E8*0.0065);
		else if(file.Contains("QCD") && file.Contains("30to50_MuEnrichedPt5"))
			return std::make_pair("qcdmuenr", 6.609E7*0.0122);
		else if(file.Contains("QCD") && file.Contains("50to80_MuEnrichedPt5"))
			return std::make_pair("qcdmuenr", 8082000.0*0.0218);
	// EMEnriched
		else if(file.Contains("QCD") && file.Contains("Pt_20_30_EMEnriched"))
			return std::make_pair("qcdemenr", 2.886E8*0.0101);
		else if(file.Contains("QCD") && file.Contains("Pt_30_80_EMEnriched"))
			return std::make_pair("qcdemenr", 7.433E7*0.0621);
		else if(file.Contains("QCD") && file.Contains("Pt_80_170_EMEnriched"))
			return std::make_pair("qcdemenr", 1191000.0*0.1539);
	// BCTOE
		else if(file.Contains("QCD") && file.Contains("Pt_20_30_BCtoE"))
			return std::make_pair("qcdemenr", 2.886E8*5.8E-4);
		else if(file.Contains("QCD") && file.Contains("Pt_30_80_BCtoE"))
			return std::make_pair("qcdemenr", 7.433E7*0.00225);
		else if(file.Contains("QCD") && file.Contains("Pt_80_170_BCtoE"))
			return std::make_pair("qcdemenr", 1191000.0*0.0109);
	// RARES
		else if(file.Contains("TTWJets"))
			return std::make_pair("ttwjets", 232.);
		else{
			std::cout << "COULD NOT IDENTIFY SAMPLE FROM FILENAME. EXITING!" << std::endl; exit(-1);
		}
	}

private:
	
};


#endif
