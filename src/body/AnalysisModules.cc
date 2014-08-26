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
void AnalysisModules::CopyOutputOnAFSWebspace(){
	/*
	copies configplot and modules onto AFS webspace
	parameters: configfile (path to the configuration file)
	return: none
	*/

	Dileptons::CopyOutputOnAFSWebspace();

}


//____________________________________________________________________________
void AnalysisModules::TagCode(TString version, TString configplot){
	/*
	uses the template tag.sh to create a lightweight tag automatically after running
	the code
	 paramters: version (current version number), configplot (current configplot)
	return: none
	*/

	Dileptons::TagCode(version, configplot);

}


//____________________________________________________________________________
void AnalysisModules::RunAnalysis(){
	/*
	running the whole physics analysis
	parameters: none
	return: none
	*/

	// read from info file

	RunModules("11, 12, 14, 15, 16");

}


//____________________________________________________________________________
void AnalysisModules::RunModules(TString module_ids, int module_group = 0){
	/*
	running on selected modules
	parameters: none
	return: none
	*/

	if(module_group > 0) {



	}

	std::vector<int> modules = Tools::ConvertTStringVectorToIntVector(Tools::ExplodeTString(module_ids,","));

	for(int i = 0; i < modules.size(); ++i) 
		CallModuleByID(modules[i]);

}


//____________________________________________________________________________
bool AnalysisModules::CallModuleByID(int module_id){

	// maybe add error message here if module returned false?

	switch(module_id){
		case 11: return Module11();
		case 12: return Module12();
		case 13: return Module13();
		case 14: return Module14();
		case 15: return Module15();
		case 16: return Module16();
	}

}


//____________________________________________________________________________
void AnalysisModules::LoopOverEntries(bool (*function)(), DataSample sample){
	/*
	performs a loop over the maximum number of entries in the sample and
	calls a specific function every iteration
	parameters: *function (pointer to the function to be called), sample (data sample)
	return: none
	*/ 
	
	for(Long64_t entry = 0; entry < sample.GetMaxEntries(); ++entry) {

		sample.GetTreeEntry(entry);
		function();

	}

}


//____________________________________________________________________________
void AnalysisModules::LoopOverSamples(bool (*function)(), std::vector<DataSample> samples){
	/*
	loops over all data samples in a vector, opens the respective trees, sets
	the event weight and calls a given function every iteration
	parameters: *function (pointer to the function to be called), samples (vector of data samples)
	return: none
	*/

	for(int i = 0; i < samples.size(); ++i) {

		sample[i].OpenTree();
		sample[i].SetEventWeight(cLuminosity);
		LoopOverEntries(function, sample[i]);
		sample[i].CloseTree();

	}
}



/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR DOING PHYSICS                                          **
******************************************************************************
*****************************************************************************/


bool AnalysisModules::Module11(){

	gather AKROSD
	define outputs
	open outputs
	open tree to write on

	LoopOverSamples(function, samples);

	write and save outputs	


}





