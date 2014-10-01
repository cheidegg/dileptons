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




/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/



//____________________________________________________________________________
Dileptons::Dileptons(){
	/* 
	constructs the Dileptons Class 
	parameters: none
	return: none
	*/


	Initialize();
	CheckResources();

}

//____________________________________________________________________________
Dileptons::Dileptons(TString configuration_file){
	/* 
	constructs the Dileptons Class 
	parameters: configuration_file (path to configuration file)
	return: none
	*/

	Initialize();
	CheckResources();
	StartDileptons(configuration_file);

}


//____________________________________________________________________________
Dileptons::~Dileptons(){
	/* 
	destructs the Dileptons Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void Dileptons::Initialize(){
	/*
	initializes the Dileptons class, defining standard values of certain variables
	parameters: none
	return: none
	*/

	kAFSFolder       = "/afs/cern.ch/user/c/";
	kAFSFolder      += Tools::GetUserName();
	kAFSFolder      += "/www/dileptons/";

	kInfoFolder      = "info/";
	kInputFolder     = "input/";
	kOutputFolder    = "output/";
	kTemplateFolder  = "templates/";
	kTemporaryFolder = "temporary/";

	kInfoFileBasicKinematicObjects      = "basic_kinematic_objects.txt";
	kInfoFileDataSamples                = "data_samples.txt";
	kInfoFileErrorMessages              = "error_messages.txt";
	kInfoFileKinematicElectronVariables = "kinematic_electron_variables.txt";
	kInfoFileKinematicEventVariables    = "kinematic_event_variables.txt";
	kInfoFileKinematicJetVariables      = "kinematic_jet_variables.txt";
	kInfoFileKinematicMuonVariables     = "kinematic_muon_variables.txt";
	kInfoFileKinematicPhotonVariables   = "kinematic_photon_variables.txt";
	kInfoFileKinematicTauVariables      = "kinematic_tau_variables.txt";
	kInfoFileModuleGroups               = "module_groups.txt";
	kInfoFileModuleList                 = Tools::ConvertStdStringToTString("module_list_" + Tools::ConvertTStringToStdString(cModuleList) + ".txt");
	kInfoFileModuleListAnalysis         = "module_list_analysis.txt";
	kInfoFileSystemMessages             = "system_messages.txt";

	kTemplateFileIndexConfigplots       = "index_configplots.php";
	kTemplateFileIndexModules           = "index_modules.php";
	kTemplateFileIndexPlots             = "index_plots.php";
	kTemplateFileTag                    = "tag.sh";
	kTemplateFileVersion                = "version.sh";

	kTemporaryFileConfiguration         = "0.cfg";
	kTemporaryFileLog                   = "0.log";
	kTemporaryFileTag                   = "tag.sh";


	std::vector<std::vector<TString> > matrix = OtherInput::ReadMatrixFromListFile(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileBasicKinematicObjects), "\t", 2);

	std::vector<Label> labels = Tools::GetColumnFromTStringMatrix(matrix, 0);
	std::vector<TString> types = Tools::GetColumnFromTStringMatrix(matrix, 1);

	for(int i = 0; i < labels.size(); ++i){
		kBasicKinematicObjects.push_back(std::make_pair(labels[i].ReplaceAll("\t", ""), types[i].ReplaceAll("\t", "")));
		//cObjectSelectionDefinitions[labels[i]] = "";
	}

	kVerbose = new Verbose((DileptonsVerbose) 0, Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileErrorMessages), Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileSystemMessages));
	//kVerbose->Class("Dileptons");


}


//____________________________________________________________________________
bool Dileptons::CheckAKROSDStringForDefinedVariables(Label variable_name, AKROSD string, std::vector<Label> selected_objects, std::vector<Label> defined_variables){
	/*
	checks the AKROSD string according to the rules of defined event variables
	parameters: string (AKROSD string to be checked), object_selection_definitions
	            (std::vector of AKROSD strings for object selection definitions)
	return: true (if everything is ok), false (else)
	*/
	
	// defined variable definitions may contain: 
	// - kinematic event variables
	// - non-kinematic event variables
	// - kinematic variables of basic kinematic objects
	// - kinematic variables of selected kinematic objects
	// - defined event variables other than this one
	// - analysis tools functions using %AT:function:argumentlist with the correct amount of arguments
	// - an asteriks * to fix the one of the objects

	// defined variable definitions may NOT contain:
	// -
	// - 

	// defined variable definitions MUST contain:
	//
	
	// their labels have to
	// - include the label of the basic kinematic object as last letter
	// - not contain * or #
	// - be unique, i.e. not already taken by another object
	// - maximally 10 letters long

	return true;
	

}



//____________________________________________________________________________
bool Dileptons::CheckAKROSDStringForEventSelection(AKROSD string, std::vector<Label> selected_objects, std::vector<Label> defined_variables){
	/*
	checks the AKROSD string according to the rules of event selection definitions
	parameters: string (AKROSD string to be checked), object_selection_definitions
	            (std::vector of AKROSD strings for object selection definitions)
	return: true (if everything is ok), false (else)
	*/

	// event selection definitions may contain:
	// - kinematic event variables
	// - non-kinematic event variables
	// - number of basic kinematic objects accessed via #
	// - number of selected kinematic objects accessed via #
	// - defined variables

	// event selection definitions may NOT contain:
	// -
	// - tools functions using %AT:
	// - an asteriks * 

	return true;
	
}


//____________________________________________________________________________
bool Dileptons::CheckAKROSDStringForObjectSelection(Label object_name, AKROSD string, std::vector<Label> selected_objects, std::vector<Label> defined_variables){
	/*
	checks the AKROSD string according to the rules of object selection definitions
	parameters: string (AKROSD string to be checked)
	return: true (if everything is ok), false (else)
	*/

	// object selection definitions may contain:
	// - kinematic variables of the basic kinematic object
	// - selections of selected kinematic objects of same type other than this one
	// - defined variables

	// object selection definitions may NOT contain:
	// - kinematic event variables
	// - non-kinematic event variables
	// - selections of basic kinematic objects of different type
	// - selection of selected kinematic objects of different type
	// - selection of the same selected kinematic object
	// - kinematic variables of basic kinematic objects of different type
	// - kinematic variables of selected kinematic objects other than this one
	// - number of basic kinematic objects
	// - number of selected kinematic objects
	// - tools functions using %AT:
	// - an asteriks * 
	// - variables of 

	// their labels have to
	// - include the label of the basic kinematic object as last letter
	// - not contain * or #
	// - be unique, i.e. not already taken by another object
	// - exactly 2 (or 3?) letters long


	return true;


	// first, we check the overall string

//	if(Tools::CountTStringOccurrence(statement, "#") > 0) return false;
//
//
//	std::vector<Label> basic_objects;
//	for(int object_iterator = 0; object_iterator < kBasicKinematicObjects.size(); ++object_iterator)
//		basic_objects.push_back(kBasicKinematicObjects[i].first);
//	
//	std::vector<Label> other_selected_objects = Tools::RemoveElementFromVector(selected_objects, object_name);
//
//
//
//	// second, we check individual statements if they contain forbidden information
//
//	std::vector<AKROSD> statements = GetAKROSDStatements(string);
//
//	for(int i = 0; i < statements.size(); ++i){
//
//		std::vector<Label> labels;
//		if(Tools::CountTStringOccurrence(statement, "%if") == 1) 
//			labels = GetAKROSDLabelsInIfThElStatement(statement);
//		else 
//			labels.push_back(GetAKROSDLabelInStatement(statement));
//
//		for(int j = 0; j < labels.size(); ++j){
//			if(Tools::FindElementInVector(selected_objects, labels[j])) return false;
//
//		}
//	}
//
//
//	// third, we check individual statements if they contain allowed information
//
//	for(int i = 0; i < statements.size(); ++i){
//
//		std::vector<Label> labels;
//		if(Tools::CountTStringOccurrence(statement, "%if") == 1) 
//			labels = GetAKROSDLabelsInIfThElStatement(statement);
//		else 
//			labels.push_back(GetAKROSDLabelInStatement(statement));
//
//		bool return_value = false;
//		
//		for(int j = 0; j < labels.size(); ++j){
//			if(Tools::FindElementInVector(object_name, labels[j])) return_value = true;
//			
//
//		}
//
//
//		if(!return_value) return false;
//
//	}
//
//	return true;
	
}


//____________________________________________________________________________
void Dileptons::CheckConfiguration(){
	/*
	checks if the given configuration obeys all rules (e.g. if the AKROSD
	strings are legal), if all variables are given and if their values make 
	at least some sense (i.e. if their values are within allowed limits),
	and returns error message and exists the code in case something is illegal
	parameters: none
	return: none
	*/

	// RunOn, Mode and Verbose have been checked already or set to default value.
	// Samples has been checked in the DataSamples class.

	
	// check user name
	if(cUserName.Length() == 0) kVerbose->ErrorAndExit(3);

	// check directories
	if(cAFSPath.Length()    > 0 && (access(cAFSPath   , 0) != 0 || cAFSPath(cAFSPath.Length()-1,1)       != "/")) kVerbose->ErrorAndExit(4);
	if(cInputPath.Length()  > 0 && (access(cInputPath , 0) != 0 || cInputPath(cInputPath.Length()-1,1)   != "/")) kVerbose->ErrorAndExit(4);
	if(cOutputPath.Length() > 0 && (access(cOutputPath, 0) != 0 || cOutputPath(cOutputPath.Length()-1,1) != "/")) kVerbose->ErrorAndExit(4);

	// check modules
	if(cModuleList < 0) kVerbose->ErrorAndExit(5);

	std::vector<int> module_ids;
	if(cModuleList > 0) module_ids = Tools::ConvertTStringVectorToIntVector(Tools::ExplodeTString(OtherInput::ReadFromTextFile(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileModuleList)),","));
	else                module_ids = Tools::ConvertTStringVectorToIntVector(Tools::ExplodeTString(cModules,","));

	bool sketch_found = false;
	for(int i = 0; i < module_ids.size(); ++i){
		if(module_ids[i] > 100) sketch_found = true;
		if(module_ids[i] < 10 || (module_ids[i] <= 100 && module_ids[i] % 10 == 0) || (sketch_found && module_ids[i] < 100)) kVerbose->ErrorAndExit(6); 
	}

	// check AKROSD strings

	for(std::map<Label, AKROSD>::iterator iterator = cObjectSelectionDefinitions.begin(); iterator != cObjectSelectionDefinitions.end(); ++iterator)
		if(!CheckAKROSDStringForObjectSelection(iterator->first, iterator->second, Tools::GetVectorFromMapKeys(cObjectSelectionDefinitions), Tools::GetVectorFromMapKeys(cDefinedVariableDefinitions))) 
			kVerbose->ErrorAndExit(7);

	for(std::map<Label, AKROSD>::iterator iterator = cDefinedVariableDefinitions.begin(); iterator != cDefinedVariableDefinitions.end(); ++iterator)
		if(!CheckAKROSDStringForDefinedVariables(iterator->first, iterator->second, Tools::GetVectorFromMapKeys(cObjectSelectionDefinitions), Tools::GetVectorFromMapKeys(cDefinedVariableDefinitions))) 
			kVerbose->ErrorAndExit(8);
	
	for(std::map<Label, AKROSD>::iterator iterator = cEventSelectionDefinitions.begin(); iterator != cEventSelectionDefinitions.end(); ++iterator)
		if(!CheckAKROSDStringForEventSelection(iterator->second, Tools::GetVectorFromMapKeys(cObjectSelectionDefinitions), Tools::GetVectorFromMapKeys(cDefinedVariableDefinitions))) 
			kVerbose->ErrorAndExit(9);


	// check the maximal size variables for the samples
	//for(int i = 0; i < cSamples.size(); ++i)
	

}


//____________________________________________________________________________
void Dileptons::CheckResources(){
	/*
	checks if all resources are available, i.e. all info files, templates, 
	input and ouput directories, config file, and returns error message and 
	exits the code in case something is missing 
	parameters: none
	return: none
	*/

	// check existence of directories
	if(access(Tools::ConvertTStringToCString(kAFSFolder)      , 0) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertTStringToCString(kInfoFolder)     , 0) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertTStringToCString(kInputFolder)    , 0) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertTStringToCString(kOutputFolder)   , 0) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertTStringToCString(kTemplateFolder) , 0) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertTStringToCString(kTemporaryFolder), 0) != 0) kVerbose->ErrorAndExit(1);


	// check existence and permissions of info files
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileBasicKinematicObjects))     , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileDataSamples))               , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileKinematicElectronVariables)), F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileKinematicEventVariables))   , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileKinematicJetVariables))     , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileKinematicMuonVariables))    , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileKinematicPhotonVariables))  , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileKinematicTauVariables))     , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileModuleGroups))              , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileModuleListAnalysis))        , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);
	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileSystemMessages))            , F_OK && R_OK) != 0) kVerbose->ErrorAndExit(1);


	// checks write permission of output folder by creating an empty txt file and deleting it right after
	// note: the read permissions of the input folder or any other folder where the samples lie are 
	// checked in the DataSamples class. If the files cannot be opened, there will be an error in the
	// DataSamples class.

	if(!Tools::CheckDirectoryWritePermission(kOutputFolder   )) kVerbose->ErrorAndExit(1);
	if(!Tools::CheckDirectoryWritePermission(kTemporaryFolder)) kVerbose->ErrorAndExit(1);
	if(!Tools::CheckDirectoryWritePermission(kAFSFolder      )) kVerbose->ErrorAndExit(1);

}


//____________________________________________________________________________
void Dileptons::CreateTemporaryConfigurationFile(TString configuration_file){
	/*
	creates the temporary configuration file out of a given version; copyable
	means that we strip off all comments and empty lines, we order the 
	variables according to their type (n,v,m,...) and name, we sort the
	statements in every AKROSD string and rename the config file; this is
	an essential step for the input-output management as we make configurations
	comparable 
	parameters: configuration_file (path to the configuration file)
	return: none
	*/

	FILE * new_file;
	char buffer[1000], cache[521];
	char symbol_char[1], type_char[20], name_char[100], value_char[500], comment_char[300];

	std::vector<std::string> full_list;
	std::vector<std::string> comparable_list;
	std::vector<std::string> sortable_list;

	ifstream IN(configuration_file);
	if(!IN.is_open()) kVerbose->ErrorAndExit(2);

	while(IN.getline(buffer, 1000, '\n')){

		if(strlen(buffer) == 0) continue;
		if(buffer[0] == '#') continue;

		if(sscanf(buffer, "%s\t\t%s\t\t%s\t\t%s\t\t%s", symbol_char, type_char, name_char, value_char, comment_char) < 4) continue;

	 	TString symbol = symbol_char;
		
		if(symbol == "n") continue;

		// we use a string of sort symbol_type_name to sort all rows
		sprintf(cache, "%s_%s_%s", symbol_char, type_char, name_char);	
		sortable_list.push_back(cache);

		// we strip off the comments column since we do not need it nowhere 
		// in the input and output management
		sprintf(cache, "%s\t\t%s\t\t%s\t\t%s", symbol_char, type_char, name_char, value_char);
		full_list.push_back(cache);

	}

	comparable_list = sortable_list;
	std::sort(sortable_list.begin(), sortable_list.end());

	new_file = fopen(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kTemporaryFolder) + Tools::ConvertTStringToStdString(kTemporaryFileConfiguration)), "w");

	for(int i = 0; i < full_list.size(); ++i) {

		int index = -1;
		for(int j = 0; j < comparable_list.size(); ++j)
			if(comparable_list[j] == sortable_list[i]) 
				index = j;

		if(index >= 0) 
			fprintf(new_file, "%s\n", Tools::ConvertStdStringToCString(full_list[index]));

	}

	fclose(new_file);
			
}


//____________________________________________________________________________
void Dileptons::CreateOutputStructure(){
	/*
	creates the entire output structure (confplot and modules) in the local
	output-folder and copies the respective templates
	parameters: none
	return: none
	*/


	if(kConfigplot == "0-0")
		Tools::ExecuteBashCommand("rm -r " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot));

	Tools::ExecuteBashCommand("mkdir " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot));
	Tools::ExecuteBashCommand("mkdir " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/0");
	Tools::ExecuteBashCommand("mv " + Tools::ConvertTStringToStdString(kTemporaryFolder) + Tools::ConvertTStringToStdString(kTemporaryFileConfiguration) + " " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/0/" + Tools::ConvertTStringToStdString(kTemporaryFileConfiguration));
	Tools::ExecuteBashCommand("cp " + Tools::ConvertTStringToStdString(kTemplateFolder) + Tools::ConvertTStringToStdString(kTemplateFileIndexModules) + " " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/index.php");

	for(int i = 0; i < kModules.size(); ++i){
		Tools::ExecuteBashCommand("mkdir " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/" + Tools::ConvertIntToStdString(kModules[i]));
		Tools::ExecuteBashCommand("cp " + Tools::ConvertTStringToStdString(kTemplateFolder) + Tools::ConvertTStringToStdString(kTemplateFileIndexPlots) + " " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/" + Tools::ConvertTStringToStdString(kModules[i]) + "/index.php");
	}

	kVerbose -> SetLogFilePath(Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/0/" + Tools::ConvertTStringToStdString(kTemporaryFileLog));

}


//____________________________________________________________________________
void Dileptons::FillEventList(){
	/*
	fills the event lists cache with a print-out about the current event
	parameters: none
	return: none
	*/

	std::string line = Form("%d\t%d\t%d", Run, Lumi, Event);
	line += "\n";
	kEventListsCache[kSampleIterator][kSelectionIterator] += Tools::ConvertStdStringToTString(line);

}


//____________________________________________________________________________
void Dileptons::EndDileptons(){
	/*
	ends dileptons, copies the outputs and tags the code
	parameters: none
	return: none
	*/

	kVerbose -> ExecutionTime();
	kVerbose -> WriteLogFile();
	FinalizeOutput();
	TagCode();

}


//____________________________________________________________________________
void Dileptons::FinalizeOutput(){
	/*
	copies log file to configplot folder and the entire configplot folder onto AFS webspace
	parameters: none
	return: none
	*/
	
	if(cMode == test) return;

	//Tools::ExecuteBashCommand("mv " + Tools::ConvertTStringToStdString(kTemplateFolder) + Tools::ConvertTStringToStdString(kTemporaryFileLog) + " " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/0/" + Tools::ConvertTStringToStdString(kTemporaryFileLog));

	TString cp_folder = Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/0/");
	OtherOutput::WriteToTextFile(cp_folder, "username.txt", cUserName);	

	if(access(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kAFSFolder) + "index.php"), 0) != 0) 
		Tools::ExecuteBashCommand("cp " + Tools::ConvertTStringToStdString(kTemplateFolder) + Tools::ConvertTStringToStdString(kTemplateFileIndexConfigplots) + " " + Tools::ConvertTStringToStdString(kAFSFolder) + "index.php");

	Tools::ExecuteBashCommand("cp -r " + Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + " " + Tools::ConvertTStringToStdString(kAFSFolder) + Tools::ConvertTStringToStdString(kConfigplot));

}


//____________________________________________________________________________
int Dileptons::GetKinematicObjectIteratorByLabel(Label object_name){
	/*
	returns the iterator of the kinematic object whose label is given
	parameters: object_name (the label of the object)
	return: the iterator of the object
	*/

	TString object_type = GetKinematicObjectTypeByLabel(object_name);

	if     (object_type.Index("electron") > -1) return kElectronIterator;
	else if(object_type.Index("jet")      > -1) return kJetIterator;
	else if(object_type.Index("muon")     > -1) return kMuonIterator;
	else if(object_type.Index("photon")   > -1) return kPhotonIterator;
	else if(object_type.Index("tau")      > -1) return kTauIterator;

	return -1;

}


//____________________________________________________________________________
TString Dileptons::GetKinematicObjectTypeByLabel(Label object_name){
	/*
	returns the type of the kinematic object whose label is given
	parameters: object_name (the label of the object)
	return: the type (electron, jet, muon, photon, tau) of the object
	*/

	for(int i = 0; i < kBasicKinematicObjects.size(); ++i)
		if(kBasicKinematicObjects[i].first == object_name(object_name.Length() - 1, 1))
			return kBasicKinematicObjects[i].second;

	return "";

}


//____________________________________________________________________________
TString Dileptons::GetOutputContent(Label quantity, Label variable_x){
	/*
  	returns the content label that enters the names of outputs in order to
  	characterize what content is stored in the output in question
  	parameters: quantity (the quantity that is plotted/presented), variable_x
  	return: the content label
  	*/

	return Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(quantity) + ":" + Tools::ConvertTStringToStdString(variable_x));

}


//____________________________________________________________________________
TString Dileptons::GetOutputContent(Label quantity, Label variable_x, Label variable_y){
	/*
  	returns the content label that enters the names of outputs in order to
  	characterize what content is stored in the output in question
  	parameters: quantity (the quantity that is plotted/presented), variable_x, 
  	            variable_y
  	return: the content label
  	*/

	return Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(quantity) + ":" + Tools::ConvertTStringToStdString(variable_x) + ":" + Tools::ConvertTStringToStdString(variable_y));

}


//____________________________________________________________________________
TString Dileptons::GetOutputContent(Label quantity, Label variable_x, Label variable_y, Label variable_z){
	/*
  	returns the content label that enters the names of outputs in order to
  	characterize what content is stored in the output in question
  	parameters: quantity (the quantity that is plotted/presented), variable_x, 
  	            variable_y, variable_z
  	return: the content label
  	*/

	return Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(quantity) + ":" + Tools::ConvertTStringToStdString(variable_x) + ":" + Tools::ConvertTStringToStdString(variable_y) + ":" + Tools::ConvertTStringToStdString(variable_z));

}


//____________________________________________________________________________
TString Dileptons::GetOutputFolder(int module_id){
	/*
  	returns the current output folder including configplot and module structure
  	parameters: module_id
  	return: the output folder of the module
  	*/

	return Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(kOutputFolder) + Tools::ConvertTStringToStdString(kConfigplot) + "/" + Tools::ConvertIntToStdString(module_id) + "/");

}


//____________________________________________________________________________
TString Dileptons::GetOutputName(int module_id, OutputType output_type, TString content, Label sample_name, Label selection_name){
	/*
	returns the output name for a given module, output type and content
	parameters: module_id (the ID of the module that produced the output), 
	            output_type (the type of output), content (the variables that
	            are given)
	return: the formatted output name
	*/
	
	//return Tools::ConvertStdStringToTString(Tools::ConvertOutputTypeToStdString(output_type) + "_" + Tools::ConvertTStringToStdString(sample_name) + "_" + Tools::ConvertTStringToStdString(selection_name) + "_" +  Tools::ConvertTStringToStdString(content) + "_" + Tools::ConvertTStringToStdString(cUserName) + "_" + Tools::GetTimestamp());

	// THIS ONE IS TOO LONG:
	return Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(kConfigplot) + "_" + Tools::ConvertIntToStdString(module_id) + "_" + Tools::ConvertOutputTypeToStdString(output_type) + "_" + Tools::ConvertTStringToStdString(sample_name) + "_" + Tools::ConvertTStringToStdString(selection_name) + "_" +  Tools::ConvertTStringToStdString(content) + "_" + Tools::ConvertTStringToStdString(kVersion) + "_" + Tools::ConvertTStringToStdString(cUserName) + "_" + Tools::GetTimestamp());

}


//____________________________________________________________________________
void Dileptons::LoadConfigurationFile(TString configuration_file){
	/*
	loads the configuration file and reads the configuration variables
	parameters: configuratoin_file (path to the configuration file)
	return: none
	*/

	char buffer[1000];
	char symbol_char[1], type_char[20], name_char[100], value_char[500], comment_char[300];

	ifstream IN(configuration_file);
	
	if(!IN.is_open()) kVerbose->ErrorAndExit(2);

	while(IN.getline(buffer, 1000, '\n')){

		if(strlen(buffer) == 0) continue;
		if(buffer[0] == '#') continue;

		if(sscanf(buffer, "%s\t%s\t\t%s\t\t%s\t\t%s", symbol_char, type_char, name_char, value_char, comment_char) < 4) continue;

		Label symbol    = Tools::ConvertStdStringToLabel(symbol_char);
		Label type      = Tools::ConvertStdStringToLabel(type_char);	
		Label name      = Tools::ConvertStdStringToLabel(name_char).ReplaceAll("\t", "");
		TString value   = value_char;
		TString comment = comment_char;

		if(symbol == "n"){
			if      (type == "TString" && name == "UserName"  ) cUserName   = value;
			else if (type == "TString" && name == "InputPath" ) cInputPath  = value;
			else if (type == "TString" && name == "OutputPath") cOutputPath = value;
			else if (type == "TString" && name == "AFSPath"   ) cAFSPath    = value;
			else if (type == "TString" && name == "Mode"      ) cMode       = Tools::ConvertTStringToDileptonsMode(value);
			else if (type == "TString" && name == "RunOn"     ) cRunOn      = Tools::ConvertTStringToDileptonsRunOn(value);
			else if (type == "TString" && name == "Modules"   ) cModules    = value;
			else if (type == "int"     && name == "ModuleList") cModuleList = value.Atoi();
		}

		if(symbol == "v"){
			if      (type == "int"     && name == "JetEnergyCorrection") cJetEnergyCorrection = value.Atoi();
			else if (type == "float"   && name == "Luminosity"         ) cLuminosity          = value.Atof();
			else if (type == "bool"    && name == "PileUpReweighting"  ) cPileUpReweighting   = (bool) value.Atoi();
		}

		if(symbol == "o" && type == "AKROSD"  && name != "") cObjectSelectionDefinitions[name] = value.ReplaceAll("\t", "");
		if(symbol == "d" && type == "AKROSD"  && name != "") cDefinedVariableDefinitions[name] = value.ReplaceAll("\t", "");
		if(symbol == "e" && type == "AKROSD"  && name != "") cEventSelectionDefinitions[name]  = value.ReplaceAll("\t", "");


		if(symbol == "n" && type == "int"     && name == "Verbose") {
			cVerbose = Tools::ConvertTStringToDileptonsVerbose(value);
			kVerbose -> SetVerbose(cVerbose);
		}

		if(symbol == "s" && type == "TString" && name != ""){
			std::string file_path = value_char;
			if(value(0, 1) != "/") file_path = Tools::ConvertTStringToStdString(cInputPath) + file_path;

			cSamples[name] = new DataSample(name, file_path, Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileDataSamples), kVerbose);
		}

		if(symbol == "m" && type == "int"     && name != "")
			cSamples[name] -> SetMaxEntries(value.Atoi());
		
	}
}


//_____________________________________________________________________________________
void Dileptons::SetConfigplot(TString configuration_file){
	/*
	analyses all configurations in the output folder and compares the current configuration
	to the ones in that folder in order to get the configplot number
	parameters: none
	return: none
	*/


	int configuration_number = 0;
	int plot_number = 0;


	// If kConfigplot is already set, we won't set it again.

	if(kConfigplot.Length() > 0) 
		return;


	// if we are in test mode, configplot is set to 0-0

	if(cMode == test) {
		kConfigplot = "0-0";
		return;
	}




	// We browse through the output folder and store all configplots in a std::vector

	std::vector<TString> configplots;

	DIR *output_directory = opendir(kOutputFolder);
    struct dirent *entry = readdir(output_directory);

    while(entry != NULL){
        if(entry -> d_type == DT_DIR && Tools::ConvertStdStringToTString(entry -> d_name) != "." && Tools::ConvertStdStringToTString(entry -> d_name) != "..") 
			configplots.push_back(entry -> d_name);
        entry = readdir(output_directory);
    }

    closedir(output_directory);


	// We compare every other configuration file of every configplot to our new
	// temporary configuration file.

	TString configplot_found = "0-0";
	std::string line;
	std::vector<std::string> this_content;

	ifstream this_file(kTemporaryFolder + kTemporaryFileConfiguration);
	while(getline(this_file, line))
		this_content.push_back(line);
	this_file.close();


	for(int i = 0; i < configplots.size(); ++i){

		bool match = true;

		ifstream that_file(kOutputFolder + configplots[i] + "/0/" + kTemporaryFileConfiguration);
		while(getline(that_file, line))
			if(!Tools::FindElementInVector(this_content, line))
				match = false;
	
		that_file.close();

		if(match) {
			configplot_found = configplots[i];	
			break;
		}
	}


	// In case we have found this configuration before, configuration_number > 0. Then,
	// we only need to find the largest plot_number, increment it by 1 and we are done.
	// If not, however, we need to find the largest configuration_number, increment
	// it by 1, set plot_number to 1 and we are done
	
	if(configplot_found != "0-0"){

		std::vector<TString> configplot_parts = Tools::ExplodeTString(configplot_found, "-");

		configuration_number = configplot_parts[0].Atoi();
		plot_number          = configplot_parts[1].Atoi();

		int highest_plot_number_found = plot_number;

		for(int i = 0; i < configplots.size(); ++i){

			configplot_parts = Tools::ExplodeTString(configplots[i], "-");
			if(configplot_parts[0].Atoi() == configuration_number && configplot_parts[1].Atoi() > highest_plot_number_found) 
				highest_plot_number_found = configplot_parts[1].Atoi();
		}	

		plot_number = highest_plot_number_found + 1;

	}

	else{

		std::vector<TString> configplot_parts;
		int highest_configuration_number_found = 0;

		for(int i = 0; i < configplots.size(); ++i){
			configplot_parts = Tools::ExplodeTString(configplots[i], "-");
			if(configplot_parts[0].Atoi() > highest_configuration_number_found)
				highest_configuration_number_found = configplot_parts[0].Atoi();
		}	
		
		configuration_number = highest_configuration_number_found + 1;
		plot_number = 1;	

	}


	// set kConfigPlot to the new value

	kConfigplot = Tools::ConvertStdStringToTString(Tools::ConvertIntToStdString(configuration_number) + "-" + Tools::ConvertIntToStdString(plot_number));

}


//_____________________________________________________________________________________
void Dileptons::SetVersion(){
	/*
	executes a git shell command using the template version.sh in order to get the
	version number from the last annotated tag
	parameters: none
	return: none
	*/

	kVersion = Tools::ExecuteShellScript(kTemplateFolder + kTemplateFileVersion);

}


//____________________________________________________________________________
void Dileptons::StartDileptons(TString configuration_file){
	/*
	starts Dileptons, i.e. loads the configuration file, checks the configuration,
	loads and sets some variables and prepares the output structure
	parameters: configuration_file (path to the configuration file)
	return: none
	*/

	// NOTE ABOUT THIS METHOD:
	// One would prefer to put these calls into the constructor directly. However,
	// we cannot do that since we construct either of the two children AnalysisModules
	// or Sketches and their constructors contain the path to the configuration file.
	// So this method is a way to load the configuration file and start Dileptons
	// via AnalysisModules or Sketches.

	// NOTE ABOUT CALLING CreateTemporaryConfigurationFile() BEFORE SetConfigplot():
	// There are in principle two possible ways how we can look for existence of the
	// current configuration in the output folder. First, we read all configuration
	// files one after another and compare the values of our variables to those values.
	// This is straight-forward, but not nice and also slow. We rather do the second
	// method and rearrange our configuration file such that the parameters and lines
	// are ordered in a way that makes the whole file comparable to that of other configurations.
	// So, first we order our own file. Then, we compare it to every other configuration
	// file in the output folder assuming that they are ordered already.

	LoadConfigurationFile(configuration_file);
	CheckConfiguration();
	UseConfigurationVariables();
	CreateTemporaryConfigurationFile(configuration_file);
	SetConfigplot(configuration_file);
	SetVersion();
	CreateOutputStructure();

}


//_____________________________________________________________________________________
void Dileptons::TagCode(){
	/*
	uses a template to create a lightweight tag automatically after running	the code
	paramters: none
	return: none
	*/

	if(cMode == test) return;
	
	std::string template_text;
	std::string line;
	ifstream template_file;
	template_file.open(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kTemplateFolder) + Tools::ConvertTStringToStdString(kTemplateFileTag)));
	
	if(template_file.is_open())
		while(getline(template_file, line))
			template_text += line;
		
	template_file.close();
		
	Tools::ReplaceAll(template_text, "__VERSION__", Tools::ConvertTStringToStdString(kVersion));
	Tools::ReplaceAll(template_text, "__CONFIGPLOT__", Tools::ConvertTStringToStdString(kConfigplot));
	
	ofstream execute_file;
	execute_file.open(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kTemporaryFolder) + Tools::ConvertTStringToStdString(kTemporaryFileTag)));
	execute_file << template_text;
	execute_file.close();
	
	Tools::ExecuteBashCommand("chmod 0755 " + Tools::ConvertTStringToStdString(kTemporaryFolder) + Tools::ConvertTStringToStdString(kTemporaryFileTag));
	Tools::ExecuteShellScript(Tools::ConvertTStringToStdString(kTemporaryFolder) + Tools::ConvertTStringToStdString(kTemporaryFileTag));
	Tools::ExecuteBashCommand("rm " + Tools::ConvertTStringToStdString(kTemporaryFolder) + Tools::ConvertTStringToStdString(kTemporaryFileTag));
	
	
}


//____________________________________________________________________________
void Dileptons::UseConfigurationVariables(){
	/*
	overrides certain default variables of dileptons by the variables given in 
	the configuration file
	parameters: none
	return: none
	*/


	if(cAFSPath    != "") kAFSFolder = cAFSPath;
	if(cInputPath  != "") kInputFolder = cInputPath;
	if(cOutputPath != "") kOutputFolder = cOutputPath;

	if(cRunOn == analysis  ) kModules = Tools::ConvertTStringVectorToIntVector(Tools::ExplodeTString(OtherInput::ReadFromTextFile(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileModuleListAnalysis)),","));
	else if(cModuleList > 0) kModules = Tools::ConvertTStringVectorToIntVector(Tools::ExplodeTString(OtherInput::ReadFromTextFile(Tools::ConvertTStringToStdString(kInfoFolder) + Tools::ConvertTStringToStdString(kInfoFileModuleList)),","));
	else                     kModules = Tools::ConvertTStringVectorToIntVector(Tools::ExplodeTString(cModules,","));

	kVerbose -> SetNumberOfModules(kModules.size());

}


/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR AKROSD STRINGS                                         **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
Label Dileptons::GetAKROSDLabelInStatement(AKROSD statement){
	/*
	takes out the label that is used in an AKROSD statement other than an if-th-el statement
	parameters: statement
	return: the label
	*/

	Label result;

	// if-th-el statement
	if(Tools::CountTStringOccurrence(statement, "%if") == 1)
		return result;

	// range statement
	else if(Tools::CountTStringOccurrence(statement, "%if") == 0 && Tools::CountTStringOccurrence(statement, ">") > 0 && Tools::CountTStringOccurrence(statement, "<") > 0){

	}

	// irregular statment without operation
	else if(Tools::CountTStringOccurrence(statement, "=") == 1 || Tools::CountTStringOccurrence(statement, ">") > 0 || Tools::CountTStringOccurrence(statement, "<") > 0){


	}

	// regular statement
	else{

	}

}


//____________________________________________________________________________
std::vector<Label> Dileptons::GetAKROSDLabelsInIfThElStatement(AKROSD statement){
	/*
	takes out all labels from an if-th-el statement and returns them in a vector
	parameters: statement
	return: the vector
	*/

	std::vector<Label> labels;
	
	if(Tools::CountTStringOccurrence(statement, "%if") != 1) return labels;




	return labels;

}


//____________________________________________________________________________
std::vector<AKROSD> Dileptons::GetAKROSDStatements(AKROSD string, AKROSD first_delimiter, AKROSD second_delimiter){
	/*
	collects all regular and irregular statements in an AKROSD string, i.e. 
	splits up the string by AND (,) and OR (|) and strips off the brackets
	parameters: string (AKROSD string)
	return: std::vector of statements
	*/

	std::vector<AKROSD> result;

	std::vector<AKROSD> first = Tools::ExplodeTString(string, first_delimiter);
	for(int i = 0; i < first.size(); ++i){
		std::vector<AKROSD> second = Tools::ExplodeTString(first[i], second_delimiter);
		for(int j = 0; j < second.size(); ++j) 
			result.push_back(second[j].ReplaceAll("(", "").ReplaceAll(")", ""));
	}

	return result;

}


//____________________________________________________________________________
std::vector<float> Dileptons::GetAnalysisToolsArgumentList(Label statement){
	/*
	collects the values we get by evaluating the statement; this can be either
	a list of all object variables (e.g. LM.PT can have 3 values one for each
	LM in the event) or the return of a defined variable
	parameters: statement
	return: vector of values
	*/

	std::vector<float> results;


	// statement is an object variable
	if(statement.First('.') > -1){
		AKROSD object = statement(0, statement.First('.'));
		object.Strip(TString::kBoth, ' ');
		if(FindKinematicObjects(object) == -1){	
			CollectKinematicObjects(object, cObjectSelectionDefinitions[object]);
			CountKinematicObjects(object);
		}

		for(int j = 0; j < kNumberOfKinematicObjects[object]; ++j)
			results.push_back(ParseAKROSDVariable(statement, j));
		
	}

	// statement is a defined variable
	else if(Tools::FindElementInMapByKey(cDefinedVariableDefinitions, statement)){
		if(RecreateDefinedVariable(statement))
			kDefinedVariables[statement] = ParseVariableDefinition(cDefinedVariableDefinitions[statement]);

		results = kDefinedVariables[statement];
	}


	return results;

}


//____________________________________________________________________________
std::vector<float> Dileptons::GetVectorOfParseResults(AKROSD operation, std::vector<AKROSD> arguments, int object_index){
	/*
  	takes an operation and a list of arguments and returns the vector of float
  	which contains the results for the operation executed for every combination
  	of the arguments; mostly the arguments are variables of selected kinematic
  	objects; say we have LM.PT and J.PT given as arguments and we have three
  	LM and two J; then the resulting vector has 3*2 = 6 elements, one for each
  	result of the operation that takes those two variables; this is also the
  	function which accesses the AnalysisTools methods, i.e. this whole function
	is for parsing definitions of defined event variables!
  	parameters: operation (string of the operation to perform, has to match the
  	            strings in the loop), arguments (the vector of arguments as strings),
  	            object_index (in case we fix an object by the use of * the index of
  	            the object to which we fix it is given, otherwise -1)
  	return: the vector of results
  	*/


	int number_of_combinations = 1;
	std::vector<float> results;
	std::vector<AKROSD> objects;
	std::vector<int> argument_correspondences;
	std::vector<int> object_iterators;
	AKROSD object_to_fix;
	int iterator_to_fix;



	// we extract the kinematic objects from the arguments, if any
	// we need them later in order to be able to parse the variables and to
	// determine the number of combinations

	for(int i = 0; i < arguments.size(); ++i){
		AKROSD object = arguments[i];
		if(arguments[i].First('.') > -1) object = arguments[i](0, arguments[i].First('.'));
		object.Strip(TString::kBoth, ' ');
		AKROSD reduced_object =  object(1, object.Length() - 1);
		
		if(object.Length() > 0 && !Tools::FindElementInMapByKey(cDefinedVariableDefinitions, object) && arguments[i].Index("-all") == -1){
			if(object(0,1) != "*"){
				if(!Tools::FindElementInVector(objects, object))
					objects.push_back(object);
				argument_correspondences.push_back(Tools::GetElementIndexInVector(objects, object));
			}
			if(object(0,1) == "*"){
				if(!Tools::FindElementInVector(objects, reduced_object)){
					objects.push_back(reduced_object);
					object_to_fix = reduced_object;
				}
				argument_correspondences.push_back(Tools::GetElementIndexInVector(objects, reduced_object));
			}
		}
	}



	// check if all objects are actually already selected, only then we can do the selection
	// if not, the object or defined variable in question is parsed first

	for(int i = 0; i < objects.size(); ++i){
		if(Tools::FindElementInMapByKey(cObjectSelectionDefinitions, objects[i]) && FindKinematicObjects(objects[i]) == -1){
			CollectKinematicObjects(objects[i], cObjectSelectionDefinitions[objects[i]]);
			CountKinematicObjects(objects[i]);
		}
	}

	for(int i = 0; i < arguments.size(); ++i){
		if(Tools::FindElementInMapByKey(cDefinedVariableDefinitions, arguments[i]) && RecreateDefinedVariable(arguments[i]))
			kDefinedVariables[arguments[i]] = ParseVariableDefinition(cDefinedVariableDefinitions[arguments[i]]);
	}



	// if there is no index given, to which we should fix the object, we take the object iterator		

	if(object_index == -1) object_index = GetKinematicObjectIteratorByLabel(object_to_fix);



	// if we have to deal with objects, then the number of selected objects in the event
	// determine the number of combinations; if we stay with the arguments (i.e. if we
	// have to deal with defined event variables, we have only one possible combination

	if(objects.size() > 0){
		object_iterators.resize(objects.size(), 0);
		for(int i = 0; i < objects.size(); ++i){
			if(object_to_fix == objects[i]) {
				object_iterators[i] = object_index;
				iterator_to_fix = i;
			}
			else
				number_of_combinations *= kNumberOfKinematicObjects[objects[i]];
			
		}
	}



	// looping over all possible combinations of the objects or arguments in general

	for(int i = 0; i < number_of_combinations; ++i){

		if     (operation == "+") 
			results.push_back(ParseAKROSDVariable(arguments[0], object_iterators[argument_correspondences[0]]) + ParseAKROSDVariable(arguments[1], object_iterators[argument_correspondences[1]]));

		else if(operation == "-")
			results.push_back(ParseAKROSDVariable(arguments[0], object_iterators[argument_correspondences[0]]) - ParseAKROSDVariable(arguments[1], object_iterators[argument_correspondences[1]]));
		
		else if(operation == "Absolute")
			results.push_back(AnalysisTools::Absolute(GetAnalysisToolsArgumentList(arguments[0].ReplaceAll("-all", ""))[0]));

		else if(operation == "AngleAddition")
			results.push_back(AnalysisTools::AngleAddition(ParseAKROSDVariable(arguments[0], object_iterators[argument_correspondences[0]]), ParseAKROSDVariable(arguments[1], object_iterators[argument_correspondences[1]])));

		else if(operation == "AngleSubtraction")
			results.push_back(AnalysisTools::AngleSubtraction(ParseAKROSDVariable(arguments[0], object_iterators[argument_correspondences[0]]), ParseAKROSDVariable(arguments[1], object_iterators[argument_correspondences[1]])));
		
		else if(operation == "DeltaPhi")
			results.push_back(AnalysisTools::DeltaPhi(ParseAKROSDVariable(arguments[0], object_iterators[argument_correspondences[0]]), ParseAKROSDVariable(arguments[1], object_iterators[argument_correspondences[1]])));

		else if(operation == "DeltaR")
			results.push_back(AnalysisTools::DeltaR(ParseAKROSDVariable(arguments[0], object_iterators[argument_correspondences[0]]), ParseAKROSDVariable(arguments[1], object_iterators[argument_correspondences[1]]), ParseAKROSDVariable(arguments[2], object_iterators[argument_correspondences[2]]), ParseAKROSDVariable(arguments[3], object_iterators[argument_correspondences[3]])));

		else if(operation == "Maximum")
			results.push_back(AnalysisTools::Maximum(GetAnalysisToolsArgumentList(arguments[0].ReplaceAll("-all", ""))));

		else if(operation == "Minimum")
			results.push_back(AnalysisTools::Minimum(GetAnalysisToolsArgumentList(arguments[0].ReplaceAll("-all", ""))));

		else if(operation == "Sum")
			results.push_back(AnalysisTools::Sum(GetAnalysisToolsArgumentList(arguments[0].ReplaceAll("-all", ""))));

		else
			return results;


		if(objects.size() > 0){
			if(iterator_to_fix != 0) ++object_iterators[0];

			for(int j = 1; j < objects.size(); ++j){
				if(object_iterators[j] != kNumberOfKinematicObjects[objects[j]] && iterator_to_fix != j){
					bool all = true;
					for(int k = 0; k < j; ++k)
						if(object_iterators[k] != kNumberOfKinematicObjects[objects[k]] && iterator_to_fix != k)
							all = false;
					if(all)
						++object_iterators[j];
				}
			}
			if(object_iterators[0] == kNumberOfKinematicObjects[objects[0]] && iterator_to_fix != 0)
				object_iterators[0] = 0;
		}					
	}

	return results;

}		


//____________________________________________________________________________
AKROSD Dileptons::InterpretAKROSDBrackets(AKROSD string, Label label){
	/*
	interprets the use of brackets by parsing every combination of regular
	statements within the brackets one after another
	parameters: string
	return: interpreted string which is only a combination of regular statements
	*/
	
	
	Ssiz_t position_closing_bracket = string.First(')');

	// the depth tells us, how many brackets are opened before the first one is closed again
	// we are interested in parsing the string which is between the last openening bracket
	// (before the first closing bracket) and the first closing bracket; this bracket (...) will
	// be replaced by the result of the parsing of the combined regular statement, and 
	// the new string is analyzed again on brackets until there are no brackets left

	int depth = Tools::CountTStringOccurrence(string, "(", 0, position_closing_bracket);
	
	AKROSD sub_string = string(0, position_closing_bracket);
	Ssiz_t position_opening_bracket = sub_string.Last('(');

	
	// we found at least one opening bracket
	if(depth > 0){

		std::string first_part    = Tools::ConvertTStringToStdString(string(0, position_opening_bracket));
		std::string replaced_part = Tools::ConvertBoolToStdString(ParseAKROSDCombinedRegularStatements(string(position_opening_bracket + 1, position_closing_bracket - position_opening_bracket - 1)));
		std::string last_part     = Tools::ConvertTStringToStdString(string(position_closing_bracket + 1, string.Length() - position_closing_bracket));

		return InterpretAKROSDBrackets(Tools::ConvertStdStringToTString(first_part + replaced_part + last_part), label);

	}

	else {

		return string;

	}



	//// opening bracket was found first
	//if(position_bracket > -1 && position_bracket < position_maximum){

	//	AKROSD sub_string = string(position_bracket + 1, string.Length() - position_bracket - 1);	
	//	Ssiz_t position_opening_bracket = sub_string.First('(');
	//	Ssiz_t position_closing_bracket = sub_string.First(')');

	//	std::cout << "=> going to interpret sub-string: " << sub_string << std::endl;

	//	return Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(string(0, position_bracket)) + Tools::ConvertTStringToStdString(InterpretAKROSDBrackets(sub_string, label)));
	//
	//}

	//// closing bracket was found first
	//// i.e. this means that this function has been called recursively
	//// hence, we only take out the string until this closing bracket and parse it
	//else if(position_maximum > -1 && (position_bracket == -1 || position_bracket > position_maximum)){


	//	std::cout << "++##++ going to parse combined regulat statements " << string(0, position_maximum) << std::endl;

	//	return InterpretAKROSDBrackets(Tools::ConvertStdStringToTString(Tools::ConvertBoolToStdString(ParseAKROSDCombinedRegularStatements(string(0, position_maximum), label)) + Tools::ConvertTStringToStdString(string(position_maximum + 1, string.Length() - position_maximum - 1))), label);

	//}
	//
	//// no bracket found
	//else{
	//	return string;
	//}
}


//____________________________________________________________________________
AKROSD Dileptons::InterpretAKROSDIfThElStatements(AKROSD string, Label label){
	/*
	performs the interpretation of ALL if-th-el statements used in an AKROSD string
	parameters: string (AKROSD string)
	return: newstring (interpreted AKROSD string)
	*/
	
	
	// we first add a whitespace because Index will return 0 if we find '%if' at the first
	// position in the string and 0 is interpreted as false in the subsequent if-clause
	
	Ssiz_t first = string.Index("%if");

	
	if(first > -1){
	
		// if the next separator is | instead of an , we separate by |, otherwise we separate by ,
		AKROSD look_for = ",";
		if(string.Index("|", first) > 0 && string.Index("|", first) < string.Index(",", first))
		    look_for = "|";

	
		Ssiz_t separate;	
		if(string.Index(look_for, first) > 0) separate = string.Index(look_for, first);
		else                                  separate = string.Length();
		
		
		// we take out the first if-th-el statement from left
		AKROSD statement = string(first, separate - first);
		statement = statement.Strip(TString::kBoth, ' ');

		
		// we take out the three regular statements between the if, th and el keywords
		// i.e. the statement looks like ifAAAthBBBelCCC and we want to get AAA, BBB, CCC individually
		std::vector<AKROSD> explode1 = Tools::ExplodeTString(statement, "th");
		std::vector<AKROSD> explode2 = Tools::ExplodeTString(explode1[1], "el");
		
		AKROSD if_statement = explode1[0](3, explode1[0].Length()-3);
		AKROSD th_statement = explode2[0];
		AKROSD el_statement = explode2[1];
			
		if_statement.Strip(TString::kBoth, ' ');
		th_statement.Strip(TString::kBoth, ' ');
		el_statement.Strip(TString::kBoth, ' ');
		
		
		// interpreting the if-th-el statement
		statement = Tools::ConvertStdStringToTString(Tools::ConvertBoolToStdString(ParseAKROSDCombinedRegularStatements(Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(if_statement) + "," + Tools::ConvertTStringToStdString(th_statement)), label)) + "," + Tools::ConvertBoolToStdString(ParseAKROSDCombinedRegularStatements(Tools::ConvertStdStringToTString(Tools::ConvertTStringToStdString(NegateAKROSDRegularStatement(if_statement)) + "," + Tools::ConvertTStringToStdString(el_statement)), label)));

		statement = Tools::ConvertBoolToTString(ParseAKROSDCombinedRegularStatements(statement, label));
	
		
		// remaining if-th-el statements are interpreted one after another recursively
		AKROSD first_part = string(0, first);
		return first_part.Strip(TString::kBoth, ' ') + statement + InterpretAKROSDIfThElStatements(string(separate, string.Length() - separate), label);
	
	}
	else {
	    return string;
	}
}


//____________________________________________________________________________
AKROSD Dileptons::InterpretAKROSDRangeStatements(AKROSD string, Label label){
	/*
	performs the interpretation of ALL range statements (e.g. NJ+2-3) used
	in an AKROSD string
	parameters: string (AKROSD string)
	return: newstring (interpreted AKROSD string)
	*/
	
	AKROSD new_string = "";
	AKROSD statement = "";
	AKROSD last_delimiter;
	
	for(Ssiz_t position = 0; position <= string.Length(); ++position){
	
		// search through every char of the AKROSD string
		AKROSD delimiter = string(position,1);

	
		// if the char is no , or | we attach it to the statement
		if(delimiter != "," && delimiter != "|" && delimiter != ")" && position != string.Length()) {
			statement += delimiter;
		}
		
		// if the char is indeed , or | or if we have reached the end of the string
		// the statement is complete
		else {
		

			// looking for a range statement which (1) is no if-th-el statement and (2) contains
			// + and - operators at the same time
			if(Tools::CountTStringOccurrence(statement, "%if") == 0 && Tools::CountTStringOccurrence(statement, "+") > 0 && Tools::CountTStringOccurrence(statement, "-") > 0) {
			

				// define which operator oomes first in the statement
				AKROSD larger  = ">";
				AKROSD smaller = "<";
				if(statement.Index(">>") > -1) larger  = ">>";
				if(statement.Index("<<") > -1) smaller = "<<";

				AKROSD first  = smaller;
				AKROSD second = larger ;
				if(statement.Index(larger) > -1 && statement.Index(larger) < statement.Index(smaller)){
					first  = larger ;
					second = smaller;
				}
				
				// we explode the statement twice at every operator in order to get the information between 
				// them i.e. the statement looks like AAA+BBB-CCC (or AAA-CCC+BBB) and we want to interpret 
				// this as AAA+BBB,AAA-CCC (or alternatively AAA-CCC,AAA+BBB) so we need to get AAA, BBB and 
				// CCC in dividually
				std::vector<AKROSD> explode1 = Tools::ExplodeTString(statement  , first );
				std::vector<AKROSD> explode2 = Tools::ExplodeTString(explode1[1], second);

				std::string to_parse  = Tools::ConvertTStringToStdString(explode1[0]) + Tools::ConvertTStringToStdString(first) + Tools::ConvertTStringToStdString(explode2[0]);
				            to_parse += ",";
				            to_parse += Tools::ConvertTStringToStdString(explode1[0]) + Tools::ConvertTStringToStdString(first) + Tools::ConvertTStringToStdString(explode2[1]);
	
				statement = Tools::ConvertBoolToTString(ParseAKROSDCombinedRegularStatements(Tools::ConvertStdStringToTString(to_parse), label));
			
			}
			
			// add the interpreted statement to the new string
			new_string = new_string + last_delimiter + statement;
			
			// reset everything and be prepared for the next statement
			last_delimiter = delimiter;
			statement = "";
		
		}
	}
	
	return new_string;
}


//____________________________________________________________________________
AKROSD Dileptons::NegateAKROSDRegularStatement(AKROSD statement){
    /*
    negates a single regular statement of the AKROSD string
    parameters: statement (single AKROSD statement)
    return: newstatement (negated statement)
    */

    // be careful when changing something here! the order of negating the
    // operators here (i.e. the order of the arguments in those two arrays)
    // is crucial!

    AKROSD new_statement = statement;

    TString search_for[6] = {">>", "<<", "=" , "!=", ">" , "<" };
    TString replace_by[6] = {"<" , ">" , "!=", "=" , "<<", ">>"};

    for(int i = 0; i < 6; ++i)
        new_statement = new_statement.ReplaceAll(search_for[i], replace_by[i]);

    return new_statement;

}


//____________________________________________________________________________
bool Dileptons::ParseAKROSDCombinedRegularStatements(AKROSD string, Label label){
	/*
	parses a string of only regular statements (no if-th-el, no range no brackets)
	which are combined using only AND (,) and OR (|)
	parameters: string
	return: true (if selection is true), false (else)
	*/
	
	
	if(string.Length() == 0) return true;

	AKROSD parenthesized_string = Tools::ConvertStdStringToTString("(" + Tools::ConvertTStringToStdString(string) + ")");
	AKROSD statement = "";
	AKROSD last_delimiter = "";
	bool statement_return = true;
	bool last_return = true;
	
	for(Ssiz_t position = 0; position <= string.Length(); ++position){
	
		AKROSD delimiter = string(position, 1);

		if(delimiter != "," && delimiter != "|" && position != string.Length()){
			statement += delimiter;
		}
		
		else{
			statement_return = ParseAKROSDRegularStatement(statement, label);
			
			if(last_delimiter == "," && (last_return == false || statement_return == false)) return false;
			if(last_delimiter == "|" && (statement_return == false && last_return == false)) return false;
			
			last_return = statement_return;
			last_delimiter = delimiter;
			statement = "";
		}
	}


	// filling event and object counts for the combined string in parantheses 

	if(label == "event") kEventCountCache[kSampleIterator][kSelectionIterator][parenthesized_string] += 1;
	else if(label != "") kObjectCountCache[kSampleIterator][label][parenthesized_string] += 1;

	return true;

}


//____________________________________________________________________________
bool Dileptons::ParseAKROSDOperation(AKROSD variable, AKROSD operation, float value){
	/*
	parses or interprets an operation within a regular statement; i.e. compares
	the value of the quantity to a given value by means of a given operation
	parameters:
	return: none
	*/

	// default especially important for triggers and calling other objects

	if     (operation == ">>") return ParseAKROSDVariable(variable, -1, -1       ) >  value;
	else if(operation == "<<") return ParseAKROSDVariable(variable, -1,  1       ) <  value;
	else if(operation == "=" ) return ParseAKROSDVariable(variable, -1,  0, value) == value;
	else if(operation == "!=") return ParseAKROSDVariable(variable, -1,  0, value) != value;
	else if(operation == ">" ) return ParseAKROSDVariable(variable, -1, -1       ) >= value;
	else if(operation == "<" ) return ParseAKROSDVariable(variable, -1,  1       ) <= value;

	return Tools::ConvertFloatToBoolAlternatively(ParseAKROSDVariable(variable));
	
}


//____________________________________________________________________________
bool Dileptons::ParseAKROSDRegularStatement(AKROSD statement, Label label){
	/*
	parses a regular statement from an AKROSD string
	parameters: statement (AKROSD statement to be parsed)
	return: true (if the statement is interpreted as true), false (else)
	*/


	// Parsing the string may have already replaced some statements by true or false
	
	if(statement.Length() == 0) return true;
	if(statement == "true" ) return true;
	if(statement == "false") return false;
	
	// We parse a regular statement, i.e. a statement that has a variable, an operation
	// and a value in this order from left to right
	
	AKROSD variable;
	AKROSD operation = "";
	AKROSD value = "";
	AKROSD reduced_value = "";
	bool found_operation = false;
	
	statement = statement.ReplaceAll(" ", "");
	
	// We search through every character of the statement in order to separate out variable,
	// operation and value
	
	for(Ssiz_t position = 0; position <= statement.Length(); ++position){
	
		AKROSD delimiter = statement(position,1);
		
		if(delimiter == ">" || delimiter == "<" || delimiter == "!" || delimiter == "="){
			operation += delimiter;
			found_operation = true;
		}
		
		else if(!found_operation)
			variable += delimiter;
		
		else
			value += delimiter;
		
	}

	float fvalue = value.Atof();

	// if the variable is compared to the number of selected kinematic objects, we 
	// set the value to the number of the kinematic object in question
	reduced_value = value(1, value.Length() - 1);
	if(Tools::FindElementInMapByKey(cObjectSelectionDefinitions, reduced_value)){
		if(FindKinematicObjects(reduced_value)){
			CollectKinematicObjects(reduced_value, cObjectSelectionDefinitions[reduced_value]);
			CountKinematicObjects(reduced_value);
		}
		fvalue = (float) kNumberOfKinematicObjects[reduced_value];
	}
	

	// if the variable is compared to a defined variable, we take the first element
	// of the return vector of the defined variable as the value

	// HERE we have room for improvement: one could write a function to access specific
	// elements of the kDefinedVariables[value] vector, and also to allow interchanging
	// of the value and the variable
	if(Tools::FindElementInMapByKey(cDefinedVariableDefinitions, value)){ 
		if(RecreateDefinedVariable(value))
			kDefinedVariables[value] = ParseVariableDefinition(cDefinedVariableDefinitions[value]);
		fvalue = kDefinedVariables[value][0];
	}


	// parse the statement

	bool return_value = ParseAKROSDOperation(variable, operation, fvalue);


	// filling event and object counts

	if(return_value && label != "") {
		if(label == "event") kEventCountCache[kSampleIterator][kSelectionIterator][statement] += 1;
		else                 kObjectCountCache[kSampleIterator][label][statement] += 1;
	}

	return return_value;
	
}


//____________________________________________________________________________
bool Dileptons::ParseAKROSDString(AKROSD string, Label label){
	/*
  	parses a full AKROSD string either for event selection, object selection
  	or variable definitions
  	parameters: string (the string to be parsed), label (the tag "event" if we
  	            do event selection, or the object name if we do object selection,
  	            default is nothing ""; important for event and object counts)
  	return: true (if event object was found to pass the selection), false (else)
  	*/

	// increase all events counter, necessary to compare event counts to
	if(label == "event")
		kEventCountCache[kSampleIterator][kSelectionIterator]["all"] += 1;

	// string is empty => return true
	if(string.Length() == 0) {
		if(label == "event") kEventCountCache[kSampleIterator][kSelectionIterator]["no selection"] += 1;
		else if(label != "") kObjectCountCache[kSampleIterator][label]["no selection"] += 1;
		return true;
	}

	// interpret irregular statements and brackets, maybe already parsing things
	// if so, the parsed statement(s) will be replaced by the string "true" or "false"
	// at the position where this/these statement(s) were before, hence, he statement
	// "true" or "false" is also a legitimate statement and can be parsed
	string = string.ReplaceAll(" ", "");
	string = InterpretAKROSDIfThElStatements(string, label);
	string = InterpretAKROSDRangeStatements(string, label);
	string = InterpretAKROSDBrackets(string, label);
	
	// at this level, we only have a combination of regular statements, i.e. only
	// regular statements separated by AND (,) or OR (|)
	bool return_value = ParseAKROSDCombinedRegularStatements(string, label);

	// increment event counter
	if(return_value && label == "event"){
		TString parenthesized_string = Tools::ConvertStdStringToTString("(" + Tools::ConvertTStringToStdString(string) + ")");
		kEventCountCache[kSampleIterator][kSelectionIterator][parenthesized_string] += 1;
	}

	return return_value;

}


//____________________________________________________________________________
float Dileptons::ParseAKROSDVariable(AKROSD variable_name, int object_index, int look_for_way, float look_for_value){
	/*
	replaces the variable name by the value in the string
	parameters: variable_name
	return: value of the tree variable 
	*/

	variable_name.Strip(TString::kBoth, ' ');

	if(variable_name.Index("*") > -1) variable_name.ReplaceAll("*", "");

	Ssiz_t dot_position = variable_name.First('.');
	AKROSD object   = variable_name(0, dot_position);
	AKROSD variable = variable_name(dot_position + 1, variable_name.Length() - dot_position - 1); 

	object  .Strip(TString::kBoth, ' ');
	variable.Strip(TString::kBoth, ' ');


	// object variables
	if(dot_position > -1){

		if(FindKinematicObjects(object) == -1){	
			CollectKinematicObjects(object, cObjectSelectionDefinitions[object]);
			CountKinematicObjects(object);
		}
	
		Label object_type = GetKinematicObjectTypeByLabel(object);

		if(object_type.Index("electron") > -1){
			if(object_index == -1) object_index = kElectronIterator;
			if     (variable == "CH"   ) return (float) ElCharge -> at(kKinematicObjects[object][object_index]);
			else if(variable == "CHISO") return (float) ElPFIso  -> at(kKinematicObjects[object][object_index]);
			else if(variable == "D0"   ) return (float) ElD0     -> at(kKinematicObjects[object][object_index]);
			else if(variable == "ETA"  ) return (float) ElEta    -> at(kKinematicObjects[object][object_index]);
			else if(variable == "GMID" ) return (float) ElGMID   -> at(kKinematicObjects[object][object_index]);
			else if(variable == "ID"   ) return (float) ElID     -> at(kKinematicObjects[object][object_index]);
			else if(variable == "ISL"  ) return Tools::ConvertBoolToFloatAlternatively(ElIsLoose -> at(kKinematicObjects[object][object_index])); 
			else if(variable == "IST"  ) return Tools::ConvertBoolToFloatAlternatively(ElIsTight -> at(kKinematicObjects[object][object_index]));
			else if(variable == "ISV"  ) return Tools::ConvertBoolToFloatAlternatively(ElIsVeto  -> at(kKinematicObjects[object][object_index]));
			else if(variable == "MID"  ) return (float) ElMID    -> at(kKinematicObjects[object][object_index]);
			else if(variable == "NEISO") return (float) ElPFIso  -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PFISO") return (float) ElPFIso  -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PHI"  ) return (float) ElPhi    -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PHISO") return (float) ElPFIso  -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PT"   ) return (float) ElPt     -> at(kKinematicObjects[object][object_index]);
		}
		
		else if(object_type.Index("jet") > -1){
			if(object_index == -1) object_index = kJetIterator;
			if     (variable == "BSTAR") return (float) JetBetaStar   -> at(kKinematicObjects[object][object_index]);
			else if(variable == "BTAG" ) return (float) JetCSVBTag    -> at(kKinematicObjects[object][object_index]);
			else if(variable == "E"    ) return (float) JetEnergy     -> at(kKinematicObjects[object][object_index]);
			else if(variable == "ETA"  ) return (float) JetEta        -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PHI"  ) return (float) JetPhi        -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PFL"  ) return (float) JetPartonFlav -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PT"   ) return (float) (cJetEnergyCorrection == 1 ? JetPt -> at(kKinematicObjects[object][object_index]) : JetRawPt -> at(kKinematicObjects[object][object_index]));
		}
	
		else if(object_type.Index("muon") > -1){
			if(object_index == -1) object_index = kMuonIterator;
			if     (variable == "CH"   ) return (float) MuCharge -> at(kKinematicObjects[object][object_index]);
			else if(variable == "CHISO") return (float) MuPFIso  -> at(kKinematicObjects[object][object_index]);
			else if(variable == "D0"   ) return (float) MuD0     -> at(kKinematicObjects[object][object_index]);
			else if(variable == "ETA"  ) return (float) MuEta    -> at(kKinematicObjects[object][object_index]);
			else if(variable == "GMID" ) return (float) MuGMID   -> at(kKinematicObjects[object][object_index]);
			else if(variable == "ID"   ) return (float) MuID     -> at(kKinematicObjects[object][object_index]);
			else if(variable == "ISL"  ) return Tools::ConvertBoolToFloatAlternatively(MuIsLoose -> at(kKinematicObjects[object][object_index]));
			else if(variable == "IST"  ) return Tools::ConvertBoolToFloatAlternatively(MuIsTight -> at(kKinematicObjects[object][object_index]));
			else if(variable == "ISV"  ) return Tools::ConvertBoolToFloatAlternatively(MuIsVeto  -> at(kKinematicObjects[object][object_index]));
			else if(variable == "NEISO") return (float) MuPFIso  -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PFISO") return (float) MuPFIso  -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PHI"  ) return (float) MuPhi    -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PHISO") return (float) MuPFIso  -> at(kKinematicObjects[object][object_index]);
			else if(variable == "PT"   ) return (float) MuPt     -> at(kKinematicObjects[object][object_index]);
		}

	
	}

	// event variables, defined variables and other objects
	else{

	
		// defined event variables
		if(Tools::FindElementInMapByKey(cDefinedVariableDefinitions, variable_name)){

			// not parsed yet
			if(RecreateDefinedVariable(variable_name))
				kDefinedVariables[variable_name] = ParseVariableDefinition(cDefinedVariableDefinitions[variable_name], object_index);
		
			if     (look_for_way >=  1) return AnalysisTools::Maximum(kDefinedVariables[variable_name]);
			else if(look_for_way <= -1) return AnalysisTools::Minimum(kDefinedVariables[variable_name]);
			else{
				float return_value = AnalysisTools::Maximum(kDefinedVariables[variable_name]);
				for(int i = 0; i < kDefinedVariables[variable_name].size(); ++i)
					if(kDefinedVariables[variable_name][i] == look_for_value)
						return_value = look_for_value;
				return return_value;
			}	
		}


		// number of kinematic objects	
		if(variable_name(0, 1) == "#"){

			Label reduced_label = variable_name(1, variable_name.Length()-1);
	
			// object not parsed yet
			if(Tools::FindElementInMapByKey(cObjectSelectionDefinitions, reduced_label) && FindKinematicObjects(reduced_label) == -1){	
				CollectKinematicObjects(reduced_label, cObjectSelectionDefinitions[reduced_label]);
				CountKinematicObjects(reduced_label);
			}

			// number of kinematic objects
			if(FindKinematicObjects(reduced_label) > -1)
				return (float) kNumberOfKinematicObjects[reduced_label];

		}
	

		// selected kinematic objects
		if(Tools::FindElementInMapByKey(cObjectSelectionDefinitions, variable_name)){

			// it is important to put here an empty string and NOT the variable_name as label argument for
			// ParseObjectSelection cause otherwise the counters are all messed up, i.e. the number of
			// selected objects will be larger than the number of basic objects that actually could
			// be selected since the counters are filled not at ONE position but multiply - that ain't good!

			// we are looping over the vector elements in the tree, so there is no way
			// we could parse this object first, and then check if the tree entry is
			// part of that object; i mean, we could do it, but since we do not save
			// the tree index of the selected objects, we cannot do it here
			if(ParseObjectSelection(cObjectSelectionDefinitions[variable_name], "")) return 1.0;
			else return 0.0;
		}


		// event variables

		if     (variable == "MET"    ) return (float) (cJetEnergyCorrection == 1) ? pfMET1 : pfMET;
		else if(variable == "METPHI" ) return (float) (cJetEnergyCorrection == 1) ? pfMET1Phi : pfMETPhi;
		else if(variable == "MU17"   ) return (float) HLT_MU17;
		else if(variable == "MU24"   ) return (float) HLT_MU24;
		else if(variable == "MU40"   ) return (float) HLT_MU40;
		else if(variable == "NVTX"   ) return (float) NVrtx;

	}

	return 1.0;

}


//____________________________________________________________________________
AKROSD Dileptons::RemoveAKROSDStatements(AKROSD string, AKROSD needle){
	/*
	removes statements containing needle from a AKROSD string
	parameters: string (AKROSD string to be edited), needle (AKROSD substring to
	            identify statements that need to be removed)
	return: new_string (edited string)
	*/

	AKROSD new_string = "";
	AKROSD statement  = "";
	AKROSD delimiter  = "";
	bool do_not_append = false;

	for(Ssiz_t position = 0; position <= string.Length(); ++position){

		delimiter = string(position, 1);
		statement += delimiter;

		if(delimiter == "," || delimiter == "|" || position == string.Length()){
			if(!do_not_append) new_string += statement;
			statement = "";
			do_not_append = false;
		}
		
		if(statement(statement.Length() - needle.Length(), needle.Length()) == needle)
			do_not_append = true;

	}

	return new_string; 	
	
}


//____________________________________________________________________________
AKROSD Dileptons::SortAKROSDStatements(AKROSD string){
	/*
	sorts the statements of the AKROSD string alphabetically
	parameters: string (AKROSD string to be edited)
	return: new_string (edited string)
	*/


	
}





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR COLLECTING OBJECTS IN AN EVENT                         **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void Dileptons::CollectBasicKinematicObjects(){
	/*
  	collects all basic kinematic objects in the event and stores them into
  	the map kBasicKinematicObjects[]; it works in principle in the same way as
  	with selected kinematic objects, only that the selection for basic kinematic
  	objects is empty
  	parameters: none
  	return: none
  	*/

	for(int i = 0; i < kBasicKinematicObjects.size(); ++i)
		if(FindKinematicObjects(kBasicKinematicObjects[i].first) == -1)
			CollectKinematicObjects(kBasicKinematicObjects[i].first, "");

}


//____________________________________________________________________________
void Dileptons::CollectElectrons(Label object_name, AKROSD object_selection){
	/*
  	collect all electron-like kinematic objects in the event
  	parameters: object_name, object_selection
  	return: none
  	*/

	std::vector<int> vector;
	kKinematicObjects.insert(std::pair<Label, std::vector<int> >(object_name, vector));

	for(kElectronIterator = 0; kElectronIterator < ElPt -> size(); ++kElectronIterator)
		if(ParseObjectSelection(object_selection, object_name))
			kKinematicObjects[object_name].push_back(kElectronIterator);

}


//____________________________________________________________________________
void Dileptons::CollectJets(Label object_name, AKROSD object_selection){
	/*
  	collects all jet-like kinematic objects in the event
  	parameters: object_name, object_selection
  	return: none
  	*/
	
	std::vector<int> vector;
	kKinematicObjects.insert(std::pair<Label, std::vector<int> >(object_name, vector));

	for(kJetIterator = 0; kJetIterator < JetPt -> size(); ++kJetIterator)
		if(ParseObjectSelection(object_selection, object_name))
			kKinematicObjects[object_name].push_back(kJetIterator);

}


//____________________________________________________________________________
void Dileptons::CollectKinematicObjects(Label object_name, AKROSD object_selection){
	/*
  	collects all kinematic objects in the event
  	parameters: object_name, object_selection
  	return: none
  	*/

	TString object_type = GetKinematicObjectTypeByLabel(object_name);

	if     (object_type.Index("electron") > -1) CollectElectrons(object_name, object_selection);
	else if(object_type.Index("jet"     ) > -1) CollectJets     (object_name, object_selection);
	else if(object_type.Index("muon"    ) > -1) CollectMuons    (object_name, object_selection);
	else if(object_type.Index("photon"  ) > -1) CollectPhotons  (object_name, object_selection);
	else if(object_type.Index("tau"     ) > -1) CollectTaus     (object_name, object_selection);

}


//____________________________________________________________________________
void Dileptons::CollectSelectedKinematicObjects(){
	/*
  	collects all selected kinematic objects in the event according to the selection
  	as given in the configuration file
  	paramters: none
  	return: none
  	*/

	for(std::map<Label, AKROSD>::iterator i = cObjectSelectionDefinitions.begin(); i != cObjectSelectionDefinitions.end(); ++i)
		if(FindKinematicObjects(i -> first) == -1)
			CollectKinematicObjects(i -> first, i -> second);

}


//____________________________________________________________________________
void Dileptons::CollectMuons(Label object_name, AKROSD object_selection){
	/*
  	collects all muons-like kinematic objects in the event
  	paramters: object_name, object_selection
  	return: none
  	*/

	std::vector<int> vector;
	kKinematicObjects.insert(std::pair<Label, std::vector<int> >(object_name, vector));

	for(kMuonIterator = 0; kMuonIterator < MuPt -> size(); ++kMuonIterator)
		if(ParseObjectSelection(object_selection, object_name))
			kKinematicObjects[object_name].push_back(kMuonIterator);

}


//____________________________________________________________________________
void Dileptons::CollectPhotons(Label object_name, AKROSD object_selection){
	/*
  	collects all photon-like kinematic objects in the event
  	parameters: object_name, object_selection
  	return: none
  	*/
	
//	std::vector<int> vector;
//	kKinematicObjects.insert(std::pair<Label, std::vector<int> >(object_name, vector));
//
//	for(kPhotonIterator = 0; kPhotonIterator < PhPt -> size(); ++kPhotonIterator)
//		if(ParseObjectSelection(object_selection, object_name))
//			kKinematicObjects[object_name].push_back(kPhotonIterator);

}


//____________________________________________________________________________
void Dileptons::CollectTaus(Label object_name, AKROSD object_selection){
	/*
  	collects all tau-like kinematic objects in the event
  	parameters: object_name, object_selection
  	return: none
  	*/
	
//	std::vector<int> vector;
//	kKinematicObjects.insert(std::pair<Label, std::vector<int> >(object_name, vector));
//
//	for(kTauIterator = 0; kTauIterator < TauPt -> size(); ++kTauIterator)
//		if(ParseObjectSelection(object_selection, object_name))
//			kKinematicObjects[object_name].push_back(kTauIterator);
	
}






/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR COUNTING OBJECTS IN AN EVENT                           **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void Dileptons::CountBasicKinematicObjects(){
	/*
  	counts the number of all basic kinematic objects found in the event
  	parameters: none
  	return: none
  	*/

	for(int i = 0; i < kBasicKinematicObjects.size(); ++i)
		CountKinematicObjects(kBasicKinematicObjects[i].first);

}


//____________________________________________________________________________
void Dileptons::CountKinematicObjects(Label object_name){
	/*
  	counts the number of a given kinematic object found in the event
  	parameters: object_name
  	return: none
  	*/

	kNumberOfKinematicObjects[object_name] = kKinematicObjects[object_name].size();

}


//____________________________________________________________________________
void Dileptons::CountSelectedKinematicObjects(){
	/*
  	counts the number of all selected kinematic objects found in the event
  	parameters: none
  	return: none
  	*/

	for(std::map<Label, AKROSD>::iterator i = cObjectSelectionDefinitions.begin(); i != cObjectSelectionDefinitions.end(); ++i)
		CountKinematicObjects(i -> first);

}





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR FEW MORE OBJECTS AND VARIABLES THINGS                  **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
int Dileptons::FindKinematicObjects(Label object_name){
	/*
  	looks if a given kinematic object already has been parsed, i.e. if the
  	key object_name exists in the map kKinematicObjects; if so, it returns
  	the number of this kinematic object found in the event; if not, it 
  	returns -1
  	parameters: object_name
  	return: kNumberOfKinematicObjects (if found), -1 (else)
  	*/

	if(!Tools::FindElementInMapByKey(kKinematicObjects, object_name)) return -1;

	return kNumberOfKinematicObjects[object_name];

}


//____________________________________________________________________________
bool Dileptons::RecreateDefinedVariable(Label label){
	/*
  	looks for a given defined event variable and tries to answer the question
  	if it has to be parsed again or not; we return true, if the defined variable
  	has not been parsed before, or if it has been parsed but contains the symbol "*";
  	then a specific object_index is fixed and the variable needs to be parsed anew
  	at every call
  	parameters: label
  	return: true (need to be parsed again), false (else)
  	*/

	if(!Tools::FindElementInMapByKey(cDefinedVariableDefinitions, label)) return false;
	if(!Tools::FindElementInMapByKey(kDefinedVariables, label)) return true;
	if(cDefinedVariableDefinitions[label].Index("*") > -1) return true;

	return false;

}


//____________________________________________________________________________
void Dileptons::ResetDefinedVariables(){
	/*
  	resets the maps and vectors of the defined event variables
  	parameters: none
 	return: none
 	*/

	kDefinedVariables.clear();

}


//____________________________________________________________________________
void Dileptons::ResetKinematicObjects(){
	/*
  	resets the maps and vectors of the kinematic objects
  	parameters: none
  	return: none
  	*/
	
	kKinematicObjects        .clear();
	kNumberOfKinematicObjects.clear();

}








/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR DOING PHYSICS                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
std::vector<float> Dileptons::ParseVariableDefinition(AKROSD variable_definition, int object_index){
	/*
	parses the definition of a defined event variable
	parameters: AKROSD string
	return: vector of values
	*/


	std::vector<float> results;
	AKROSD delimiter;


	// if the definition is empty, return empty vector

	if(variable_definition.Length() == 0) return results;


	// calling AnalysisTools

	if(variable_definition.Index("%AT:") > -1){

		Ssiz_t position = variable_definition.Index("%AT:");
		std::vector<AKROSD> components;
		std::vector<AKROSD> arguments;

		components = Tools::ExplodeTString(variable_definition(position + 4, variable_definition.Length() - position - 4), ":");
		AKROSD function = components[0];

		for(int i = 1; i < components.size(); ++i)
			arguments.push_back(components[i]);

		results = GetVectorOfParseResults(function, arguments, object_index);

	}


	// sum of things

	else if(variable_definition.First("+") > -1 || variable_definition.First("-") > -1){

		std::vector<AKROSD> observables = GetAKROSDStatements(variable_definition, "+", "-");

		if(variable_definition.First("+") != -1) delimiter = "+";
		else delimiter = "-";

		results = GetVectorOfParseResults(delimiter, observables, object_index);

	}

	return results;
}


//____________________________________________________________________________
void Dileptons::PrepareEventSelection(){
	/*
  	prepares all resources needed to perform the event selection, i.e. we parse,
  	collect and count all kinematic objects; defined variables are not parsed and
  	collected right away, but as we need them
  	parameters: none
  	return: none
  	*/


	// reset the maps of the kinematic objects and the defined event variables
	// which are still filled from the old event, i.e. we prepare for the new event
	ResetDefinedVariables();
	ResetKinematicObjects();


	// we collect and count all basic kinematic objects  
	CollectBasicKinematicObjects();
	CountBasicKinematicObjects();


	// we collect and count the selected kinematic objects
	CollectSelectedKinematicObjects();
	CountSelectedKinematicObjects();

}


//____________________________________________________________________________
bool Dileptons::ParseEventSelection(AKROSD event_selection){
	/*
	applies the selection of kinematic regions (events) by means of a given
	AKROSD string; this only works if one loops over the entries of the minitrees
	implementing the AKROSD selection for a given kinematic region
	parameters: event_selection (AKROSD string)
	return: true (if event is selected), false (else)
	*/ 

	return ParseAKROSDString(event_selection, "event");

}



//____________________________________________________________________________
bool Dileptons::ParseObjectSelection(AKROSD object_selection, Label object_name){
	/*
	applies the selection of kinematic objects by means of a given AKROSD string;
	this only works if one loops over the entries of the minitrees
	parameters: object_selection (AKROSD string)
	return: true (if object is selected), false (else)
	*/

	
	return ParseAKROSDString(object_selection, object_name);

}

















