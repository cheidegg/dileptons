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


#include "src/head/Dileptons.hh"
#include "src/head/AnalysisModules.hh"


using namespace std;



/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
AnalysisModules::AnalysisModules(TString configfile){
	/* 
	constructor AnalysisModules Class 
	parameters: configfile (path to configuration file)
	return: none
	*/

	Initialize();
	LoadConfigFile(configfile);

}


//____________________________________________________________________________
AnalysisModules::~AnalysisModules(){
	/* 
	destructor AnalysisModules Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void AnalysisModules::Initialize(){
	/*
	initializing AnalysisModules Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void AnalysisModules::LoadConfigFile(TString configfile){
	/*
	loading the configuration file
	parameters: configfile (path to the configuration file)
	return: none
	*/

	Dileptons::LoadConfigFile(configfile);

}


//____________________________________________________________________________
void AnalysisModules::RunAnalysis(){
	/*
	running the whole physics analysis
	parameters: none
	return: none
	*/


}


//____________________________________________________________________________
void AnalysisModules::RunModules(TString modules, TString modulegroup){
	/*
	running on selected modules
	parameters: none
	return: none
	*/


}



/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR DOING PHYSICS                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void AnalysisModules::FillFakeRatioMaps(AKROSD selection){
	/*
	produces all binned 2d Fake Ratio Maps for given kinematic selection
	parameters: none
	return: none
	*/




	for() { // loop over events

		float DeltaPhiAwayJetLepton = 0;
		int NumberOfElectrons       = 0;
		int NumberOfAwayJets        = 0;
		int NumberOfBJets           = 0;
		int NumberOfJets            = 0;
		int NumberOfLeptons         = 0;
		int NumberOfLooseElectrons  = 0;
		int NumberOfLooseLeptons    = 0;
		int NumberOfLooseMuons      = 0;
		int NumberOfMuons           = 0;
		int NumberOfTightElectrons  = 0;
		int NumberOfTightLeptons    = 0;
		int NumberOfTightMuons      = 0;
		int NumberOfVetoElectrons   = 0;
		int NumberOfVetoLeptons     = 0;
		int NumberOfVetoMuons       = 0;

		IndexOfAwayJet      .clear();
		IndexOfBJet         .clear();
		IndexOfClosestJet   .clear();
		IndexOfElectron     .clear();
		IndexOfJet          .clear();
		IndexOfLooseElectron.clear();
		IndexOfLooseMuon    .clear();
		IndexOfMuon         .clear();
		IndexOfTightElectron.clear();
		IndexOfTightMuon    .clear();
		IndexOfVetoElectron .clear();
		IndexOfVetoMuon     .clear();
	
		if(Dileptons::KinematicRegionSelection(mrstring)) {

			Dileptons::KinematicObjectSelection(tmstring);
		}
	}
}



//____________________________________________________________________________
void AnalysisModules::FillControlPlots(AKROSD selection){
	/*
	produces all control quantity plots for given kinematic selection
	parameters: none
	return: none
	*/

	

}


