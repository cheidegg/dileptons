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

#ifndef DILEPTONS_HH
#define DILEPTONS_HH

#include "TMath.h"
#include "TString.h"
#include "TObject.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TROOT.h"
#include "TVirtualPad.h"
#include "TLorentzVector.h"
#include "TPaveStats.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <map>
#include <time.h> // access to date/time

#include "src/head/Base.hh"
#include "src/helper/AnalysisTools.hh"
#include "src/helper/CustomTypes.hh"
#include "src/helper/DataSample.hh"
#include "src/helper/Debug.hh"
#include "src/helper/H1D.hh"
#include "src/helper/H2D.hh"
#include "src/helper/OtherInput.hh"
#include "src/helper/OtherOutput.hh"
#include "src/helper/Tools.hh"
#include "src/helper/Verbose.hh"



class Dileptons: public Base{

public:


	// Member Functions

	Dileptons();
	Dileptons(TString);
	virtual ~Dileptons();
	virtual void Initialize();
	bool CheckAKROSDStringForDefinedVariables(Label, AKROSD, std::vector<Label>, std::vector<Label>);
	bool CheckAKROSDStringForEventSelection(AKROSD, std::vector<Label>, std::vector<Label>);
	bool CheckAKROSDStringForObjectSelection(Label, AKROSD, std::vector<Label>, std::vector<Label>);
	void CheckConfiguration();
	void CheckResources();
	void CloseRootTree();
	void CreateTemporaryConfigurationFile(TString);
	void CreateOutputStructure();
	void EndDileptons();
	void FillEventList();
	void FinalizeOutput();
	int GetKinematicObjectIteratorByLabel(Label);
	TString GetKinematicObjectTypeByLabel(Label);
	TString GetOutputContent(Label, Label);
	TString GetOutputContent(Label, Label, Label);
	TString GetOutputContent(Label, Label, Label, Label);
	TString GetOutputFolder(int);
	TString GetOutputName(int, OutputType, TString, Label = "multiple", Label = "none");
	void LoadConfigurationFile(TString);
	void OpenRootTree(TString);
	void SetConfigplot(TString);
	void SetVersion();
	void StartDileptons(TString);
	void TagCode();
	void UseConfigurationVariables();

	Label GetAKROSDLabelInStatement(AKROSD);
	std::vector<Label> GetAKROSDLabelsInIfThElStatement(AKROSD);
	std::vector<AKROSD> GetAKROSDStatements(AKROSD, AKROSD = ",", AKROSD = "|");
	std::vector<float> GetAnalysisToolsArgumentList(Label);
	std::vector<float> GetVectorOfParseResults(AKROSD, std::vector<AKROSD>, int = 0);
	AKROSD InterpretAKROSDBrackets(AKROSD, Label);
	AKROSD InterpretAKROSDIfThElStatements(AKROSD, Label);
	AKROSD InterpretAKROSDRangeStatements(AKROSD, Label);
	AKROSD NegateAKROSDRegularStatement(AKROSD);
	bool ParseAKROSDCombinedRegularStatements(AKROSD, Label = "");
	bool ParseAKROSDOperation(AKROSD, AKROSD = "", float = 0.);
	bool ParseAKROSDRegularStatement(AKROSD, Label = "");
	bool ParseAKROSDString(AKROSD, Label = "");
	float ParseAKROSDVariable(AKROSD, int = -1, int = 0, float = 0.);	
	AKROSD RemoveAKROSDStatements(AKROSD, AKROSD);
	AKROSD SortAKROSDStatements(AKROSD);

	void CollectBasicKinematicObjects();
	void CollectElectrons(Label, AKROSD);
	void CollectJets(Label, AKROSD);
	void CollectKinematicObjects(Label, AKROSD);
	void CollectSelectedKinematicObjects();
	void CollectMuons(Label, AKROSD);
	void CollectPhotons(Label, AKROSD);
	void CollectTaus(Label, AKROSD);

	void CountBasicKinematicObjects();
	void CountKinematicObjects(Label);
	void CountSelectedKinematicObjects();
	
	int FindKinematicObjects(AKROSD);
	bool RecreateDefinedVariable(Label);
	void ResetDefinedVariables();
	void ResetKinematicObjects();

	std::vector<float> ParseVariableDefinition(AKROSD, int = 0);
	bool ParseEventSelection(AKROSD);
	bool ParseObjectSelection(AKROSD, Label);
	void PrepareEventSelection();






	// Configuration File Variables

	TString cUserName;
	TString cInputPath;
	TString cOutputPath;
	TString cAFSPath;
	DileptonsVerbose cVerbose;
	DileptonsMode cMode;
	DileptonsRunOn cRunOn;
	TString cModules;
	int cModuleList;
	float cLuminosity;
	int cJetEnergyCorrection;
	bool cPileUpReweighting;
	std::map <Label, AKROSD> cDefinedVariableDefinitions;
	std::map <Label, AKROSD> cEventSelectionDefinitions;
	std::map <Label, AKROSD> cObjectSelectionDefinitions;
	std::map <Label, DataSample*> cSamples;


	// Folders and Files

	TString kAFSFolder;
	TString kInfoFolder;
	TString kInputFolder;
	TString kOutputFolder;
	TString kTemplateFolder;
	TString kTemporaryFolder;

	TString kInfoFileBasicKinematicObjects; 
	TString kInfoFileDataSamples;     
	TString kInfoFileErrorMessages;
	TString kInfoFileKinematicElectronVariables;
	TString kInfoFileKinematicEventVariables;
	TString kInfoFileKinematicJetVariables;
	TString kInfoFileKinematicMuonVariables;
	TString kInfoFileKinematicPhotonVariables; 
	TString kInfoFileKinematicTauVariables; 
	TString kInfoFileModuleGroups;
	TString kInfoFileModuleList;
	TString kInfoFileModuleListAnalysis;
	TString kInfoFileSystemMessages;

	TString kTemplateFileIndexConfigplots;
	TString kTemplateFileIndexModules;
	TString kTemplateFileIndexPlots;
	TString kTemplateFileTag;
	TString kTemplateFileVersion;

	TString kTemporaryFileConfiguration;
	TString kTemporaryFileLog;
	TString kTemporaryFileTag;


	// Other Member Variables

	TString kConfigplot;
	TTree * kRootTree;
	Verbose * kVerbose;
	TString kVersion;

	std::vector <int> kModules;
	std::vector <std::pair<Label, TString> > kBasicKinematicObjects;
	std::map <Label, std::vector<int> > kKinematicObjects;
	std::map <Label, int> kNumberOfKinematicObjects;

	//std::map <Label, std::vector<Electron> > kSelectedElectrons;
	//std::map <Label, std::vector<Jet> >      kSelectedJets;
	//std::map <Label, std::vector<Muon> >     kSelectedMuons;
	//std::map <Label, std::vector<Photon> >   kSelectedPhotons;
	//std::map <Label, std::vector<Tau> >      kSelectedTaus;

	std::map <Label, std::vector<float> > kDefinedVariables;

	std::vector<std::vector<std::map<AKROSD, int> > > kEventCountCache;
	std::vector<std::vector<TString> > kEventListsCache;
	std::vector<std::vector<TTree*> > kEventTreeCache;
	std::vector<std::vector<std::vector<H1D*> > > kH1DCache;
	std::vector<std::vector<std::vector<H2D*> > > kH2DCache;
	std::vector<std::map<Label, std::map<AKROSD, int> > > kObjectCountCache;

	int kElectronIterator;
	int kJetIterator;
	int kMuonIterator;
	int kPhotonIterator;
	int kSampleIterator;
	int kSelectionIterator;
	int kTauIterator;
	int kVariableIterator;


};


#endif
