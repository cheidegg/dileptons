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





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
AnalysisModules::AnalysisModules(){
	/* 
	constructs the AnalysisModules Class 
	parameters: configuration_file (path to configuration file)
	return: none
	*/

	kVerbose -> Class("AnalysisModules");
	Initialize();

}


//____________________________________________________________________________
AnalysisModules::AnalysisModules(TString configuration_file){
	/* 
	constructs the AnalysisModules Class 
	parameters: configuration_file (path to configuration file)
	return: none
	*/

	kVerbose -> Class("AnalysisModules");
	Initialize();
	Dileptons::StartDileptons(configuration_file);

}


//____________________________________________________________________________
AnalysisModules::~AnalysisModules(){
	/* 
	destructs the AnalysisModules Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void AnalysisModules::Initialize(){
	/*
	initializes the AnalysisModules Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void AnalysisModules::CallModuleByID(int module_id){
	/*
	calls the module given by the module ID
	parameters: module_id (unique number of the module)
	return: none
	*/

	switch(module_id){
		case 11: Module11Frame(); break;  
		case 12: Module12Frame(); break; 
		case 13: Module13Frame(); break; 
		//case 14: Module14Frame(); break; 
		//case 15: Module15Frame(); break; 
		//case 16: Module16Frame(); break; 
		default: kVerbose->Error(); break;
	}

}


//____________________________________________________________________________
void AnalysisModules::EndDileptons(){
	/*
	ends dileptons, copies the outputs and tags the code
	parameters: none
	return: none
	*/

	Dileptons::EndDileptons();

}


//____________________________________________________________________________
void AnalysisModules::RunModules(){
	/*
	running on selected modules given in kModules
	parameters: none
	return: none
	*/


	for(int i = 0; i < kModules.size(); ++i){
		kVerbose -> Module();
		CallModuleByID(kModules[i]);
	}

}


//____________________________________________________________________________
void AnalysisModules::LoopOverEntries(void (AnalysisModules::*kernel)(float), Label sample_key){
	/*
	performs a loop over the maximum number of entries in the sample and
	calls a specific kernel function every iteration
	parameters: *kernel (pointer to the kernel function to be called), sample_index
	return: none
	*/ 

	// loop over entries	
	for(kEntryIterator = 0; kEntryIterator < cSamples[sample_key] -> GetMaxEntries(); ++kEntryIterator) {
		
		// get tree entry, i.e. load branches
		kRootTree -> GetEntry(kEntryIterator);

		// get event weight, PU reweight it if needed 
		float event_weight = cSamples[sample_key] -> GetEventWeight();
		if(cPileUpReweighting) event_weight *= PUWeight;

		// call the kernel
		(this->*kernel)(event_weight);
	}

}


//____________________________________________________________________________
void AnalysisModules::LoopOverEntries(void (AnalysisModules::*kernel)(float), Label sample_key, std::vector<Label> selection_keys){
	/*
	performs a loop over the maximum number of entries in the sample and
	calls a specific kernel function every iteration
	parameters: *kernel (pointer to the kernel function to be called), sample (data sample),
	            selections (given event selections)
	return: none
	*/ 


	// loop over entries
	for(kEntryIterator = 0; kEntryIterator < cSamples[sample_key] -> GetMaxEntries(); ++kEntryIterator) {

		//std::cout << "loading entries " << kEntryIterator << ": ";

		// get tree entry, i.e. load branches
		kRootTree -> GetEntry(kEntryIterator);

		// get event weight, PU reweight it if needed 
		float event_weight = cSamples[sample_key] -> GetEventWeight();
		if(cPileUpReweighting) event_weight *= PUWeight;

		// prepare event selection
		PrepareEventSelection();

		//std::cout << "(#LM=" << kNumberOfKinematicObjects["LM"] << ", " << kNumberOfKinematicObjects["LE"]<< ", " << std::endl;
			
		// we reset the selection iterator to -1, since we increment it at the beginning of the loop
		kSelectionIterator = -1;

		// loop over selections
		for(std::map<Label, AKROSD>::iterator i = cEventSelectionDefinitions.begin(); i != cEventSelectionDefinitions.end(); ++i){

			// selection is used
			if(Tools::FindElementInVector(selection_keys, i -> first)) {
				++kSelectionIterator;

				//Label key = "NLL";
				bool return_value = ParseEventSelection(i -> second);

				//std::cout << Tools::FindElementInMapByKey(kDefinedVariables, key) << ") " << std::endl;
				//std::cout << kDefinedVariables["NLL"].size() << ") " << std::endl;

				// parse event selection, if true we fill event list, event tree (later) and call the kernel
				if(return_value){
					FillEventList();
					(this->*kernel)(event_weight);
				}
			}
		}
	}
}


//____________________________________________________________________________
void AnalysisModules::LoopOverSamples(void (AnalysisModules::*kernel)(float), std::vector<Label> sample_keys, std::vector<Label> selection_keys){
	/*
	loops over all data samples in a vector, opens the respective trees, sets
	the event weight and calls a given kernel function every iteration
	parameters: *kernel (pointer to the kernel function to be called), samples 
	            (vector of data samples), selections (given event selections)
	return: none
	*/


	// loop over samples
	for(kSampleIterator = 0; kSampleIterator < sample_keys.size(); ++kSampleIterator) {

		// open file
		kVerbose -> Sample(sample_keys[kSampleIterator]);
		TFile * root_file = TFile::Open(cSamples[sample_keys[kSampleIterator]] -> GetPath());
		if(root_file == NULL) kVerbose -> ErrorAndExit();
		
		// open tree
		kRootTree = (TTree *) root_file -> Get("Analysis");
		kRootTree -> ResetBranchAddresses();
		Base::Initialize(kRootTree);

		// set event weight
 		cSamples[sample_keys[kSampleIterator]] -> SetEventWeight(cLuminosity);

		// loop over entries
		std::cout << "going to loop over entries" << std::endl;
		if(selection_keys.size()>0) LoopOverEntries(kernel, sample_keys[kSampleIterator], selection_keys);
		else                        LoopOverEntries(kernel, sample_keys[kSampleIterator]); 

		// delete the tree from the memory again
		kRootTree -> Delete();
		
	}
}


//____________________________________________________________________________
void AnalysisModules::DefineOutputCache(int module_id, std::vector<Label> sample_names, std::vector<Label> selection_names, std::vector<Label> h1d_names, std::vector<Label> h2d_names){
	/*
	reserves the memory for all caches needed in the module
	parameters: module_id, sample_names, selection_names, h1d_names, h2d_names
	return: none
	*/

	TString output_folder = GetOutputFolder(module_id);
	

	// if there are no samples and no selections given, then there
	// is no cache needed

	if(sample_names.size() == 0 || selection_names.size() == 0) return;


	// reset the full cache

	kEventCountCache .clear();
	kEventListsCache .clear();
	kH1DCache        .clear();
	kH2DCache        .clear();
	kObjectCountCache.clear();


	// one column for every sample

	kEventCountCache .resize(sample_names.size());
	kEventListsCache .resize(sample_names.size());
	kH1DCache        .resize(sample_names.size());
	kH2DCache        .resize(sample_names.size());
	kObjectCountCache.resize(sample_names.size());


	// loop over samples
	for(int i = 0; i < sample_names.size(); ++i){

		// one column for every selection

		kEventCountCache[i] .resize(selection_names.size());
		kEventListsCache[i] .resize(selection_names.size(), "");
		kH1DCache[i]        .resize(selection_names.size());
		kH2DCache[i]        .resize(selection_names.size());


		// loop over selections
		for(int j = 0; j < selection_names.size(); ++j) {
			
			// 1d histograms
			if(h1d_names.size() > 0){
				kH1DCache[i][j].resize(h1d_names.size());
				for(int k = 0; k < h1d_names.size(); ++k){
					kH1DCache[i][j][k] = new H1D(GetTimeDifferenceMS(), kVerbose);
					kH1DCache[i][j][k] -> SetMajorParameters(output_folder, GetOutputName(module_id, histogram, h1d_names[k], sample_names[i], selection_names[j]));
				}
			}

			// 2d histograms
			if(h2d_names.size() > 0){
				kH2DCache[i][j].resize(h2d_names.size());
				for(int k = 0; k < h2d_names.size(); ++k){
					kH2DCache[i][j][k] = new H2D(GetTimeDifferenceMS(), kVerbose);
					kH2DCache[i][j][k] -> SetMajorParameters(output_folder, GetOutputName(module_id, histogram, h2d_names[k], sample_names[i], selection_names[j]));
				}
			}
		}
	}
}


//____________________________________________________________________________
void AnalysisModules::WriteOutputCache(int module_id, std::vector<Label> sample_names, std::vector<Label> selection_names){
	/*
  	writes standard output for a module with samples and event selections
  	parameters: module_id, sample_names, selection_names
  	return: none
  	*/

	TString output_folder = GetOutputFolder(module_id);


	// loop over samples	
	for(int i = 0; i < sample_names.size(); ++i){

		// write object counts
		for(std::map<Label, std::map<AKROSD, int> >::iterator k = kObjectCountCache[i].begin(); k != kObjectCountCache[i].end(); ++k){
			TString obj_name = Tools::ConvertStdStringToTString("objcount_" + Tools::ConvertTStringToStdString(k->first));
			OtherOutput::WriteToTextFile(output_folder, GetOutputName(module_id, text, obj_name, sample_names[i]), Tools::PrintContentsOfMap(k->second));
		}

		// loop over event selections
		for(int j = 0; j < selection_names.size(); ++j){
			
			// write event counts and event lists
			OtherOutput::WriteToTextFile(output_folder, GetOutputName(module_id, text, "evtcount", sample_names[i], selection_names[j]), Tools::PrintContentsOfMap(kEventCountCache[i][j]));
			OtherOutput::WriteToTextFile(output_folder, GetOutputName(module_id, list, "evtlist", sample_names[i], selection_names[j]), kEventListsCache[i][j]);
	
			// write 1d histograms
			for(int k = 0; k < kH1DCache[0][0].size(); ++k)
				kH1DCache[i][j][k] -> Write(kCanvas);
			
			// write 2d histograms
			for(int k = 0; k < kH2DCache[0][0].size(); ++k){
				kCanvas -> ls();
				kH2DCache[i][j][k] -> Write(kCanvas);
			}
		}

		// print all H1D and H2D histograms in a single root file
	}
}



/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR DOING PHYSICS                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void AnalysisModules::Module11Frame(){
	/*
  	fills the fake ratio maps for the measurement regions
 	parameters: none
 	return: none
 	*/
	

	// samples, event selections, 1d histograms and 2d histograms
	
	std::vector<Label> h1ds;
	std::vector<Label> h2ds;
	std::vector<Label> samples;
	std::vector<Label> selections;
	std::vector<Label> slist;


	// data samples

	slist.push_back("qcdmu20.");
	slist.push_back("dyjll10");
	slist.push_back("dyjll50");
	slist.push_back("wjlnu");

	samples = Tools::GetVectorFromMapKeys(Tools::GetSubSetOfMapByKeys(cSamples, slist));


	// event selections
	
	selections = Tools::GetVectorFromMapKeys(Tools::GetSubSetOfMapByKeys(cEventSelectionDefinitions, "MR"));

	
	// 1d histograms
	
	// none

	
	// 2d histograms	
	
	h2ds.push_back(GetOutputContent("#LM", "LM.PT", "LM.ETA"));
	h2ds.push_back(GetOutputContent("#TM", "TM.PT", "TM.ETA"));
	h2ds.push_back(GetOutputContent("FR" , "TM.PT", "TM.ETA"));
	

	// Defining all outputs

	DefineOutputCache(11, samples, selections, h1ds, h2ds);


	// Set histogram binning
	
	double FR_bins_eta[6]     = {0., 0.5, 1., 1.5, 2., 2.5};
	double FR_bins_pt[9]      = {10., 15., 20., 25., 30., 35., 40., 45., 50.};

	for(int i = 0; i < samples.size(); ++i){
		for(int j = 0; j < selections.size(); ++j){
			for(int k = 0; k < h2ds.size(); ++k)
				kH2DCache[i][j][k] -> SetBins(Tools::ConvertArrayToVector(FR_bins_pt), Tools::ConvertArrayToVector(FR_bins_eta));
		}
	}
			

	// Loop over samples

	LoopOverSamples(&AnalysisModules::Module11Kernel, samples, selections);


	// Divide histograms to fill fake ratio map

	for(int i = 0; i < samples.size(); ++i)
		for(int j = 0; j < selections.size(); ++j)
			kH2DCache[i][j][2] -> Divide(kH2DCache[i][j][0]);


	// Write histograms and outputs to disk

	WriteOutputCache(11, samples, selections);


	// Save fake ratio map in member variable

	
}


//____________________________________________________________________________
void AnalysisModules::Module11Kernel(float event_weight){
	/*
  	kernel to module 12
  	parameters: event_weight
  	return: none
  	*/

	
	// variables of kinematic object "LM"

	for(int i = 0; i < kNumberOfKinematicObjects["LM"]; ++i){
		kH2DCache[kSampleIterator][kSelectionIterator][0] -> Fill(MuPt -> at(kKinematicObjects["LM"][i]), MuEta -> at(kKinematicObjects["LM"][i]), event_weight);
	}


	// variables of kinematic object "TM"
	
	for(int i = 0; i < kNumberOfKinematicObjects["TM"]; ++i){
		kH2DCache[kSampleIterator][kSelectionIterator][1] -> Fill(MuPt -> at(kKinematicObjects["TM"][i]), MuEta -> at(kKinematicObjects["TM"][i]), event_weight);
		kH2DCache[kSampleIterator][kSelectionIterator][2] -> Fill(MuPt -> at(kKinematicObjects["TM"][i]), MuEta -> at(kKinematicObjects["TM"][i]), event_weight);
	}

}



//____________________________________________________________________________
void AnalysisModules::Module12Frame(){
	/*
  	fills lepton, jet and event control plots for the measurement regions
 	parameters: none
 	return: none
 	*/
	

	// samples, event selections, 1d histograms and 2d histograms
	
	std::vector<Label> h1ds;
	std::vector<Label> h2ds;
	std::vector<Label> samples;
	std::vector<Label> selections;
	std::vector<Label> slist;


	// data samples

	slist.push_back("qcdmu20.");
	slist.push_back("dyjll10" );
	slist.push_back("dyjll50" );
	slist.push_back("wjlnu"   );
	
	samples = Tools::GetVectorFromMapKeys(Tools::GetSubSetOfMapByKeys(cSamples, slist));


	// event selections
	
	selections = Tools::GetVectorFromMapKeys(Tools::GetSubSetOfMapByKeys(cEventSelectionDefinitions, "MR"));

	
	// 1d histograms
	
	h1ds.push_back(GetOutputContent("#EVT", "HT"    ));
	h1ds.push_back(GetOutputContent("#EVT", "NBJ"   ));
	h1ds.push_back(GetOutputContent("#EVT", "NJ"    ));
	h1ds.push_back(GetOutputContent("#EVT", "NVTX"  ));
	h1ds.push_back(GetOutputContent("#LM" , "LM.D0" ));
	h1ds.push_back(GetOutputContent("#LM" , "LM.ETA"));
	h1ds.push_back(GetOutputContent("#LM" , "LM.ISO"));
	h1ds.push_back(GetOutputContent("#LM" , "LM.PT" ));
	h1ds.push_back(GetOutputContent("#TM" , "TM.D0" ));
	h1ds.push_back(GetOutputContent("#TM" , "TM.ETA"));
	h1ds.push_back(GetOutputContent("#TM" , "TM.ISO"));
	h1ds.push_back(GetOutputContent("#TM" , "TM.PT" ));


	// 2d histograms	

	// none


	// Defining all outputs

	DefineOutputCache(12, samples, selections, h1ds, h2ds);


	// Set histogram binning

	for(int i = 0; i < samples.size(); ++i){
		for(int j = 0; j < selections.size(); ++j){
			kH1DCache[i][j][0]  -> SetBins(10,   0.0, 400.0);
			kH1DCache[i][j][1]  -> SetBins( 3,   0.0,   3.0);
			kH1DCache[i][j][2]  -> SetBins( 5,   1.0,   6.0);
			kH1DCache[i][j][3]  -> SetBins(40,   0.0,  40.0);
			kH1DCache[i][j][4]  -> SetBins(20,   0.0,   0.2);
			kH1DCache[i][j][5]  -> SetBins(12,   0.0,   2.4);
			kH1DCache[i][j][6]  -> SetBins(20,   0.0,   1.0);
			kH1DCache[i][j][7]  -> SetBins(20,  10.0,  70.0);
			kH1DCache[i][j][8]  -> SetBins(20,   0.0,   0.2);
			kH1DCache[i][j][9]  -> SetBins(12,   0.0,   2.4);
			kH1DCache[i][j][10] -> SetBins(20,   0.0,   1.0);
			kH1DCache[i][j][11] -> SetBins(20,  10.0,  70.0);
		}
	}
			

	// Loop over samples

	std::cout << "going to loop over samples" << std::endl;
	LoopOverSamples(&AnalysisModules::Module12Kernel, samples, selections);


	// Write histograms and outputs to disk

	WriteOutputCache(12, samples, selections);
	

	// Save fake ratio map in member variable


}


//____________________________________________________________________________
void AnalysisModules::Module12Kernel(float event_weight){
	/*
  	kernel to module 12
  	parameters: event_weight
  	return: none
  	*/
	

	// event variables

	//kH1DCache[kSampleIterator][kSelectionIterator][0] -> Fill(kDefinedVariables["HT"][0]     , event_weight);
	kH1DCache[kSampleIterator][kSelectionIterator][1] -> Fill(kNumberOfKinematicObjects["GJ"], event_weight);
	kH1DCache[kSampleIterator][kSelectionIterator][2] -> Fill(kNumberOfKinematicObjects["BJ"], event_weight);
	kH1DCache[kSampleIterator][kSelectionIterator][3] -> Fill((NVrtx>40)?40:NVrtx            , event_weight);


	// variables of kinematic object "LM"

	for(int i = 0; i < kNumberOfKinematicObjects["LM"]; ++i){
		kH1DCache[kSampleIterator][kSelectionIterator][4] -> Fill(MuD0    -> at(kKinematicObjects["LM"][i]), event_weight);
		kH1DCache[kSampleIterator][kSelectionIterator][5] -> Fill(MuEta   -> at(kKinematicObjects["LM"][i]), event_weight);
		kH1DCache[kSampleIterator][kSelectionIterator][6] -> Fill(MuPFIso -> at(kKinematicObjects["LM"][i]), event_weight);
		kH1DCache[kSampleIterator][kSelectionIterator][7] -> Fill(MuPt    -> at(kKinematicObjects["LM"][i]), event_weight);
	}


	// variables of kinematic object "TM"

	for(int i = 0; i < kNumberOfKinematicObjects["TM"]; ++i){
		kH1DCache[kSampleIterator][kSelectionIterator][8]  -> Fill(MuD0    -> at(kKinematicObjects["TM"][i]), event_weight);
		kH1DCache[kSampleIterator][kSelectionIterator][9]  -> Fill(MuEta   -> at(kKinematicObjects["TM"][i]), event_weight);
		kH1DCache[kSampleIterator][kSelectionIterator][10] -> Fill(MuPFIso -> at(kKinematicObjects["TM"][i]), event_weight);
		kH1DCache[kSampleIterator][kSelectionIterator][11] -> Fill(MuPt    -> at(kKinematicObjects["TM"][i]), event_weight);
	}


	// variables of kinematic object "GJ"

	//for(int i = 0; i < kNumberOfKinematicObjects["GJ"]; ++i){
	//	kH1DCache[kSampleIterator][kSelectionIterator][8]  -> Fill(JetD0    -> at(kKinematicObjects["TM"][i]), event_weight);
	//	kH1DCache[kSampleIterator][kSelectionIterator][9]  -> Fill(JetEta   -> at(kKinematicObjects["TM"][i]), event_weight);
	//	kH1DCache[kSampleIterator][kSelectionIterator][10] -> Fill(JetPFIso -> at(kKinematicObjects["TM"][i]), event_weight);
	//	kH1DCache[kSampleIterator][kSelectionIterator][11] -> Fill(JetPt    -> at(kKinematicObjects["TM"][i]), event_weight);
	//}




}


//____________________________________________________________________________
void AnalysisModules::Module13Frame(){

	std::vector<Label> samples;
	std::vector<Label> h1d;
	std::vector<Label> h2d;

	samples.push_back("qcdmu20.");

	std::vector<Label> sample_names    = Tools::GetVectorFromMapKeys(Tools::GetSubSetOfMapByObjectNames(cSamples, samples));
	std::vector<Label> selection_names;

	LoopOverSamples(&AnalysisModules::Module13Kernel, sample_names, selection_names);


}


//____________________________________________________________________________
void AnalysisModules::Module13Kernel(float event_weight){
}




