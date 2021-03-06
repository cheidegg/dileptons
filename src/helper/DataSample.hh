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

#include "TMath.h"

#include "TString.h"
#include "TObject.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TROOT.h"
#include "TVirtualPad.h"
#include "TLorentzVector.h"
#include "TPaveStats.h"

#include "src/head/Base.hh"
#include "src/helper/CustomTypes.hh"
#include "src/helper/OtherInput.hh"
#include "src/helper/Tools.hh"
#include "src/helper/Verbose.hh"



class DataSample: public Base{

public:

	// Member Functions

	DataSample(Label, std::string, std::string, Verbose*);
	virtual ~DataSample();
	virtual void Initialize();
	void CheckFile(std::string);
	void SetParametersFromInfoFile(Label, std::string, std::string);

	void SetCrossSection(float);
	void SetDataSetName(TString);
	void SetEventWeight(float);
	void SetLineColor(TString);
	void SetLineStyle(TString);
	void SetMaxEntries(Long64_t);
	void SetName(Label);
	void SetPath(TString);
	void SetTotEntries(Long64_t = 0);
	void SetType(SampleType);
	void SetTypeFromTString(TString);

	Label GetName();
	float GetEventWeight();
	TString GetDataSetName();
	TString GetPath();
	float GetCrossSection();
	TTree * GetTree();	
	SampleType GetType();
	TString GetLineColor();
	TString GetLineStyle();
	Long64_t GetTotEntries();
	Long64_t GetMaxEntries();

	void CloseTree();
	void OpenTree();


private:

	float kCrossSection;
	TString kDataSetName;
	float kEventWeight;
	TString kLineColor;
	TString kLineStyle;
	Long64_t kMaxEntries;
	Label kName;
	TString kPath;
	TFile * kRootFile;
	TTree * kRootTree;
	Long64_t kTotEntries;
	SampleType kType;
	Verbose * kVerbose;	


	
};


#endif
