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


#include "src/head/Sketches.hh"




/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
Sketches::Sketches(TString configuration_file){
	/* 
	constructs the Sketches Class 
	parameters: configuration_file (path to configuration file)
	return: none
	*/

	Initialize();
	StartDileptons(configuration_file);

}


//____________________________________________________________________________
Sketches::~Sketches(){
	/* 
	destructs the Sketches Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void Sketches::Initialize(){
	/*
	initializes the Sketches Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void Sketches::CallSketchByID(int sketch_id){
	/*
	calls the sketch given by the sketch ID
	parameters: sketch_id (unique number of the sketch)
	return: none
	*/

	// Since Sketches is daughter of AnalysisModules one would like to use the
	// function AnalysisModules::CallModuleByID() which basically does the same
	// as this function. However, AnalysisModules::CallModuleByID() calls 
	// only modules.

	switch(sketch_id){
		case 101: Sketch101Frame(); break;
		//case 102: Sketch102(); break;
		//case 103: Sketch103(); break;
		//case 104: Sketch104(); break;
		//case 105: Sketch105(); break;
		//case 106: Sketch106(); break;
		default : kVerbose -> Error(); break;
	}

}


//____________________________________________________________________________
void Sketches::EndDileptons(){
	/*
	ends dileptons, copies the outputs and tags the code
	parameters: none
	return: none
	*/
	
	Dileptons::EndDileptons();

}


//____________________________________________________________________________
void Sketches::RunSketches(){
	/*
	running on selected sketches given in kModules
	parameters: none
	return: none
	*/

	// Since Sketches is daughter of AnalysisModules one would like to use the
	// function AnalysisModules::RunModules() which basically does the same
	// as this function. However, AnalysisModules::RunModules() calls 
	// AnalysisModules::CallModuleByID() which executes only modules, not 
	// sketches.

	for(int i = 0; i< kModules.size(); ++i)
		CallSketchByID(kModules[i]);

}





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR DOING PHYSICS                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void Sketches::Sketch101Frame(){



}


//____________________________________________________________________________
void Sketches::Sketch101Kernel(float event_weight){
	/*
  	kernel to sketch 101
  	parameters: event_weight
  	return: none
  	*/


}






