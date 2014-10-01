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


#include <TROOT.h>
#include <TString.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

//#include "src/head/AnalysisModules.hh"
#include "src/head/Sketches.hh"



//_____________________________________________________________________________________
void PrintUsage(){


	std::cout << "printing usage" << std::endl;

}


//_____________________________________________________________________________________
TString GetRunOnFromConfigurationFile(TString configuration_file, bool tried_it = false){
	/*
	opens and reads the configuration file, analyzes the file content for the variable
	runon and returns its value
	parameters: configuration_file (the file path of the config file)
	return: RunOn
	*/

	char buffer[1000];
	char symbol_char[2], type_char[20], name_char[100], value_char[500], comment_char[300];
	
	ifstream IN(configuration_file);
	if(!IN.is_open()) {
		if(tried_it) return "modules";
		else         return GetRunOnFromConfigurationFile("current.cfg", true);
	}
	
	while(IN.getline(buffer, 1000, '\n')){
	
		if(strlen(buffer) == 0) continue;
		if(buffer[0] == '#') continue;	
		if(sscanf(buffer, "%s\t%s\t\t%s\t\t%s\t\t%s", symbol_char, type_char, name_char, value_char, comment_char) < 4) continue;

		TString symbol = symbol_char;
		TString type   = type_char;
		TString name   = name_char;
		TString value  = value_char;
				
		if(symbol == "n" && type == "TString" && name == "RunOn") 
			return value;

	}
}


//_____________________________________________________________________________________
int main(int argc, char* argv[]) {
	/*
	main function, does the whole job
	parameters:
	return: none
	*/



	// Starting Dileptons

	std::cout << ">> STARTING DILEPTONS" << std::endl;


	// Getting Configuration File Path

	TString configuration_file = "";
	char ch;

	while ((ch = getopt(argc, argv, "c:h:?")) != -1 ) {
		switch (ch) {
			case 'c': configuration_file = TString(optarg); break;
			case '?':
			case 'h': PrintUsage(); ; break;
			default : PrintUsage();
		}
	}

	// Checking Arguments

	if(argc < 2) configuration_file = "current.cfg";



	// Reading the Mode to Run on

	TString run_on = GetRunOnFromConfigurationFile(configuration_file);



	// Running on Analysis or Modules

	if(run_on == "analysis" || run_on == "modules") {

		AnalysisModules *AM = new AnalysisModules(configuration_file);
		AM->RunModules();
		AM->EndDileptons();

	}



	// Running on Sketches

	else {
		
		Sketches *SK = new Sketches(configuration_file);
		SK->RunSketches();
		SK->EndDileptons();

	}



	// Closing Dileptons

	std::cout << ">> CLOSING DILEPTONS" << std::endl;



	// Return

	return 0;
}

