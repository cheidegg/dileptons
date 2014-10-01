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

#ifndef ANALYSISMODULES_HH
#define ANALYSISMODULES_HH

#include "src/head/Dileptons.hh"



class AnalysisModules: public Dileptons {

public:


	// Member Functions

	AnalysisModules();
	AnalysisModules(TString);
	virtual ~AnalysisModules();
	virtual void Initialize();

	void CallModuleByID(int);
	void EndDileptons();
	void RunModules();
	void LoopOverEntries(void (AnalysisModules::*)(float), Label);
	void LoopOverEntries(void (AnalysisModules::*)(float), Label, std::vector<Label>);
	void LoopOverSamples(void (AnalysisModules::*)(float), std::vector<Label>, std::vector<Label>);
	void DefineOutputCache(int, std::vector<Label>, std::vector<Label>, std::vector<Label>, std::vector<Label>);
	void WriteOutputCache(int, std::vector<Label>, std::vector<Label>);

	void Module11Frame();
	void Module11Kernel(float);
	void Module12Frame();
	void Module12Kernel(float);
	void Module13Frame();
	void Module13Kernel(float);



private:


	Long64_t kEntryIterator;
	
};


#endif
